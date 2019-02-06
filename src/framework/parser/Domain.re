open Types;
/* Map from domain a to domain b */
type procDefDomainMapper('a, 'b) = 'a => 'b;

module type Domain_t = {
  type t; /* data type exchanged between steps */
  type ft = future(t);

  /* Used for logging, authentication, user validation etc */
  let preHook: t => ft;

  /* Used for logging and debugging etc */
  let tapStepBefore: (string, t) => unit;
  let tapStepAfter: (string, t) => unit;

  /* Used for logging, packaging results  */
  let postHook: t => ft;

  let evalPredicate: (string, t) => bool;
  let mapper: procDefDomainMapper(string, t => future(t));
  let fold: list(ft) => ft;
};

/* module MyProcess = Engine.Make(domain); */