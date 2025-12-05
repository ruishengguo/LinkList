#include "io.h"

LinkList<Product> Product::product_lst;
LinkList<Cart> Data::carts;

bool match_cart(const Cart& cart, const string& userName) {
	return cart.getOwnerName() == userName;
}
bool match_req(const BuyRequest& req, const string& productName) {
	return req.product.getName() == productName;
}
bool match_prod(const Product& prodPtr, const string& productName) {
	return prodPtr.getName() == productName;
}


// 输出商品名、商品单价、购买量
std::ostream& operator<<(std::ostream& cout, const BuyRequest& req) {
	return cout << "购买商品: " << req.product.getName() << "(单价：" << req.product.getPrice() << ") - " << req.count << "件" << std::endl;
}

// 从文件中读取所有商品及单价
void readAllProducts() {
    std::ifstream fin("products.txt");
    if (!fin) return;
    string word;
    string number;
    while (fin >> word)
    {
        fin >> number;
        Product* p = new Product(word, stod(number));
        p->push();
    }
}
// 购买
void purchase(const string& userName, const string& prodName, const int& count) {

}
// 取消购买
void cancel(const string& userName, const string& prodName, const int& count) {

}
// 查询所有购买
void query(const string& userName) {
    cout << "\n购买记录查询" << endl;
    cout << "════════════════════════════════════════" << endl;
    cout << "用户: " << userName << endl;

    // 在全局购物车链表中查找该用户
    auto cartIt = query(Data::carts.begin(), Data::carts.end(), userName, match_cart);

    if (cartIt == Data::carts.end())
    {
        cout << "错误: 用户 \"" << userName << "\" 不存在" << endl;
        cout << "════════════════════════════════════════" << endl;
        return;
    }

    cout << "────────────────────────────────────────" << endl;

    if ((*cartIt).size() == 0)
    {
        cout << "该用户暂无购买记录" << endl;
        cout << "════════════════════════════════════════" << endl;
        return;
    }

    int index = 1;
    double totalCost = 0.0;
    int totalItems = 0;

    // 使用 Cart 的 begin() 和 end() 直接遍历
    for (const BuyRequest& req: *cartIt)
    {
        // 使用 operator<< 输出
        cout << index++ << ". " << req << endl;

        // 累加统计
        totalCost += req.product.getPrice() * req.count;
        totalItems += req.count;
    }

    // 输出统计信息
    cout << "════════════════════════════════════════" << endl;
    cout << "   统计信息:" << endl;
    cout << "   商品总数: " << totalItems << " 件" << endl;
    cout << "   总计金额: ￥" << totalCost << endl;
    cout << "════════════════════════════════════════" << endl;

}
// 清空购物车
void clear(const string& userName) {
    cout << "\n清空购物车" << endl;
    cout << "════════════════════════════════════════" << endl;

    // 在全局购物车链表中查找该用户
    auto cartIt = query(Data::carts.begin(), Data::carts.end(), userName, match_cart);

    if (cartIt == Data::carts.end())
    {
        cout << "错误: 用户 \"" << userName << "\" 不存在" << endl;
        cout << "════════════════════════════════════════" << endl;
        return;
    }
    Data::carts.remove(cartIt);

    // 输出结果
    cout << "────────────────────────────────────────" << endl;
    cout << "   已清空购物车！" << endl;
    cout << "════════════════════════════════════════" << endl;

}
// 结账
void checkout(const string& userName) {
    cout << "\n结账操作" << endl;
    cout << "════════════════════════════════════════" << endl;
    cout << "用户: " << userName << endl;
    cout << "────────────────────────────────────────" << endl;

    // 在全局购物车链表中查找该用户
    auto cartIt = query(Data::carts.begin(), Data::carts.end(), userName, match_cart);

    if (cartIt == Data::carts.end())
    {
        cout << "错误: 用户 \"" << userName << "\" 不存在" << endl;
        cout << "════════════════════════════════════════" << endl;
        return;
    }

    // 显示购物车内容并计算总价
    cout << "购物车内容:" << endl;
    cout << "────────────────────────────────────────" << endl;

    double totalCost = 0.0;
    int totalItems = 0;

    for (const BuyRequest& request: *cartIt)
    {
        totalCost += request.product.getPrice() * request.count;
        totalItems += request.count;

        cout << request << endl;
    }
    // 显示账单
    cout << "────────────────────────────────────────" << endl;
    cout << "   账单汇总:" << endl;
    cout << "   商品总数: " << totalItems << " 件" << endl;
    cout << "   商品总额: ￥" << totalCost << endl;

    // 清空购物车
    Data::carts.remove(cartIt);

    // 打印收据
    cout << "────────────────────────────────────────" << endl;
    cout << "   电子收据" << endl;
    cout << "   用户: " << userName << endl;
    cout << "   金额: ￥" << totalCost << endl;
    cout << "   状态: 已支付" << endl;
    cout << "════════════════════════════════════════" << endl;
    cout << "   感谢光临，欢迎下次再来！" << endl;
    cout << "════════════════════════════════════════" << endl;
}