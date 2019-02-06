open Types;
open FsmGeneric.Fsm;
open Infix;
open TransactionFsm;
module FakeDb = {
  type t =
    | Fake;
  type task_t2('d) = task_t(state_t, event_t, workerCtx_t('d));

  let withLogging =
      (pre, post, task: task_t2('d), data: fsmContext_t('d)): ft('d) => {
    data |> taplog(pre) |> task <$> taplog(post);
  };
  /* Implementations of core functions of this module */
  let connect_ = doNothing;

  let beginTransaction_ = doNothing;
  let commit_ = doNothing;
  let rollback_ = doNothing;
  let commitDone_ = doNothing;
  let rollbackDone_ = doNothing;
  let transactionDone_ = doNothing;
  /* Wrappers with logging */

  let connect = (data: fsmContext_t('d)): ft('d) =>
    data
    |> taplog("(Fake) connecting..")
    |> taskRunAndInject(connect_, Connected)
    <$> taplog("(Fake) connected");

  let beginTransaction = (data: fsmContext_t('d)): ft('d) =>
    data
    |> taplog("(Fake) beginTransaction_ing..")
    |> taskRunAndInject(beginTransaction_, Nothing)
    <$> taplog("(Fake) beginTransaction_ed");

  let commit = (data: fsmContext_t('d)): ft('d) =>
    data
    |> taplog("(Fake) commit_ing..")
    |> taskRunAndInject(commit_, CommitDone)
    <$> taplog("(Fake) commit_ed");

  let rollback = (data: fsmContext_t('d)): ft('d) =>
    data
    |> taplog("(Fake) rollback_ing..")
    |> taskRunAndInject(rollback_, RollbackDone)
    <$> taplog("(Fake) rollback_ed");

  let commitDone = (data: fsmContext_t('d)): ft('d) =>
    data
    |> taplog("(Fake) post commit..")
    |> taskRunAndInject(commitDone_, Nothing)
    <$> taplog("(Fake) post commit done");

  let rollbackDone = (data: fsmContext_t('d)): ft('d) =>
    data
    |> taplog("(Fake) post rollback..")
    |> taskRunAndInject(rollbackDone_, Nothing)
    <$> taplog("(Fake) post rollback done");

  let transactionDone = (data: fsmContext_t('d)): ft('d) =>
    data
    |> taplog("(Fake) transaction post cleanup..")
    |> transactionDone_
    <$> taplog("(Fake) transaction post cleanup done");
};

/* Usage:  FakeTransactionFsm.run(worker, data); */
module FakeTransactionFsm = MakeTransaction(FakeDb);