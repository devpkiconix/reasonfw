let print = x => x->AstDump.dump->Js.log;

let test = () =>
  "myproc = a?al:ar -> b?bl:br || c ? cl : cr || c2 -> d?dl:dr"
  |> Parser.FlowParser.parseDefinition
  |> (
    maybed =>
      {
        switch (maybed) {
        | Some(def) => AstDump.dumpFlow(def)
        | _ => "Invalid process definition"
        };
      }
      |> Js.log
  );

test();

let dotest2 = () =>
  "
  # Comment
  p = a->b -> #comment
  c || pq -> zx; #comment
  q = abc -> def -> f21# comment"
  |> Parser.FlowParser.parsePara
  |> List.map(AstDump.dumpFlow)
  |> Js.log;

dotest2();