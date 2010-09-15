

// this all works as expected.  Not sure how to simulate 

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
a();


