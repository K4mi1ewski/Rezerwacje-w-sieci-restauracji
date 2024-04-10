#pragma once
#include "Table.h"
#include "Date.h"

class Reservation : public Table
{
private:
	string name, comments;
	Date reservdate;
	
	typedef shared_ptr <Reservation> smart2;
	smart2 pointer2;

	friend class List_res;
public: 
	Reservation(string& c, int& n, int& s, string& resname, string& com, Date& dat, smart2 next2);
	Reservation(string& c, int& n, int& s, string& resname, string& com, Date& dat);
	Reservation(const Reservation& r);
	void display();
	friend class List_table;
	friend ostream& operator << (ostream& s, List_res& list);
	friend ostream& operator << (ostream& s, Reservation& res);
};

typedef shared_ptr <Reservation> smart2;