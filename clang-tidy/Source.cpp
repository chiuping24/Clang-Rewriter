#include "Header.h"
// classes example
#include <iostream>
using namespace std;

//int minus();
struct A {
        virtual void foo(int) = 0;
};

struct B : public A {
	int a = 0;
	virtual void foo(int x) {
		if (x == 1) {
			a = 5;
		}
	};
};


int main(void) {
	long double glBND_xn_limit = 4.2;
	long double glBND_yn_limit = 2.1;
	double distance = 0.0;
	long distance2 = 0;
	struct B aa;
	struct A;
	int result = Cube(3);
	int val = Square(2);
	double DD = D(2.1);
	long LL = L(2.1);

	long double glBND_xp_limit = 4.3;
	long double glBND_yp_limit = 2.1;
	if (glBND_yp_limit == 12) {
		distance = 3.5;
	}
	else {
		distance = fabs(glBND_xp_limit - glBND_xn_limit);
		distance2 = fabs(glBND_yp_limit - glBND_yn_limit);
	}
	do_math(&val);
	return result;
}
