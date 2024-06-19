#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class TableRow
{
private:
    vector<string> data;

public:

    TableRow() = default;

    TableRow(vector<string> data);

    string operator[](int index);

    const string operator[](int index)const;

    void removeElement(int index);

    void parseFromFile(string data);

    int getSize()const;

    bool swapElement(int index, string newElement);

    void addElement(string newElement);

    bool swap(int first, int second);

    void reset();

    bool isEmpty()const;

    friend ostream& operator<<(ostream& os, const TableRow& row);
    friend bool operator==(const TableRow& lhs, const TableRow& rhs);
};

ostream& operator<<(ostream& os, const TableRow& row);
bool operator==(const TableRow& lhs, const TableRow& rhs);