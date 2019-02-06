let preHook = Types.fIdentity;
let tapStepBefore = Engine.logPre;
let tapStepAfter = Engine.logPost;
let postHook = Types.fIdentity;

let fold = List.hd;
let evalPredicate = (str, data) => {
  Js.log((str, data));
  true;
};
let mapper = k =>
  switch (k) {
  | _ => (
      x => {
        Js.log("No matching function, no-op: " ++ k);
        Types.fresolve(x);
      }
    )
  };