#include <stdio.h>


// interface class
class A 
{
public:
	virtual void hello() = 0;
	virtual ~A() {};
};

class B : public A
{
public:
	B() {
		printf("B constructor\n");
	}

	~B() {
		printf("B destructor\n");
	}

	void hello()
	{
		printf("hello\n");
	}
};


main ()
{
	A * a = new B();

	// when we delete a, the B destructor is also called
	delete a;
}

