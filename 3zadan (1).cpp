// Пириев Пири (2 вариант) КМБО-01-23
//

#include <iostream>

using namespace std;

class A1
{
protected:
	int x;
public:
	A1() { x = 0; cout << "\nA1 default constructor " << x << "\n"; }
	A1(int B) { x = B; cout << "\nA1 constructor " << x << "\n"; }
	~A1() { cout << "\nA1 destructor"; }
	virtual void print()
	{
		cout << "A1" << endl;
	}
	virtual void Show()
	{
		cout << "a1 = " << x << endl;
	}
};

class B1 : virtual public A1
{
protected:
	int b1;
public:
	B1(int D, int B) : A1(B)
	{
		b1 = D; cout << "\nB1 constructor " << b1 << "\n";
	}
	virtual void Show() { cout << "b1= " << b1 << "   a1 = " << x << endl; }
	virtual void print()
	{
		cout << "B1" << endl;
	}
};

class B2 : virtual public A1
{
protected:
	int b2;
public:
	B2(int D, int B) : A1(B)
	{
		b2 = D; cout << "\nB2 constructor " << b2 << "\n";
	}
	virtual void Show() { cout << "b2 = \n" << b2 << " a1 =\t" << x; }
	virtual void print()
	{
		cout << "B2" << endl;
	}
};

class B3 : virtual public A1
{
protected:
	int b3;
public:
	B3(int D, int B) : A1(B)
	{
		b3 = D; cout << "\nB3 constructor " << b3 << "\n";
	}
	virtual void Show() { cout << "b3 = \n" << b3 << " a1 = \t" << x; }
	virtual void print()
	{
		cout << "B3" << endl;
	}
};


class C1 : public B1, public B2, public B3
{
protected:
	int d;
public:
	C1(int D, int B1, int B2, int B3) : B1(B1, B1), B2(B2, B2), B3(B3, B3)
	{
		d = D; cout << "\nC1 constructor " << d << "\n";
	}
	virtual void Show() { cout << "\n" << "c1 = " << d << "\ta1 = " << x << "\t  b1 = " << b1 << "\tb2 = " << b2 << "\tb3 = " << b3 << endl; }
	virtual void print()
	{
		cout << "C1" << endl;
	}
};

int main()
{

	C1 c(100, 2, 3, 4);
	A1* p = &c;
	p->Show();
	p->print();
	B1 b(77, 10);
	A1* po = &b;
	po->Show();
	po->print();
	return 0;
}

