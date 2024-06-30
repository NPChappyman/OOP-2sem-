#include <iostream>
using namespace std;

class MyArrayParent
{
protected:
	//сколько памяти выделено?
	int capacity;
	//количество элементов - сколько памяти используем
	int count;
	//массив
	double* ptr;
public:
	//конструкторы и деструктор
	MyArrayParent(int Dimension = 100)
	{
		cout << "\nMyArrayParent constructor" << endl;
		ptr = new double[Dimension];
		capacity = Dimension;
		count = 0;
	}
	//конструктор принимает существующий массив
	MyArrayParent(double* arr, int len)
	{
		cout << "\nMyArrayParent constructor";
		//заполнить массив ptr, заполнить поля
		ptr = new double[len];
		if (len > 0)
		{
			for (int i = 0; i < len; i++)
				ptr[i] = arr[i];
		}
		capacity = len;
		count = len;
	}
	//деструктор
	~MyArrayParent()
	{
		cout << "\nMyArrayParent destructor";
		//освободить память, выделенную под ptr

		if (ptr != NULL)
		{
			delete[] ptr;
			ptr = NULL;
		}
	}
	//обращение к полям
	int Capacity() { return capacity; }
	int Size() { return count; }
	double GetComponent(int index)
	{
		if (index >= 0 && index < count)
			return ptr[index];
		//сгенерировать исключение, если индекс неправильный
		return -1;
	}
	void SetComponent(int index, double value)
	{
		if (index >= 0 && index < count)
			ptr[index] = value;
		else
		{
			cout << "error";
		}
		//сгенерировать исключение, если индекс неправильный
	}

	//добавление в конец нового значения
	void push(double value)
	{
		if (count < capacity)
		{
			ptr[count++] = value;
			//count++;
		}
	}

	//удаление элемента с конца
	void RemoveLastValue()
	{
		if (count >= 0)
			count--;

		//что делаем, если пуст?
	}

	double& operator[](int index)
	{
		return ptr[index];
		//перегрузка оператора []
	}

	MyArrayParent& operator=(const MyArrayParent& V)
	{
		cout << "\noperator = ";
		if (capacity < V.capacity)
		{
			delete[] ptr;
			ptr = new double[V.capacity];
			capacity = V.capacity;
		}
		count = V.count;

		for (int i = 0; i < count; i++)
			ptr[i] = V.ptr[i];

		return *this;

		//оператор =
		//arr1 = arr2 = arr3; где arr_i - объекты нашего класса
	}

