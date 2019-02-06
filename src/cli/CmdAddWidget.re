open Types;
type privilegedRequest_t('payload) =
  ProcessTypes.privilegedRequest_t('payload);

let run = (request: privilegedRequest_t((id_t, apiKey_t, widgetType_t))) => {
  WidgetSvc.addWidget(request)
  |> ffold(CliUtil.extractErr, CliUtil.extractResult);
};