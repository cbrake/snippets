var _ = require('underscore');

function existy(x) { return x != null };
function truthy(x) { return (x != false) && existy(x) };


var shadowed = 0;

function argShadow(shadowed) {
  return ["Value is", shadowed].join( ' ');
}

console.log(argShadow(108))
console.log(argShadow())

function complement(PRED) {
  return function() {
    return !PRED.apply(null, _.toArray(arguments));
  };
}

function isEven(n) {return (n%2) === 0}

var isOdd = complement(isEven);

console.log(isOdd(2));
console.log(isOdd(413));

function plucker(FIELD) {
  return function(obj) {
    return (obj && obj[FIELD]);
  };
}

var best = {title: "Infinite Jest", author: "DFW"};

var getTitle = plucker('title');

console.log(getTitle(best));

var books = [{ title : "Chthon" }, { stars : 5 }, { title : "Botchan" }]; 

var third = plucker ( 2 ); 

console.log(third ( books ))

console.log(_.filter(books, getTitle));




