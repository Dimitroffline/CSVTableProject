#include "Table.h"

bool checkPerm(const MyString& perm)
{
    bool isFound;
    int permSize = perm.size();

    for (int i = 1; i <= permSize; i++)
    {
        isFound = false;

        for (int j = 0; j < permSize; j++)
        {
            if (perm.cstr()[j] - '0' == i)
            {
                isFound = true;
                break;
            }
        }

        if (!isFound)
            return false;
    }

    return true;
}

void Table::erase()
{
    delete[] rows;
    size = 0;
    capacity = 0;
    names.reset();
}

void Table::copy(const TableRow* rows, int size, int capacity, const TableRow& names)
{
    this->size = size;
    this->capacity = capacity;

    if (capacity == 0)
    {
        rows = nullptr;
        this->size = 0;
        return;
    }

    this->rows = new(nothrow) TableRow[capacity];

    if (!this->rows)
    {
        cout << "Problem with memory!\n";
        return;
    }

    for (int i = 0; i < size; i++)
        this->rows[i] = rows[i];

    this->names = names;
}

void Table::resize(int newCapacity)
{
    TableRow* newRows = new(nothrow) TableRow[newCapacity];

    if (!newRows)
    {
        cout << "Problem with memory!\n";
        return;
    }

    for (int i = 0; i < size; ++i)
    {
        newRows[i] = move(rows[i]);
    }

    int oldSize = size;
    erase();
    size = oldSize;
    rows = newRows;
    capacity = newCapacity;
}

Table::Table()
{
    rows = nullptr;
    names.reset();
    size = 0;
    capacity = 0;
}

Table::Table(const Table& other)
{
    copy(other.rows, other.size, other.capacity, other.names);
}

Table::Table(Table&& other) noexcept : rows(other.rows), size(other.size), capacity(other.capacity), names(other.names)
{
    other.rows = nullptr;
    names.reset();
    other.size = 0;
    other.capacity = 0;
}

Table& Table::operator=(const Table& other)
{
    if (this != &other)
    {
        erase();
        copy(other.rows, other.size, other.capacity, other.names);
    }

    return *this;
}

Table& Table::operator=(Table&& other) noexcept
{
    if (this != &other)
    {
        erase();
        rows = other.rows;
        size = other.size;
        capacity = other.capacity;
        names = other.names;
        other.rows = nullptr;
        other.names.reset();
        other.size = 0;
        other.capacity = 0;
    }

    return *this;
}

Table::~Table()
{
    erase();
}

Table::Table(const TableRow* rows, int size, const TableRow& names)
{
    copy(rows, size, size, names);
}

TableRow& Table::operator[](int index)
{
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");

    return rows[index];
}

int Table::rowCount() const
{
    return size;
}

void Table::addRow(const TableRow row)
{
    if (size == capacity)
    {
        resize(capacity == 0 ? 1 : capacity * 2);
    }

    rows[size++] = row;
}

void Table::addRow(TableRow&& row)
{
    if (size == capacity)
    {
        resize(capacity == 0 ? 1 : capacity * 2);
    }

    rows[size++] = std::move(row);
}

bool Table::copyRow(int index)
{
    if (index < 0 || index >= size)
        return 0;

    addRow(rows[index]);
    return 1;
}

void Table::removeRow(int index)
{
    if (rows == nullptr)
        return;

    if (index < 0 || index >= size)
        return;

    for (int i = index; i < size - 1; i++)
    {
        rows[i] = rows[i + 1];
    }

    --size;
}

void Table::removeColumn(int index)
{
    if (rows == nullptr)
        return;

    int cols = rows[0].getSize();

    if (index < 0 || index >= cols)
        return;

    for (int i = 0; i < size; i++)
        rows[i].removeElement(index);

    names.removeElement(index);
}

void Table::removeColumn(const MyString& name)
{
    if (names.isEmpty())
        return;

    int cols = names.getSize();

    int index = -1;

    for (int i = 0; i < cols; i++)
    {
        if (names[i] == name)
            index = i;
    }

    if (index == -1)
        return;

    removeColumn(index);
}

MyString Table::findMin(int index) const
{
    MyString result;

    if (rows == nullptr)
        return result;

    int cols = rows[0].getSize();

    if (index < 0 || index >= cols)
        return result;

    result = rows[0][index];

    for (int i = 1; i < size; i++)
    {
        if (compare(result, rows[i][index]) > 0)
        {
            result = rows[i][index];
        }
    }

    return result;
}

MyString Table::findMax(int index) const
{
    MyString result;

    if (rows == nullptr)
        return result;

    int cols = rows[0].getSize();

    if (index < 0 || index >= cols)
        return result;

    result = rows[0][index];

    for (int i = 1; i < size; i++)
    {
        if (compare(result, rows[i][index]) < 0)
        {
            result = rows[i][index];
        }
    }

    return result;
}

void Table::copyMin()
{
    if (!rows)
        return;

    int cols = rows[0].getSize();

    if (!cols)
        return;

    TableRow newRow(cols);

    for (int i = 0; i < cols; i++)
        newRow.swapElement(i, findMin(i));

    addRow(newRow);
}

void Table::copyMax()
{
    if (!rows)
        return;

    int cols = rows[0].getSize();

    if (!cols)
        return;

    TableRow newRow(cols);

    for (int i = 0; i < cols; i++)
        newRow.swapElement(i, findMax(i));

    addRow(newRow);
}

