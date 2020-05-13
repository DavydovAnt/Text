#include "TText.h"
#include "TTextLink.h"
#include <fstream>
#include <iostream>
#include <string>
#include <conio.h>

#define HOME 71
#define DOWN 80
#define NEXT 77
#define UP 72																																																	
#define PGDN 81
#define ESC 27
#define DEL 83 
#define INS 82 

TTextMem TTextLink::MemHeader;

void Menu(TText& txt) {
	int key, count = 1;
	string str;
	txt.Reset();
	while (true) {
		key = _getch();
		switch (key)
		{
		case PGDN: txt.GoNext(); count++;
			cout << "Number pCurr " << count << endl; break;
		case DEL: txt.DelDown();
			TTextLink::MemCleaner(txt);
			system("cls");

			cout << "PGDN-GoNext INS-InsDownLine DOWN - InsNextSect DEL-DelDown HOME - DelNext  ESC" << endl;
			for (txt.Reset(); !txt.IsEnd(); txt.GoNext()) {
				cout << txt.GetLine() << endl;
			}
			count = 1; txt.Reset();
			cout << "Number pCurr " << count << endl; break;
		case HOME: txt.DelNext();
			TTextLink::MemCleaner(txt);
			system("cls");

			cout << "PGDN-GoNext INS-InsDownLine DOWN - InsNextSect DEL-DelDown HOME - DelNext  ESC" << endl;
			for (txt.Reset(); !txt.IsEnd(); txt.GoNext()) {
				cout << txt.GetLine() << endl;
			}
			count = 1; txt.Reset();
			cout << "Number pCurr " << count << endl; break;
		case INS: cout << "Enter the string ";
			cin >> str;
			txt.InsDownLine(str);

			system("cls");
			cout << "PGDN-GoNext INS-InsDownLine DOWN - InsNextSect DEL-DelDown HOME - DelNext  ESC" << endl;
			for (txt.Reset(); !txt.IsEnd(); txt.GoNext()) {
				std::cout<< txt.GetLine() << endl;
			}
			count = 1; txt.Reset();
			cout << "Number pCurr " << count << endl; break;
		case DOWN: cout << "Enter the string ";
			cin >> str;
			txt.InsNextSect(str);

			system("cls");
			cout << "PGDN-GoNext INS-InsDownLine DOWN - InsNextSect DEL-DelDown HOME - DelNext  ESC" << endl;
			for (txt.Reset(); !txt.IsEnd(); txt.GoNext()) {
				std::cout << txt.GetLine() << endl;
			}
			count = 1; txt.Reset();
			cout << "Number pCurr " << count << endl; break;
		case ESC: return;
		default:
			break;
		}
	}
}

void main() {
	TTextLink::IntMemSystem(100);
	TText txt;
	int key, count;
	txt.Read("1.txt");
	cout << "PGDN-GoNext INS-InsDownLine DOWN - InsNextSect DEL-DelDown HOME - DelNext  ESC" << endl;
	for (txt.Reset(); !txt.IsEnd(); txt.GoNext()) {
		cout << txt.GetLine() << endl;
	}
	Menu(txt);
	txt.Write("2.txt");
	exit(0);
}