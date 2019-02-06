open Infix;
open Types;
open WidgetTypes;

/* Switch between mock and real here */

let buildResponse = (resp: getWidgetData_t) => {
  switch (resp) {
  | Result(data) => fresolve(data)

  /* Should never happen! */
  | _ => freject("Invalid output from login Auth process")
  };
};

let getWidget =
    (deps: WidgetTypes.findWidget_deps_t, req: WidgetTypes.getWidgetRequest_t) => {
  req |> deps.buildReq |> deps.runFsm(deps.worker) >>= deps.buildResponse;
};