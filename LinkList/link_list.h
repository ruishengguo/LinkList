#pragma once
#include <initializer_list>
#include <exception>

using std::size_t;
using std::exception;
using std::initializer_list;

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
	// the length of the list
	size_t cnt = 0;
public:
	// the iterator class
	class iterator {
		friend class LinkList<T>;
		void IndexOutOfRange() {
			throw new exception("List index out of range");
		}
		using pointer = Node<T>*;
		pointer ptr;
		LinkList<T>* master;
		iterator(pointer p, LinkList<T>* _master) : ptr(p), master(_master) {}
	public:
		iterator& operator++() {
			if (ptr == nullptr || ptr->nxt == nullptr) {
				IndexOutOfRange();
			}
			ptr = ptr->nxt;
			return *this;
		}
		iterator operator++(int) {
			iterator Temp = *this;
			if (ptr == nullptr || ptr->nxt == nullptr) {
				IndexOutOfRange();
			}
			ptr = ptr->nxt;
			return Temp;
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
		iterator& operator=(const pointer& pt) {
			ptr = pt;
			return *this;
		}
		bool operator!=(const iterator& other) const {
			return other.ptr != ptr;
		}
		bool operator==(const iterator& other) const {
			return other.ptr == ptr;
		}
		// decide whether two iterators belong to the same list
		bool operator&(const iterator& other) const {
			return other.master == master;
		}
		T& operator* () {
			if (ptr == nullptr) {
				throw new exception("List index out of range.");
			}
			return ptr->val;
		}
		~iterator() {
			ptr = nullptr;
			master = nullptr;
		}
	};
	friend class iterator;
private:
	// notice: Iter_end is always the next of Iter_back except for the list is empty
	iterator Iter_end = { new Node<T>(), this };
	iterator Iter_begin = Iter_end, Iter_back = Iter_end;
public:
	LinkList() {}
	LinkList(initializer_list<T> lst) {
		for (const T& Elem : lst) {
			push_back(Elem);
		}
	}
	iterator begin() const {
		return Iter_begin;
	}
	T front() const {
		return *Iter_begin;
	}
	iterator end() const {
		return Iter_end;
	}
	T back() const {
		return *Iter_back;
	}
	size_t size() const {
		return cnt;
	}
	// append element to the back of the list
	void push_back(const T& val) {
		Node<T>* nxt = new Node<T>(val);
		if (Iter_back == Iter_end || Iter_begin == Iter_end) {
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
		if (Iter_back != Iter_end) {
			Iter_back.ptr->nxt = Iter_end.ptr;
			Iter_end.ptr->last = Iter_back.ptr;
		}
	}
	// push element to the front of the list
	void push_front(const T& val) {
		Node<T>* nxt = new Node<T>(val);
		if (Iter_back == Iter_end || Iter_begin == Iter_end) {
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
	// delete the last node of the list
	void pop_back() {
		if (Iter_back == Iter_end) {
			throw new exception("pop_back() called on empty link list");
			return;
		}
		cnt--;
		Node<T>* temp = Iter_back.ptr;
		if (cnt == 0) {
			delete temp;
			Iter_begin = Iter_back = Iter_end;
		}
		else {
			Iter_back--;
			delete temp;
			Iter_back.ptr->nxt = Iter_end.ptr;
			Iter_end.ptr->last = Iter_back.ptr;
		}		
	}
	// delete the first node of the list
	void pop_front() {
		iterator it = Iter_begin;
		if (Iter_begin == Iter_end) {
			throw new exception("pop_front() called on empty link list");
			return;
		}
		cnt--;
		Node<T>* temp = Iter_begin.ptr;
		if (cnt == 0) {
			delete temp;
			Iter_begin = Iter_back = Iter_end;
		}
		else {
			Iter_begin++;
			delete temp;
		}
	}
	// delete the given node of the list
	void remove(iterator& Iter) {
		if (Iter == Iter_end) {
			throw new exception("List index out of range");
		}
		if (Iter.master != this) {
			throw new exception("Remove range out of the list");
		}
		cnt--;
		if (Iter == Iter_begin) {
			return pop_front();
		}
		else if (Iter == Iter_back) {
			return pop_back();
		}
		else {
			(Iter - 1).ptr->nxt = (Iter + 1).ptr;
			(Iter + 1).ptr->last = (Iter - 1).ptr;
			delete Iter.ptr;
			Iter = Iter_end;
		}
	}
	// return the value of the indexed node of the list
	T& operator[](const size_t& Idx) {
		return *(begin() + Idx);
	}
	// the copy construct method of the class
	LinkList(const LinkList& other) {
		for (const T& Elem : other) {
			push_back(Elem);
		}
	}
	// copy the other list to this list
	// return *this;
	LinkList<T>& operator=(const LinkList<T>& other) {
		clear();
		for (const T& Elem : other) {
			push_back(Elem);
		}
		return *this;
	}
	// clear the list
	void clear() {
		for (; Iter_begin != Iter_end; ) {
			Node<T>* cur = Iter_begin.ptr;
			Iter_begin++;
			delete cur;
		}
		cnt = 0;
		Iter_end.ptr->nxt = nullptr;
		Iter_end.ptr->last = nullptr;
		Iter_begin = Iter_end;
		Iter_back = Iter_end;
	}
	// deconstruct the object
	virtual ~LinkList() {
		clear();
		delete Iter_end.ptr;
	}
};
