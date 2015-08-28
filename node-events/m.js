var util = require("util");
var events = require("events");

var MyStream = module.exports = function() {
    events.EventEmitter.call(this);
}

util.inherits(MyStream, events.EventEmitter);

MyStream.prototype.add = function(a) {
  this.emit('add', a);
};



