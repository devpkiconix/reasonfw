open Types;

let rec dump = (fl: flow(string)) =>
  switch (fl) {
  | Noop => "noop"
  | Step(x, _) => "step(" ++ x ++ ")"
  | CondStep(c, l, r) =>
    "cond(" ++ c ++ "?" ++ dump(l) ++ ":" ++ dump(r) ++ ")"
  | Sequence(left, right) =>
    "seq(" ++ dump(left) ++ "," ++ dump(right) ++ ")"
  | Parallel(flowList) =>
    "par("
    ++ (
      flowList
      |> List.map(dump)
      |> List.fold_left((acc, s) => acc ++ ", " ++ s, "")
    )
    ++ ")"
  };

let dumpFlow = (def: Types.definition(string)) => {
  switch (def) {
  | Definition(lhs, rhs) => lhs ++ " = " ++ dump(rhs)
  };
};