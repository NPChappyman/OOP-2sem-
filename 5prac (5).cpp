#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
class Exception : public exception
{
protected:
	//сообщение об ошибке
	char* str;
public:
	Exception(const char* s)
	{
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception(char* s)
	{
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception(const Exception& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
	}
	~Exception()
	{
		delete[] str;
	}

	//функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика
	virtual void print()
	{
		cout << "Exception: " << str << "; " << what();
	}
};

class IndexOutOfBoundsExeption : public Exception
{
protected:
	int Row; int Col;
public:
	IndexOutOfBoundsExeption(char* s, int row, int col) : Exception(s) { Row = row; Col = col; }
	IndexOutOfBoundsExeption(const char* s, int row, int col) : Exception(s) { Row = row; Col = col; }
	virtual void print()
	{
		cout << "IndexOutOfBoundsExeption: " << str << " , row: " << Row << ", col :" << Col;
	}
};


class InvalidOperationException : public Exception
{
protected:
	int Row1; int Col1; int Row2; int Col2;
public:
	InvalidOperationException(char* s, int row1, int col1, int row2 = -1, int col2 = -1) : Exception(s) { Row1 = row1; Col1 = col1; Row2 = row2; Col2 = col2; }
	InvalidOperationException(const char* s, int row1, int col1, int row2 = -1, int col2 = -1) : Exception(s) { Row1 = row1; Col1 = col1; Row2 = row2; Col2 = col2; }
	virtual void print()
	{
		cout << "InvalidOperationException: " << str << " row1: " << Row1 << " col1: " << Col1 << " row2: " << Row2 << " col2: " << Col2;
	}
};

class WrongSizeException : public Exception
{
protected:
	int Row1; int Col1; int Row2; int Col2;
public:
	WrongSizeException(char* s, int row1, int col1, int row2 = -1, int col2 = -1) : Exception(s) { Row1 = row1; Col1 = col1; Row2 = row2; Col2 = col2; }
	WrongSizeException(const char* s, int row1, int col1, int row2 = -1, int col2 = -1) : Exception(s) { Row1 = row1; Col1 = col1; Row2 = row2; Col2 = col2; }
	virtual void print()
	{
		cout << "WrongSizeException: " << str << " row1: " << Row1 << " col1: " << Col1 << " row2: " << Row2 << " col2: " << Col2;
	}
};

class NonPositiveSizeException : public WrongSizeException
{
public:
	NonPositiveSizeException(char* s, int Row, int Col) : WrongSizeException(s, Row, Col) {}
	NonPositiveSizeException(const char* s, int Row, int Col) : WrongSizeException(s, Row, Col) {}
	virtual void print()
	{
		cout << "NonPositiveSizeException: " << str << " row1: " << Row1 << " col1: " << Col1;
	}
};

class TooLargeSizeException : public WrongSizeException
{
public:
	TooLargeSizeException(char* s, int Row, int Col) : WrongSizeException(s, Row, Col) {}
	TooLargeSizeException(const char* s, int Row, int Col) : WrongSizeException(s, Row, Col) {}
	virtual void print()
	{
		cout << "TooLargeSizeException: " << str << " row1: " << Row1 << " col1: " << Col1;
	}
};


class TooSmallException : public WrongSizeException
{
public:
	TooSmallException(char* s, int Row, int Col) : WrongSizeException(s, Row, Col) {}
	TooSmallException(const char* s, int Row, int Col) : WrongSizeException(s, Row, Col) {}
	virtual void print()
	{
		cout << "ToosmallSizeException: " << str << " row1: " << Row1 << " col1: " << Col1;
	}
};



template<class T>
class BaseMatrix
{
protected:
	T** ptr;
	int height;
	int width;
public:
	BaseMatrix(int Height = 2, int Width = 2)
	{
		if (Height < 1 || Width < 1) throw NonPositiveSizeException("Non Positive Size Exceptionn in BaseMatrix constructor", Height, Width);
		if (Height > 16000 || Width > 16000) throw TooLargeSizeException("Too Large Size Exception in BaseMatrix constructor", Height, Width);
		height = Height;
		width = Width;
		ptr = new T * [height];
		for (int i = 0; i < height; i++)
			ptr[i] = new T[width];
	}

	BaseMatrix(const BaseMatrix& M)
	{
		height = M.height;
		width = M.width;
		ptr = new T * [height];
		for (int i = 0; i < height; i++)
		{
			ptr[i] = new T[width];
			for (int j = 0; j < width; j++)
				ptr[i][j] = M.ptr[i][j];
		}
	}

	~BaseMatrix()
	{

		//деструктор
		if (ptr != NULL)
		{
			for (int i = 0; i < height; i++)
				delete[] ptr[i];
			delete[] ptr;
			ptr = NULL;
		}
	}

	BaseMatrix operator=(const BaseMatrix& M)
	{
		if (height != M.height || width != M.width)
		{
			if (ptr != NULL)
			{
				for (int i = 0; i < height; i++)
					delete[] ptr[i];
				delete[] ptr;
				ptr = NULL;
			}
			height = M.height;
			width = M.width;
			ptr = new T * [height];
			for (int i = 0; i < height; i++)
			{
				ptr[i] = new T[width];
			}
		}
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
				ptr[i][j] = M.ptr[i][j];
		}

		return *this;
	}

	T Trace() {
		if (width != height) throw InvalidOperationException("InvalidOperationException Trace, Cannot calculate trace for non-square matrix", height, width);
		T ans = 0;
		for (int i = 0; i < width; i++)
			ans += ptr[i][i];
		return ans;
	}

	BaseMatrix<T> operator+(BaseMatrix<T>& M)
	{
		if (width != M.width || height != M.height) throw InvalidOperationException("InvalidOperationException + undefined values for matrix of different sizes", height, width, M.height, M.width);
		BaseMatrix<T> A;
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				A(i, j) = ptr[i][j] + M(i, j);
		return A;
	}

	void print()
	{
		//вывод
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
				cout << ptr[i][j] << " ";
			cout << "\n";
		}
	}

