#pragma once
#include "List_res.h"
#include <fstream>
#include <iostream>
#include <windows.h>
#include <sstream>
#include <string>
void List_res::load_from_file(const string& name)
{
	ifstream file(name);
	smart2 p = this->ptr;
	string place, table, seats, resdate, resname, comments;
	int day_, month_, year_, hour_, minute_, t_number, seats_;

	if (file.good())
	{

		while (!file.eof())
		{
			getline(file, place, ',');
			if (place.empty())
				break;
			getline(file, table, '#'); getline(file, table, ','); t_number = stoi(table);
			getline(file, seats, '-'); seats_ = stoi(seats); getline(file, seats, ',');
			getline(file, resdate, '.'); day_ = stoi(resdate);
			getline(file, resdate, '.'); month_ = stoi(resdate);
			getline(file, resdate, ','); year_ = stoi(resdate);
			getline(file, resdate, ':'); hour_ = stoi(resdate);
			getline(file, resdate, ','); minute_ = stoi(resdate);
			getline(file, resname, ',');
			getline(file, comments);
			

			Date d(year_, month_, day_, hour_, minute_);
			p = make_shared <Reservation>(place, t_number, seats_, resname, comments, d, this->ptr);
			this->ptr = p;

		}
	}
	file.close();
}

List_res::List_res(smart2& resptr)
{
	ptr = resptr;
}
List_res::List_res()
{
	List_res::ptr = nullptr;
}

bool List_res::checkdate(string& city, string& seats, string& stringdate)
{
	stringstream ss; char sign;
	int seatsnumber = stoi(seats);
	string year_; string month_; string day_; string hour_; string minute_;
	int resyear, resmonth, resday, reshour, resminute;
	ss << stringdate; int i = 1;
	while (ss >> sign)
	{
		
		if (!isdigit(sign) && (sign != '-' && sign != ':' && sign != ','))
		{
			cout << "Niepoprawne dane, wprowadz date jeszcze raz" << endl; cin.get();
			return false;
		}
	
		if (i <= 2)
		{
			day_.push_back(sign);
		}
		if (i == 3 && (sign != '-' && sign != '.'))
		{
			cout << "Niepoprawne dane, wprowadz date jeszcze raz"; cin.get();
			return false;
		}
		
		if (i > 3 && i <= 5)
		{
			month_.push_back(sign);
		}
		
		
		if (i == 6 && (sign != '-' && sign != '.'))
		{
			cout << "Niepoprawne dane, wprowadz date jeszcze raz"; cin.get();
			return false;
		}
		if (i >= 7 && i < 11)
		{
			year_.push_back(sign);
		}
		
		
		if (i == 11 && sign != ',')
		{
			cout << "Po podaniu daty nalezy wpisac przecinek i wprowadzic po nim godzine"; cin.get();
			return false;
		}
		if (i > 11 && i <= 13)
		{
			hour_.push_back(sign);
		}
		
		if (i == 14 && sign != ':')
		{
			cout << "Podaj godzine rezerwacji w formacie (hh:min), np. 18:30"; cin.get();
			return false;
		}
		if (i > 14 && i <= 16)
		{
			minute_.push_back(sign);
		}
		
		
		i++;
	}
	if (i != 17)
	{
		cout << "Niepoprawne wprowadzone dane"; cin.get();
		return false;
	}
	resday = stoi(day_);
	resmonth = stoi(month_);
	if (resmonth < 1 || resmonth > 12)
	{
		cout << "Niepoprawne dane, wprowadz date jeszcze raz"; cin.get();
		return false;
	}
	if ((resmonth == 1 || resmonth == 3 || resmonth == 5 || resmonth == 7 || resmonth == 8 || resmonth == 10 || resmonth == 12) && (resday < 1 || resday > 31))
	{
		cout << "Niepoprawne dane, wprowadz date jeszcze raz"; cin.get();
		return false;
	}
	if ((resmonth == 4 || resmonth == 6 || resmonth == 9 || resmonth == 11) && (resday < 1 || resday > 30))
	{
		cout << "Niepoprawne dane, wprowadz date jeszcze raz"; cin.get();
		return false;
	}
	if (resmonth == 2 && (resday < 1 || resday > 29))
	{
		cout << "Niepoprawne dane, wprowadz date jeszcze raz"; cin.get();
		return false;
	}
	resyear = stoi(year_);
	if (resyear < 2022 || resyear > 2030)
	{
		cout << "Wprowadz poprawny rok"; cin.get();
		return false;
	}
	reshour = stoi(hour_);
	if (reshour < 14 || reshour > 22)
	{
		cout << "Przyjmujemy rezerwacje miedzy godzina 14 a 22."; cin.get();
		return false;
	}
	resminute = stoi(minute_);
	if (resminute < 0 || resminute > 59)
	{
		cout << "Niepoprawna minuta rezerwacji"; cin.get();
		return false;
	}
	if ((resyear == 2022 && resmonth < 9) || (resyear == 2022 && resmonth == 9 && resday < 8))
	{
		cout << "Niepoprawne dane rezerwacji"; cin.get();
		return false;
	}
	ss.str(""); ss.clear();
	return true;

}

Date List_res::getdate(string& stringdate)
{
	stringstream ss; char sign;
	string year_; string month_; string day_; string hour_; string minute_;
	int resyear, resmonth, resday, reshour, resminute;
	ss << stringdate; int i = 1;
	while (ss >> sign)
	{

		if (i <= 2)
		{
			day_.push_back(sign);
		}

		if (i > 3 && i <= 5)
		{
			month_.push_back(sign);
		}

		if (i >= 7 && i < 11)
		{
			year_.push_back(sign);
		}

		if (i > 11 && i <= 13)
		{
			hour_.push_back(sign);
		}

		if (i > 14 && i <= 16)
		{
			minute_.push_back(sign);
		}
		i++;
	}
	resday = stoi(day_);
	resmonth = stoi(month_);
	resyear = stoi(year_);
	reshour = stoi(hour_);
	resminute = stoi(minute_);

	Date newdate(resyear, resmonth, resday, reshour, resminute);
	return newdate;
}

void List_res::addtolist(Reservation& res)
{
	smart2 R = make_shared <Reservation>(res);
	R->pointer2 = this->ptr;
	this->ptr = R;

}

void List_res::display()
{
	cout << *this;
}

ostream& operator << (ostream& s, List_res& list)
{
	smart2 p = list.ptr;
	while (p)
	{
		s << *p;
		p = p->pointer2;
	}
	return s;
}

void List_res::savetofile(const string&name)
{
	ofstream file;
	file.open(name);
	smart2 p = this->ptr;
	while (p)
	{
		file << p->city << ", " << "Stolik nr #" << p->number << ", " << p->seats << "-osobowy, ";
		
		if (p->reservdate.day < 10)
		{
			file << "0" << p->reservdate.day << ".";
		}
		else
		{
			file << p->reservdate.day << ".";
		}

		if (p->reservdate.month < 10)
		{
			file << "0" << p->reservdate.month << ".";
		}
		else
		{
			file << p->reservdate.month << ".";
		}

		file << p->reservdate.year << ", ";

		if (p->reservdate.hour < 10)
		{
			file << "0" << p->reservdate.hour << ":";
		}
		else
		{
			file << p->reservdate.hour << ":";
		}

		if (p->reservdate.minute < 10)
		{
			file << "0" << p->reservdate.minute;
		}
		else
		{
			file << p->reservdate.minute;
		}
		file<< ", " << p->name << ", " << p->comments << endl;
		
		p = p->pointer2;

	}
	file.close();
}