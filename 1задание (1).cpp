#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cstring>
using namespace std;
class Kvadrat
{
private:
	int a;
	int x;
	int y;
public:
	Kvadrat() { a = 0; x = 0; y = 0; }
	Kvadrat(int A, int X, int Y) { a = A; x = X; y = Y; }
	void print() { cout << a << "= a " << x << "= x  " << y<<"=y"; }
	int getnumber()
	{
		
		return a;

	}

	int setnumber(double ff)
	{
		a = ff;
		return a;
	}

	double operator+()
	{
		double P = 4 * a;
		return P;
	}

	double operator*()
	{
		double S = a * a;
		return S;
	}

	Kvadrat operator* (double u)
	{
		Kvadrat t ;
		t.a = a*u;
		return t;

	}
	friend Kvadrat operator * (double, Kvadrat);
	
};

Kvadrat operator * (double z, Kvadrat yy)
{
	Kvadrat y;
	y.a = yy.a * z;
	return y;
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Kvadrat aa(8, 0, 0);
	cout << "Периметр квадрата: "<< +aa << endl;
	
	Kvadrat res = aa * 5;
	cout << "Kvadrat * double = "<<res.getnumber() << endl;

	Kvadrat ter = 5 * aa;
	cout << "double * Kvadrat = " << ter.getnumber() << endl;

	cout << "Площадь: " << *aa;
	
	
	return 0;
}


