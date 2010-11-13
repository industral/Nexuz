/**
 * Server class.
 * 
 * @author Alex Ivasyuv
 */
"use strict";

var http = require("http");
var router = require("./router");

http.createServer(function(request, response) {

  response.writeHead(200, {
    "Content-Type": "text/plain"
  });

  router.init(response);
  router.act(request);

}).listen(8365);
