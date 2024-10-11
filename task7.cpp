// -- AVL TREE --

#include <iostream>
#include <functional>
#include <string>

using namespace std;

class Patient {
protected:
    string lastName;
    string firstName;
    short birthDay;
    short birthMonth;
    short birthYear;
    string phone;
    string address;
    long cardNumber;
    short bloodGroup;
    char rhFactor;

public:
    Patient(string ln, string fn, short bd, short bm, short by, string ph, string ad, long cn, short bg, char rh)
        : lastName(ln), firstName(fn), birthDay(bd), birthMonth(bm), birthYear(by), phone(ph), address(ad), cardNumber(cn), bloodGroup(bg), rhFactor(rh) {}
    Patient(string ln, string fn) : lastName(ln), firstName(fn) {}
    ~Patient() {};
    string get_lastname() const { return lastName; }
    string get_firstname() const { return firstName; }
    string get_phone() const { return phone; }
    string get_address() const { return address; }
    short get_birthday() const { return birthDay; }
    short get_birthmonth() const { return birthMonth; }
    short get_birthyear() const { return birthYear; }
    short get_blood() const { return bloodGroup; }
    long get_card() const { return cardNumber; }
    char get_rhfactor() const { return rhFactor; }

    void set_lastname(string input) { lastName = input; }
    void set_firstname(string input) { firstName = input; }
    void set_phone(string input) { phone = input; }
    void set_address(string input) { address = input; }
    void set_birthday(short input) { birthDay = input; }
    void set_birthmonth(short input) { birthMonth = input; }
    void set_birthyear(short input) { birthYear = input; }
    void set_card(long input) { cardNumber = input; }
    void set_blood(short input) { bloodGroup = input; }
    void set_rhfactor(char input) { rhFactor = input; }

    void print_patient() const 
    {
        cout << "Last Name: " << lastName << endl
             << "First Name: " << firstName << endl
             << "Birth Date: " << birthDay << "-" << birthMonth << "-" << birthYear << endl
             << "Card Number: " << cardNumber << endl
             << "Phone number: " << phone << endl
             << "Address: " << address << endl
             << "Blood group: " << bloodGroup << rhFactor << endl;
    }



    bool operator==(const Patient& p) const
    {
        return lastName == p.lastName && firstName == p.firstName;
    }

    bool operator<(const Patient& p) const 
    {
        if (lastName < p.lastName) return true;
        if (lastName == p.lastName && firstName < p.firstName) return true;
        return false;
    }

    bool operator>(const Patient& p) const 
    {
        return p < *this;
    }

    friend ostream& operator<<(ostream& s, const Patient& p) 
    {
        s << "Last Name: " << p.lastName << endl
          << "First Name: " << p.firstName << endl
          << "Birth Date: " << p.birthDay << "-" << p.birthMonth << "-" << p.birthYear << endl
          << "Card Number: " << p.cardNumber << endl
          << "Phone number: " << p.phone << endl
          << "Address: " << p.address << endl
          << "Blood group: " << p.bloodGroup << p.rhFactor << endl;
        return s;
    }
};


template<class T>
class Node {
protected:
    T data;
    Node* left;
    Node* right;
    Node* parent;
    int height;

public:
    Node(T d) : data(d), left(NULL), right(NULL), parent(NULL), height(1) {}

    T getData() { return data; }
    int getHeight() { return height; }
    Node* getLeft() { return left; }
    Node* getRight() { return right; }
    Node* getParent() { return parent; }

    void setData(T d) { data = d; }
    void setHeight(int h) { height = h; }
    void setLeft(Node* N) { left = N; }
    void setRight(Node* N) { right = N; }
    void setParent(Node* N) { parent = N; }

    Node* Min(Node* current) 
    {
        while (current->getLeft() != NULL)
            current = current->getLeft();
        return current;
    }

    Node* Max(Node* current) 
    {
        while (current->getRight() != NULL)
            current = current->getRight();
        return current;
    }

