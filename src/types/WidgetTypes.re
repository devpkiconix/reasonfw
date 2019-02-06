open Types;

type userId_t = string;
type dbWidgetId_t = string;

type apikey_t = string;
type widgetType_t = string;
type mfr_t = string;
type macAddress_t = string;
type createWidgetDetails_t = {
  id: id_t,
  name: string,
};

type getWidgetRequest_t = {id: string};
type getWidgetResponse_t = DbTypes.widgetRecord_t;
type getWidgetData_t =
  | Request(getWidgetRequest_t)
  | Result(getWidgetResponse_t);
type findWidgetWorker_t = TransactionFsm.worker_t(getWidgetData_t);
type findWidget_deps_t = {
  buildReq: getWidgetRequest_t => TransactionFsm.workerCtx_t(getWidgetData_t),
  worker: findWidgetWorker_t,
  buildResponse: getWidgetData_t => future(getWidgetResponse_t),
  runFsm:
    (
      TransactionFsm.worker_t(getWidgetData_t),
      TransactionFsm.workerCtx_t(getWidgetData_t)
    ) =>
    future(getWidgetData_t),
};