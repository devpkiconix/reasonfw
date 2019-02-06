/*
 */
open Types;
open FsmGeneric.Fsm;
open Infix;

type state_t =
  | Start
  | Connecting
  | TBegin
  | TCommitting
  | TRollingBack
  | Disconnecting
  | Working
  | Done;

type event_t =
  | Connected
  | Disconnected
  | TSuccess
  | TFailure
  | CommitDone
  | RollbackDone
  | Nothing;

let taplog = FsmGeneric.taplog;

type workerCtx_t('d) = {
  dbconn: string, /* placeholder */
  transactionId: string, /* placeholder */
  data: 'd,
};
type fsm_t('d) = list(transition_t(state_t, event_t, workerCtx_t('d)));
type fsmContext_t('d) = context_t(state_t, event_t, workerCtx_t('d));

/* alias, basically a short-hand notation to a future context */
type ft('d) = future(fsmContext_t('d));
type worker_t('d) = workerCtx_t('d) => future(workerCtx_t('d));

let doNothing = (ctx: fsmContext_t('d)): ft('d) => fresolve(ctx);

let updateWorkerData = (ctx: workerCtx_t('d), data: 'd): workerCtx_t('d) => {
  {...ctx, data};
};

module type Db_t = {
  type t;
  let connect: fsmContext_t('d) => ft('d);
  let beginTransaction: task_t(state_t, event_t, workerCtx_t('d));
  let commit: task_t(state_t, event_t, workerCtx_t('d));
  let commitDone: task_t(state_t, event_t, workerCtx_t('d));
  let rollback: task_t(state_t, event_t, workerCtx_t('d));
  let rollbackDone: task_t(state_t, event_t, workerCtx_t('d));
  let transactionDone: task_t(state_t, event_t, workerCtx_t('d));
};

module MakeTransaction = (Db: Db_t) => {
  let beginWork = (worker: worker_t('d), data: fsmContext_t('d)): ft('d) => {
    let workerCtx: workerCtx_t('d) = data.data;
    worker(workerCtx)
    >>= (
      (resultWrkCtx: workerCtx_t('d)) =>
        fresolve({...data, data: resultWrkCtx})
    );
  };
  let run = (worker: worker_t('d), wctx: workerCtx_t('d)): future('d) => {
    let fsm: fsm_t('d) = [
      /* srcState, event, target,    task */
      (Start, Nothing, Connecting, Db.connect),
      (Connecting, Connected, TBegin, Db.beginTransaction),
      (TBegin, Nothing, Working, beginWork(worker)),
      (Working, TSuccess, TCommitting, Db.commit),
      (TCommitting, CommitDone, Done, Db.commitDone),
      (Working, TFailure, TRollingBack, Db.rollbackDone),
      (TRollingBack, RollbackDone, Done, Db.transactionDone),
    ];
    let context: fsmContext_t('d) = {fsm, state: Start, data: wctx};
    fsmExec(fsm, Start, [Nothing], context)
    >>= ((ctx: fsmContext_t('d)) => fresolve(ctx.data.data));
  };
};

/* TODO: Make Sql transaction FSM like the above */