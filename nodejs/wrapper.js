sys = require('sys');

var p = function(a) {
  sys.puts(sys.inspect(a));
}

var myfunc = function(a, b, c, callback) {
  console.log("in original func, a = " + a);
  p(arguments);
  callback('all done');
}

// try wrapping a function, callback and passing on arguments
// callback is assumed to be last argument
var mywrapper = function(f) {
  return function() {
    console.log("in wrapper");
    var args = [].slice.call(arguments);
    // assume the last arg is the callback
    var saved_callback = args.pop();
    var new_callback = function() {
      console.log("in callback wrapper");
      saved_callback.apply(this, arguments);
    }
    args.push(new_callback);
    return f.apply(this, args);
  }
}

var wrappedmyfunc = mywrapper(myfunc);

wrappedmyfunc(5, 6, 7, function(result) {
  console.log('callback returned: ' + result);
});





    
