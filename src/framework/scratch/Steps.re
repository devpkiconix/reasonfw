type floData = { token: int };

let cancelTimer = (timerId, ()) => Js.Global.clearTimeout(timerId);
let setTimeout = Js.Global.setTimeout;

let asyncIncr = (data: floData) =>
  BsFluture.make((_reject, resolve) => {
    let timeoutId = setTimeout(() => resolve({ token: data.token + 1}), 30);
    /* EITHER return a wrapped cancellation function ... */
    BsFluture.Cancel(cancelTimer(timeoutId));
    /* ... OR return NoCancel */
    /* BsFluture.NoCancel; */
  });

let asyncDouble = (data: floData) =>
  BsFluture.make((_reject, resolve) => {
    let timeoutId = setTimeout(() => resolve({token: data.token*2}), 300);
    /* EITHER return a wrapped cancellation function ... */
    BsFluture.Cancel(cancelTimer(timeoutId));
    /* ... OR return NoCancel */
    /* BsFluture.NoCancel; */
  });

let syncTriple = (data: floData) =>
  BsFluture.resolve({token: data.token*3})
