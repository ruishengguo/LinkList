#pragma once
#include "link_list.h"

template <typename T, class _Pr>
void sort(typename LinkList<T>::iterator& begin, typename LinkList<T>::iterator& end, _Pr pred = std::greater<T>) {
	throw new exception("This method hasn't been implemented.");
}

template <typename T>
void reverse(typename LinkList<T>::iterator& begin, typename LinkList<T>::iterator& end) {
	throw new exception("This method hasn't been implemented.");
}

template<typename T>
typename LinkList<T>::iterator find(typename LinkList<T>::iterator begin, typename LinkList<T>::iterator end, const T& Elem) {
	throw new exception("This method hasn't been implemented.");
}

template<typename T>
void extend(LinkList<T>& lst1, const LinkList<T>& lst2) {
	throw new exception("This method hasn't been implemented.");
}

template<typename T>
void merge(LinkList<T>& lst1, LinkList<T>& lst2) {
	throw new exception("This method hasn't been implemented.");
}