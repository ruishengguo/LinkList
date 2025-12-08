#include "io.h"
using std::to_string;

struct action {
	void (*method)();
	string explain;
};

template <typename T>
T input(string msg = "", string err = "") {
	T result;
	while (true) {
		cout << msg;
		cout.flush();
		try {
			cin >> result;
			break;
		}
		catch(exception){
			cout << err << endl;
		}
	}
	return result;
}

void input_purchase() {
	string name = input<string>("输入用户名：");
	string prod_name = input<string>("购买什么物品：");
	unsigned int count = input<unsigned int>("数量：", "请输入正整数");
	purchase(name, prod_name, count);
}
void input_cancel() {
	string name = input<string>("输入用户名：");
	string prod_name = input<string>("取消购买什么物品：");
	unsigned int count = input<unsigned int>("数量：", "请输入正整数");
	cancel(name, prod_name, count);
}
void input_query() {
	string name = input<string>("输入用户名：");
	query(name);
}
void input_clear() {
	string name = input<string>("输入用户名：");
	char dec = input<char>("是否确认？(Y/n)：");
	if (dec == 'Y') {
		clear(name);
	}
	else {
		cout << "操作已取消" << endl;
	}
}
void input_checkout() {
	string name = input<string>("输入用户名：");
	checkout(name);
}
void prt_prodlst() {
	for (const Product& p : Product::product_lst) {
		cout << p.getName() << "\t-\t" << p.getPrice() << endl;
	}
}

int main() {
	readAllProducts();
	LinkList<action> act_lst({
		{prt_prodlst, "查看商品种类"},
		{input_purchase, "登记购买商品"},
		{input_cancel, "登记取消购买商品"},
		{input_query, "查询所有购买"},
		{input_clear, "清空购物车"},
		{input_checkout, "登记结账"}
		});
	string op_query = "输入操作：\n0 - 退出";
	int cnt = 1;
	for (const action& a : act_lst) {
		op_query += "\n" + to_string(cnt++) + " - " + a.explain;
	}
	op_query += "\n>>> ";
	while (true) {
		int op_code = input<int>(op_query);
		if (op_code == 0) {
			cout << "正在退出";
			break;
		}
		else if (op_code > act_lst.size()) {
			cout << "无效输入！" << endl;
		}
		else {
			system("cls");
			act_lst[op_code - 1].method();
		}
		system("pause");
		system("cls");
	}
}
