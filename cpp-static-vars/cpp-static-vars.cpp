#include <stdio.h>

class A {
	public:
		void test() {
			static int a = 0;
			printf ("a = %i\n", a);
			a++;
		}
};

main() {
	A a1, a2;

	a1.test();
	a2.test();
}


