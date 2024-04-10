#pragma once
#include "Table.h"
#include <iostream>
using namespace std;
Table::Table(string& c, int& n, int& s, smart& next) : city(c), number(n), seats(s), pointer (next) {}
Table::Table(string& c, int& n, int& s): city (c), number (n), seats (s) {}

void Table::display()
{
	cout  << *this;
}
ostream& operator << (ostream& s, Table& t)
{
	s << t.city << "; " << "Stolik " << t.seats << "-osobowy nr #" << t.number << endl;
	return s;
}

Table::Table() {}