#include "MyString.h"

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
    other.str = nullptr;
    other.length = 0;
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

bool MyString::operator==(const MyString& other) const
{
    if (length != other.length)
        return false;

    for (int i = 0; i < length; ++i) {
        if (str[i] != other.str[i])
            return false;
    }

    return true;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
    if (this != &other)
    {
        erase();
        str = other.str;
        length = other.length;
        other.str = nullptr;
        other.length = 0;
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

MyString MyString::operator+(char ch) const
{
    MyString result;

    result.length = length + 1;

    result.str = new(nothrow) char[result.length + 1];

    strcpy(result.str, str);

    result.str[length] = ch;
    result.str[result.length] = '\0';

    return result;
}

int MyString::size() const
{
    return length;
}

ostream& operator<<(ostream& os, const MyString& s)
{
    os << s.str;
    return os;
}
