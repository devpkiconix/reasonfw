open Types;

/* Map a definition from one domain ('a) to another ('b)
 *
 * Type 'a almost always will be string. 'b will be functions in
 * execution context, string for debugging, codegen etc.
 */
let mapDefinition =
    (f: Domain.procDefDomainMapper('a, 'b), eq: definition('a))
    : definition('b) => {
  /**
   * Recursively map a flow definition from one domain (e.g. string)
   * to another.
   */
  let rec mapFlow = (p: flow('a)): flow('b) =>
    switch (p) {
    | Noop => Noop
    | Step(name, s) => Step(name, f(s))
    | CondStep(cond, left, right) =>
      CondStep(cond, mapFlow(left), mapFlow(right))

    | Parallel(flows) => Parallel(flows |> List.map(mapFlow))
    | Sequence(left, right) => Sequence(mapFlow(left), mapFlow(right))
    };
  switch (eq) {
  | Definition(name, flow) => Definition(name, mapFlow(flow))
  };
};