void Table::copyFrequent()
{
    if (!rows)
        return;

    int cols = rows[0].getSize();

    if (!cols)
        return;

    int* indexes = new(nothrow) int[cols];

    if (!indexes)
        return;

    int* counts = new(nothrow) int[cols];

    if (!counts)
        return;

    int* maxCounts = new(nothrow) int[cols];

    if (!maxCounts)
        return;

    fill(indexes, indexes + cols, 0);
    fill(maxCounts, maxCounts + cols, 1);

    for (int i = 0; i < size - 1; i++)
    {
        fill(counts, counts + cols, 1);

        for (int j = i + 1; j < size; j++)
        {
            for (int k = 0; k < cols; k++)
            {
                if (rows[i][k] == rows[j][k])
                    ++counts[k];
            }

            for (int k = 0; k < cols; k++)
            {
                if (counts[k] > maxCounts[k])
                {
                    maxCounts[k] = counts[k];
                    indexes[k] = j;
                }

                if (counts[k] == maxCounts[k])
                {
                    if (compare(rows[j][k], rows[indexes[k]][k]) < 0)
                    {
                        maxCounts[k] = counts[k];
                        indexes[k] = j;
                    }
                }
            }
        }
    }

    TableRow newRow(cols);

    for (int k = 0; k < cols; k++)
    {
        newRow.swapElement(k, rows[indexes[k]][k]);
    }

    addRow(newRow);

    delete[] indexes;
    delete[] counts;
    delete[] maxCounts;
}

bool Table::swapRows(int first, int second)
{
    if (first < 0 || first >= size)
    {
        return false;
    }

    if (second < 0 || second >= size)
    {
        return false;
    }

    if (first == second)
    {
        return true;
    }

    TableRow temp = rows[first];

    rows[first] = rows[second];
    rows[second] = temp;

    return true;
}

bool Table::swapCols(int first, int second)
{
    for (int i = 0; i < size; i++)
    {
        if (!rows[i].swap(first, second))
            return false;
    }

    names.swap(first, second);

    return true;
}

bool Table::permutate(const MyString& perm)
{
    if (!rows)
        return true;

    int cols = rows[0].getSize();

    if (!cols)
        return true;

    if (cols != perm.size())
        return false;

    if (!checkPerm(perm))
        return false;

    Table newTable;

    TableRow newRow(cols);
    TableRow newNames(cols);

    for (int i = 0; i < size; i++)
        newTable.addRow(newRow);

    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < size; j++)
            newTable[j].swapElement(i, rows[j][perm.cstr()[i] - '1']);

        if(!names.isEmpty())
            newNames.swapElement(i, names[perm.cstr()[i] - '1']);
    }

    *this = newTable;

    return true;
}

void Table::removeDupes()
{
    for (int i = 0; i < size - 1; i++)
        for (int j = i + 1; j < size; j++)
            if (rows[i] == rows[j])
                removeRow(j--);
}

void Table::sort(int index, bool order)
{
    int minInd;
    int result;

    for (int i = 0; i < size - 1; i++)
    {
        minInd = i;

        for (int j = i + 1; j < size; j++)
        {
            result = compare(rows[j][index], rows[minInd][index]);
            
            if (order)
                result = -result;

            if (result < 0)
                minInd = j;
        }

        if(minInd != i)
            swapRows(i, minInd);
    }
}

void Table::sort(const MyString& name, bool order)
{
    if (names.isEmpty())
        return;

    int cols = names.getSize();

    int index = -1;

    for (int i = 0; i < cols; i++)
    {
        if (names[i] == name)
            index = i;
    }

    if (index == -1)
        return;

    sort(index, order);
}

void Table::filter(int index, const MyString& sign, const MyString& other)
{
    if (!rows)
        return;

    int cols = rows[0].getSize();

    if (index < 0 || index >= cols)
        return;

    int result;

    for (int i = 0; i < size; i++)
    {
        result = compare(rows[i][index], other);

        if (result == 0 && (sign == "<=" || sign == ">=" || sign == "=="))
        {
            continue;
        }
        if (result < 0 && (sign == "<=" || sign == "<" || sign == "!="))
        {
            continue;
        }
        if (result > 0 && (sign == ">=" || sign == ">" || sign == "!="))
        {
            continue;
        }

        removeRow(i--);
    }
}

void Table::filter(const MyString& name, const MyString& sign, const MyString& other)
{
    if (names.isEmpty())
        return;

    int cols = names.getSize();

    int index = -1;

    for (int i = 0; i < cols; i++)
    {
        if (names[i] == name)
            index = i;
    }

    if (index == -1)
        return;

    filter(index, sign, other);
}

void Table::addNames()
{
    if (!names.isEmpty())
        return;

    if (!rows)
        return;

    names = rows[0];

    removeRow(0);
}

bool Table::isEmpty() const
{
    return size == 0;
}

ostream& operator<<(ostream& os, const Table& table)
{
    if(!table.names.isEmpty())
        os << table.names << '\n';

    for (int i = 0; i < table.size; i++)
    {
        os << table.rows[i];
        
        if (i < table.size - 1)
            os << '\n';
    }

    return os;
}