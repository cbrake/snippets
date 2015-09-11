var Promise = require('bluebird');
var mongo = require('promised-mongo');

var db = mongo('test', ['a'])

db.a.insert({a:'this is a test'})
.then(db.a.find().forEach(function(doc) {
  console.log(doc);
})
.then(function() {
  console.log('finished');
}))


