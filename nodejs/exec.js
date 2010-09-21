
// exec blocks for as long as it takes 

exec = require('child_process').exec;

var sleep_test = function(i, callback) {
  exec('sleep 2', function(error, stdout, stderr) {
    callback(i);
  });
}

/* this does not work as i == 10 in all the callbacks
for (var i=0; i < 10; i++) {
 console.log("test ", i);
 sleep_test(i, function(i_) {
   console.log("callback " + i + " " + i_);
 });
}
*/

/*
// the following works
for (var i=0; i < 10; i++) {
  console.log("test ", i);
  sleep_test(i, function(i) { 
    return function(i_) {
      console.log("callback " + i + " " + i_);
    }
  }(i));
}
*/

// another way to implement
for (var i=0; i < 10; i++) (function(i) {
  console.log("test ", i);
  sleep_test(i, function(i_) {
    console.log("callback " + i + " " + i_);
  });
})(i);


