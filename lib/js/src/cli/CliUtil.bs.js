// Generated by BUCKLESCRIPT VERSION 4.0.14, PLEASE EDIT WITH CARE
'use strict';


function extractErr(err) {
  if (typeof err === "number" || err.tag) {
    return "Unknown Error";
  } else {
    return err[0];
  }
}

function extractResult(res) {
  var match = JSON.stringify(res);
  if (match !== undefined) {
    return match;
  } else {
    return "Invalid output, can't convert to JSON";
  }
}

exports.extractErr = extractErr;
exports.extractResult = extractResult;
/* No side effect */