	T& operator()(int i, int j)
	{
		if (i < 0 || i >= height || j<0 || j>width) throw IndexOutOfBoundsExeption("IndexOutOfBoundsExeption", i, j);
		return ptr[i][j];
	}



	template<class T1>
	friend ostream& operator <<(ostream& s, BaseMatrix<T1>& M);
	template<class T1>
	friend istream& operator >>(istream& s, BaseMatrix<T1>& M);
	template<class T1>
	friend ifstream& operator >>(ifstream& s, BaseMatrix<T1>& M);
};



template<class T1>
ostream& operator<<(ostream& s, BaseMatrix<T1>& M)
{

	if (typeid(s) == typeid(ofstream))
	{
		s << M.height << " " << M.width;
		for (int i = 0; i < M.height; i++)
			for (int j = 0; j < M.width; j++)
				s << " " << M.ptr[i][j];
		return s;
	}
	for (int i = 0; i < M.height; i++)
	{
		for (int j = 0; j < M.width; j++)
			cout << M.ptr[i][j] << " ";
		cout << "\n";
	}
	return s;
}

template<class T1>
istream& operator>>(istream& s, BaseMatrix<T1>& M)
{
	for (int i = 0; i < M.height; i++)
		for (int j = 0; j < M.width; j++)
			s >> M.ptr[i][j];
	return s;
}

template<class T1>
ifstream& operator >>(ifstream& s, BaseMatrix<T1>& M)
{

	int w, h;
	s >> h >> w;

	if (h != M.height || w != M.width)
	{
		if (M.ptr != NULL)
		{
			for (int i = 0; i < M.height; i++)
				delete[] M.ptr[i];
			delete[] M.ptr;
			M.ptr = NULL;
		}
		M.ptr = new T1 * [h];
		M.height = h;
		M.width = w;

		for (int i = 0; i < M.height; i++)
		{
			M.ptr[i] = new T1[M.width];
		}
	}

	for (int i = 0; i < M.height; i++)
		for (int j = 0; j < M.width; j++)
			s >> M.ptr[i][j];
	return s;

}


