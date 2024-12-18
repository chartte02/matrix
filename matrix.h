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

using namespace std;

class matrix {
public:
	string name;//名称 
	int No;//序号 
	int row, col;//行列 
	double **data;//元素二维数组 
    
	matrix(int r = 0, int c = 0) : row(r), col(c) {} // 默认构造函数
	matrix(const matrix &other); // 拷贝构造函数
	matrix& operator=(const matrix &other); // 重载赋值运算符
	matrix operator+(const matrix& other);// 重载加法运算符
	matrix operator-(const matrix& other);// 重载减法运算符
	matrix operator*(const matrix& other);// 重载乘法运算符
	matrix operator^(int k);//重载幂运算符
	~matrix(); // 析构函数
	
	void matrix_create(int r = 0, int c = 0);//生成函数（零矩阵）
	void matrix_create_1(int order,int i, int j);//生成函数（初等矩阵1）
	void matrix_create_2(int order,int i, double k);//生成函数（初等矩阵2）
	void matrix_create_3(int order,int i, int j, double k);//生成函数（初等矩阵3）
	void matrix_create_random(int i, int j, double a, double b);//生成函数（随机矩阵）
	
	void matrix_store(); // 存储函数（任意矩阵）
	void matrix_input();//输入函数 （二维矩阵） 
	void matrix_display(int no_name = 0);//输出函数（输出完整矩阵）（无需存储）
	
	matrix matrix_transpose();//转置矩阵
	matrix matrix_simplify_1();//化简为行阶梯形矩阵
	void matrix_simplify_2();
	void matrix_simplify_3();
	double matrix_det();//行列式 
	
};

int matrix_search (string na); //查找函数 （给名字返回编号）
void transpose(); //转置函数（前端） 
void matrix_calculate();//计算函数（前端） 
void det();//行列式（前端）
void output();//输出函数（前端）
void del();//删除函数
void clear();//清空函数
#endif

