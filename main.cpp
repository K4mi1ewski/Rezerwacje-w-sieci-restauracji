
#include "List_table.h"
#include "List_res.h"
#include <iostream>
using namespace std;

int main()
{
	const string base = "baza.txt";
	const string base2 = "rezerwacje.txt";
	smart start; smart2 res_start;
	List_table tables(start); List_res reserved(res_start);
	tables.load_from_file(base); reserved.load_from_file(base2);
	bool next = true; bool next2 = false; bool next3 = false;
	do
	{
		cin.clear(); tables.display_cities();
		string choice_city; getline(cin, choice_city);
		if (choice_city == "0") { break; }
		if (next2 = tables.check(choice_city))
		{
			do 
			{
				string seats_choice;
				tables.display_seats(choice_city); getline(cin, seats_choice);
				if (seats_choice == "0") { break; }
				if (next2 = tables.check2(choice_city, seats_choice))
				{
					do 
					{
						system("cls");
						string datechoice;
						cout << "Podaj date i godzine rezerwacji (dd-mm-rrrr, hh:min) (jesli chcesz wrocic, wybierz '0'):" << endl;
						getline(cin, datechoice);  if (datechoice == "0") { next2 = false;  break; }
						if (next3 = reserved.checkdate(choice_city, seats_choice, datechoice))
						{
							string reservename; string comments = ""; string choicenext;
							Date dateofreserv = reserved.getdate(datechoice);
							Table chosentable = tables.choose_table(dateofreserv, choice_city, seats_choice, reserved);
							cout << "Wprowadz nazwisko na jakie ma zostac zapisana rezerwacja: "; getline(cin, reservename); 
							cout << endl << "Dodatkowe uwagi do zamowienia (jesli brak, wcisnij enter): "; getline (cin, comments);
							Reservation newreservation(chosentable.city, chosentable.number, chosentable.seats, reservename, comments, dateofreserv);
							reserved.addtolist(newreservation);
							newreservation.display(); cin.get(); 
							do
							{
								system("cls");
								cout << "Czy chcesz dokonac kolejnej rezerwacji? Wpisz 't' lub 'n': " << endl; getline(cin, choicenext);
								if (choicenext == "n")
								{
									next = false;
								}
								else if (choicenext != "t" && choicenext != "n")
								{
									cout << "Wpisz 't' lub 'n' !"; cin.get();
								}
							} while (choicenext != "t" && choicenext != "n");
						}	
					} while (!next3);
				}
			} while (!next2);
		}
	} while (next);
	reserved.savetofile(base2);











}