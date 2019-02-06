
let resolve = (data: Steps.floData) => Js.log(data.token);
Js.log("We are expecting output of 186. Actual result:");
MyProcess.run({token: 30}, Js.log, resolve)
