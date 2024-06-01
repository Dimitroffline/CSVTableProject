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

    TableRow(TableRow&& other) noexcept;

    TableRow& operator=(TableRow&& other) noexcept;

    MyString& operator[](int index);
};