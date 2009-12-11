#include <stdio.h>
#include <string.h>


struct A
{
	int _a;
	int _b;
};

class B
{
public:
	int _a;
	int _b;
	B(int a, int b) 
	{
		printf("constructor\n");
		_a = a;
		_b = b;
	};

	~B() 
	{
		printf("destructor\n");
	}

	int get_a() {
		return _a;
	}
};


main()
{
	A a;
	B b(1,2);
	B b2(3,4);
	
	memset(&b2, 0, sizeof(b2));

	printf("sizeof(a) = %i, sizeof(b) = %i\n", sizeof(a), sizeof(b));
	printf("b2.get_a() returns %i\n", b2.get_a());
}

