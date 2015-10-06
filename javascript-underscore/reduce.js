var _ = require('underscore');

// reduce(list, iteratee, [memo], [context])

// both of the following return the same result, because if there is no memo
// the first item is used as the memo
console.log(_.reduce([1,2,3], function(memo, num) {return memo+num;}, 0));

console.log(_.reduce([1,2,3], function(memo, num) {return memo+num;}));

