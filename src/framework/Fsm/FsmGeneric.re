open Infix;
open Types;
let enableLogging = false;

let taplog = (msg, x) => {
  if (enableLogging) {
    Js.log((msg, x));
  };
  x;
};

/* The FSM is a bunch of transitions, parametrized by: (a) state type
 * (b) event type and (c) a context type. For each transition entry a
 * task that returns a future context is also specified.
 */
module Fsm = {
  /* 's = state type, 'e = event type, 'd = data type */
  type future('d) = Types.future('d);

  /* mutually recursive types */
  type context_t('s, 'e, 'd) = {
    fsm: list(transition_t('s, 'e, 'd)),
    state: 's,
    data: 'd,
  }
  and task_t('s, 'e, 'd) =
    context_t('s, 'e, 'd) => future(context_t('s, 'e, 'd))
  /* Transition table entry is a tuple */
  and transition_t('s, 'e, 'd) = ('s, 'e, 's, task_t('s, 'e, 'd));

  /* future value of context */
  type ft('ctx) = future('ctx);
  /* executable task that returns a future context */

  /* noop */
  let doNothing = data => fresolve(data);
  /* reject invalid state transition */
  let reject = (msg, _data: 'ctx): ft('ctx) => freject(msg);

  type fsm_t('s, 'e, 'd) = list(transition_t('s, 'e, 'd));
  let changeState = (state, context) => {...context, state};
  /*
   * There are two main recursive functions, fsmExec and next.
   *
   * fsmExec takes the transition list, the current state and
   * a bunch of events. For each event:
   *   - find the relevant transition entry, matching on from state and the event
   *   - execute the task corresponding to the transition
   *   - transition to the next state, by calling the `next` function
   */
  let rec fsmExec = (fsm: fsm_t('s, 'e, 'd), state: 's, events: list('e)) => {
    switch (events) {
    | [] => doNothing
    | [first, ...rest] =>
      let transitionFinder = ((from, event, _, _)) =>
        from === state && event === first;
      switch (fsm |> List.find(transitionFinder)) {
      | (src, _evt, tgt, task) => next(task, src, tgt, rest, fsm)
      | exception Not_found => reject("Invalid input") /* not found */
      };
    };
  }
  and next = (task, _src, tgt, events, fsm, ctx) => {
    changeState(tgt, ctx) |> task >>= fsmExec(fsm, tgt, events);
  };
  let inject = (event, ctx) => {
    fsmExec(ctx.fsm, ctx.state, [event], ctx);
  };
  let taskRunAndInject = (task, event, ctx) => {
    ctx |> task <$> taplog("finished") >>= inject(event);
  };
};