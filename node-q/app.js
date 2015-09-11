#!/usr/bin/env node

var Q = require('q');
var fs = require('fs');

Q.nfcall(fs.readdir, './').then(function(dirs) {
  console.log(dirs);
})
 

