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
      db.sendRequest(function(data) {
        _response.end(data);
      }, "/_design/accounts/_list/auth/auth?" + postData);
    });

  }
};

// --------------------------------------------------------------------
// Private variables
// --------------------------------------------------------------------

var _response = null;
var db = require("./db/main");
