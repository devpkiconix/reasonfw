module FakeTransactionFsm: {
  let beginWork:
    (TransactionFsm.worker_t('d), TransactionFsm.fsmContext_t('d)) =>
    TransactionFsm.ft('d);
  let run:
    (TransactionFsm.worker_t('d), TransactionFsm.workerCtx_t('d)) =>
    FsmGeneric.Fsm.future('d);
};