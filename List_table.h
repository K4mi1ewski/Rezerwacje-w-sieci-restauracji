#pragma once
#include "ListOrigin.h"
#include "List_res.h"
#include "Table.h"
#include <set>
class List_table : public List_res
{
private:
	smart ptr;
	set <string> cities;
public:
	void load_from_file(const string& name);
	void display_cities();
	void display_seats(string& city);
	Table choose_table(Date& dat, string& city, string& seats, List_res& thelist);
	friend ostream& operator << (ostream& s, set<string> c);
	friend ostream& operator << (ostream& s, List_table& list);
	bool check(string& city);
	bool check2(string& city, string& seats);
	List_table(smart& tableptr);
};