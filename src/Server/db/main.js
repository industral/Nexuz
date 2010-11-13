var http = require("http");

/**
 * Send request.
 * 
 * @param callback callback function
 * @param path request path
 * @param method request method (optional), default "GET"
 * @param inputData input data (optional)
 */

exports.sendRequest = function sendRequest(callback, path, method, inputData) {

  var dbRequest = http.createClient(_db.port, _db.URL);
  var request = dbRequest.request(method ? method : "GET", _db.name + path, inputData ? inputData : {});
  request.end();

  request.on("response", function(response) {
    response.setEncoding("utf8");
    response.on("data", function(data) {
      if (typeof callback === "function") {
        callback(data);
      }
    });
  });

}

var _db = {
  URL: "localhost",
  port: 5984,
  name: "/accounts" // <-- component
};
