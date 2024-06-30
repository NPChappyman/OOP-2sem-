#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
class Team
{
protected:
    string Name;
    string city;
    int win;
    int loose;
    int drawn;
    int points;

public:
    void set_name(string v) { Name = v; }
    void set_city(string v) { city = v; }
    void set_win(int v) { win = v; }
    void set_loose(int v) { loose = v; }
    void set_drawn(int  v) { drawn = v; }
    void set_points(int v) { points = v; }
    string get_name() { return Name; }
    string get_city() { return city; }
    int get_win() { return win; }
    int get_loose() { return loose; }
    int get_drawn() { return drawn; }
    int get_points() { return points; }

    Team(string N = " ", string C = " ", int w = 0, int l = 0, int d = 0, int p = 0) { Name = N; city = C; win = w; loose = l; drawn = d; points = p; }
    ~Team() {}

    void info()
    {
        cout << "Name: " << Name << endl << "City: " << city << endl << "Win: " << win << endl << "Loose: " << loose << endl << "Drawn games: " << drawn << endl << "points " << points << endl;
    }

    friend ostream& operator<<(ostream& s, Team& value);
    friend ofstream& operator<<(ofstream& s, Team& value);
};


ostream& operator<<(ostream& s, Team& value)
{
    s << "Name: " << value.Name << endl << "City: " << value.city << endl << "Win: " << value.win << endl << "Loose: " << value.loose << endl << "Drawn games: " << value.drawn << endl << "points " << value.points << endl;
    return s;
}


ofstream& operator<<(ofstream& f, Team& value)
{
    f << "Name: " << value.Name << endl << "City: " << value.city << endl << "Win: " << value.win << endl << "Loose: " << value.loose << endl << "Drawn games: " << value.drawn << endl << "points " << value.points << endl;
    return f;
}


template<class T>
class Element
{
protected:
    Element* next;
    Element* prev;
    T info;
    void f() {}
public:
    Element* get_next() { return next; }
    Element* get_prev() { return prev; }
    T get_info() { return info; }

    void set_next(Element* value) { next = value; }
    void set_prev(Element* value) { prev = value; }
    void set_info(T value) { info = value; }

    Element(T data)
    {
        next = prev = NULL;
        info = data;
    }

    Element(Element* Next, Element* Prev, T data)
    {
        next = Next;
        prev = Prev;
        info = data;
    }

    Element(const Element& el)
    {
        next = el.next;
        prev = el.prev;
        info = el.info;
    }

    virtual ~Element() {}

    template<class T1>
    friend ostream& operator<<(ostream& s, Element<T1>& el);
    template<class T1>
    friend istream& operator>>(istream& s, Element<T1>& el);

};

template<class T1>
ostream& operator<<(ostream& s, Element<T1>& el)
{
    s << el.info;
    return s;
}


template<class T1>
istream& operator>>(istream& s, Element<T1>& el)
{
    s >> el.info;
    return s;
}

template<class T>
class LinkedList
{
protected:
    Element<T>* head;
    Element<T>* tail;
    int count;

public:

    Element<T>* get_head() { return head; }
    Element<T>* get_tail() { return tail; }
    int get_count() { return count; }

    void set_head(Element<T>* value) { head = value; }
    void set_tail(Element<T>* value) { tail = value; }
    void set_count(int value) { count = value; }

    LinkedList()
    {
        head = tail = NULL;
        count = 0;
    }

    virtual Element<T>* front(T value) { return head; }
    virtual Element<T>* back(T value) { return tail; }

    virtual Element<T>& operator[](int index) {
        Element<T>* Current = head;

        for (int i = 0; i < index && Current != NULL; Current = Current->get_next(), i++);
        return *Current;
    }


    void save(ofstream& file)
    {
        if (file)
        {
            Element<T>* current = head;
            while (current != NULL)
            {
                file << *current << " ";
                current = current->get_next();
            }
        }
    }


    void load(ifstream& file)
    {
        T info;
        while (file >> info)
        {
            Element<T>* newElement = new Element<T>(info);
            if (!head)
                head = tail = newElement;
            else
            {
                tail->set_next(newElement);
                tail = newElement;
            }
            count++;
        }
    }


    virtual ~LinkedList()
    {
        Element<T>* current = head;
        while (current != NULL) {
            Element<T>* next = current->get_next();
            delete current;
            current = next;
        }
        head = NULL;
        tail = NULL;
    }



