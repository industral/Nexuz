/**
 * Set host.
 * 
 * @author Alex Ivasyuv
 */

function(doc, request) {

  doc.host = request.query.host;

  // save doc
  return [
    doc,
    JSON.stringify({
      result: "success"
    })];
}