    Node* successor() 
    {
        if (right != NULL)
            return Min(right);
        Node* current = parent;
        Node* prev = this;
        while (current != NULL && current->getRight() == prev) 
        {
            prev = current;
            current = current->getParent();
        }
        return current;
    }

    Node* predecessor() 
    {
        if (left != NULL)
            return Max(left);
        Node* current = parent;
        Node* prev = this;
        while (current != NULL && current->getLeft() == prev) 
        {
            prev = current;
            current = current->getParent();
        }
        return current;
    }

    void print() 
    {
        cout << data << " ";
    }

    friend ostream& operator<<(ostream& stream, Node<T>& N) 
    {
        stream << "\nNode data: " << N.data << ", height: " << N.height;
        return stream;
    }
};

template<class T>
class Tree 
{
protected:
    Node<T>* root;

public:
    Tree() : root(NULL) {}

    Node<T>* getRoot() { return root; }

    virtual Node<T>* push_R(Node<T>* N) 
    {
        return push_R(N, root);
    }

    virtual Node<T>* push_R(Node<T>* N, Node<T>* Current) 
    {
        if (N == NULL) return NULL;

        if (Current == NULL) Current = root;

        if (root == NULL)
        {
            root = N;
            return root;
        }

        if (Current->getData() > N->getData()) 
        {
            if (Current->getLeft() != NULL) return push_R(N, Current->getLeft());
            else 
            {
                Current->setLeft(N);
                N->setParent(Current);
            }
        } 
        else if (Current->getData() < N->getData()) 
        {
            if (Current->getRight() != NULL) return push_R(N, Current->getRight());
            else 
            {
                Current->setRight(N);
                N->setParent(Current);
            }
        }
        return N;
    }

    virtual Node<T>* push(T value) 
    {
        Node<T>* N = new Node<T>(value);
        return push_R(N);
    }

    virtual void Remove(Node<T>* N) 
    {
        if (N == NULL) return;

        Node<T>* current = root;
        Node<T>* parent = NULL;
        while (current != NULL && current != N) 
        {
            parent = current;
            if (N->getData() < current->getData())
                current = current->getLeft();
            else
                current = current->getRight();
        }

        if (current == NULL) return;

        if (current->getLeft() == NULL && current->getRight() == NULL) 
        {
            if (parent != NULL) {
                if (current == parent->getLeft())
                    parent->setLeft(NULL);
                else
                    parent->setRight(NULL);
            } 
            else 
            {
                root = NULL;
            }
            delete current;
        } 
        else if (current->getLeft() == NULL || current->getRight() == NULL) 
        {
            Node<T>* child = (current->getLeft() != NULL) ? current->getLeft() : current->getRight();
            if (parent != NULL) 
            {
                if (current == parent->getLeft())
                    parent->setLeft(child);
                else
                    parent->setRight(child);
            } 
            else 
            {
                root = child;
            }
            if (child != NULL)
                child->setParent(parent);
            delete current;
        } 
        else 
        {
            Node<T>* successor = current->successor();
            current->setData(successor->getData());
            Remove(successor);
        }
    }

    virtual Node<T>* Min(Node<T>* Current = NULL) 
    {
        if (root == NULL)
            return NULL;

        Node<T>* current = root;

        while (current->getLeft() != NULL)
            current = current->getLeft();

        return current;
    }

    virtual Node<T>* Max(Node<T>* Current = NULL) 
    {
        if (root == NULL)
            return NULL;

        Node<T>* current = root;

        while (current->getRight() != NULL)
            current = current->getRight();

        return current;
    }

    virtual Node<T>* Find(const T& value) 
    {
        if (root == NULL) return NULL;
        return Find_R(value, root);
    }



    // Интерфейс для функции поиска в виде перегрузки операции [].
    Node<T>* operator[](const T& value)
    {
        return Find(value);
    }


