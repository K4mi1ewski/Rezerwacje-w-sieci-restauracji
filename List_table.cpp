#pragma once
#include "List_table.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
void List_table::load_from_file (const string& name)
{
	ifstream file(name);
	smart p = this->ptr;
	string city, line, t_number, seats;
	int seats_, table;
	stringstream ss; char sign;

	if (file.good())
	{
		while (!file.eof())
		{
			getline(file, city); cities.insert(city);
			int i = 0;
			do 
			{
				i++;
				if (i % 2 == 1)
				{
					getline(file, line);
					if (line.empty())
					{
						break;
					}
					ss << line;
					while (ss >> sign)
					{
						if (isdigit(sign))
						{
							seats.push_back(sign);
						}
					}
					seats_ = stoi(seats);
					seats.clear(); ss.str(""); ss.clear();
				}
				else
				{
					getline(file, line); 
					ss << line; 
					while (ss >> sign)
					{
						if (isdigit(sign))
						{
							t_number = sign; table = stoi(t_number);
							p = make_shared <Table>(city, table, seats_, this->ptr);
							this->ptr = p;
						}
					}
					ss.str(""); ss.clear();
				}

			} while (!file.eof());
		}
	}
	file.close();
}


ostream& operator << (ostream& s, set<string> c)
{
	for (auto iter = c.begin(); iter != c.end(); ++iter)
	{
		s << ">" << *iter << endl;
	}
	return s;
}

ostream& operator << (ostream& s, List_table& list)
{
	smart p = list.ptr;
	while (p)
	{
		s << *p;
		p = p -> pointer;
	}
	return s;
}

void List_table::display_cities()
{
	system("cls");
	cout << "====DOSTEPNE MIASTA====";
	cout << endl << cities << endl;
	cout << "Aby zakonczyc, wprowadz '0'" << endl;
	cout << endl << "Wprowadz nazwe miasta, w ktorym chcesz dokonac rezerwacji" << endl;
}

List_table::List_table(smart& tableptr)
{
	List_table::ptr = tableptr;
}

bool List_table::check(string& city)
{
	string cityupper;
	char sign; stringstream ss;
	ss << city;
	while (ss >> sign)
	{
		sign = toupper(sign);
		cityupper.push_back(sign);
	}
	ss.str(""); ss.clear();

		int i = 0;
		for (auto iter = cities.begin(); iter != cities.end(); ++iter)
		{
			string place = *iter;
			string iterupper = ""; 
			ss << place;
			while (ss >> sign)
			{
				sign = toupper(sign);
				iterupper.push_back(sign);
			} ss.clear(); ss.str("");
			if (iterupper == cityupper)
				return true;
			else
				i++;
		}
		
		if (i == cities.size())
		{
			cout << endl << "NIEPOPRAWNE WPROWADZONE DANE, SPROBUJ PONOWNIE!" << endl;
			cin.get();
			return false;
		}
		return true;
}

void List_table::display_seats(string& city)
{
	system("cls"); stringstream ss; char sign;
	ss << city; string cityupper = "";
	while (ss >> sign)
	{
		sign = toupper(sign);
		cityupper.push_back(sign);
	}
	ss.str(""); ss.clear();
	cout << "=====" << cityupper << "=====" << endl << "Dostepne stoliki:" << endl;
	smart p = this->ptr;
	int x=0;
	while (p)
	{
		string pcity = p->city;
		ss << pcity; pcity = "";
		while (ss >> sign)
		{
			sign = toupper(sign);
			pcity.push_back(sign);
		} ss.str(""); ss.clear();
		
		if (pcity == cityupper && p->seats != x)
		{
			cout << "Stoliki " << p->seats << "-osobowe" << endl;
			x = p->seats;
		}
		p = p->pointer;
	}
	cout << "Wybierz, jaki stolik chcesz zarezerwowac, wpisujac liczbe odpowiadajaca ilosci miejsc przy nim (aby wrocic do wyboru miasta wpisz '0'):"; 
}

