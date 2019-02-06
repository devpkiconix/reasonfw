open Types;
type loginSession_t = {
  email: string,
  username: string,
  accessToken: string,
};
type authRequest_t = {
  username: string,
  password: string,
};
type authResponse_t = DbTypes.userRecord_t;
type authData_t =
  | Request(authRequest_t)
  | LoginSession(loginSession_t);

type login_worker_t = TransactionFsm.worker_t(authData_t);
type loginDeps_t = {
  buildReq: authRequest_t => TransactionFsm.workerCtx_t(authData_t),
  worker: login_worker_t,
  buildResponse: authData_t => future(loginSession_t),
  runFsm:
    (
      TransactionFsm.worker_t(authData_t),
      TransactionFsm.workerCtx_t(authData_t)
    ) =>
    future(authData_t),
};