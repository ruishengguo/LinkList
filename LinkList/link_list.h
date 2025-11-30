#pragma once
#include <initializer_list>
#include <exception>
using namespace std;

/*
	container of data for a single node of link list
*/
template<typename T>
class Node {
private:
	// the pointer of the next node
	Node<T>* nxt;
	// the pointer of the last node
	Node<T>* last;
	// the value of the node
	T val;
	template<typename _Ty>
	friend class LinkList;
public:
	Node() : nxt(nullptr), last(nullptr), val() {}
	Node(const T& _val) : nxt(nullptr), last(nullptr), val(_val) {}
	Node(const Node& other) : nxt(nullptr), last(nullptr), val(other.val) {}
	Node& operator=(const T& _val) {
		val = _val;
		return *this;
	}
	Node& operator=(const Node& other) {
		val = other.val;
		return *this;
	}
	virtual ~Node() {
		nxt = nullptr;
		last = nullptr;
	}
};

/*
	the main structure of a link list
*/
template<typename T>
class LinkList {
public:
	// the iterator class
	class iterator {
		friend class LinkList<T>;
		void IndexOutOfRange() {
			throw new exception("List index out of range");
		}
		using pointer = Node<T>*;
		pointer ptr;
	public:
		iterator(pointer p) : ptr(p) {}
	public:
		iterator& operator++() {
			if (ptr == nullptr || ptr->nxt == nullptr) {
				IndexOutOfRange();
			}
			ptr = ptr->nxt;
			return *this;
		}
		iterator operator++(int) {
			if (ptr == nullptr || ptr->nxt == nullptr) {
				IndexOutOfRange();
			}
			ptr = ptr->nxt;
			return ptr->last;
		}
		iterator operator+(size_t cnt) {
			iterator Tmp = *this;
			while (cnt--) {
				Tmp++;
			}
			return Tmp;
		}
		iterator& operator+=(size_t cnt) {
			while (cnt--) {
				ptr++;
			}
			return *this;
		}
		iterator& operator--() {
			if (ptr == nullptr || ptr->last == nullptr) {
				IndexOutOfRange();
			}
			ptr = ptr->last;
			return *this;
		}
		iterator operator--(int) {
			if (ptr == nullptr) {
				return *this;
			}
			iterator Tmp = *this;
			ptr = ptr->last == nullptr ? ptr : ptr->last;
			return Tmp;
		}
		iterator operator-(size_t cnt) {
			iterator Tmp = *this;
			while (cnt-- && Tmp.ptr != nullptr) {
				Tmp.ptr = Tmp.ptr->last;
			}
			return Tmp;
		}
		iterator& operator-=(size_t cnt) {
			while (cnt-- && ptr != nullptr && ptr->last != nullptr) {
				ptr = ptr->last;
			}
			return *this;
		}
		bool operator!=(const iterator& other) const {
			return other.ptr != ptr;
		}
		T& operator* () {
			if (ptr == nullptr) {
				throw new exception("List index out of range.");
			}
			return ptr->val;
		}
		~iterator() {
			ptr = nullptr;
		}
	};
private:
	friend class iterator;
	// notice: Iter_end is always the next of Iter_back except for the list is empty
	iterator Iter_begin = nullptr, Iter_back = nullptr, Iter_end = new Node<T>();
	// the length of the list
	size_t cnt = 0;
public:
	LinkList() {}
	LinkList(initializer_list<T> lst) {
		size_t cnt = sizeof(lst) / sizeof(T);
		for (const T& Elem : lst) {
			push_back(Elem);
		}
	}
	iterator begin() {
		return Iter_begin;
	}
	T front() {
		return *Iter_begin;
	}
	iterator end() {
		return Iter_end;
	}
	T back() {
		return *Iter_back;
	}
	size_t size() {
		return cnt;
	}
	// append element to the back of the list
	void push_back(const T& val) {
		Node<T>* nxt = new Node<T>(val);
		if (Iter_back.ptr == nullptr || Iter_begin.ptr == nullptr) {
			cnt = 1;
			Iter_back = nxt;
			Iter_begin = nxt;
		}
		else {
			Iter_back.ptr->nxt = nxt;
			nxt->last = Iter_back.ptr;
			Iter_back.ptr = nxt;
			cnt++;
		}
		if (Iter_back.ptr != nullptr) {
			Iter_back.ptr->nxt = Iter_end.ptr;
			Iter_end.ptr->last = Iter_back.ptr;
		}
	}
	// push element to the front of the list
	void push_front(const T& val) {
		Node<T>* nxt = new Node<T>(val);
		if (Iter_back.ptr == nullptr || Iter_begin.ptr == nullptr) {
			cnt = 1;
			Iter_back.ptr = nxt;
			Iter_begin.ptr = nxt;
			Iter_back.ptr->nxt = Iter_end.ptr;
			Iter_end.ptr->last = Iter_back.ptr;
		}
		else {
			Iter_begin.ptr->last = nxt;
			nxt->nxt = Iter_begin.ptr;
			Iter_begin.ptr = nxt;
			cnt++;
		}
	}
	// not implemented
	// delete the last node of the list
	void pop_back() {
		throw new exception("This method hasn't been implemented.");
	}
	// not implemented
	// delete the first node of the list
	void pop_front() {
		throw new exception("This method hasn't been implemented.");
	}
	// not implemented
	// delete the given node of the list
	void remove(iterator& Iter) {
		throw new exception("This method hasn't been implemented.");
	}
	// not implemented
	// return the value of the indexed node of the list
	T& operator[](const size_t& Idx) {
		throw new exception("This method hasn't been implemented.");
	}
	// not implemented
	// the copy construct method of the class
	LinkList(const LinkList& other) {
		throw new exception("This method hasn't been implemented.");
	}
	// not implemented
	// copy the other list to this list
	// return *this;
	LinkList& operator=(const LinkList& other) {
		throw new exception("This method hasn't been implemented.");
	}
	// not implemented
	// clear the list
	void clear() {
		throw new exception("This method hasn't been implemented.");
	}
	// not implemented
	// deconstruct the object
	virtual ~LinkList() {
		// throw new exception("This method hasn't been implemented.");
	}
};
