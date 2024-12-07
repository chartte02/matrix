#ifndef _matrix_h
#define _matrix_h

#include <iostream>
#include <cstring>
using namespace std;

class matrix {
public:
    string name;
    int No;
    int row, col;
    double **data;
	int n;
    matrix(int r = 0, int c = 0) : row(r), col(c), n(1), No(n - 1) {} // 默认构造函数
    matrix(const matrix &other); // 拷贝构造函数
    matrix& operator=(const matrix &other); // 赋值运算符重载
    ~matrix(); // 析构函数

	void Matrix_Create (int row, int col);//生成零矩阵
    void Matrix_Input();//输入函数 （二维矩阵）
    void Matrix_Output();//临时的输出函数，只能输出完整矩阵（为了debug输入函数临时凑得）
    matrix get_Matrix();
//	double det();
//    void create(string *s, int row, int col);
//    void add(const matrix &m1, const matrix &m2);
//    void sub(const matrix &m1, const matrix &m2);
//    void multiply(const matrix &m1, const matrix &m2);
//    void power(const matrix &m1, int k);
//    void det(const matrix &m1, int n);
//    void transpose(const matrix &m1);
//    void display(int row, int col, string *name);
	void get_matrix_1(int order,int r, int c);
        void get_matrix_2(int order,int r, int k);
        void get_matrix_3(int order,int r, int c, int k);
};

matrix list[100];

// 拷贝构造函数
matrix::matrix(const matrix &other) {
    // 分配新的内存
	data = new double*[row];
    if (!data) {
    	cout << "内存已满，无法新建矩阵" << endl;
		return;
	}

	name = other.name;
    row = other.row;
    col = other.col;

    for (int i = 0; i < row; i++) {
        data[i] = new double[col];
        for (int j = 0; j < col; j++) {
            data[i][j] = other.data[i][j]; // 复制数据
        }
    }
}

// 赋值运算符重载（曾某查询了11章的资料，大家也查一下吧，这里解释不清楚）
matrix& matrix::operator=(const matrix &other) {
    if (this != &other) { // 防止自我赋值
        // 释放旧的内存
        for (int i = 0; i < row; i++) {
            delete[] data[i];
        }
        delete[] data;

        // 复制数据
        row = other.row;
        col = other.col;

        // 分配新的内存
        data = new double*[row];
        for (int i = 0; i < row; i++) {
            data[i] = new double[col];
            for (int j = 0; j < col; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }
    return *this;
}

// 析构函数
matrix::~matrix() {
    for (int i = 0; i < row; i++) {
        delete[] data[i];
    }
    delete[] data;
}

// 名称：Matrix_Create 生成函数（零矩阵）
// 作用：生成已知行和列的零矩阵
// 参数：行，列
void matrix::Matrix_Create(int row, int col){
	data = new double *[row];//申请row个数组指针空间
	if (!data) {
    	cout << "内存已满，无法新建矩阵" << endl;
		return;
	}
	for (int i = 0; i < row; i++) {
		data[i] = new double [col];//申请col个数组指针空间
		if (!data[i]) {
    	cout << "内存已满，无法新建矩阵" << endl;
		return;
	}
    }
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			data[i][j] = 0;
		}
	}
}

// 名称：Matrix_Input 输入函数（二维矩阵）
// 作用：输入矩阵的名称，行，列，和全部元素，并存储于list数组（曾某认为有些不妥）
// 参数：无
void matrix::Matrix_Input() {
    cout << "Name : ";
	cin >> name;//输入名称
	cout << "Row : " ;
	cin >> row ;
	cout << "Column : " ;
	cin >> col;//输入行列
	cout<<"please input data : "<<endl;
	Matrix_Create(row, col);//调用生成函数
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cin >> data[i][j];//输入data
        }
    }
//    list[No] = *this;//复制到list[No]
}

void matrix::Matrix_Output() {
	cout << name << endl;
	for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << data[i][j] << "\t";
        }
        cout << "\n";
    }
    cout << "\n";
}

matrix get_Matrix() {
	string str;
	cin >> str;
	for (int i = 0; i < 100; i++) {
        if (list[i].name == str){
        	return list[i];
		}
    }
}

#endif

