#pragma once
#include "Reservation.h"
#include <iostream>
using namespace std;

Reservation::Reservation(string& c, int& n, int& s, string& resname, string& com, Date& dat, smart2 next2) : Table(c, n, s), 
name(resname), comments(com), reservdate(dat), pointer2(next2) {}

void Reservation::display()
{
	cout << *this;
}

Reservation::Reservation(string& c, int& n, int& s, string& resname, string& com, Date& dat) : Table(c, n, s),
name(resname), comments(com), reservdate(dat) 
{
	Reservation::pointer2 = nullptr;
}

Reservation::Reservation(const Reservation& r)
{
	Reservation::city = r.city;
	Reservation::number = r.number;
	Reservation::seats = r.seats;
	Reservation::name = r.name;
	Reservation::comments = r.comments;
	Reservation::reservdate = r.reservdate;
	Reservation::pointer2 = r.pointer2;
}

ostream& operator << (ostream& s, Reservation& res)
{
	s << "Miasto: " << res.city << "; Stolik nr #" << res.number << "(" << res.seats << "-osobowy) ";
	
	
	if (res.reservdate.day < 10)
	{
		s << "0" << res.reservdate.day << ".";
	}
	else
	{
		s << res.reservdate.day << ".";
	}

	if (res.reservdate.month < 10)
	{
		s << "0" << res.reservdate.month << ".";
	}
	else
	{
		s << res.reservdate.month << ".";
	}

	s << res.reservdate.year << ", ";

	if (res.reservdate.hour < 10)
	{
		s << "0" << res.reservdate.hour << ":";
	}
	else
	{
		s << res.reservdate.hour << ":";
	}

	if (res.reservdate.minute < 10)
	{
		s << "0" << res.reservdate.minute;
	}
	else
	{
		s << res.reservdate.minute;
	}
	

	s << endl << "Nazwisko: " << res.name << endl;
	if (!res.comments.empty())
	{
		s << "Dodatkowe uwagi: " << res.comments;
	}
	return s;
}