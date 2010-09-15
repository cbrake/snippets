
sys = require('sys');

var a = {error: ['asdf','asdf','sdf','cliff', 'test']}

sys.puts(sys.inspect(a))

for (var i in a) {
  sys.puts(sys.inspect(a[i]))
  for (var j in a[i]) {
    // apparently i is the index, not the value
    sys.puts(sys.inspect(a[i][j]))
  }
}

console.log("dump in function")

function dump(a) {
  for (var i in a) {
    sys.puts(sys.inspect(a[i]))
    for (var j in a[i]) {
      sys.puts(sys.inspect(a[i][j]))
    }
  }
}

dump(a)