    virtual Node<T>* Find_R(const T& value, Node<T>* Current) 
    {
        if (Current == NULL) return NULL;
        if (value == Current->getData()) return Current;
        if (value < Current->getData()) return Find_R(value, Current->getLeft());
        return Find_R(value, Current->getRight());
    }

    virtual void InOrder(Node<T>* Current, const function<void(Node<T>*)>& func) {
        if (Current != NULL) 
        {
            InOrder(Current->getLeft(), func);
            func(Current);
            InOrder(Current->getRight(), func);
        }
    }

    void print() 
    {
        print_(root);
    }

    void print_(Node<T>* node) 
    {
        if (node) 
        {
            print_(node->getLeft());
            cout << node->getData() << endl;
            print_(node->getRight());
        }
    }
};

template<class T>
class AVL_Tree : public Tree<T> 
{
protected:
    int bfactor(Node<T>* p) 
    {
        int hl = 0;
        int hr = 0;
        if (p->getLeft() != NULL)
            hl = p->getLeft()->getHeight();
        if (p->getRight() != NULL)
            hr = p->getRight()->getHeight();
        return (hr - hl);
    }

    void fixHeight(Node<T>* p) 
    {
        int hl = 0;
        int hr = 0;
        if (p->getLeft() != NULL)
            hl = p->getLeft()->getHeight();
        if (p->getRight() != NULL)
            hr = p->getRight()->getHeight();
        p->setHeight((hl > hr ? hl : hr) + 1);
    }

    Node<T>* RotateRight(Node<T>* p) 
    {
        Node<T>* q = p->getLeft();
        p->setLeft(q->getRight());
        q->setRight(p);
        if (p->getParent() != NULL) 
        {
            if (p->getParent()->getLeft() == p)
                p->getParent()->setLeft(q);
            else
                p->getParent()->setRight(q);
        }
        q->setParent(p->getParent());
        p->setParent(q);
        if (p->getLeft() != NULL)
            p->getLeft()->setParent(p);
        fixHeight(p);
        fixHeight(q);
        if (this->root == p)
            this->root = q;
        return q;
    }

    Node<T>* RotateLeft(Node<T>* q) 
    {
        Node<T>* p = q->getRight();
        q->setRight(p->getLeft());
        p->setLeft(q);
        if (q->getParent() != NULL) 
        {
            if (q->getParent()->getLeft() == q)
                q->getParent()->setLeft(p);
            else
                q->getParent()->setRight(p);
        }
        p->setParent(q->getParent());
        q->setParent(p);
        if (q->getRight() != NULL)
            q->getRight()->setParent(q);
        fixHeight(q);
        fixHeight(p);
        if (this->root == q)
            this->root = p;
        return p;
    }

    Node<T>* Balance(Node<T>* p) 
    {
        fixHeight(p);
        if (bfactor(p) == 2) 
        {
            if (bfactor(p->getRight()) < 0)
                p->setRight(RotateRight(p->getRight()));
            return RotateLeft(p);
        }
        if (bfactor(p) == -2) 
        {
            if (bfactor(p->getLeft()) > 0)
                p->setLeft(RotateLeft(p->getLeft()));
            return RotateRight(p);
        }
        return p;
    }

    Node<T>* push_R(Node<T>* N, Node<T>* Current) 
    {
        if (N == NULL)
            return NULL;

        if (Current == NULL)
            Current = this->root;

        if (this->root == NULL) {
            this->root = N;
            return this->root;
        }

        if (Current->getData() > N->getData()) 
        {
            if (Current->getLeft() != NULL)
                return push_R(N, Current->getLeft());
            else 
            {
                Current->setLeft(N);
                N->setParent(Current);
            }
        } else if (Current->getData() < N->getData()) 
        {
            if (Current->getRight() != NULL)
                return push_R(N, Current->getRight());
            else 
            {
                Current->setRight(N);
                N->setParent(Current);
            }
        }

        return Balance(Current);
    }
public:


