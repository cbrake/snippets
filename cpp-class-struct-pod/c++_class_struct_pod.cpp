#include <stdio.h>


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

	printf("sizeof(a) = %i, sizeof(b) = %i\n", sizeof(a), sizeof(b));
}

