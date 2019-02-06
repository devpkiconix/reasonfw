open Types;
let mapMaybe = (f: 'a => 'b, maybe: option('a)) =>
  Belt.Option.map(maybe, f);

module FlowParser = {
  let wsRe = [%bs.re "/[\\n\\t ]+/gm"];
  let commentRe = [%bs.re "/#.*$/gm"];
  let stripComments = Js_string.replaceByRe(commentRe, "");

  let seqRe = [%bs.re "/->/g"];
  let parRe = [%bs.re "/\\|\\|/g"];
  let ternaryRe = [%bs.re "/[\\?\\:]/"];

  /* remove comments and get rid of newlines, extra whitespace etc. */
  let cleanup = (code: string) =>
    code
    |> stripComments
    |> Js_string.replaceByRe(wsRe, " ")
    |> Js_string.trim;

  /* Break into parallel flows (parallel bars) */
  let parTokenize = (code: string) =>
    code |> Js_string.splitByRe(parRe) |> Array.to_list;

  /* Break into sequences (split by arrows) */
  let seqTokenize = (code: string) =>
    code |> Js_string.trim |> Js_string.splitByRe(seqRe) |> Array.to_list;

  /* convert string to step object */
  let rec makeStep = s => {
    let parts = s |> Js_string.splitByRe(ternaryRe) |> Array.to_list;
    switch (parts) {
    | [s] => Step(Js_string.trim(s), Js_string.trim(s))
    | [c, l, r] => CondStep(Js_string.trim(c), makeStep(l), makeStep(r))
    | _ => Step(Js_string.trim(s), Js_string.trim(s))
    };
  };

  /* convert string to parllels connected by arrows */
  let rec par2flow = (par: list(string)): flow(string) =>
    switch (par) {
    | [] => Noop
    | [x] => makeStep(x)
    | _ => Parallel(par |> List.map(s => s |> seqTokenize |> seq2flow))
    }

  /* convert string to a set of parallels separated by parallel bars */
  and seq2flow = (seq: list(string)): flow(string) =>
    switch (seq) {
    | [] => Noop
    | [s] => makeStep(s)
    | [s, ...acc] => Sequence(s |> parTokenize |> par2flow, seq2flow(acc))
    };

  /* RHS of a process definition */
  let parseFlow = (input: string) =>
    input |> cleanup |> seqTokenize |> seq2flow;

  /* a definition is like an equation - name on the left &
   * spec on the right separated by an equal sign */
  let parseDefinition = (input: string) => {
    let parts = input |> cleanup |> Js_string.split("=") |> Array.to_list;
    switch (parts) {
    | [] => None
    | [left, right] => Some(Definition(left, parseFlow(right)))
    | _ => None
    };
  };

  /* A para is a set of process definitions, separated by semicolons */
  let parsePara = (input: string) =>
    input
    |> cleanup
    |> Js_string.split(";")
    |> Array.to_list
    |> List.map(parseDefinition)
    |> List.fold_left(
         (acc, optdef) =>
           switch (optdef) {
           | None => acc
           | Some(def) => List.append(acc, [def])
           },
         [],
       );

  /**
   * Parse process definitions from string and put them into
   * registry. Registry allows linking processes when used with
   * the Process engine.
   * Returns a modified registry.
   */;
  /* let registerDefs = (input: string, registry) => {
       let defs = parsePara(input);
       DefRegistry.register(registry, defs);
     }; */
};