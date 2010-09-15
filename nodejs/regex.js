
function p(x) {
  sys.puts(sys.inspect(x))
}

sys = require('sys')

a = '  this is a test.txt wer asdf';

b = 'blah blah blah\nVERSION=1.20.3';
console.log(b)

// returns index of match
p(a.search(/this/));   // 2
p(a.search(/thiss/));  // -1

p(/this/.test(a));  // true

p(/this/.exec(a));  // array

// grouping
p(/VERSION=(\d+.\d+.\d+)/.test(b));  // true
p(RegExp.$1);

// replacement
p(b.replace(/VERSION=\d+.\d+.\d+/, "VERSION=1.20.4"));
p(b)


