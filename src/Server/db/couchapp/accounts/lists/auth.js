function(head, request) {
  var obj = {
    status: "error"
  };

  while (row = getRow()) {

    if (request.query.username == row.value.nickname && request.query.password == row.value.password) {
      obj.status = "success";
      obj.list = row.value.roster
    }
  }

  send(JSON.stringify(obj));
}
