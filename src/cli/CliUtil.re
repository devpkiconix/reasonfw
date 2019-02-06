open Types;
let extractErr = err =>
  switch (err) {
  | Error(x) => x
  | _ => "Unknown Error"
  };

let extractResult = res =>
  switch (Js.Json.stringifyAny(res)) {
  | Some(json) => json
  | _ => "Invalid output, can't convert to JSON"
  };