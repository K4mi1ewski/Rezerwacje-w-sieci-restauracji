#pragma once
#include <string>
#include <memory>
#include "TableOrigin.h"

using namespace std;

class Table : public TableOrigin
{
public:
	string city;
	int number;
	int seats;

	typedef shared_ptr <Table> smart;

	Table(string& c, int& n, int& s, smart& next);
	Table(string& c, int& n, int& s);
	Table();
	void display();
	
private:
	smart pointer;


	friend class List_table;
	friend ostream& operator << (ostream& s, List_table& list);
	friend ostream& operator << (ostream& s, Table& t);
	
};
typedef shared_ptr <Table> smart;
