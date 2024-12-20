//文件：matrix.h
#ifndef matrix_h

#define matrix_h
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>
using namespace std;

extern int n;//现有矩阵个数 
extern bool fraction_fail;
extern bool calculate_success;

class fraction {
public:	
	long long num, den;//分子，分母
	
	long long gcd (long long a, long long b) {//求最大公约数 
		if(a < b){
			swap(a,b);
		}
		long long c;
		while(b){
			c = a % b;
			a = b;
			b = c;
		}
		return a;
	}
	void fraction_reduct() {//分数化简 
		if (num && den){
			long long x = gcd(abs(num), den);
			num = num / x;
			den = den / x;
		}
		else {
			den = 1ll;
		}
	}
	long long abs(long long x){//取绝对值 
		if (x < 0) {
			return -x;
		}
		return x;
	}
	fraction(long long n = 1ll, long long d = 1ll) : num(n), den(d) {//构造函数 
		if (den == 0){
			fraction_fail = 1;
			cout << "Error : the denominator is 0 " << endl;
			return;
		}
		if (den < 0){
			den = den * -1;
			num = num * -1;
		}
		fraction_reduct();
	}
	fraction(int n) : num(n), den(1ll) {}//int转fraction
	fraction(double n){//double转fraction 
		int len, x;
		x = n / 1;
		for (len = 0; ; len++){
			x = n / 1;
			if (n != x){
				n *= 10;
			
				den *= 10;
			} else{
				break;
			}
		}
		num = n;
		fraction_reduct();
	}
	void fraction_create(){//生成函数 
		if (den == 0){
			fraction_fail = 1;
			cout << "Error : the denominator is 0 " << endl;
			return;
		}
		if (den < 0){
			den = den * -1;
			num = num * -1;
		}
		fraction_reduct();
	}
	fraction& operator=(const fraction &other){//赋值运算符重载 
		den = other.den;
		num = other.num;
	}
	fraction operator+(const fraction &other){//+运算符重载 
		fraction result(num * other.den + den * other.num, den * other.den);
		return result;
	}
	fraction operator-(const fraction &other){//-运算符重载 
		fraction result(num * other.den - den * other.num, den * other.den);
		return result;
	}
	fraction operator-(){//-运算符重载 
		fraction result(- num, den);
		return result;
	}
	fraction operator*(const fraction &other){//*运算符重载 
		fraction result(num * other.num, den * other.den);
		return result;
	}
	fraction operator/(const fraction &other){// / 运算符重载 
		if (other.num == 0){
			calculate_success = false;
			return *this;
		}
		fraction result(num * other.den, den * other.num);
		return result;
	}
	fraction& operator+=(const fraction &other){//+=
		num = num * other.den + den * other.num;
		den = den * other.den;
		fraction_reduct();
		return *this;
	}
	fraction& operator-=(const fraction &other){//-=
		num = num * other.den - den * other.num;
		den = den * other.den;
		fraction_reduct();
		return *this;
	}
	explicit operator bool() const {//fraction转bool 
        return num != 0; // 例如，分子不为零时视为 true
    }
	friend ostream& operator<<(ostream &os, const fraction &obj){//输出流重载 
		if (obj.den != 1){
			os << obj.num << '/' << obj.den;
		} else{
			os << obj.num;
		}
		return os;
	}
	friend istream& operator>>(istream &in, fraction &obj){//输入流重载 
		string str;
		in >> str;
		int k = str.size();
		long long x = 0, y = 0;
		int sign = 0;
		int lenx = 0, leny = 0;
		bool flagf = 1, flagx = 0, flagy = 0;
		for (int i = 0; i < k; i++){
			if (str[i] == '-') {
				sign ++;
			} else if (str[i] == '/'){
				flagf = 0;
			} else if (str[i] == '.' && flagf){
				flagx = 1;
			} else if (str[i] == '.' && !flagf){
				flagy = 1;
			} else {
				if (flagf) {
					x = 10 * x + (str[i] - '0');
					if (flagx){
						lenx ++;
					}
				} else {
					y = 10 * y + (str[i] - '0');
					if (flagy){
						leny ++;
					}
				}
			} 
		}
		if (flagf){
			if (sign % 2){
				obj.num = -1 * x;
				obj.den = 1ll;
			} else{
				obj.num = x;
				obj.den = 1ll;
			}		
		} else {
			if (sign % 2){
				obj.num = -1 * x;
				obj.den = y;
			} else{
				obj.num = x;
				obj.den = y;
			}	
		}
		if (flagx) {
			for (int i = 0; i < lenx; i++){
				obj.den *= 10;
			} 
		}
		if (flagy) {
			for (int i = 0; i < leny; i++){
				obj.num *= 10;
			} 
		}
		obj.fraction_create();
		return in;
	}
	bool operator==(const fraction &other){
		if (den == other.den && num == other.num){
			return 1;
		}
		return 0;
	}
	bool operator!=(const fraction &other){
		if (den == other.den && num == other.num){
			return 0;
		}
		return 1;
	}
};

