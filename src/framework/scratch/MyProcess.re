open Types;
open Infix;

let createProcess = (input: Steps.floData) =>
  input
  |> fresolve
  >>= Steps.asyncIncr
  >>= Steps.syncTriple
  >>= Steps.asyncDouble;

/* returns cancel function */
let run = (input, rej, resolve) =>
  input |> createProcess |> ffork(rej, resolve);