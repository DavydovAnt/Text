#pragma once
#include <string>
#include "TStack.h"
//Здесь было написано #include "TText.h", программа не компилировалась и выдавала непонятные ошибки, почему?
#include <fstream>
#include <iostream>
using namespace std;
class TText;
class TTextLink;

struct TTextMem {
	TTextLink* pFirst;
	TTextLink* pLast;
	TTextLink* pFree;
	friend class TTextLink;
};


class TTextLink {
protected:
	static TTextMem MemHeader;
public:
	TTextLink *pNext, *pDown;
	char str[81];
	TTextLink(const char *c = NULL, TTextLink *pN = NULL, TTextLink *pD = NULL) {
		pNext = pN;
		pDown = pD;
		if (c == NULL) str[0] = '\0'; else
			strcpy_s(str, c);
	}
	static void IntMemSystem(int size);
	void * operator new(size_t size);
	void operator delete(void *pM);
	static void PrintFreeLink();
	static void MemCleaner(TText &txt);
	friend class TText;
};
