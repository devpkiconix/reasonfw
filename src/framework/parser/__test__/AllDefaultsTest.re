open Types;
[@bs.deriving jsConverter]
type testdataType = {token: int};

let mapMaybe = (f: 'a => 'b, maybe: option('a)) =>
  Belt.Option.map(maybe, f);

/**
 * Everything in this process domain is defaulted,
 * including mapper. If you run this, you should see the steps being
 * executed, and data being simply forwarded from step to step.
 */
module Domain = {
  type t = testdataType;
  type ft = future(t);
  include DomainDefaults;
};

/* Process specification */
let spec = "x = incr -> foo->  junk ->
        mult100 -> double ->
        morejunk ->
        mult10 ->
        incr -> blah ->
        incr";

/* Instantiate process from process spec and domain */
module MyProcess = Engine.Make(Domain);

/* ..start.. */
let input = {token: 180};

input |> MyProcess.run(spec) |> ffork(Js.log, Js.log) |> ignore;