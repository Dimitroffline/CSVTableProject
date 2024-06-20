#include "Table.h"

int compare(string lhs, string rhs)
{
    return strcmp(lhs.c_str(), rhs.c_str());
}

bool checkPerm(string perm)
{
    bool isFound;
    int permSize = perm.size();

    for (int i = 1; i <= permSize; i++)
    {
        isFound = false;

        for (int j = 0; j < permSize; j++)
        {
            if (perm[j] - '0' == i)
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

Table::Table(vector<TableRow> rows, const TableRow& names)
{
    this->rows = move(rows);
    this->names = names;
}

TableRow& Table::operator[](int index)
{
    if (index < 0 || index >= getSize())
        throw std::out_of_range("Index out of range");

    return rows[index];
}

const TableRow& Table::operator[](int index) const
{
    if (index < 0 || index >= getSize())
        throw std::out_of_range("Index out of range");

    return rows[index];
}

int Table::getSize() const
{
    return rows.size();
}

void Table::addRow(TableRow row)
{
    rows.push_back(move(row));
}

bool Table::copyRow(int index)
{
    if (index < 0 || index >= getSize())
        return 0;

    addRow(rows[index]);
    return 1;
}

void Table::removeRow(int index)
{
    int size = getSize();
    if (index < 0 || index >= size)
        return;

    rows.erase(rows.begin() + index);
}

void Table::removeColumn(int index)
{
    int cols = rows[0].getSize();

    if (index < 0 || index >= cols)
        return;

    int size = getSize();

    for (int i = 0; i < size; i++)
        rows[i].removeElement(index);

    names.removeElement(index);
}

void Table::removeColumn(string name)
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

string Table::findMin(int index) const
{
    string result;

    int cols = rows[0].getSize();

    if (index < 0 || index >= cols)
        return result;

    result = rows[0][index];
    int size = getSize();

    for (int i = 1; i < size; i++)
    {
        if (compare(result, rows[i][index]) > 0)
        {
            result = rows[i][index];
        }
    }

    return result;
}

string Table::findMax(int index) const
{
    string result;

    int cols = rows[0].getSize();

    if (index < 0 || index >= cols)
        return result;

    result = rows[0][index];
    int size = getSize();

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
    int cols = rows[0].getSize();

    if (!cols)
        return;

    TableRow newRow;

    for (int i = 0; i < cols; i++)
        newRow.addElement(findMin(i));

    addRow(newRow);
}

void Table::copyMax()
{
    int cols = rows[0].getSize();

    if (!cols)
        return;

    TableRow newRow;

    for (int i = 0; i < cols; i++)
        newRow.addElement(findMax(i));

    addRow(newRow);
}

void Table::copyFrequent()
{
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

    int size = getSize();

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

    TableRow newRow;

    for (int k = 0; k < cols; k++)
    {
        newRow.addElement(rows[indexes[k]][k]);
    }

    addRow(newRow);

    delete[] indexes;
    delete[] counts;
    delete[] maxCounts;
}

bool Table::swapRows(int first, int second)
{
    int size = getSize();

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
    int size = getSize();

    for (int i = 0; i < size; i++)
    {
        if (!rows[i].swap(first, second))
            return false;
    }

    names.swap(first, second);

    return true;
}

bool Table::permutate(string perm)
{
    int cols = rows[0].getSize();

    if (!cols)
        return true;

    if (cols != perm.size())
        return false;

    if (!checkPerm(perm))
        return false;

    Table newTable;

    TableRow emptyRow;
    TableRow newNames;
    int size = getSize();

    for (int i = 0; i < size; i++)
        newTable.addRow(emptyRow);

    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < size; j++)
            newTable[j].addElement(rows[j][perm[i] - '1']);

        if(!names.isEmpty())
            newNames.addElement(names[perm[i] - '1']);
    }

    *this = newTable;

    return true;
}

void Table::removeDupes()
{
    int size = getSize();

    for (int i = 0; i < size - 1; i++)
        for (int j = i + 1; j < size; j++)
            if (rows[i] == rows[j])
            {
                removeRow(j--);
                --size;
            }
}

void Table::sort(int index, bool order)
{
    int minInd;
    int result;
    int size = getSize();

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

void Table::sort(string name, bool order)
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

void Table::filter(int index, string sign, string other)
{
    int cols = rows[0].getSize();

    if (index < 0 || index >= cols)
        return;

    int result;
    int size = getSize();

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
        size--;
    }
}

void Table::filter(string name, string sign, string other)
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

    names = rows[0];

    removeRow(0);
}

bool Table::isEmpty() const
{
    return rows.empty();
}

ostream& operator<<(ostream& os, const Table& table)
{
    int size = table.getSize();

    if(!table.names.isEmpty())
        os << table.names << '\n';

    for (int i = 0; i < size; i++)
    {
        os << table.rows[i];
        
        if (i < size - 1)
            os << '\n';
    }

    return os;
}