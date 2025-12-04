#pragma once
#include "link_list.h"
#include "list_algo.h"
#include <string>

using std::string;

class Product
{
private:
    string name;
    double price;
public:
    // static container for pointers of all constructed product object
    static LinkList<Product*> product_lst;
    Product(const string& _Name = "", double _Price = 0.0) : name(_Name), price(_Price) { product_lst.push_back(this); };
    // getter方法
    string getName() const { return name; };
    double getPrice() const { return price; };
};

struct BuyRequest {
    Product product;
    int count;
};

class Cart
{
private:
    string ownerName;
    LinkList<BuyRequest> itemList;
public:
    // 构造函数
    Cart(const string& owner = "") : ownerName(owner) {}
    LinkList<BuyRequest>::iterator begin() { return itemList.begin(); }
    LinkList<BuyRequest>::iterator end() { return itemList.end(); }
    // ========== 基本操作 ==========
    string getOwnerName() const { return ownerName; };
    void clear() { itemList.clear(); };
    bool empty() const { return itemList.size() == 0; };
};
