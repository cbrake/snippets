
// see exec.js

// this all works as expected.  Not sure how to simulate 
// some of these examples came from http://ejohn.org/apps
// some examples from Javascript The Good Parts

assert = require('assert');

var myobj = {
  a: 'hi',
  func: function() {
    console.log("a = ", this.a);
  }
}

myobj.func();

var f2 = function() {
  myobj.func();
}

f2();


var not_block_scope = function() {

  console.log("b = ", b);     // prints undefined
  // console.log("c = ", c);  // throws error

  var b = 10;
}

not_block_scope();


console.log("============================");
var i = 0;
var inc = function() {
  i = i + 1;
  return i;
};

console.log("i = ", inc());
console.log("i = ", inc());
console.log("i = ", inc());


console.log("============================");
var counter = (function(start) {
  return function() { return start++};
})();

var a = counter(5);
// a();  // does not work


console.log("============================");
var myObject = function() {
  var value = 0;
  return {
    increment: function (inc) {
      value += typeof inc === 'number' ? inc : 1;
    },
    getValue: function() {
      return value;
    }
  };
}();

myObject.increment();
myObject.increment(2);
myObject.getValue();
console.log("myObject.getValue = ", myObject.getValue());


console.log("============================");
console.log("counting function, hides current from outside modification");

var count = function() {
  var current = 0;
  return function() {
    current += 1;
    return current;
  }
}();

console.log("count() = ", count());
console.log("count() = ", count());
console.log("count() = ", count());


console.log("============================");
(function(){ 
  var count = 0; 
 
  var timer = setInterval(function(){ 
    if ( count < 5 ) { 
      console.log( "Timer call: ", count ); 
      count++; 
    } else { 
      assert.ok( count == 5, "Count came via a closure, accessed each step." ); 
      assert.ok( timer, "The timer reference is also via a closure." ); 
      clearInterval( timer ); 
    } 
  }, 100); 
})(); 
 
//assert.ok( typeof count == undefined, "count doesn't exist outside the wrapper" ); 
//assert.ok( typeof timer == undefined, "neither does timer" );


console.log("============================");
console.log("now we can handle closures and looping");
for ( var d = 0; d < 3; d++ ) (function(d){ 
 setTimeout(function(){ 
   console.log( "Value of d: ", d ); 
   assert.ok( d == d, "Check the value of d." ); 
 }, d * 200); 
})(d);

