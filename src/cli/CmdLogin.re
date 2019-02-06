open Types;
let login = (username, pass) =>
  AuthSvc.login(FakeDeps.LoginDeps.get(), username, pass);

let run = (username, pass) =>
  login(username, pass) |> ffold(CliUtil.extractErr, CliUtil.extractResult);