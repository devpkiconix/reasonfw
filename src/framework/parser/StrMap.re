open Types;
type t = {token: int};
module Str2FuncMap = Belt.Map.String;

let funcs = [
  ("incr", ({token}) => fresolve({token: token + 1})),
  ("mult10", ({token}) => fresolve({token: token * 10})),
  ("double", ({token}) => fresolve({token: token + token})),
];

let mapper = k => List.assoc(k, funcs);