#pragma once
#include <iostream> 
template <class T>
class Tstack {
	T* arr;
	int size;
	int num;
public:
	Tstack(int _size = 20) {
		if (_size < 0)throw 1;
		size = _size;
		arr = new T[size];
		num = -1;
	}
	~Tstack() {
		delete[] arr;
	}

	Tstack(const Tstack<T>& a) {
		size = a.size;
		num = a.num;
		arr = new T[size];
		for (int i = 0; i <= num; i++) {
			arr[i] = a.arr[i];
		}
	}

	bool IsEmpty()const {
		if (num == -1)return true;
		return false;
	}

	void push(const T& a) {
		if (IsFull()) throw 1;
		arr[num + 1] = a;
		num++;
	}

	T pop() {
		if (IsEmpty())throw - 1;
		num--;
		return arr[num + 1];
	}
	T top() {
		if (IsEmpty()) throw - 1;
		return arr[num];
	}
	void clear() {
		T a;
		while (!(IsEmpty())) { a = pop(); }
	}
	bool IsFull() {
		if (num == (size - 1))return true;
		return false;
	}
};