template<class T2>
class Matrix : public BaseMatrix<T2>
{
public:
	Matrix(int Height = 2, int Width = 2) : BaseMatrix<T2>(Height, Width) {}
	Matrix(const BaseMatrix<T2>& M) : BaseMatrix<T2>(&M) {}


	// Заполение по столбцам
	void filMatrix()
	{
		for (int i = 0; i < this->width; i++)
			for (int j = 0; j < this->height; j++)
				cin >> this->ptr[j][i];
	}

	// 21 вариант
	Matrix<T2> vec()
	{
		if (this->width == 1) throw TooSmallException("ToosmallException", this->height, this->width);
		Matrix<T2> ans(this->height, 1);
		for (int i = 0; i < this->height; i++) {
			bool f = true; bool u = true;
			for (int j = 0; j < (this->width) - 1; j++)
			{
				if (this->ptr[i][j] > this->ptr[i][j + 1])
				{
					f = false;
					break;
				}
			}
			for (int ji = 1; (ji < this->width); ji++)
			{
				if (this->ptr[i][ji] > this->ptr[i][ji - 1])
				{
					u = false;
					break;
				}
			}
			(ans.ptr[i][0]) = u == true || f == true;
		}
		return ans;
	}

};



int main()
{
	try
	{

		Matrix<double> M;
		M(0, 0) = 1;
		M(0, 1) = 2;
		M(1, 0) = 6;
		M(1, 1) = 7;
		cout << "M maxtrix" << endl; M.print(); cout << endl;

		cout << " --------------  " << endl;
		cout << M << endl;

		Matrix<double> M3(3, 3);
		Matrix<double> M4;

		M3.filMatrix();
		cout << endl;
		cout << M3 << endl;
		M4 = M3.vec();
		cout << M4 << endl;


		ofstream out("4.txt");
		if (out)
		{
			out << "3" << endl;
			Matrix<double> M_test1(3, 3);
			Matrix<double> M_test2(3, 1);
			Matrix<double> M_test3(1, 3);
			M_test1(0, 0) = 1; M_test1(0, 1) = 2; M_test1(0, 2) = 3;
			M_test1(1, 0) = 4; M_test1(1, 1) = 5; M_test1(1, 2) = 6;
			M_test1(2, 0) = 7; M_test1(2, 1) = 8; M_test1(2, 2) = 9;

			M_test2(0, 0) = 1; M_test2(1, 0) = 2; M_test2(2, 0) = 3;
			M_test3(0, 0) = 1; M_test3(0, 1) = 2; M_test3(0, 2) = 3;
			out << M_test3 << "\n"; out << M_test1 << "\n"; out << M_test2 << "\n";

			out.close();
		}

		ifstream in("4.txt");
		if (in)
		{
			int n;
			in >> n;

			Matrix<double>* p = new Matrix<double>[n];
			for (int i = 0; i < n; i++)
			{
				in >> p[i];
				cout << p[i] << endl;
			}

			in.close();
		}


	}
	catch (TooLargeSizeException ex)
	{
		cout << "Too Large Size has been caught "; ex.print();
	}
	catch (NonPositiveSizeException ex)
	{
		cout << "Non Positive Size has been caught "; ex.print();
	}

	catch (IndexOutOfBoundsExeption ex)
	{
		cout << "Index out of bounds has been caught "; ex.print();
	}
	catch (TooSmallException ex)
	{
		cout << "To Small Size of rows has been caught "; ex.print();
	}
	catch (Exception ex)
	{
		cout << "exception has been caught "; ex.print();
	}
	catch (exception ex)
	{
		cout << "exception has been caught "; ex.what();
	}
	catch (...)
	{
		cout << "Something has been caught ";
	}

	return 0;
}