    template<class T1>
    friend ostream& operator<<(ostream& s, LinkedList<T1>& el);
};


template<class T1>
ostream& operator<<(ostream& s, LinkedList<T1>& list)
{

    for (Element<T1>* Current = list.head; Current != NULL; Current = Current->get_next())
    {
        s << *Current << "; ";
    }

    return s;
}

template<class T>
class Stack : virtual public LinkedList<T>
{
public:

    Stack() :LinkedList<T>() {}
    virtual ~Stack() {}

    Element<T>* push(T value)
    {
        Element<T>* newElem = new Element<T>(value);
        if (LinkedList<T>::tail != NULL)
            LinkedList<T>::tail->set_next(newElem);
        else
            LinkedList<T>::head = newElem;
        LinkedList<T>::tail = newElem;
        LinkedList<T>::count++;
        return LinkedList<T>::tail;
    }


    Element<T>* pop()
    {
        if (LinkedList<T>::tail == NULL)
            return NULL;

        Element<T>* Res = LinkedList<T>::tail;
        if (LinkedList<T>::head == LinkedList<T>::tail) // 1 'k'
        {
            LinkedList<T>::head = LinkedList<T>::tail = NULL;
            return Res;
        }


        Element<T>* Current = LinkedList<T>::head;
        for (; Current->get_next() != LinkedList<T>::tail; Current = Current->get_next());
        Current->set_next(NULL);
        LinkedList<T>::tail = Current;
        LinkedList<T>::count--;
        return Res;
    }

    virtual Element<T>* insert(T value, Element<T>* previous = NULL)
    {
        if (previous == NULL)
            return push(value);

        Element<T>* inserted = new Element<T>(value);
        inserted->set_next(previous->get_next());
        previous->set_next(inserted);
        LinkedList<T>::count++;
        return inserted;
    }

};

template<class T>
class Queue : virtual public LinkedList<T>
{
public:
    Queue() :LinkedList<T>() {}
    virtual ~Queue() {}

    Element<T>* push(T value)
    {
        Element<T>* newElem = new Element<T>(value);
        if (LinkedList<T>::tail != NULL)
            LinkedList<T>::tail->set_next(newElem);
        else
            LinkedList<T>::head = newElem;
        LinkedList<T>::tail = newElem;
        LinkedList<T>::count++;
        return LinkedList<T>::tail;
    }


    Element<T>* pop()
    {
        if (LinkedList<T>::tail == NULL)
            return NULL;

        Element<T>* Res = LinkedList<T>::head;
        if (LinkedList<T>::head == LinkedList<T>::tail)
        {
            LinkedList<T>::head = LinkedList<T>::tail = NULL;
            return Res;
        }

        LinkedList<T>::head = Res->get_next();
        Res->set_next(NULL);
        LinkedList<T>::count--;
        return Res;
    }

    virtual Element<T>* insert(T value, Element<T>* previous = NULL)
    {
        if (previous == NULL)
            return push(value);
        Element<T>* inserted = new Element<T>(value);
        inserted->set_next(previous->get_next());
        previous->set_next(inserted);
        LinkedList<T>::count++;
        return inserted;
    }

};

template<class T>
class StackQueue : virtual protected Stack<T>, virtual protected Queue<T>
{
public:
    StackQueue() : Stack<T>(), Queue<T>() {}
    virtual ~StackQueue() {}
    virtual Element<T>* push_back(T value) { return Stack<T>::push(value); }
    virtual Element<T>* pop_back() { return Stack<T>::pop(); }
    virtual Element<T>* pop_front() { return Queue<T>::pop(); }
    virtual Element<T>* push_front(T value)
    {
        Element<T>* newElem = new Element<T>(value);
        if (LinkedList<T>::head != NULL)
            newElem->set_next(LinkedList<T>::head);
        else
            LinkedList<T>::tail = newElem;
        LinkedList<T>::head = newElem;
        LinkedList<T>::count++;
        return LinkedList<T>::tail;
    }
};


template<class T>
class DoubleLinkedStack : virtual protected Stack<T>
{
public:
    DoubleLinkedStack() :Stack<T>() {}
    ~DoubleLinkedStack() {}

