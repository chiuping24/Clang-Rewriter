//#include <iostream>
//using namespace std;
#include "../Header.h"
#include <iostream>
using namespace std;

int Cube(int x)
{
	return x * x * x;
}

int Square(int x)
{
	return x * x;
}

double D(double x) {
	long double a = x*x;
	long double b = x;
	double c = fabs(a - b);
	return c;
}


long L(double x) {
	long double a = x*x*x;
	long double b = x;
	long c = a - b;
	return c;
}