    // Функция удаления улзла
    void Remove(Node<T>* N) override {
        if (N == NULL)
            return;

        Node<T>* current = this->root;
        Node<T>* parent = NULL;
        while (current != NULL && current != N) 
        {
            parent = current;
            if (N->getData() < current->getData())
                current = current->getLeft();
            else
                current = current->getRight();
        }

        if (current == NULL)
            return;

        if (current->getLeft() == NULL && current->getRight() == NULL) 
        {
            if (parent != NULL) 
            {
                if (current == parent->getLeft())
                    parent->setLeft(NULL);
                else
                    parent->setRight(NULL);
            }
            else 
                this->root = NULL;
            
            delete current;
        } 
        else if (current->getLeft() == NULL || current->getRight() == NULL) 
        {
            Node<T>* child = (current->getLeft() != NULL) ? current->getLeft() : current->getRight();
            if (parent != NULL) 
            {
                if (current == parent->getLeft())
                    parent->setLeft(child);
                else
                    parent->setRight(child);
            }
            else 
                this->root = child;
            if (child != NULL)
                child->setParent(parent);
            delete current;
        } 
        else 
        {
            Node<T>* successor = current->successor();
            current->setData(successor->getData());
            Remove(successor);
        }

        if (parent != NULL)
            Balance(parent);
        else if (this->root != NULL)
            Balance(this->root);
    }
};




int main() {
    AVL_Tree<Patient> patientTree;

    Patient firstPatient("Bublik", "Grisha", 11, 11, 1999, "88005553535", "Moscow, Mirea", 1234567890, 3, '+');
    Patient patient1("Nikolaev", "Pavel", 16, 5, 2003, "89112345678", "Chelyabinsk, Sverdlovsk", 1234567801, 3, '+');
    Patient patient2("Sidorova", "Natalia", 22, 9, 1993, "89123456789", "Vladivostok, Admiral", 1234567802, 1, '-');
    Patient patient3("Zaytsev", "Andrey", 10, 12, 1977, "89134567890", "Perm, Komsolskaya", 1234567803, 4, '+');
    Patient patient4("Kozlova", "Lyudmila", 8, 11, 1989, "89145678901", "Tyumen, Turgenev", 1234567804, 2, '+');
    Patient patient5("Vorobiev", "Oleg", 27, 2, 1982, "89156789012", "Khabarovsk, Muravyov", 1234567805, 3, '-');
    Patient patient6("Kovaleva", "Svetlana", 14, 7, 2006, "89167890123", "Krasnodar, Kubanskaya", 1234567806, 1, '+');
    Patient patient7("Lebedev", "Roman", 11, 1, 1991, "89178901234", "Sochi, Lenin", 1234567807, 2, '-');

    patientTree.push(firstPatient);patientTree.push(patient1);patientTree.push(patient2);patientTree.push(patient3);
    patientTree.push(patient4);patientTree.push(patient5);patientTree.push(patient6);patientTree.push(patient7);

    cout << "Initial tree contents:" << endl << endl;
    patientTree.print();

    patientTree.Remove(patientTree[Patient("Zaytsev", "Andrey")]);
    patientTree.Remove(patientTree[Patient("Nikolaev", "Pavel")]);
    patientTree.Remove(patientTree[Patient("Kozlova", "Lyudmila")]);
    patientTree.Remove(patientTree[Patient("Vorobiev", "Oleg")]);
    patientTree.Remove(patientTree[Patient("Lebedev", "Roman")]);

    
    cout << "\nTree contents after removing patients:" << endl << endl;
    patientTree.print();


    return 0;
}


