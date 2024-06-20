#include "TableRow.h"


TableRow::TableRow(vector<string> data)
{
	this->data = move(data);
}

string& TableRow::operator[](int index)
{
	if (index < 0 || index >= getSize()) 
		throw out_of_range("Index out of range");

	return data[index];
}

const string& TableRow::operator[](int index) const
{
	if (index < 0 || index >= getSize())
		throw out_of_range("Index out of range");

	return data[index];
}

void TableRow::removeElement(int index)
{
	int size = getSize();
	if (index < 0 || index >= size)
		return;

	data.erase(data.begin() + index);
}

void TableRow::parseFromFile(string data)
{
	int len = data.size();
	string buff;

	for (int i = 0; i < len; i++)
	{
		if (data[i] == ' ' && !buff.empty())
		{
			this->data.push_back(buff);
			buff.clear();
		}
		else
			buff = buff + data[i];
	}

	if (!buff.empty())
		this->data.push_back(buff);
}

int TableRow::getSize() const
{
	return data.size();
}

void TableRow::addElement(string newElement)
{
	data.push_back(move(newElement));
}

bool TableRow::swap(int first, int second)
{
	if (first < 0 || first >= getSize())
	{
		return 0;
	}

	if (second < 0 || second >= getSize())
	{
		return 0;
	}

	if (first == second)
	{
		return 1;
	}

	string temp = data[first];

	data[first] = data[second];
	data[second] = temp;

	return 1;
}

void TableRow::reset()
{
	data.clear();
}

bool TableRow::isEmpty() const
{
	return data.empty();
}

ostream& operator<<(ostream& os, const TableRow& row)
{
	int size = row.getSize();

	for (int i = 0; i < size; i++)
	{
		os << row.data[i];

		if (i < size - 1)
			os << ' ';
	}
	
	return os;
}

bool operator==(const TableRow& lhs, const TableRow& rhs)
{
	return lhs.data == rhs.data;
}
