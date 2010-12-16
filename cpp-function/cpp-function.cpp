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

	void mf(int i) {  
		std::cout << "mf " << i << "\n";
	} 

	void process() {
		_b->process();
	}
}; 

int main() 
{ 
	B b;
	std::tr1::function<void (A*, int)> f(&A::mf); 
	A a(&b); 
	f( &a, 3); // OK, calls &a->mf(3) 
	std::tr1::function<void (A&, int)> f2(&A::mf); 
	f2( a, 4); // OK, calls a.mf(4) 

	// the following is example where object b calls back into a method
	// in object a
	a.process();
} 

