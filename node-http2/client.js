var path = require('path');
var fs = require('fs');
var http2 = require('http2');
var urlParse = require('url').parse;

// Setting the global logger (optional)
http2.globalAgent = new http2.Agent({
  rejectUnauthorized: true,
});

// Sending the request
var url = 'https://localhost:8080';
var options = urlParse(url);

// Optionally verify self-signed certificates.
if (options.hostname == 'localhost') {
  options.key = fs.readFileSync(path.join(__dirname, '/localhost.key'));
  options.ca = fs.readFileSync(path.join(__dirname, '/localhost.crt'));
}

var request = process.env.HTTP2_PLAIN ? http2.raw.get(options) : http2.get(options);

// Receiving the response
request.on('response', function(response) {
  response.pipe(process.stdout);
});

// Receiving push streams
request.on('push', function(pushRequest) {
  console.error('Receiving pushed resource: ' + pushRequest.url);
  pushRequest.on('response', function(pushResponse) {
    pushResponse.on('readable', function() {
      console.log(JSON.parse(pushResponse.read().toString()));
    });
  });
});