bool List_table::check2(string& city, string& seats)
{
	stringstream ss; char sign;
	ss << seats; 
	while (ss >> sign)
	{
		if (!isdigit(sign))
		{
			cout << "Niepoprawny wybor, wprowadz liczbe!" << endl;
			cin.get();
			return false;
		}
	}
	int seatsnr = stoi(seats);
	ss.str(""); ss.clear();
	smart p = this->ptr;
	string cityupper; string pcity;
	ss << city;
	while (ss >> sign)
	{
		sign = toupper(sign);
		cityupper.push_back(sign);
	}
	ss.str(""); ss.clear();
	while (p)
	{
		pcity = p->city;
		ss << pcity; pcity = "";
		while (ss >> sign)
		{
			sign = toupper(sign);
			pcity.push_back(sign);
		}
		ss.str(""); ss.clear();
		if (pcity == cityupper && p->seats == seatsnr)
		{
			return true;
		}
		p = p->pointer;
	}
	cout << "Nie posiadamy wolnych stolikow dla podanej liczby osob!" << endl;
	cin.get();
	return false;

}

Table List_table::choose_table(Date& dat, string& city, string& seats, List_res& thelist)
{
	int tablenr; string tnr;
	smart p = this->ptr;
	smart2 thelistp = thelist.ptr;
	stringstream ss; char sign;
	string cityupper, pcity;
	vector <int> notfree;
	
	ss << city;
	while (ss >> sign)
	{
		sign = toupper(sign);
		cityupper.push_back(sign);
	}
	ss.str(""); ss.clear();
	int seatsnr = stoi(seats);
	
	
	while (thelistp)
	{
		string thelistpcity = thelistp->city;
		ss << thelistpcity; thelistpcity = "";
		while (ss >> sign)
		{
			sign = toupper(sign);
			thelistpcity.push_back(sign);
		} ss.str(""); ss.clear();

		if (thelistpcity == cityupper && thelistp->seats == seatsnr  && dat == thelistp->reservdate)
		{
			int reserved = thelistp->number;
			notfree.push_back(reserved);
		}
		thelistp = thelistp->pointer2;
	}
	int x = 0; int freenr;
	bool goodinput = false;
	do {
		p = this->ptr;
		system("cls");
		cout << "Dostepne stoliki: " << endl;
		vector <int> freetables;
		while (p)
		{
			bool free = true; 
			pcity = p->city; ss << pcity; pcity = "";
			while (ss >> sign)
			{
				sign = toupper(sign);
				pcity.push_back(sign);
			} ss.str(""); ss.clear();

			for (auto iter = notfree.begin(); iter != notfree.end(); iter++)
			{
				if (*iter == p->number)
					free = false;
			}

			if (pcity == cityupper && seatsnr == p->seats && free == true)
			{
				p->display();
				x++;
				freenr = p->number; freetables.push_back(freenr);
			}
			p = p->pointer;
		}
		if (x != 0)
		{
			bool digit = true;
			cout << "Wybierz numer stolika aby go zarezerwowac: "; getline(cin, tnr);
			if (tnr.empty())
			{
				cout << "Zly wybor, wprowadz liczbe jeszcze raz"; cin.get(); digit = false;
			}
			else 
			{
				ss << tnr;
				while (ss >> sign)
				{
					if (!isdigit(sign))
					{
						cout << "Zly wybor, wprowadz liczbe jeszcze raz"; cin.get(); digit = false; break;
					}
				}
				ss.str(""); ss.clear();
				if (digit)
				{
					tablenr = stoi(tnr);

					for (auto iter = freetables.begin(); iter != freetables.end(); iter++)
					{
						if (*iter == tablenr)
						{
							goodinput = true;
							break;
						}
					}
					if (!goodinput)
					{
						cout << "Taki stolik jest niedostepny lub nie istnieje, sprobuj ponownie"; cin.get();
					}
				}
			}
		}
	} while (!goodinput);
	
	Table T(cityupper, tablenr, seatsnr);
	return T;
}