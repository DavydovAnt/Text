#pragma once
#include <string.h>
#include "TStack.h"
#include "TTextLink.h"
#include <fstream>
#include <iostream>
using namespace std;

class TText {
	TTextLink *pFirst, *pCurr;
	Tstack <TTextLink *> stack;
public:
	TText() { pFirst = NULL;
	stack.clear();
	}
	~TText(){}
	void GoFirstLink() { pCurr = pFirst;
	stack.clear();
	}
	void GoDownLink() {
		if (pCurr== NULL) throw - 1;
		if (pCurr->pDown==NULL) return;
		stack.push(pCurr);
		pCurr = pCurr->pDown;
	}
	void GoNextLink() {
		if (pCurr== NULL) throw -1;
		if (pCurr->pNext == NULL) return;
		stack.push(pCurr);
		pCurr = pCurr->pNext;
	}
	void GoPrevLink() {
		if (pCurr==NULL)throw - 1;
		if (pCurr == pFirst)return;
		pCurr = stack.pop();
	}
	void SetLine(string str1) {
		if (pCurr == NULL)throw - 1;
		strcpy_s(pCurr->str, str1.c_str());
	}
	string GetLine() {  
		if (pCurr == NULL) throw - 1;   
		return string(pCurr->str); 
	}
	void InsNextLine(string st) {
		if (pCurr == NULL) throw - 1;
		TTextLink *p = new TTextLink(st.c_str());
		p->pNext = pCurr->pNext;
		pCurr->pNext = p;
	}
	void InsNextSect(string s) {
		if (pCurr == NULL)throw - 1;
		TTextLink *p = new TTextLink(s.c_str());
		p->pDown = pCurr->pNext;
		pCurr->pNext = p;
	}
	void InsDownSect(string s) {
		if (pCurr == NULL)throw - 1;
		TTextLink *p = new TTextLink(s.c_str());
		p->pDown = pCurr->pDown;
		pCurr->pDown = p;
		}
	void InsDownLine(string s) {
		if (pCurr == NULL)throw - 1;
		TTextLink *p = new TTextLink(s.c_str());
		p->pNext = pCurr->pDown;
		pCurr->pDown = p;
	}
	void DelNext() {
		if (pCurr == NULL)throw - 1;
		if (pCurr->pNext == NULL)return;
		TTextLink *tmp = pCurr->pNext;
		pCurr->pNext = tmp->pNext;
		delete tmp;
	}
	void DelDown() {
		if (pCurr == NULL)throw - 1;
		if (pCurr->pDown == NULL)return;
		TTextLink *tmp = pCurr->pDown;
		pCurr->pDown = tmp->pNext;
		delete tmp;
	}
	void Read(string fn) {
		ifstream ifs(fn);
		pFirst = ReadRec(ifs);
	}
	TTextLink* ReadRec(ifstream &ifs) {
		TTextLink *pHead, *p, *tmp;
		pHead = NULL;
		p = NULL;
		char str[81];
		while (!ifs.eof()) {
			ifs.getline(str, 80, '\n');
			if (str[0] == '}')break;
			else if (str[0] == '{')p->pDown = ReadRec(ifs);
			else {
				tmp = new TTextLink(str);
				if (pHead == NULL)pHead = p = tmp;
				else {
					p->pNext = tmp;
					p = tmp;
				}
			}
		}
		return pHead;
	}
	void Write(string fn) {
		ofstream ofs(fn);
		WriteRec(ofs, pFirst);
	}
	void WriteRec(ofstream &ofs, TTextLink *p) {
		ofs << p->str << endl;
			if (p->pDown) {
				ofs << '{' << endl;
				WriteRec(ofs, p->pDown);
				ofs << '}' << endl;
			}
			if (p -> pNext != NULL) {
				WriteRec(ofs, p->pNext);
			}	
	}
	int Reset() {
		stack.clear();
		pCurr = pFirst;
		if (pCurr != NULL) {
			stack.push(pCurr);
			if (pCurr->pNext != NULL) stack.push(pCurr->pNext);
			if (pCurr->pDown != NULL) stack.push(pCurr->pDown);
		}
		return IsEnd();
	}
	int IsEnd() {
		return stack.IsEmpty();
	}
	int GoNext() {
		if (!IsEnd()) {
			pCurr = stack.pop();
			if (pCurr != pFirst) {
				if (pCurr->pNext != NULL) stack.push(pCurr->pNext);
				if (pCurr->pDown != NULL) stack.push(pCurr->pDown);
			}
			return true;
		}
		return false;
	}
};