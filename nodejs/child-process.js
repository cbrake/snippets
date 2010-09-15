var spawn = require('child_process').spawn;

process.argv.forEach(function (val, index, array) {
  console.log(index + ': ' + val);
});

function handle_ls_data(data) {
	console.log("ls stdout: ", data);
}

ls = spawn('ls', ['-l', '-i', '/usr']);

ls.stdout.on('data', handle_ls_data)

ls.stderr.on('data', function(data) {
	console.log("ls stderr: ", data);
})

ls.on('exit', function(code, signal) {
	console.log("ls exitted, code = ", code, "signal = ", signal);
})

// another way to do the same thing
// this uses cwd instead of an argument to ls

ls2 = spawn('ls', ['-l', '-i'], {cwd:'/usr'});

ls2.stdout.on('data', function(data) {
	console.log("ls2 stdout: ", data);
})



