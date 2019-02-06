open Types;
open ProcessTypes;
open WidgetTypes;

let showWidget =
    (deps: findWidget_deps_t, request: privilegedRequest_t(id_t)) =>
  GetWidgetProcess.getWidget(deps, {id: request.payload});

let addWidget =
    (request: privilegedRequest_t((id_t, apiKey_t, widgetType_t))) => {
  let (id, _apiKey, _widgetType) = request.payload;
  fresolve(id);
};