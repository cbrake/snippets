// todo: http://mckoss.com/jscript/object.htm
// todo: http://www.devarticles.com/c/a/JavaScript/Object-Oriented-JavaScript-Using-the-Prototype-Property/3/

function ObjectA()
{
  this.a = 2;
}

ObjectA.prototype.inc_a = function()
{
  this.a++;
}

a_ = new ObjectA();

console.log("a_.a = ", a_.a);

a_.inc_a();

// ====================================

console.log("a_.a = ", a_.a);

function ObjectB() 
{
  this.b = 2;

  this.inc_b = function() {
    this.b++;
  }
}

b_ = new ObjectB();

console.log("b_.b = ", b_.b);

b_.inc_b();

console.log("b_.b = ", b_.b);


// =========================================
// inheritance

function Animal(named)
{
    var name = named ? named : 'Unknown';
    this.Name = function()
    {
        return name;
    }

    this.MakeSound = function()
    {
        return 'That\'s the ' + name + ' sound';
    }
}

function Cat()
{
    var base = new Animal('Cat');

    this.Name = base.Name;
    this.MakeSound = function()
    {
        console.log('Mew');
        return base.MakeSound();
    }
}

c = new Cat();

console.log("name = ", c.Name());
console.log("sound = ", c.MakeSound());


// ==========================================
// alternate for inheritance

function Animal(named)
{
   var name = named ? named : 'Unknown';
   this.Name = function()
   {
       return name;
   }

   this.MakeSound = function()
   {
       return 'That\'s the ' + name + ' sound';
   }
}

function Cat()
{
   var base = new Animal('Cat');
   //base.Name = base.Name; <-- unnecessary
   base.MakeSound2 = base.MakeSound; // could probably do this another way

   // override away
   base.MakeSound = function()
   {
       console.log('Mew');
       return this.MakeSound2();
   }
   return base;
}

c = new Cat()
console.log("name = ", c.Name());
console.log("sound = ", c.MakeSound());


// ==========================================

obj = new Object;
obj.x = 1;
obj.y = 2;

function Foo()
{
  this.x = 1;
  this.y = 2;
}

obj = new Foo;


// ==========================================
// http://javascript.crockford.com/prototypal.html
// Javascript, the good parts

// ==========================================
if (typeof Object.create !== 'function') {
    Object.create = function (o) {
        function F() {}
        F.prototype = o;
        return new F();
    };
}

var myMammal = {
    name : 'Herb the Mammal',
    get_name : function ( ) {
        return this.name;
    },
    says : function ( ) {
        return this.saying || '';
    }
};

var myCat = Object.create(myMammal);
myCat.name = 'Henrietta';
myCat.saying = 'meow';
myCat.purr = function (n) {
    var i, s = '';
    for (i = 0; i < n; i += 1) {
        if (s) {
            s += '-';
        }
        s += 'r';
    }
    return s;
};


myCat.get_name = function ( ) {
    return this.says( ) + ' ' + this.name + ' ' + this.says( );
};

console.log("get_name = ", myCat.get_name());
console.log("says = ", myCat.says());
console.log("purr = ", myCat.purr());





