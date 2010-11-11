
test_modules = require('./test_modules');

var test1_ = function() {
  console.log("hi");
};

exports.test1 = test1_;

test_modules.test1();

