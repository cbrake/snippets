var fs = require('fs');
var path = require('path');
var http2 = require('http2');

// The callback to handle requests
function onRequest(request, response) {
  console.log('request:', request.url);

  if (request.url == '/count') {
    var push = response.push('push data');
    push.writeHead(200);

    var count = 0;

    setInterval(function() {
      push.write(JSON.stringify({count:count}));
      count += 1;
    }, 10000);
  } else {
    response.write('hello :-)');
    response.end();
  }
}

// Creating the server in plain or TLS mode (TLS mode is the default)
var server;
if (process.env.HTTP2_PLAIN) {
  server = http2.raw.createServer({
  }, onRequest);
} else {
  server = http2.createServer({
    key: fs.readFileSync(path.join(__dirname, '/localhost.key')),
    cert: fs.readFileSync(path.join(__dirname, '/localhost.crt'))
  }, onRequest);
}
server.listen(process.env.HTTP2_PORT || 8080);
