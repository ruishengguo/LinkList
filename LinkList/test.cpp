#include "link_list.h"
#include <iostream>

int main() {
	LinkList<int> lst({ 1, 2, 3 });
	for (int i = 0; i < 10; i++) {
		lst.push_back(i);
	}
	for (int i = 0; i < 5; i++) {
		lst.push_front(i);
	}
	cout << *(lst.begin() + 6) << ' ' << *(lst.end() - 3) << endl;
	for (int& i : lst) {
		cout << i << ' ';
	}
}