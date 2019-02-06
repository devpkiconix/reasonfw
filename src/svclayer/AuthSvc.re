open Infix;
open Types;

let login = (deps: AuthTypes.loginDeps_t, username: string, password: string) => {
  let req: AuthTypes.authRequest_t = {username, password};
  let extractResults = (resp: AuthTypes.authData_t) => {
    switch (resp) {
    | AuthTypes.LoginSession(session) => fresolve(session)
    | _ => freject("Invalid output from login Auth process")
    };
  };
  LoginProcess.login(deps, req);
};