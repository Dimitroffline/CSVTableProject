#pragma once
#include "TableRow.h"

class Table
{
private:
    TableRow names;
    vector<TableRow> rows;

public:
    
    Table() = default;

    Table(vector<TableRow> rows, const TableRow& names);

    TableRow& operator[](int index);

    const TableRow& operator[](int index)const;

    int getSize() const;

    void addRow(TableRow row);

    bool copyRow(int index);

    void removeRow(int index);

    void removeColumn(int index);

    void removeColumn(string name);

    string findMin(int index)const;

    string findMax(int index)const;

    void copyMin();
    
    void copyMax();

    void copyFrequent();

    bool swapRows(int first, int second);

    bool swapCols(int first, int second);

    bool permutate(string perm);

    void removeDupes();

    void sort(int index, bool order);

    void sort(string name, bool order);

    void filter(int index, string sign, string other);

    void filter(string name, string sign, string other);

    void addNames();

    bool isEmpty()const;

    friend ostream& operator<<(ostream& os, const Table& table);
};

ostream& operator<<(ostream& os, const Table& table);

bool checkPerm(string perm);
