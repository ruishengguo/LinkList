#pragma once
#include "cart_basic.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;

struct Data {
	static LinkList<Cart> carts;
};

// 输出商品名、商品单价、购买量
std::ostream& operator<<(std::ostream& cout, const BuyRequest& req);

// 从文件中读取所有商品及单价
void readAllProducts();
// 购买
void purchase(const string& userName, const string& prodName, const int& count);
// 取消购买
void cancel(const string& userName, const string& prodName, const int& count);
// 查询所有购买
void query(const string& userName);
// 清空购物车
void clear(const string& userName);
// 结账
void checkout(const string& userName);
