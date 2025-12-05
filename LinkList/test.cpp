#include "io.h"
#include <iostream>
#include <vector>
using namespace std;

bool dec(const int& a, const int& b) {
	return a == b + 1;
}

int main() {
	readAllProducts();
	for (Product* prod : Product::product_lst) {
		cout << prod->getName() << ' ' << prod->getPrice() << endl;
	}
	Data::carts.push_back(Cart("a"));
	//Data::carts[0].push_back({ *Product::product_lst[0], 3 });
	//Data::carts[0].push_back({ *Product::product_lst[1], 2 });
	query("a");
	checkout("a");
	query("a");
}
int main1() {
	//vector<int> lst2 = { 1, 2, 3 }, lst3 = {1, 2, 3};
	//lst3.erase(lst2.begin(), lst2.begin());
	LinkList<int> lst1;
	for (int& i : lst1) {
		cout << i;
	}
	LinkList<int> lst({ 1, 2, 3 });
	for (int& i : lst) {
		cout << i << ' ';
	}
	for (int i = 0; i < 10; i++) {
		lst.push_back(i);
	}
	for (int& i : lst) {
		cout << i << ' ';
	}
	lst.clear();
	for (int& i : lst) {
		cout << i << ' ';
	}
	for (int i = 0; i < 10; i++) {
		lst.push_front(i);
	}
	for (int& i : lst) {
		cout << i << ' ';
	}
	cout << *(lst.begin() + 6) << ' ' << *(lst.end() - 3) << endl;
	for (int& i : lst) {
		cout << i << ' ';
	}
	return 0;
}