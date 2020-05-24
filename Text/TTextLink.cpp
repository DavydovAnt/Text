#include "TTextLink.h"
#include "TText.h"

void TTextLink::IntMemSystem(int size) {

	MemHeader.pFirst = (TTextLink*)new char[sizeof(TTextLink)*size];
	MemHeader.pFree = MemHeader.pFirst;
	MemHeader.pLast = MemHeader.pFirst + (size - 1);
	TTextLink *pLink = MemHeader.pFirst;
	for (int i = 0; i < size - 1; i++) {
		pLink->str[0] = '\0';
		pLink->pNext = pLink + 1;
		pLink++;
	}
	pLink->pNext = NULL;
}
void * TTextLink:: operator new(size_t size) {
	TTextLink* pLink = MemHeader.pFree;
	if (MemHeader.pFree != NULL) MemHeader.pFree = MemHeader.pFree->pNext;
	return pLink;
}
void  TTextLink::operator delete(void *pM) {
	TTextLink *pLink = (TTextLink*)pM;
	pLink->pNext = MemHeader.pFree;
	MemHeader.pFree = pLink;
}
void TTextLink::PrintFreeLink(int add) {              // Программа пропускает строчку кода, где вызывается данная функция даже в отладке если не передавать никаких параметров
	cout << endl << "List of free links" << endl;
	for (TTextLink *pLink = MemHeader.pFree; pLink != NULL; pLink = pLink->pNext) {
		cout << pLink->str << endl;
	}
}
 void TTextLink::MemCleaner(TText &txt) {
	for (txt.Reset(); !txt.IsEnd(); txt.GoNext()) {
		string tmp = "&&&";
		tmp += txt.GetLine();
		txt.SetLine(tmp);
	}
	for (TTextLink *pLink = MemHeader.pFree; pLink != NULL; pLink = pLink->pNext) {
		strcpy_s(pLink->str, "&&&");
	}
	for (TTextLink *pLink = MemHeader.pFirst; pLink <= MemHeader.pLast; pLink++) {
		if (strstr(pLink->str, "&&&") != NULL) {
			strcpy_s(pLink->str, pLink->str + 3);
		}
		else {
			delete pLink;
		}
	}
}