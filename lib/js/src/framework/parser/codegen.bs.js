// Generated by BUCKLESCRIPT VERSION 4.0.14, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Printf = require("bs-platform/lib/js/printf.js");

function mapper(stepName) {
  return "    ->Future.flatMap(" + (stepName + ".run)");
}

function map(steps) {
  return List.map(mapper, steps);
}

function cat(param) {
  return List.fold_left((function (acc, s) {
                return acc + (s + "\n");
              }), "", param);
}

function genSeries(name, steps) {
  return Curry._3(Printf.sprintf(/* Format */[
                  /* String_literal */Block.__(11, [
                      "\nopen ",
                      /* String */Block.__(2, [
                          /* No_padding */0,
                          /* String_literal */Block.__(11, [
                              "Types;\nlet run = (input: ",
                              /* String */Block.__(2, [
                                  /* No_padding */0,
                                  /* String_literal */Block.__(11, [
                                      "FloData) =>\n    Future.value(input)\n",
                                      /* String */Block.__(2, [
                                          /* No_padding */0,
                                          /* String_literal */Block.__(11, [
                                              ";\n    ",
                                              /* End_of_format */0
                                            ])
                                        ])
                                    ])
                                ])
                            ])
                        ])
                    ]),
                  "\nopen %sTypes;\nlet run = (input: %sFloData) =>\n    Future.value(input)\n%s;\n    "
                ]), name, name, cat(List.map(mapper, steps)));
}

var xxxFlowTemplate = "\n\nopen xxxTypes;\nlet run = (input: xxxFloData) =>\nFuture.value(input)\n->Future.flatMap(Step1.run)\n->Future.flatMap(Step2.run)\n->Future.flatMap(Step3.run)\n->Future.flatMap(Step4.run)\n->Future.flatMap(Step6.run);\n\n";

exports.xxxFlowTemplate = xxxFlowTemplate;
exports.mapper = mapper;
exports.map = map;
exports.cat = cat;
exports.genSeries = genSeries;
/* No side effect */
