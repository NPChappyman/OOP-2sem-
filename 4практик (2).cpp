#include <iostream>

using namespace std;

class BaseString
{
protected:
    char* p;
    int len;
    int capacity;
public:
    BaseString(char* ptr)
    {
        //cout<<"\nConstructor\n";
        char* p1 = ptr;
        while (*p1++ != '\0');

        len = p1 - ptr;
        capacity = len + 1 > 256 ? len + 1 : 256;
        p = new char[capacity];

        p1 = ptr; char* p2 = p;
        while ((*p2++ != *p1++) != '\0');

        p[len] = '\0';
    }
    BaseString(const char* ptr)
    {
        //cout<<"\nBase const char Constructor\n";
        int i = 0;
        while (ptr[i] != '\0')
            i++;

        len = i;
        capacity = len + 1 > 256 ? len + 1 : 256;
        p = new char[capacity];
        for (i = 0; ptr[i] != '\0'; i++)
            p[i] = ptr[i];
        p[len] = '\0';

    }

    BaseString(int Capacity = 256)
    {
        cout << "\nBase Constructor 0\n";
        capacity = Capacity;
        p = new char[capacity];
        len = 0;
    }

    ~BaseString()
    {
        //cout<<"\nBase Destructor\n";
        if (p != NULL)
            delete[] p;
        len = 0;
    }

    int Length() { return len; }
    int Capacity() { return capacity; }
    char* get() { return p; }
    char& operator[](int i) { return p[i]; }


    BaseString& operator=(BaseString& s)
    {
        cout << "\nBase Operator = \n";

        if (capacity < s.capacity)
        {
            delete[] p;
            capacity = s.capacity;
            p = new char[s.capacity];
        }
        len = s.len;

        for (char* p1 = s.p, *p2 = p; *p1 != '\0'; *p2++ = *p1++);
        p[len] = '\0';

        return *this;
    }

    BaseString(BaseString& s)
    {
        cout << "\nBase Copy Constructor\n";
        capacity = s.capacity;
        len = s.len;
        p = new char[capacity];
        for (char* p1 = s.p, *p2 = p; *p1 != '\0'; *p2++ = *p1++);
        p[len] = '\0';
    }

    virtual void print()
    {
        int i = 0;
        while (p[i] != '\0')
        {
            cout << p[i];
            i++;
        }
    }
    virtual bool isPalindrome()
    {
        char* p1 = p;
        char* p2 = &p[len - 1];
        while (p2 > p1)
        {
            if (*p1 != *p2) { return false; }
            p2--; p1++;
        }
        return true;

    }
    virtual int IndexOf(char c)
    {
        char* p1 = p;
        while (*p1 != '\0')
        {
            if (*p1 == c)
                return p1 - p;
            p1++;
        }
        return -1;
    }

};


class String : virtual public BaseString
{
protected:

    char tolower(char c)
    {
        return (c >= 'A' && c <= 'Z') ? 'a' + c - 'A' : c;
    }

public:
    String(int Capacity = 256) : BaseString(Capacity) {}
    String(char* s) : BaseString(s) {}
    String(const char* s) : BaseString(s) {}

    String& operator=(const String& s)
    {
        cout << "\nStringBase Operator = \n";
        if (capacity < s.capacity)
        {
            delete[] p;
            capacity = s.capacity;
            p = new char[s.capacity];
        }
        len = 0;
        for (char* p1 = s.p, *p2 = p; *p1 != '\0'; *p2++ = *p1++, len++);
        p[len] = '\0';
        return *this;
    }
    virtual bool isPalindrome()
    {
        cout << "Palindrome from Derived class ";
        char* p1 = p;
        char* p2 = &p[len - 1];
        while (p2 > p1)
        {
            if (tolower(*p1) != tolower(*p2)) { return false; }
            p2--; p1++;
        }
        return true;

    }

    virtual int IndexOf(char c)
    {
        char* p1 = &p[len - 1];
        while (p1 >= p)
        {
            if (*p1 == c)
                return p1 - p;
            p1--;
        }
        return -1;
    }
    String prohod()
    {
        String res(capacity);
        char* pop1 = res.p;
        *pop1++ = *p++;
        res.len = len;
        for (char* p1 = p; *p1 != '\0'; p1++)
        {
            if (*p1 == ' ' && *(p1 - 1) == ' ') { res.len--; }
            else { *pop1++ = *p1; }
        }
        res.p[res.len] = '\0';

        return res;
    }

};

int main()
{
    String t("Today      is              a               good                   day     ! ");

    String ui;
    ui = t.prohod();

    ui.print();

    char c; cin >> c;
    return 0;
}