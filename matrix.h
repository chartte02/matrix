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
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

extern int n;//现有矩阵个数 
extern bool fraction_fail;
extern bool calculate_success;
extern int precision;

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
//		while (num >= pow(10, precision) || den >= pow(10, precision)){
//			num /= 10;
//			den /= 10;
//			if (den < 1000){
//				break;
//			}
//		}
	}
	long long abs(long long x){//取绝对值 
		if (x < 0) {
			return -1 * x;
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
		den = 1 * pow(10, precision);
		num = n * pow(10, precision);
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
		double x = double(*this) + double(other);
		fraction result(x);
		return result;
	}
	fraction operator-(const fraction &other){//-运算符重载 
		double x = double(*this) - double(other);
		fraction result(x);
		return result;
	}
	fraction operator-(){//-运算符重载 
		fraction result(- num, den);
		return result;
	}
	fraction operator*(const fraction &other){//*运算符重载 
		double x = double(*this) * double(other);
		fraction result(x);
		return result;
	}
	fraction operator*(const int &other){//*运算符重载 
		double x = double(*this) * other;
		fraction result(x);
		return result;
	}
	fraction operator/(const fraction &other){// / 运算符重载 
		if (other.num == 0){
			calculate_success = false;
			return *this;
		}
		double x = double(*this) / double(other);
		fraction result(x);
		return result;
	}
	fraction& operator+=(const fraction &other){//+=
		double x = double(*this) + double(other);
		fraction result(x);
		num = result.num;
		den = result.den;
		return *this;
	}
	fraction& operator-=(const fraction &other){//-=
		double x = double(*this) - double(other);
		fraction result(x);
		num = result.num;
		den = result.den;
		return *this;
	}
	explicit operator bool() const {//fraction转bool 
        return num != 0; // 例如，分子不为零时视为 true
    }
    operator double() const {
        return static_cast<double>(num) / den;
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
	void matrix_create_diagonal(int i, int a,int b);//生成函数（随机对角矩阵）
	void matrix_create_upper_triangular(int i, int a, int b);//生成函数（随机上三角矩阵）
	void matrix_cin_diagonal(int i);//用户输入对角线上元素的对角矩阵
	void matrix_scalar(int i, fraction k);//对角线上元素为k的纯量矩阵


    void matrix_store(); // 存储函数（任意矩阵）
    void matrix_input();//输入函数 （二维矩阵）
    void matrix_display(int no_name = 0, int type = 0);//输出函数（输出完整矩阵）（无需存储）

    matrix matrix_transpose();//转置矩阵
    matrix matrix_inverse();//逆矩阵
    matrix matrix_simplify_1();//化简为行阶梯形矩阵
    matrix matrix_simplify_2(int *the_number_of_pivots=nullptr);//化简为简化行阶梯形矩阵
    void matrix_simplify_3();
    fraction matrix_det();//行列式
    matrix matrix_adjoint();//伴随矩阵
    matrix matrix_ortho_gs();//正交化
	matrix matrix_R();//QR分解中的R 
	matrix matrix_eigenvalue();//特征值 

    void matrix_modify_name(string na);
    matrix matrix_intercept_row(const matrix&m,int r1,int r2);
    matrix matrix_intercept_col(const matrix&m,int c1,int c2);
    matrix matrix_intercept_dia(const matrix &m,int d);
    void matrix_modify();
    void matrix_intercept();
    matrix create_argumentation(const matrix&m1,const matrix &m2);
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
void oth();
void eig();
#endif
