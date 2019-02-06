/* FIRST */

type error_t =
  | Error(string)
  | PermissionDenied
  | InvalidInput(string)
  | OtherError(string);

type cond_t = string;
/* flow is the right hand portion of a process definition */
type flow('a) =
  | Noop
  | Step(string, 'a)
  | CondStep(cond_t, flow('a), flow('a))
  | Sequence(flow('a), flow('a))
  | Parallel(list(flow('a)));

/* Single process definiiton, e.g. p = a->b->c||d */
type definition('a) =
  | Definition(
      string, /* name */
      flow('a),
    );

/* Multiple definitions */
type para('a) = list(definition('a));

/** Flow definition containing strings, i.e. each node in the definition tree is a string */
type stringflow = flow(string);
type stringDefinition = definition(string);

let identity = (name, x) => {
  Js.log("No matching function, no-op: " ++ name);
  BsFluture.resolve(x);
};

let fIdentity = BsFluture.resolve;
let alwaysTrue = _ => true;

let funcMapper = (funcs: list((string, 'a => BsFluture.t('e, 'a))), k) => {
  switch (List.find(i => i === k, funcs)) {
  | (_, item) => item
  | exception Not_found => (x => BsFluture.resolve(x))
  };
};

type future('d) = BsFluture.t(error_t, 'd);
let fresolve = (fvalue: 't): future('t) => BsFluture.resolve(fvalue);
let freject = (err: string) => BsFluture.reject(Error(err));
let ffork = (reject: error_t => unit, resolve: 'v => unit, f: future('v)) =>
  BsFluture.fork(reject, resolve, f);
let ffold = (reject: error_t => 'a, resolve: 'v => 'a, f: future('v)) =>
  BsFluture.fold(reject, resolve, f);
let futureString = (str): future(string) => BsFluture.resolve(str);

type id_t = string;
type apiKey_t = string;
type widgetType_t = string;
type otp_t = string;
type accessToken_t = string;

type creds_t = string;
type appName_t = string;
type timeframe_t = string; /* for now */
type api_entity_t = string;
type username_t = string;
type password_t = string;