    Element<T>* push(T value)
    {
        Element<T>* old_tail = LinkedList<T>::tail;
        Stack<T>::push(value);
        LinkedList<T>::tail->set_prev(old_tail);
        return LinkedList<T>::tail;
    }

    Element<T>* insert(T value, Element<T>* previous = NULL)
    {
        if (previous == NULL || previous == LinkedList<T>::tail) return push(value);
        Stack<T>::insert(value, previous);
        previous->get_next()->set_prev(previous);
        previous->get_next()->get_next()->set_prev(previous->get_next());
        return previous->get_next();
    }

    Element<T>* remove(Element<T>* current = NULL)
    {
        if (current == NULL || current == LinkedList<T>::tail) return NULL;
        current->get_next()->set_prev(current->get_prev());
        current->get_prev()->set_next(current->get_next());
        return current;
    }

    Element<T>* pop()
    {
        if (LinkedList<T>::tail == NULL || LinkedList<T>::tail == LinkedList<T>::head)
            return Stack<T>::pop();
        Element<T>* res = LinkedList<T>::tail;
        LinkedList<T>::tail = LinkedList<T>::tail->get_prev();
        LinkedList<T>::tail->get_next()->set_prev(NULL);
        LinkedList<T>::tail->set_next(NULL);
        LinkedList<T>::count--;
        return res;
    }

    virtual Element<T>& operator[](int index) {
        return LinkedList<T>(*this)[index];
    }

    Element<T> find(T value)
    {
        Element<T> ans;
        for (Element<T>* current = LinkedList<T>::head; current != NULL; current = current->get_next())
            if (current->get_info() == value)
                ans.push(current);

        return ans;
    }

    template<class T1>
    friend ostream& operator <<(ostream& s, DoubleLinkedStack<T1>& list);

};


template<class T1>
ostream& operator <<(ostream& s, DoubleLinkedStack<T1>& list)
{
    for (Element<T1>* Current = list.get_tail(); Current != NULL; Current = Current->get_prev())
        s << *Current << "; ";
    return s;

}

template<class T>
class NewDoubleLinked : virtual protected DoubleLinkedStack<T>
{
public:
    NewDoubleLinked() :DoubleLinkedStack<T>() {}
    virtual ~NewDoubleLinked() {}

    // Конструктор копий
    NewDoubleLinked(NewDoubleLinked& list)
    {
        cout << "Copy" << endl;
        Element<T>* current = list.get_head();

        while (current != NULL)
        {
            this->push(current->get_info());
            current = current->get_next();
        }

    }

    Element<T>* push(T value)
    {
        Element<T>* newElem = new Element<T>(value);
        if (LinkedList<T>::head != NULL)
        {
            LinkedList<T>::head->set_prev(newElem);
            newElem->set_next(LinkedList<T>::head);
        }
        else
            LinkedList<T>::tail = newElem;
        LinkedList<T>::head = newElem;
        LinkedList<T>::head->set_prev(NULL);
        LinkedList<T>::count++;
        return LinkedList<T>::head;
    }



    Element<T>* pop()
    {
        if (LinkedList<T>::tail == NULL)
            return NULL;

        Element<T>* Res = LinkedList<T>::head;
        if (LinkedList<T>::head == LinkedList<T>::tail)
        {
            LinkedList<T>::head = LinkedList<T>::tail = NULL;
            return Res;
        }

        LinkedList<T>::head = Res->get_next();
        Res->set_next(NULL);
        LinkedList<T>::head->set_prev(NULL);
        LinkedList<T>::count--;
        return LinkedList<T>::head;
    }

    //Element<T>* find(string value) 
    //{
    //    for (Element<T>* current = LinkedList<T>::head; current != NULL; current = current->get_next())
    //    	if (current->get_info().get_name() == value)	
    //    	    return current;
    //
    //   	return NULL;
    //}


    // Рекурсивная функция поиска
    Element<T>* find(string value, Element<T>* current = nullptr)
    {
        if (current == nullptr)
            current = LinkedList<T>::get_head();
        if (current == nullptr)
            return nullptr;
        return ((value == current->get_info().get_name()) ? current : find(value, current->get_next()));
    }

    Element<T>* find_by_function(bool (*func)(T))
    {
        for (Element<T>* current = LinkedList<T>::head; current != nullptr; current = current->get_next())

            if (func(current->get_info()))
                return current;
        return NULL;
    }



