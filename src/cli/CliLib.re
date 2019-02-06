open Types;

type privilegedRequest_t('payload) =
  ProcessTypes.privilegedRequest_t('payload);

/* TODO - replace upon login */
/* WARNING: File global variable */
let accessToken = ref("token1");
/* Wrap request in authorizable request */
let wrapAuth = (payload: 'p): privilegedRequest_t('p) => {
  accessToken: accessToken^,
  payload,
};

/* placeholder for now */
type privilege_t =
  | ConfigAdmin
  | UserAdmin
  | WidgetAdmin;

/* User commands */
type command =
  | NoCommand
  | Show(id_t)
  | Login(username_t, password_t)
  | Add(id_t, apiKey_t, widgetType_t) /* From factory */
  /* User-related */
  | CreateUser
  | RemoveUser
  | AddPrivilege(privilege_t) /* Change this string to a variant type */
  | RevokePrivilege(privilege_t)
  /* API keys*/
  | NewApiKey(api_entity_t)
  | RemoveApiKey(api_entity_t)
  /* Queue related */
  | QListPending
  | UnknownCommand;

let getCmd = cmd => {
  switch (cmd) {
  | [""] => NoCommand
  | ["login", userName, password] => Login(userName, password)
  | ["show", id] => Show(id)
  | ["add", id, apiKey, widgetType] => Add(id, apiKey, widgetType)
  | _ => UnknownCommand
  };
};
let execUnknown = () => futureString("Unknown Command");
let execAdd = (id, apiKey, widgetType) =>
  futureString("execAdd(" ++ id ++ "," ++ apiKey ++ "," ++ widgetType ++ ")");

let execCmd =
  fun
  | NoCommand => futureString("")
  | Login(username, pass) => CmdLogin.run(username, pass)
  | Show(id) => CmdShow.run(wrapAuth(id))
  | Add(id, apiKey, widgetType) => execAdd(id, apiKey, widgetType)

  | UnknownCommand => execUnknown();

let wsRe = [%bs.re "/[\\n\\t ]+/gm"];
let commentRe = [%bs.re "/#.*$/gm"];
let stripComments = Js_string.replaceByRe(commentRe, "");

let cleanup = (code: string) =>
  code |> stripComments |> Js_string.replaceByRe(wsRe, " ") |> Js_string.trim;

let parseCmd = cmd =>
  cmd
  |> cleanup
  |> Js_string.split(" ")
  |> Array.to_list
  |> List.map(Js_string.trim)
  |> getCmd;

let execLine = line => line |> parseCmd |> execCmd;

let processLine = line =>
  line |> execLine |> ffork(Js.log, result => Js.log(result));