	MyArrayParent(const MyArrayParent& V)
	{
		cout << "\nCopy constructor";
		capacity = V.capacity;
		count = V.count;
		ptr = new double[capacity];

		for (int i = 0; i < count; i++)
			ptr[i] = V.ptr[i];
		//создание копии объекта - в основном, при возвращении результата из функции / передаче параметров в функцию
	}
	int IndexOf(double value, bool bFindFromStart = true)
	{
		if (bFindFromStart)
		{
			for (int i = 0; i < count; i++)
				if (abs(value - ptr[i]) < 0.0001)
					return i;
			return -1;
		}
		for (int i = count; i > 0; i--)
			if (abs(value - ptr[i]) < 0.0001)
				return i;
		return -1;
	}
	void print()
	{
		cout << "\nMyArrParent, size: " << count << ", values: {";
		int i = 0;
		for (i = 0; i < count; i++)
		{
			cout << ptr[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "}";
	}

};

class MyArrayChild : public MyArrayParent
{
public:
	//используем конструктор родителя. Нужно ли что-то ещё?
	MyArrayChild(int Dimension = 100) : MyArrayParent(Dimension) { cout << "\nMyArrayChild constructor"; }
	MyArrayChild(double* arr, int len) : MyArrayParent(arr, len) {}
	~MyArrayChild() { cout << "\nMyArrayChild destructor\n"; }

	//удаление элемента
	void RemoveAt(int index = -1)
	{
		if (index == -1) { RemoveLastValue(); return; }
		if (index < 0 || index >= count || count == 0) return;

		for (int i = index; i < count; i++)
			ptr[i] = ptr[i + 1];
		count--;

	}
	//вставка элемента
	// 
	void InsertAt(double value, int index = -1)
	{
		if (index == -1) { push(value); return; }
		if (index < 0 || index >= count || count >= capacity) return;

		for (int i = count - 1; i >= index; i--)
			ptr[i + 1] = ptr[i];
		ptr[index] = value;
		count++;
	}


	//выделение подпоследовательности
	MyArrayChild SubSequence(int StartIndex = 0, int Length = -1)
	{
		MyArrayChild res;
		for (int i = 0; i < Length && i+StartIndex<count; i++)
			res.push(ptr[i + StartIndex]);
		return res;

	}
	//добавление элемента в конец
	//operator + ?
	MyArrayChild operator +(double value)
	{
		MyArrayChild res;
		res.push(value);
		return res;
	}

	MyArrayChild permutation()
	{
		int mid = count / 2;
		int i = 0;
		int end = count - 1;
		MyArrayChild res(*this);

		while (end >= mid && i <= mid)
		{
			if ((int(ptr[i])) % 2 == (int(ptr[end])) % 2)
			{

				double tmpt = res[i];
				res[i] = res[end];
				res[end] = tmpt;
			}
			end--; i++;
		}
		return res;
	}
};

class MySortedArray : public MyArrayChild
{
public:

	MySortedArray(int Dimension = 100) : MyArrayChild(Dimension) { cout << "\nMySortedArray constructor"; }

	MySortedArray(double* arr, int len) : MyArrayChild(arr, len) {}

	~MySortedArray() { cout << "\nMySortedArray destructor\n"; }

	MySortedArray permutation()
	{
		int mid = count / 2;
		int i = 0;
		int end = count - 1;
		MySortedArray res(*this);

		while (end >= mid && i <= mid)
		{
			if ((int(ptr[i])) % 2 == (int(ptr[end])) % 2)
			{

				double tmpt = res[i];
				res[i] = res[end];
				res[end] = tmpt;
			}
			end--; i++;
		}
		return res;
	}

	int BinS(double value, int left, int right)
	{
		while (left <= right)
		{
			int middle = (left + right) / 2;
			if (abs(ptr[middle] - value) < 0.0001)
				return middle;
			if (ptr[middle] > value)
				right = middle - 1;
			if (ptr[middle] > value)
				left = middle + 1;
		}
		return -1;
	}
	int BinS2(double value, int left, int right) 
	{
		while (left <= right)
		{
			int middle = (left + right) / 2;

			if (abs(ptr[middle] - value) < 0.0001)
				return middle;

			if (ptr[middle] > value)
				right = middle - 1;
			else
				left = middle + 1;
		}

		if (ptr[right] < value)
			return right + 1;
		else
			return right;
	}

	int BinSearch(double value, int left, int right)
	{
		int middle = (left + right) / 2;
		if (abs(ptr[middle] - value) < 0.0001) return middle; // base
		if (right == left + 1) return (abs(ptr[right] - value) < 0.0001) ? right : -1;

		if (ptr[middle] > value)
			return BinSearch(value, left, middle);
		if (ptr[middle] < value)
			return BinSearch(value, middle, right);
	}

	int BinSearch2(double value, int left, int right)
	{
		int middle = (left + right) / 2;
		if (fabs(ptr[middle] - value) < 0.0001) return middle; // base
		if (right == left + 1)
		{
			if (abs(ptr[right] - value) < 0.001) return right;
			if (ptr[left]<value && ptr[right]>value) return right;
			if (ptr[right] < value) return right + 1;
			if (ptr[left] > value) return left;
		}

		if (ptr[middle] > value) return BinSearch2(value, left, middle);
		if (ptr[middle] < value) return BinSearch2(value, middle, right);
	}


	void push(double value) // Добавление с использованием итеративного бинарного поиска 
	{
		if (count >= capacity) return;
		if (count == 0) { MyArrayParent::push(value); return; }
		if (ptr[count - 1] < value) { MyArrayParent::push(value); return; }
		if (count == 1)
		{
			if (ptr[0] > value)
				InsertAt(value, 0);
			else
				MyArrayParent::push(value);
			return;
		}
		int index = BinS2(value, 0, count - 1); 
		InsertAt(value, index);

	}

	int IndexOf(double value, bool bFindFromStart = true)
	{
		int index = BinS(value, 0, count - 1);
		if (bFindFromStart && index != -1) { return index; }
		else if (bFindFromStart == 0 && index != -1) { return (count - index ); }
		return -1;
	}

};
int main()
{
	if (true)
	{
		double a[] = { 4,2,6,16,10,110,11 };
		MyArrayChild arr(a, 7);
		arr.print();

		MyArrayChild h = arr.permutation();
		h.print();

		MySortedArray ty;
		for (int i = 0; i < 10; i++) ty.push(i + 17);
		ty.InsertAt(777, 2);
		ty.print();
		ty.RemoveAt(2);
		ty.print();

		MySortedArray t(12);
		t.push(77);
		t.push(101);
		t.push(10);
		t.push(2);
		t.push(10000);
		t.push(10010);
		t.print();
		MySortedArray tt = t.permutation();
		tt.print();
		
		cout << endl << tt.IndexOf(101, true) << " " << tt.IndexOf(101,false);
		cout << "\n";
		cout << "\n\nSubSequence: "; tt.SubSequence(2, 4).print();

		cout << endl << arr.IndexOf(10, true) << " " << arr.IndexOf(10);
		cout << "\n";
	}
	char c; cin >> c;
	return 0;
}
