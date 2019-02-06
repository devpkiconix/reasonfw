open Types;

let makeStep = x => Step(x, x);
/* a */
let def1 = Definition("sampleProcess1", makeStep("a"));

/* a -> b */
let def2 =
  Definition("sampleProcess2", Sequence(makeStep("a"), makeStep("b")));

/* a -> b -> c */
let def3 =
  Definition(
    "sampleProcess3",
    Sequence(makeStep("a"), Sequence(makeStep("b"), makeStep("c"))),
  );

/* a -> b || c */
let def4 =
  Definition(
    "sampleProcess4",
    Sequence(makeStep("a"), Parallel([makeStep("b"), makeStep("c")])),
  );

/* a -> b || c || d -> e */
let def5 =
  Definition(
    "sampleProcess5",
    Sequence(
      makeStep("a"),
      Parallel([makeStep("b"), makeStep("c"), makeStep("d")]),
    ),
  );

/* a || b -> c || d -> e */
let def6 =
  Definition(
    "sampleProcess6",
    Sequence(
      Parallel([makeStep("a"), makeStep("b")]),
      Sequence(Parallel([makeStep("c"), makeStep("d")]), makeStep("e")),
    ),
  );