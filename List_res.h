#pragma once
#include "ListOrigin.h"
#include "Reservation.h"
using namespace std;

class List_res : public ListOrigin
{
private:
	smart2 ptr;

public:
	void load_from_file(const string& name);
	bool checkdate(string& city, string& seats, string& stringdate);
	void addtolist(Reservation& res);
	void display();
	void savetofile(const string &name);
	Date getdate(string& stringdate);
	List_res(smart2& resptr);
	List_res();
	friend class List_table;
	friend ostream& operator << (ostream& s, List_res& list);
};