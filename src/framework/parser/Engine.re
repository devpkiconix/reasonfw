open Types;
open Infix;

let mapMaybe = (f: 'a => 'b, maybe: option('a)) =>
  Belt.Option.map(maybe, f);
let logPre = (name, x) => Js.log(("[" ++ name ++ " input]", x));
let logPost = (name, x) => Js.log(("[" ++ name ++ " output]", x));

module Make = (Dom: Domain.Domain_t) => {
  /* aliases */
  type stepFunctionType = Dom.t => Dom.ft;
  type stepConditionFunc = Dom.t => bool;
  type instType = Types.definition(stepFunctionType);
  type flowType = Types.flow(stepFunctionType);

  /* Maps parsed data structure from strings to functions,
   * using passed-in mapper function */
  let defmapper = DefMapper.mapDefinition(Dom.mapper);
  /**
   * Parse process def string and return process definition,
   * ready to execute with data
   */
  /* instantiate :: string => option(instType) */
  let instantiate = (def: string) =>
    def |> Parser.FlowParser.parseDefinition |> mapMaybe(defmapper);

  let tap = (f, x) => {
    f(x);
    x;
  };

  let ftap = (f, futval) => futval <$> tap(f);
  let beforeHook = name => tap(Dom.tapStepBefore(name));
  let afterHook = name => ftap(Dom.tapStepAfter(name));

  /* Execute a single step */
  /* execStep ::  string => step =>  Dom.t => Dom.ft */
  let execStep = (name, stepFunc, data) =>
    data |> beforeHook(name) |> stepFunc |> afterHook(name);

  /* execFlow ::  flowType => (Dom.t => Dom.ft) */
  let rec execFlow = (flow: flowType) =>
    switch (flow) {
    | Step(name, s) => execStep(name, s)
    | CondStep(cond, left, right) => execCondStep(cond, left, right)
    | Sequence(left, right) => execSeq(left, right)
    | Parallel(flows) => execPar(flows)
    | Noop => fresolve
    }
  /* execCondStep ::  string => flow => flow =>  Dom.t => Dom.ft */
  and execCondStep = (cond, left, right, data) => {
    let fl = Dom.evalPredicate(cond, data) ? left : right;
    data |> execFlow(fl);
  }
  /* execSeq :: flow => flow =>  Dom.t => Dom.ft */
  and execSeq = (left, right, data) =>
    execFlow(left, data) >>= execFlow(right)
  /* execPar ::  list(flow) =>  Dom.t => Dom.ft */
  and execPar = (flows, data) => data |> execFlowList(flows) |> Dom.fold
  /* execFlowList ::  (list(flowType), Dom.t) => list(Dom.ft) */
  and execFlowList = (flowList: list(flowType), data: Dom.t) =>
    flowList |> List.map(execFlow(_, data));

  /* exec :: instType => Dom.t => list(Dom.ft) */
  let exec = (instance, data) => {
    switch (instance) {
    | Types.Definition(_, flow) => data |> execFlow(flow)
    };
  };

  /* runner :: string -> (Dom.t -> option(list(Dom.ft)))*/
  let runnerGet = (def: string) => def |> instantiate |> mapMaybe(exec);

  /* run :: string -> Dom.t -> option(Dom.ft)*/
  let run = (def: string, data: Dom.t) =>
    def
    |> runnerGet
    |> mapMaybe(runFunc => runFunc(data))
    |> (
      x => {
        switch (x) {
        | None => freject("Unknown error")
        | Some(y) => y
        };
      }
    );
};

/*
 * This functor basically creates a link function that
 * links two domains.
 */
module MakeLink = (Domain1: Domain.Domain_t, Domain2: Domain.Domain_t) => {
  /* Domain 1 & 2 - process domains */
  module First = Make(Domain1);
  module Second = Make(Domain2);

  /* spec 1 & 2: Process specs */
  /* The link function takes as input data of type Domain1.t and
   * returns data of type Domain2.ft (future type)
   */
  let link =
      (spec1: string, spec2: string, domMapper: Domain1.t => Domain2.t, data) =>
    data
    |> First.run(spec1)  /* run first process */
    <$> domMapper  /* Map output to the input of the second process */
    >>= Second.run(spec2); /* and run the second process */
};