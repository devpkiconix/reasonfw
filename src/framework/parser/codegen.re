/**
 * Code generator notes
 *
 * Generated files: (all file names prefixed with the name of the process)
 */;

let xxxFlowTemplate = {|

open xxxTypes;
let run = (input: xxxFloData) =>
Future.value(input)
->Future.flatMap(Step1.run)
->Future.flatMap(Step2.run)
->Future.flatMap(Step3.run)
->Future.flatMap(Step4.run)
->Future.flatMap(Step6.run);

|};

let mapper = (stepName: string) =>
  "    ->Future.flatMap(" ++ stepName ++ ".run)";
let map = (steps: list(string)) => List.map(mapper, steps);
let cat = List.fold_left((acc, s) => acc ++ s ++ "\n", "");

let genSeries = (name: string, steps: list(string)) => {
  Printf.sprintf(
    {|
open %sTypes;
let run = (input: %sFloData) =>
    Future.value(input)
%s;
    |},
    name,
    name,
    cat(map(steps)),
  );
};

/* Js.log(genSeries("myflow", ["step1", "step2", "step3"])); */