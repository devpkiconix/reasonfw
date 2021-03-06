// Generated by BUCKLESCRIPT VERSION 4.0.14, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Types$Iconixfw = require("../types/Types.bs.js");
var CmdShow$Iconixfw = require("./CmdShow.bs.js");
var CmdLogin$Iconixfw = require("./CmdLogin.bs.js");
var Caml_builtin_exceptions = require("bs-platform/lib/js/caml_builtin_exceptions.js");

var accessToken = /* record */[/* contents */"token1"];

function execCmd(param) {
  if (typeof param === "number") {
    switch (param) {
      case 0 : 
          return Types$Iconixfw.futureString("");
      case 4 : 
          return Types$Iconixfw.futureString("Unknown Command");
      default:
        throw [
              Caml_builtin_exceptions.match_failure,
              /* tuple */[
                "CliLib.re",
                53,
                2
              ]
            ];
    }
  } else {
    switch (param.tag | 0) {
      case 0 : 
          return CmdShow$Iconixfw.run(/* record */[
                      /* accessToken */accessToken[0],
                      /* payload */param[0]
                    ]);
      case 1 : 
          return CmdLogin$Iconixfw.run(param[0], param[1]);
      case 2 : 
          var id = param[0];
          var apiKey = param[1];
          var widgetType = param[2];
          return Types$Iconixfw.futureString("execAdd(" + (id + ("," + (apiKey + ("," + (widgetType + ")"))))));
      default:
        throw [
              Caml_builtin_exceptions.match_failure,
              /* tuple */[
                "CliLib.re",
                53,
                2
              ]
            ];
    }
  }
}

var wsRe = (/[\n\t ]+/gm);

var commentRe = (/#.*$/gm);

function cleanup(code) {
  return code.replace(commentRe, "").replace(wsRe, " ").trim();
}

function parseCmd(cmd) {
  var cmd$1 = List.map((function (prim) {
          return prim.trim();
        }), $$Array.to_list(cleanup(cmd).split(" ")));
  if (cmd$1) {
    switch (cmd$1[0]) {
      case "" : 
          if (cmd$1[1]) {
            return /* UnknownCommand */4;
          } else {
            return /* NoCommand */0;
          }
      case "add" : 
          var match = cmd$1[1];
          if (match) {
            var match$1 = match[1];
            if (match$1) {
              var match$2 = match$1[1];
              if (match$2 && !match$2[1]) {
                return /* Add */Block.__(2, [
                          match[0],
                          match$1[0],
                          match$2[0]
                        ]);
              } else {
                return /* UnknownCommand */4;
              }
            } else {
              return /* UnknownCommand */4;
            }
          } else {
            return /* UnknownCommand */4;
          }
      case "login" : 
          var match$3 = cmd$1[1];
          if (match$3) {
            var match$4 = match$3[1];
            if (match$4 && !match$4[1]) {
              return /* Login */Block.__(1, [
                        match$3[0],
                        match$4[0]
                      ]);
            } else {
              return /* UnknownCommand */4;
            }
          } else {
            return /* UnknownCommand */4;
          }
      case "show" : 
          var match$5 = cmd$1[1];
          if (match$5 && !match$5[1]) {
            return /* Show */Block.__(0, [match$5[0]]);
          } else {
            return /* UnknownCommand */4;
          }
      default:
        return /* UnknownCommand */4;
    }
  } else {
    return /* UnknownCommand */4;
  }
}

function processLine(line) {
  return Types$Iconixfw.ffork((function (prim) {
                console.log(prim);
                return /* () */0;
              }), (function (result) {
                console.log(result);
                return /* () */0;
              }), execCmd(parseCmd(line)));
}

exports.processLine = processLine;
/* wsRe Not a pure module */