//template <typename T>
class matrix {
public:
    string name;//名称
    int No;//序号
    int row, col;//行列
    fraction **data;//元素二维数组

    matrix(int r = 0, int c = 0) : row(r), col(c) {} // 默认构造函数
    matrix(const matrix &other); // 拷贝构造函数
    matrix& operator=(const matrix &other); // 重载赋值运算符
    bool operator==(const matrix& other); //重载相等运算符
    matrix operator+(const matrix& other);// 重载加法运算符
    matrix operator-(const matrix& other);// 重载减法运算符
    matrix operator*(const matrix& other);// 重载乘法运算符
    matrix operator^(int k);//重载幂运算符
    ~matrix(); // 析构函数

    void matrix_create(int r = 0, int c = 0);//生成函数（零矩阵）
    void matrix_create_E (int order);//生成函数（单位矩阵）
    void matrix_create_1(int order,int i, int j);//生成函数（初等矩阵1）
    void matrix_create_2(int order,int i, fraction k);//生成函数（初等矩阵2）
    void matrix_create_3(int order,int i, int j, fraction k);//生成函数（初等矩阵3）
    void matrix_create_random(int i, int j, double a, double b);//生成函数（随机矩阵）
    void matrix_create_diagonal(int i,int j, double a,double b);//生成函数（随机对角矩阵）
    void matrix_create_upper_triangular(int i, int j, double a, double b);//生成函数（随机上三角矩阵）

    void matrix_store(); // 存储函数（任意矩阵）
    void matrix_input();//输入函数 （二维矩阵）
    void matrix_display(int no_name = 0);//输出函数（输出完整矩阵）（无需存储）

    matrix matrix_transpose();//转置矩阵
    matrix matrix_inverse();//逆矩阵
    matrix matrix_simplify_1();//化简为行阶梯形矩阵
    matrix matrix_simplify_2(int *the_number_of_pivots=nullptr);//化简为简化行阶梯形矩阵
    void matrix_simplify_3();
    fraction matrix_det();//行列式

    void matrix_modify_name(string na);
    void matrix_intercept_row(int r2,int r1);
    void matrix_intercept_col(int c2,int c1);
    void matrix_intercept_dia(int d);
    void matrix_modify();
    void matrix_intercept();
    void create_argumentation(const matrix&m1,const matrix &m2);
    void matrix_modify_data(int i,int j,fraction data_);

    void solve_system_of_linear_equtions(matrix &m1, matrix &m2);
};

int matrix_search (string na); //查找函数 （给名字返回编号）
void transpose(); //转置函数（前端）
void matrix_calculate();//计算函数（前端）
void det();//行列式（前端）
void output();//输出函数（前端）
void del();//删除函数
void clear();//清空函数
#endif
