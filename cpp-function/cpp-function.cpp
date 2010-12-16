#include <iostream>
#include <tr1/functional> 

struct B
{
	std::tr1::function <void ()> _callback;

	void register_callback(std::tr1::function <void ()> callback)
	{
		_callback = callback;
	}

	void unregister_callback()
	{
		_callback = NULL;
	}

	void process() {
		// simply calls callback
		if (_callback)
			_callback();
	}
};

struct A 
{ 
	B * _b;

	A(B * b) :
		_b(b)
	{
		std::tr1::function<void()> callback = std::tr1::bind(&A::callback, this);
		b->register_callback(callback);
	}

	~A()
	{
		_b->unregister_callback();
	}

	void callback() {
		std::cout << "A::callback called\n";
	}

	void process() {
		_b->process();
	}
}; 

int main() 
{ 
	B * b = new B();
	A * a = new A(b); 

	// the following is example where object b calls back into a method
	// in object a
	a->process();

	// now delete object a, and verify the callback in B does not crash
	delete a;

	// try following still tries to call the callback
	b->process();
} 


