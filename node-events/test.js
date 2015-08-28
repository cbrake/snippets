
var M = require('./m');

var t = new M();

t.on('add', function(a) {
  console.log('something added', a);
});

t.add('hi')

