
console.log("wait multiple");

var mywait = function(delay, callback) {
  setTimeout(callback, delay);
}


var timer_count = 0;

for (var i=0; i < 10; i++) {
  console.log("setting delay for " + i);
  timer_count++;
  (function(i) {
    mywait((10-i)*1000, function() {
      timer_count--;
      console.log("callback " + i);
      if (!timer_count) {
        console.log("all timers expired");
      }
    });
  })(i);
}

console.log("done setting all timers");

