//文件：matrix.cpp 
#include "matrix.h"

extern vector<matrix> matlist;//矩阵数组
extern int n;//现有矩阵个数 
extern bool fraction_fail;
extern bool calculate_success;

// 拷贝构造函数
matrix::matrix(const matrix &other) {
	name = other.name;
    row = other.row;
    col = other.col;
	No = other.No;

    // 分配新的内存
	data = new fraction*[row];
    if (!data) {
    	cout << "Error: memory is full" << endl;
		return; 
	}
	
    for (int i = 0; i < row; i++) {
        data[i] = new fraction[col];
        for (int j = 0; j < col; j++) {
            data[i][j] = other.data[i][j]; // 复制数据
        }
    }
}

// 赋值运算符重载
matrix& matrix::operator=(const matrix &other) {
    if (this != &other) { // 防止自我赋值
        // 释放旧的内存
        for (int i = 0; i < row; i++) {
            delete[] data[i];
        }
        delete[] data;

        // 复制数据
        name = other.name;
        row = other.row;
        col = other.col;
		No = other.No;
        // 分配新的内存
        data = new fraction*[row];
//!此处未检测new 
        for (int i = 0; i < row; i++) {
            data[i] = new fraction[col];
//!此处未检测new
            for (int j = 0; j < col; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }
    return *this;
}

//相等运算符重载
bool matrix::operator==(const matrix& other) {
	if (row != other.row || col != other.col){
		return 0;
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (data[i][j] != other.data[i][j]){
				return 0;
			}
		}
	}
	return 1;
}

// 析构函数
matrix::~matrix() {
    for (int i = 0; i < row; i++) {
        delete[] data[i];
		data[i] = NULL;//就是他 
    }
    delete[] data;
	data = NULL;//还有他 
}

