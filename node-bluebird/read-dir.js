var Promise = require("bluebird");
var fs = Promise.promisifyAll(require("fs"));
var Path = require("path");

function readDir(dirName) {
    return fs.readdirAsync(dirName).map(function (fileName) {
        var path = Path.join(dirName, fileName);
        return fs.statAsync(path).then(function(stat) {
            return stat.isDirectory() ? readDir(path) : path;
        });
    }).reduce(function (a, b) {
        return a.concat(b);
    }, []);
}

readDir("./").then(function(v){
    console.log(v.join("\n"));
});
