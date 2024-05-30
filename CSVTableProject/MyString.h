#pragma once
#include <iostream>
#include <cstring>

using namespace std;

class MyString {
private:
    char* str;
    int length;

    void copy(const char* str);
    void erase();

public:
    MyString();
    MyString(const char* s);
    MyString(const MyString& other);
    MyString(MyString&& other) noexcept;
    ~MyString();

    MyString& operator=(MyString&& other) noexcept;

    MyString& operator=(const MyString& other);

    bool operator==(const MyString& other) const;

    MyString operator+(const MyString& other) const;

    MyString operator+(const char* other) const;

    MyString operator+(char ch) const;

    char& operator[](int index);

    int size() const;

    friend ostream& operator<<(ostream& os, const MyString& s);
};

ostream& operator<<(ostream& os, const MyString& s);