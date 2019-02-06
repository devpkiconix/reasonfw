type phrase =
  | Step(string) /* just step */
  | Parallel(string, phrase) /* step || phrase */
  | Sequence(string, phrase); /* step -> phrase */
type equation =
  | Equation(string, phrase); /* name '=' phrase */

/* a */
let def1 = Equation("sampleProcess1", Step("a"));

/* a -> b */
let def2 = Equation("sampleProcess2", Sequence("a", Step("b")));

/* a -> b -> c */
let def3 =
  Equation("sampleProcess3", Sequence("a", Sequence("b", Step("c"))));

/* a -> b || c */
let def4 =
  Equation("sampleProcess4", Sequence("a", Parallel("b", Step("c"))));

/* a -> b || c || d -> e */
let def5 =
  Equation(
    "sampleProcess5",
    Sequence("a", Parallel("b", Parallel("c", Sequence("d", Step("e"))))),
  );

let rec dumpPhrase = (ph: phrase): string => {
  switch (ph) {
  | Step(step) => step
  | Parallel(step, (ph2: phrase)) => step ++ " || " ++ dumpPhrase(ph2)
  | Sequence(step, (ph2: phrase)) => step ++ " -> " ++ dumpPhrase(ph2)
  };
};

let dump = (eq: equation) => {
  switch (eq) {
  | Equation(name, ph) => name ++ " = " ++ dumpPhrase(ph)
  };
};

Js.log(dump(def1));
Js.log(dump(def2));
Js.log(dump(def3));
Js.log(dump(def4));
Js.log(dump(def5));