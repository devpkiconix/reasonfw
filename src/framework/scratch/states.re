type cancelMsg = string;
type processId = string;
type userId = string;

let instantiate = () /*def: 'def*/ => 0;

module type Proc = {
  type def;
  type step;
  type result;
  type floData;
  type request;

  type processState =
    | Start(request)
    | Running(step, floData)
    | Completed(result)
    | Canceling
    | Canceled(cancelMsg);

  /* Process states */
  type processInfo = (processId, processState, userId);

  let createInstance: def => processInfo;
  let start: processInfo => processInfo;
  let resume: processInfo => processInfo;
};