#include "MyString.h"


int power(int base, int pwr)
{
    int result = 1;

    if (pwr == 0)
        return 1;

    else
    {
        for (int i = 0; i < pwr; i++)
            result *= base;
    }

    return result;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
    if (lhs.size() != rhs.size())
        return false;

    int size = lhs.size();

    for (int i = 0; i < size; i++)
        if (lhs[i] != rhs[i])
            return false;

    return true;
}

int compare(const MyString& lhs, const MyString& rhs)
{
    return strcmp(lhs.cstr(), rhs.cstr());
}


void MyString::copy(const char* str)
{
    if (!str)
        length = 0;
    else
        length = strlen(str);

    this->str = new(nothrow) char[length + 1];

    if (!this->str)
    {
        cout << "Problem with memory!\n";
        return;
    }

    strcpy(this->str, str);
}

void MyString::erase()
{
    delete[] str;
}

MyString::MyString()
{
    copy("\0");
}

MyString::MyString(const char* s)
{
    copy(s);
}

MyString::MyString(const MyString& other) 
{
    copy(other.str);
}

MyString::MyString(MyString&& other) noexcept : str(other.str), length(other.length)
{
    other.copy("\0");
}

MyString::~MyString()
{
    erase();
}

MyString& MyString::operator=(const MyString& other)
{
    if (this != &other) 
    {
        erase();
        copy(other.str);
    }

    return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
    if (this != &other)
    {
        erase();
        str = other.str;
        length = other.length;
        other.copy("\0");
    }

    return *this;
}

MyString MyString::operator+(const MyString& other) const
{
    MyString result;
    result.length = length + other.length;
    result.str = new(nothrow) char[result.length + 1];

    if (!result.str)
    {
        cout << "Problem with memory!\n";
        return nullptr;
    }

    strcpy(result.str, str);
    strcat(result.str, other.str);

    return result;
}

MyString MyString::operator+(const char* other) const
{
    int otherLength = 0;

    if (other)
        otherLength = strlen(other);

    MyString result;

    result.length = length + otherLength;

    result.str = new(nothrow) char[result.length + 1];

    if (!result.str)
    {
        cout << "Problem with memory!\n";
        return nullptr;
    }

    strcpy(result.str, str);

    if (other != nullptr) {
        strcat(result.str, other);
    }

    return result;
}

char& MyString::operator[](int index)
{
    if (index < 0 || index >= length) 
        throw out_of_range("Index out of range");

    return str[index];
}

bool MyString::toInt(int& result)const
{
    result = 0;
    int counter = 0;

    for (int i = length - 1; i >= 0; i--, counter++)
    {
        if (str[i] < '0' || str[i] > '9')
            return false;

        result += (str[i] - '0') * power(10, counter);
    }

    return true;
}

const char* MyString::cstr() const
{
    return str;
}

const char& MyString::operator[](int index)const
{
    if (index < 0 || index >= length)
        throw out_of_range("Index out of range");

    return str[index];
}

MyString MyString::operator+(char ch) const
{
    MyString result;

    result.length = length + 1;

    result.str = new(nothrow) char[result.length + 1];

    if (!result.str)
    {
        cout << "Problem with memory!\n";
        return nullptr;
    }

    strcpy(result.str, str);

    result.str[length] = ch;
    result.str[result.length] = '\0';

    return result;
}

int MyString::size() const
{
    return length;
}

bool MyString::isEmpty() const
{
    return (length == 0);
}

ostream& operator<<(ostream& os, const MyString& s)
{
    os << s.str;
    return os;
}

istream& getline(istream& is, MyString& str)
{
    str.erase();
    str.copy("\0");

    char c;
    while (is.get(c) && c != '\n')
        str = str + c;

    if (is.eof() && str.size() > 0)
    {
        is.clear();
    }

    return is;
}
