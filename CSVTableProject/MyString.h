#pragma once
#include <iostream>
#include <cstring>

using namespace std;

int power(int base, int pwr);

class MyString 
{
private:
    char* str;
    int length;

    void copy(const char* str);
    void erase();

public:
    MyString();
    MyString(const MyString& other);
    MyString& operator=(const MyString& other);
    ~MyString();

    MyString(const char* s);

    MyString(MyString&& other) noexcept;

    MyString& operator=(MyString&& other) noexcept;

    bool operator==(const MyString& other) const;

    MyString operator+(const MyString& other) const;

    MyString operator+(const char* other) const;

    MyString operator+(char ch) const;

    char& operator[](int index);

    const char& operator[](int index)const;

    bool isEmpty()const;

    bool toInt(int& result)const;

    int size() const;

    const char* cstr()const;

    friend ostream& operator<<(ostream& os, const MyString& s);
    friend istream& getline(istream& is, MyString& str);
};

istream& getline(istream& is, MyString& str);
ostream& operator<<(ostream& os, const MyString& s);
int compare(const MyString& lhs, const MyString& rhs);