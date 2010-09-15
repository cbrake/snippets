
// exec blocks for as long as it takes 

exec = require('child_process').exec;

var sleep_test = function(i, callback) {
  exec('sleep 2', function(error, stdout, stderr) {
    callback(i);
  });
}

var i;
for (i=0; i < 10; i++) {
  console.log("test ", i);

  sleep_test(i, function(i_) {
    console.log("callback " + i + " " + i_);
  });
}



