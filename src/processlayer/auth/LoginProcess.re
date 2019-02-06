open Infix;
open Types;

let login = (deps: AuthTypes.loginDeps_t, req: AuthTypes.authRequest_t) =>
  req |> deps.buildReq |> deps.runFsm(deps.worker) >>= deps.buildResponse;