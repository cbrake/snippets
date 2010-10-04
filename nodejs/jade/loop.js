/**
 * Module dependencies.
 */

var jade = require('jade');

var options = { locals: {loopvars: ['text1', 'text2', 'text3'], test: 'this is a test'}};
jade.renderFile(__dirname + '/loop.jade', options, function(err, html){
    if (err) throw err;
    console.log(html);
});