    NewDoubleLinked<T> filter(bool (*func)(T)) {
        NewDoubleLinked result;
        for (Element<T>* current = LinkedList<T>::head; current != nullptr; current = current->get_next())
            if (func(current->get_info()))
                result.push(current->get_info());


        return result;
    }

    void recursiveFilter(Element<T>* current, bool (*func)(T), NewDoubleLinked& result) {
        if (current == nullptr) return;
        if (func(current->get_info()))
            result.push(current->get_info());

        recursiveFilter(current->get_next(), func, result);
    }
    NewDoubleLinked<T> filter_rerursion(bool (*func)(T)) {
        NewDoubleLinked result;
        recursiveFilter(this->get_head(), func, result);
        return result;
    }

    void save(ofstream& file)
    {
        this->save(file);
    }

    template<class T1>
    friend ostream& operator <<(ostream& s, NewDoubleLinked<T1>& list);

};


// Функции сравнения
bool is_team_winning(Team state) {
    return state.get_win() >= 100;
}

bool is_team_loose(Team state) {
    return state.get_loose() >= 100;
}

bool is_team_spartack(Team state) {
    return state.get_name() == "Spartack";
}




template<class T1>
ostream& operator <<(ostream& s, NewDoubleLinked<T1>& list)
{
    for (Element<T1>* Current = list.get_head(); Current != NULL; Current = Current->get_next())
        s << *Current << "---------------" << endl;

    return s;
}


//Вывод в 16-ричной системе счисления, не более 3 знаков после запятой 
ostream& custom_format(ostream& os) {
    os.unsetf(ios::dec);
    os.setf(ios::hex);

    os << setprecision(3);

    return os;
}


int main()
{

    NewDoubleLinked<int> integer;
    integer.push(1); integer.push(2); integer.push(3); integer.push(4);
    cout << integer;


    NewDoubleLinked<int> integer2 = integer;
    cout << endl << integer2;
    integer.pop();
    cout << endl << integer;
    cout << endl << integer2;


    NewDoubleLinked<Team> football;
    Team Spartack("Spartack", "Moscow", 12, 122, 12, 100);
    Team Lokomotiv("Lokomotiv", "Kazan", 1223, 1212, 1322, 1011330);
    Team CSKA("CSKA", "Moscow", 11, 12, 1, 10210);
    Team Zenit("Zenit", "Sankt peterburg", 1212, 1323, 1323, 1313);
    Team Rubin("Rubin", "Krasnodar", 123, 113222, 1312, 113200);
    Team Ahmat("Ahmat", "Grozny", 1212, 12, 2, 13100);

    football.push(Spartack); football.push(Lokomotiv); football.push(CSKA); football.push(Zenit);  football.push(Rubin);
    football.push(Ahmat);



    cout << "Teams " << endl << football << endl << endl;

    // Использование функции find
    cout << "Team with name CSKA: " << endl << *football.find("CSKA") << endl << endl;



    NewDoubleLinked<Team> teams_winning = football.filter(&is_team_winning);
    cout << "Teams with more than 100 victories :" << endl << teams_winning << endl;

    NewDoubleLinked<Team> team_is_spartack = football.filter_rerursion(&is_team_spartack);
    cout << "Team with name Spartack :" << endl << team_is_spartack << endl;

    Stack<int> st;
    for (int i = 7; i < 17; i++)
        st.push(i + 1);
    cout << "Stack " << st << endl;
    Element<int>* a = st.pop();
    st.insert(777, &st[2]);
    cout << "Stack " << st << endl << endl;

    LinkedList<int>* p_base;
    Stack<int> d;
    p_base = &d;
    if (typeid(*p_base) == typeid(Stack<int>))
    {
        Stack<int>* d_ptr = dynamic_cast<Stack<int>*>(p_base);
        cout << "ptr " << d_ptr->get_head() << endl;

    }
    ofstream f("8.txt");
    st.save(f);
    f.close();


    ifstream fin("8.txt");
    Queue<int> queue;
    queue.load(fin);
    cout << "Queue from file " << queue << endl << endl;

    Queue<int> q;
    q.push(16.16); q.push(17); q.push(323);  q.push(16); q.push(1235.3234); q.push(100);
    cout << "Queue with hex numbers with 3 decimal places " << custom_format << q << endl;


    return 0;
}



