// Generated by BUCKLESCRIPT VERSION 4.0.14, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");

function dump(fl) {
  if (typeof fl === "number") {
    return "noop";
  } else {
    switch (fl.tag | 0) {
      case 0 : 
          return "step(" + (fl[0] + ")");
      case 1 : 
          return "cond(" + (fl[0] + ("?" + (dump(fl[1]) + (":" + (dump(fl[2]) + ")")))));
      case 2 : 
          return "seq(" + (dump(fl[0]) + ("," + (dump(fl[1]) + ")")));
      case 3 : 
          return "par(" + (List.fold_left((function (acc, s) {
                          return acc + (", " + s);
                        }), "", List.map(dump, fl[0])) + ")");
      
    }
  }
}

function dumpFlow(def) {
  return def[0] + (" = " + dump(def[1]));
}

exports.dump = dump;
exports.dumpFlow = dumpFlow;
/* No side effect */