/* // --- HEAP ---


#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class Patient {
protected:
    string lastName;
    string firstName;
    short birthDay;
    short birthMonth;
    short birthYear;
    string phone;
    string address;
    long cardNumber;
    short bloodGroup;
    char rhFactor;

public:
    Patient() 
        : lastName(""), firstName(""), birthDay(0), birthMonth(0), birthYear(0), phone(""), address(""), cardNumber(0), bloodGroup(0), rhFactor(' ') {}
    Patient(string ln, string fn, short bd, short bm, short by, string ph, string ad, long cn, short bg, char rh)
        : lastName(ln), firstName(fn), birthDay(bd), birthMonth(bm), birthYear(by), phone(ph), address(ad), cardNumber(cn), bloodGroup(bg), rhFactor(rh) {}
    
    ~Patient() {};
    string get_lastname() const { return lastName; }
    string get_firstname() const { return firstName; }
    string get_phone() const { return phone; }
    string get_address() const { return address; }
    short get_birthday() const { return birthDay; }
    short get_birthmonth() const { return birthMonth; }
    short get_birthyear() const { return birthYear; }
    short get_blood() const { return bloodGroup; }
    long get_card() const { return cardNumber; }
    char get_rhfactor() const { return rhFactor; }

    void set_lastname(string input) { lastName = input; }
    void set_firstname(string input) { firstName = input; }
    void set_phone(string input) { phone = input; }
    void set_address(string input) { address = input; }
    void set_birthday(short input) { birthDay = input; }
    void set_birthmonth(short input) { birthMonth = input; }
    void set_birthyear(short input) { birthYear = input; }
    void set_card(long input) { cardNumber = input; }
    void set_blood(short input) { bloodGroup = input; }
    void set_rhfactor(char input) { rhFactor = input; }

    void print_patient() const 
    {
        cout << "Last Name: " << lastName << endl
             << "First Name: " << firstName << endl
             << "Birth Date: " << birthDay << "-" << birthMonth << "-" << birthYear << endl
             << "Card Number: " << cardNumber << endl
             << "Phone number: " << phone << endl
             << "Address: " << address << endl
             << "Blood group: " << bloodGroup << rhFactor << endl;
    }



    bool operator==(const Patient& p) const
    {
        return lastName == p.lastName && firstName == p.firstName;
    }

    bool operator<(const Patient& p) const {
        if (cardNumber < p.cardNumber) return true;
        if (cardNumber == p.cardNumber && bloodGroup < p.bloodGroup) return true;
        if (cardNumber == p.cardNumber && bloodGroup == p.bloodGroup && lastName < p.lastName) return true;
        if (cardNumber == p.cardNumber && bloodGroup == p.bloodGroup && lastName == p.lastName && firstName < p.firstName) return true;
        return false;
    }

    bool operator>(const Patient& p) const 
    {
        return p < *this;
    }

    friend ostream& operator<<(ostream& s, const Patient& p) 
    {
        s << "Last Name: " << p.lastName << endl
          << "First Name: " << p.firstName << endl
          << "Birth Date: " << p.birthDay << "-" << p.birthMonth << "-" << p.birthYear << endl
          << "Card Number: " << p.cardNumber << endl
          << "Phone number: " << p.phone << endl
          << "Address: " << p.address << endl
          << "Blood group: " << p.bloodGroup << p.rhFactor << endl;
        return s;
    }
};

template <class T>
class Heap
{
private:
    T* arr;
    int len;
    int size;

    
    void Heapify(int index = 0)
    {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largestChild = index;

        if (leftChild < len && arr[leftChild] > arr[largestChild]) 
            largestChild = leftChild;

        if (rightChild < len && arr[rightChild] > arr[largestChild]) 
            largestChild = rightChild;

        if (largestChild != index) 
        {
            Swap(index, largestChild);
            Heapify(largestChild);
        }

    }

    void SiftUp(int index = -1)
    {
        if (index == -1)
            index = len - 1;
        int parent = GetParentIndex(index);
        while (index > 0 && arr[parent] < arr[index]) 
        {
            Swap(parent, index);
            index = parent;
            parent = GetParentIndex(index);
        }
    }
public:

    
    Heap<T>(int MemorySize = 100)
    {
        arr = new T[MemorySize];
        len = 0;
        size = MemorySize;
    }
    ~Heap() 
    {
        delete[] arr;
    }

    
    int getCapacity() { return size; }
    int getCount() { return len; }

    T& operator[](int index)
    {
        if (index < 0 || index > len)
            throw out_of_range("Index out of range");

        return arr[index];
    }


    void Swap(int index1, int index2)
    {   
        T temp = arr[index1];
        arr[index1] = arr[index2];
        arr[index2] = temp;
    }

    
    int GetLeftChildIndex(int index)
    {
        if (index < 0 || index * 2 > len)
            throw out_of_range("Index out of range");;

        return (index << 1) + 1;
    }

    int GetRightChildIndex(int index)
    {
        if (index < 0 || index * 2 > len)
            throw out_of_range("Index out of range");;

        return (index << 1) + 2;
    }

    int GetParentIndex(int index)
    {
        if (index < 0 || index > len)
            throw out_of_range("Index out of range");

        return (index - 1) >> 1;
    }


    void push(T v)
    {
        if (len > size)
            throw overflow_error("Heap is full");

        arr[len] = v;
        len++;
        SiftUp(len - 1);
    }

    
    T ExtractMax()
    {
        if (len == 0)
            throw underflow_error("Heap is empty");
        T res = arr[0];
        Swap(0,len - 1);
        len--;
        Heapify();
        return res;
    }

    void Remove(int index)
    {
        if (index < 0 || index >= len)
            throw out_of_range("Index out of range");
        Swap(index, len - 1);
        len--;

        if (index > 0 && arr[index] > arr[GetParentIndex(index)]) 
            SiftUp(index);
        else 
            Heapify(index); 

    }



    void print()
    {
        for (int i = 0; i < len; i++)
        {
            cout << arr[i];
            cout << endl;
        }
    cout << endl;
    }

    
};


int main()
{
    Patient firstPatient("Bublik", "Grisha", 11, 11, 1999, "88005553535", "Moscow, Mirea", 1234567890, 3, '+');
    Patient patient1("Nikolaev", "Pavel", 16, 5, 2003, "89112345678", "Chelyabinsk, Sverdlovsk", 1234567801, 3, '+');
    Patient patient2("Sidorova", "Natalia", 22, 9, 1993, "89123456789", "Vladivostok, Admiral", 1234567802, 1, '-');
    Patient patient3("Zaytsev", "Andrey", 10, 12, 1977, "89134567890", "Perm, Komsolskaya", 1234567803, 4, '+');
    Patient patient4("Kozlova", "Lyudmila", 8, 11, 1989, "89145678901", "Tyumen, Turgenev", 1234567804, 2, '+');
    Patient patient5("Vorobiev", "Oleg", 27, 2, 1982, "89156789012", "Khabarovsk, Muravyov", 1234567805, 3, '-');
    Patient patient6("Kovaleva", "Svetlana", 14, 7, 2006, "89167890123", "Krasnodar, Kubanskaya", 1234567806, 1, '+');
    Patient patient7("Lebedev", "Roman", 11, 1, 1991, "89178901234", "Sochi, Lenin", 1234567807, 2, '-');


    Heap<Patient> patientHeap;
    patientHeap.push(firstPatient);patientHeap.push(patient1);patientHeap.push(patient2);patientHeap.push(patient3);
    patientHeap.push(patient4);patientHeap.push(patient5);patientHeap.push(patient6);patientHeap.push(patient7);
    patientHeap.print();

    cout << "Patients after removal:" << endl << endl;
    patientHeap.Remove(1);patientHeap.Remove(1);
    patientHeap.Remove(1);patientHeap.Remove(1);
    patientHeap.print();
    cout << endl;

    cout << "Extracted Max Element: " << endl<< endl;
    Patient maxPatient = patientHeap.ExtractMax();
    cout << maxPatient << endl;
    return 0;
}

*/