// npm install email


Email = require('email').Email;

var myMsg = new Email(
{ from: "cbrake@bec-systems.com"
//, to: "cliff.brake@gmail.com"
, to: ["cliff.brake@gmail.com", "cbrake@bec-systems.com"]
, subject: "Test email from nodejs email"
, body: "body of test email"
, timeout: 20000
})

myMsg.send(function(err) {
	console.log("mail send");
	if (err) {
		console.log("Error: " + err);
	}
});


