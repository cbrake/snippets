
var Promise = require("bluebird");
var influx = require('influx');
var util = require('util');

Promise.promisifyAll(influx);

//console.log(util.inspect(influx, { showHidden: true }));

var tsd = influx({
  host: 'localhost',
  username: 'test',
  password: 'test',
  database: 'test2'
});

var w1 = tsd.writePointAsync('promise.test', {value: 1})
var w2 = tsd.writePointAsync('promise.test', {value: 2})

Promise.all([w1, w2]).done(function() {
  console.log('all is well');
}, function(e) {
  console.log('done', e);
});

Promise.all([w1, w2]).catch(function(e) {
  console.log('catch', e);
});

