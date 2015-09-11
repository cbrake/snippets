Promise = require('bluebird');

function a() {
  return new Promise(function(res) {
    res('hi');
  });
}

Promise.then(function() {
  return 'hi';
}).then(function(input) {
  return input + ' there';
}).then(function(input) {
  return input + ' :-)';
}).then(function(input) {
  console.log(input);
});


