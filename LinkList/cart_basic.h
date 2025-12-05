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
    static LinkList<Product> product_lst;
    Product(const string& _Name = "", double _Price = 0.0) : name(_Name), price(_Price) {};
    void push() {
        product_lst.push_back(*this);
    }
    // getter方法
    string getName() const { return name; };
    double getPrice() const { return price; };
};

struct BuyRequest {
    Product product;
    int count = 0;
};

class Cart: public LinkList<BuyRequest>
{
private:
    string ownerName;
public:
    // 构造函数
    Cart(const string& owner = "") : ownerName(owner) {}
    string getOwnerName() const { return ownerName; };
};
