#pragma once
#include "MyString.h"

class TableRow
{
private:
    MyString* data;
    int size;

    void copy(const MyString* data, int size);
    void erase();

public:

    TableRow();
    TableRow(const TableRow& other);
    TableRow& operator=(const TableRow& other);
    ~TableRow();

    TableRow(const MyString* data, int size);

    TableRow(TableRow&& other) noexcept;

    TableRow& operator=(TableRow&& other) noexcept;

    MyString& operator[](int index);

    const MyString& operator[](int index)const;

    void removeElement(int index);

    void parseFromFile(const MyString& data, int size);

    int getSize()const;

    friend ostream& operator<<(ostream& os, const TableRow& row);
};

ostream& operator<<(ostream& os, const TableRow& row);