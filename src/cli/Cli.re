let options =
  Readline.interfaceOptions(
    ~input=[%raw "process.stdin"],
    ~output=[%raw "process.stdout"],
    (),
  );

let readline = Readline.createInterface(options);
let read = Readline.question(readline, "cli> ");

let rec cli = () => {
  read(line => {
    line |> CliLib.processLine |> ignore;
    cli();
  });
};

cli();
/* Readline.close(readline); */