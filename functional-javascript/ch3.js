var _ = require('underscore');

function existy(x) { return x != null };
function truthy(x) { return (x != false) && existy(x) };


aVariable = "Outer" ; 

function afun () { 
  var aVariable = "Middle" ; 
  return _ . map ([ 1 , 2 , 3 ], function ( e ) { 
    var aVariable = "In" ; 
    return [ aVariable , e ]. join ( ' ' ); 
  });
}

console.log('afun', afun());

var globals = {};

function makeBindFun(resolver) {
  return function(k, v) {
    var stack = globals[k] || [];
    globals[k] = resolver(stack, v);
    return globals;
  };
}

var stackBinder = makeBindFun(function(stack, v) {
  stack.push(v);
  return stack;
});

var stackUnbinder = makeBindFun(function(stack) {
  stack.pop();
  return stack;
});

var dynamicLookup = function(k) {
  var slot = globals[k] || [];
  return _.last(slot);
};

stackBinder('a', 1);
stackBinder('b', 100);
stackBinder('a', 2);

console.log(dynamicLookup('a'));
console.log(globals);

function f() { return dynamicLookup('a'); };
function g() { 
  stackBinder('a', 'g'); 
  return f();
};

console.log('f()', f());
console.log('g()', g());
console.log('globals', globals);

function globalThis() { return this; }

console.log('globalThis()', globalThis());

console.log(globalThis.call('barnabas'));

console.log(globalThis.apply('orsulak', []));

var nopeThis = _.bind(globalThis, 'nope');
console.log(nopeThis.call('wat'));

var target = {
  name: 'the right value',
  aux: function() {
    return this.name;
  },
  act: function() {
    return this.aux();
  }
};

_.bindAll(target, 'aux', 'act');

console.log(target.act.call('wat'));

// stopped at Function Scope, pg 73


var shadowed = 0;

function argShadow(shadowed) {
  return ["Value is", shadowed].join( ' ');
}

argShadow(108)










