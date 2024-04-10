#pragma once
#include "TableOrigin.h"
class Date : public TableOrigin {
public:
	int year;
	int month;
	int day;
	int hour;
	int minute;
public:
	void display();
	bool operator == (const Date& d);

	Date(int& y, int& m, int& d, int& h, int& min);
	Date();
	
	friend class List_res;
	friend class Reservation;
};

