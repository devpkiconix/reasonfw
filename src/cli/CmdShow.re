open Types;
open WidgetTypes;
open Infix;
open ProcessTypes;

let run = (req: privilegedRequest_t(id_t)) => {
  req
  |> WidgetSvc.showWidget(FakeDeps.FindWidgetDeps.get())
  |> ffold(CliUtil.extractErr, CliUtil.extractResult);
};