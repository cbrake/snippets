function test(a) {
	console.log("a = ", a);
	a = 50;
}


var b = 20;
test(b);
console.log("b now = ", b);

// try using functions -- this really does not work

function state() {
   a = 10;
   b = 20;
}

console.log("state.a = ", state.a);

function update_state(obj) {
  obj.a = 50;
}

update_state(state);

console.log("state.a = ", state.a);

// try using a hash, this seems to work

state = {
  a:1,
  b:2,
}

console.log("(hash) state.a = ", state.a);

update_state(state);

console.log("(hash) state.a = ", state.a);


// note, passing a raw string does not work
function append_last(s) {
  s += "brake"
}


var a = 'cliff'

append_last(a)

console.log("a = ", a)

// outputs: cliff

// try via objects, does not work either
function append_last(s) {
  s += "brake"
}

var a = Object('cliff')

append_last(a)

console.log("a = ", a)


// outputs: cliff


// note, embedding a string in an array works fine 
function append_last(s) {
  s.s += "brake"
}

a = {s:'cliff'}

append_last(a)

console.log("a = ", a.s)


