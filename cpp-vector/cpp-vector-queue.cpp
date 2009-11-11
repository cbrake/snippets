// to build
// g++ `pkg-config --cflags --libs gtk+-2.0`  cpp-vector-queue.cpp -o cpp-vector-queue


// the first try at doing this did not work as there is _NO_ way to call the delete
// method on a vector and free it if not created with the new method.  Even after the 
// clear method, it still leaks like crazy

#include <vector>
#include <iostream>
#include <glib.h>


using namespace std;

class A {
public:
	int _a;
	A(int a) : _a(a)
	{}

	~A()
	{
		cout << "destorying class A, value =" << _a << endl;
	}
};

class B {
public:
	vector<A> v_a;
};

class C {
public:
	vector<A> * v_a;
};



GQueue * q;

void queue_value()
{
	cout << "starting queue_value" << endl;

	B * b = (B*)g_slice_alloc0(sizeof(*b));
	//B * b = new B();

	b->v_a.push_back(A(2));
	b->v_a.push_back(A(3));

	g_queue_push_tail(q, b);

	cout << "ending queue_value" << endl;
}

void deque_value()
{
	cout << "starting deque value" << endl;

	B * b = (B*)g_queue_pop_head(q);
	cout << "1st vector value = " << b->v_a[0]._a << endl;

	// ways to make sure vector memory is reclaimed
	//b->v_a.erase(b->v_a.begin(), b->v_a.end());
	//delete b;
	b->v_a.clear();

	g_slice_free(B, b);

	cout << "ending deque value" << endl;
}

void queue_value2()
{
	cout << "starting queue_value" << endl;

	C * c = (C*)g_slice_alloc0(sizeof(*c));
	//B * b = new B();
	
	c->v_a = new vector<A>();

	c->v_a->push_back(A(4));
	c->v_a->push_back(A(5));

	g_queue_push_tail(q, c);

	cout << "ending queue_value" << endl;
}

void deque_value2()
{
	cout << "starting deque value" << endl;

	C * c = (C*)g_queue_pop_head(q);
	cout << "1st vector value = " << (*(c->v_a))[0]._a << endl;

	// this deletes the vector and frees its elements
	delete c->v_a;

	g_slice_free(C, c);

	cout << "ending deque value" << endl;
}



main ()
{
	q = g_queue_new();

	vector<A> v_a;

	//v_a.resize(10);

	//A * a = new A(1);
	//delete a;

	while(1) {
		queue_value2();
		deque_value2();
	}
}


