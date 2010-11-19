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

  if (act && acts[act]) {
    acts[act](request);
  } else {
    console.error("Wrong action method");
  }
}

// --------------------------------------------------------------------
// Private methods
// --------------------------------------------------------------------

var acts = {
  auth: function(request) {

    var postData = "";
    var responseData = null;

    // ---------------------------------------------------------------------//

    /**
     * Set host to db.
     * 
     * @param id account id
     * @param host client host
     */
    var setHost = function(id, host) {
      db.sendRequest(function(data) {
      }, "/_design/accounts/_update/auth/" + id + "?host=" + host, "PUT");
    };

    // ---------------------------------------------------------------------//

    /**
     * Resolve Roster list. Get first & last name by id.
     * 
     * @param list {Array} roster list
     */
    var resolveRosterList = function(list) {
      db.sendRequest(function(data) {
        responseData.list = JSON.parse(data).list;
        _response.end(JSON.stringify(responseData));
      }, "/_design/accounts/_list/roster/roster?list=[" + list.join(",") + "]", "GET");
    };

    // ---------------------------------------------------------------------//

    // Get POST data
    request.addListener("data", function(chunk) {
      postData += chunk;
    });

    request.addListener("end", function() {
      db.sendRequest(function(data) {
        responseData = JSON.parse(data);

        if (responseData.status == "success") {
          var parsedPostData = require("querystring").parse(postData);

          setHost(responseData.id, parsedPostData.host);
          resolveRosterList(responseData.list);
        }

      }, "/_design/accounts/_list/auth/auth?" + postData);
    });

  }
};

// --------------------------------------------------------------------
// Private variables
// --------------------------------------------------------------------

var _response = null;
var db = require("./db/main");
