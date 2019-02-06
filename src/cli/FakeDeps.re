open Types;
open WidgetTypes;
open Infix;

type privilegedRequest_t('payload) =
  ProcessTypes.privilegedRequest_t('payload);

type workerCtx_t('d) = TransactionFsm.workerCtx_t('d);

let makeWorkerCtx = (data: 'd): workerCtx_t('d) => {
  dbconn: "foo",
  transactionId: "2",
  data,
};

let runFsm = FakeFsm.FakeTransactionFsm.run;
let updateWorkerData = TransactionFsm.updateWorkerData;

module FindWidgetDeps = {
  type inRequest_t = getWidgetRequest_t;
  type processData_t = getWidgetData_t;
  type dbResponse_t = DbTypes.widgetRecord_t;
  type workerCtx_t2 = workerCtx_t(processData_t);

  /* Convert DB record to response object with results */
  let dbResp2WorkerCtx = (ctx: workerCtx_t2, widget: dbResponse_t) =>
    updateWorkerData(ctx, Result(widget));

  let worker = (ctx: workerCtx_t2) =>
    switch (ctx.data) {
    | Request(req) => req.id |> Db.FakeDb.findWidget <$> dbResp2WorkerCtx(ctx)

    /* Should never happen! */
    | _ => freject("invalid input to login worker")
    };

  let buildReq = (req: inRequest_t) => makeWorkerCtx(Request(req));

  let buildResponse = (resp: processData_t) => {
    switch (resp) {
    | Result(data) => fresolve(data)

    /* Should never happen! */
    | _ => freject("Invalid output from login Auth process")
    };
  };

  let deps: findWidget_deps_t = {buildReq, worker, buildResponse, runFsm};

  let get = () => deps;
};

module LoginDeps = {
  type inRequest_t = AuthTypes.authRequest_t;
  type processData_t = AuthTypes.authData_t;
  type dbResponse_t = DbTypes.userRecord_t;
  type workerCtx_t2 = workerCtx_t(processData_t);

  let buildResponse = (resp: processData_t) => {
    switch (resp) {
    | LoginSession(session) => fresolve(session)

    /* Should never happen! */
    | _ => freject("Invalid output from login Auth process")
    };
  };

  let buildReq = req => makeWorkerCtx(AuthTypes.Request(req));

  /* Convert DB record to response object with results */
  let dbResp2WorkerCtx = (ctx: workerCtx_t2, user: dbResponse_t) =>
    updateWorkerData(
      ctx,
      LoginSession({
        email: user.email,
        username: user.username,
        accessToken: user.accessToken,
      }),
    );

  let worker = (ctx: workerCtx_t2) =>
    switch (ctx.data) {
    | Request(req) =>
      Db.FakeDb.login(req.username, req.password) <$> dbResp2WorkerCtx(ctx)

    /* Should never happen! */
    | _ => freject("invalid input to login worker")
    };

  let deps: AuthTypes.loginDeps_t = {buildReq, worker, buildResponse, runFsm};
  let get = () => deps;
};