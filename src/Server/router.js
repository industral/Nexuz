/**
 * Router class.
 * 
 * @author Alex Ivasyuv
 */
"use strict";

/**
 * Init routing.
 * 
 * @param response response object
 */
exports.init = function(response) {
  _response = response;

  response.end("Hello World\n");
}

/**
 * Act the route. Deside what to do, based on input url.
 * 
 * @param request request
 */
exports.act = function(request) {
  var act = request.url.slice(1);

  if (act) {
    acts[act](request);
  } else {
    throw new Error("Wrong action method");
  }
}

// --------------------------------------------------------------------
// Private methods
// --------------------------------------------------------------------

var acts = {
  auth: function(request) {

    // Get POST data
    var postData = "";
    request.addListener("data", function(chunk) {
      postData += chunk;
    });

    request.addListener("end", function() {
      console.log(require("querystring").parse(postData));
    });
    
//    db.sendRequest(function() {}, );

  }
};

// --------------------------------------------------------------------
// Private variables
// --------------------------------------------------------------------

var _response = null;
var db = require("./db/main");
