var _ = require('underscore');

function existy(x) { return x != null };
function truthy(x) { return (x != false) && existy(x) };

function doWhen(cond, action) {
  if (truthy(cond))
    return action();
  else
    return undefined;
}

var l = console.log

function finder(valueFun, bestFun, coll) {
  return _.reduce(coll, function(best, current) {
    var bestValue = valueFun(best);
    var currentValue = valueFun(current);
    return (bestValue === bestFun(bestValue, currentValue)) ? best : current;
  });
}

l(finder(_.identity, Math.max, [1,2,3,4,5]));

function best(fun, coll) {
  return _.reduce(coll, function(x, y) {
    return fun(x, y) ? x : y
  });
}

l(best (function(x,y) {return x > y}, [1,2,3,4,5]));

function repeat(times, VALUE) {
  return _.map(_.range(times), function() {
    return VALUE; 
  });
}

l(repeat(4, "Major"));

function repeatedly(times, fun) {
  return _.map(_.range(times), fun);
}

l(repeatedly(3, function() {
  return Math.floor((Math.random()*10)+1);
}));

l(repeatedly(3, function() { return "Odelay!"; }));

function iterateUntil(fun, check, init) {
  var ret = [];
  var result = fun(init);

  while(check(result)) {
    ret.push(result);
    result = fun(result);
  }
  return ret;
};

l(iterateUntil(function(n) {return n+n},
  function(n) {return n <= 1024},
  1));


function always(VALUE) {
  return function() {
    return VALUE;
  }
};

function invoker (NAME, METHOD) {
  return function(target) {
    if (!existy(target)) {
      l("Must provide a target");
    }

    var targetMethod = target[NAME];
    var args = _.rest(arguments);

    return doWhen((existy(targetMethod) && METHOD === targetMethod), function() {
      return targetMethod.apply(target, args);
    });
  };
};

var rev = invoker('reverse', Array.prototype.reverse);

l(_.map([[1,2,3]], rev));










