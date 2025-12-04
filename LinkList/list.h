#pragma once
#include <initializer_list>
#include <exception>

using std::size_t;
using std::exception;
using std::initializer_list;

template<typename T>
class simple_vector {
	T* Lst;
	size_t Cnt = 0;
	size_t Cap = 100;
	void __extend_capacity() {
		T* new_lst = new T[Cap * 3 / 2];
		Cap = Cap * 3 / 2;
		for (size_t Idx = 0; Idx < Cnt; Idx++) {
			new_lst[Idx] = Lst[Idx];
		}
		Lst = new_lst;
	}
public:
	simple_vector() {
		__extend_capacity();
	}
	size_t size() {
		return Cnt;
	}
	void push_back(const T& Elem) {
		Lst[Cnt++] = Elem;
		if (Cnt >= Cap * 4 / 5) {
			__extend_capacity();
		}
	}
	T& operator[](const size_t& Idx) {
		if (Idx < 0 || Idx >= Cnt) {
			throw new exception("List index out of range.");
		}
		return Lst[Idx];
	}
};
