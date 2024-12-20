//文件：create.cpp
/*
各种生成矩阵函数
*/
#include "matrix.h"

extern vector<matrix> matlist;//矩阵数组
extern int n;

// 名称：matrix_create 生成函数（零矩阵） 
// 功能：生成已知行和列的零矩阵 
// 参数：行，列 
void matrix::matrix_create(int r, int c) {//此处默认值都为0
	row = r;
	col = c;
	data = new fraction *[row];//申请row个数组指针空间 
	if (!data) {
    	cout << "Error: memory is full" << endl;
		return; 
	}
	for (int i = 0; i < row; i++) {
		data[i] = new fraction [col];//申请col个数组指针空间
		if (!data[i]) {
    		cout << "Error: memory is full" << endl;
			return; 
		}
    }
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			data[i][j] = 0;
		}
	}
}

// 名称：matrix_create_1 生成函数（初等矩阵1）
// 功能：获得第一类初等矩阵 E(i,j)
// 参数：order：矩阵阶数 	r,c: r行c列
void matrix::matrix_create_1 (int order, int i, int j) {
    int c = i - 1, r = j - 1;
    matrix_create(order, order);
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
            if(i == j && i != r && i != c) data[i][j] = 1;
            else if((i == c && j == r)||(i == r && j == c)) data[i][j] = 1;
            else data[i][j] = 0;
        }
    }
}

// 名称：matrix_create_E 生成函数（单位矩阵）
// 功能：获得第一类初等矩阵 E(i,j)
// 参数：order：矩阵阶数 	r,c: r行c列
void matrix::matrix_create_E (int order) {
    matrix_create(order, order);
    for (int i = 0; i < order; i++) {
        data[i][i] = 1;
    }
}

// 名称：matrix_create_2 生成函数（初等矩阵2）
// 功能：获得第二类初等矩阵 E(i(k))
// 参数：order: 矩阵阶数  	r:r行 		k: k倍
void matrix::matrix_create_2 (int order, int i, fraction k) {
    int r = i - 1;
	matrix_create(order, order);
    for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			if(i == j && i != r)
			data[i][j]=1;
			else if(i == r && j == r) data[i][j]=k;
			else data[i][j] = 0;
		}
    }
}

// 名称：matrix_create_3 生成函数（初等矩阵3）
// 功能：获取第三类初等矩阵E(i,j(k))
// 参数：order：矩阵阶数		r,c:r行c列 		k：k倍
void matrix::matrix_create_3 (int order, int i, int j, fraction k) {
    int r = i - 1, c = j - 1;
    matrix_create(order, order);
    for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			if(i == j) data[i][j] = 1;
			else if(i == r && j == c) data[i][j] = k;
			else data[i][j] = 0;
		}
	}
}

//名称： matrix_create_random 生成函数（随机矩阵）
//功能：随机生成矩阵
//参数：i,j:行列数  a,b:随机生成值的范围 
void matrix::matrix_create_random(int i, int j, double a, double b) {
	srand(time(NULL));
    matrix_create(i,j);
    for(int k=0;k<row;k++) {
        for(int l=0;l<col;l++) {
            data[k][l]= fraction(a) + fraction((b - a) * rand(), RAND_MAX);
        }
    }
}

//名称： matrix_create_diagonal 生成函数（对角矩阵）
//功能：随机生成对角矩阵
//参数：i,j:行列数  a,b:随机生成值的范围 
void matrix::matrix_create_diagonal(int i, int j, double a, double b) {
	if (i != j) {
        cout << "Error: Diagonal matrix must be square" << endl;
        return;
    }
	srand(time(NULL));
	matrix_create(i, j);
	for (int k = 0; k < row; k++) {
		for (int l = 0; l < col; l++) {
			if (k == l) {
				data[k][l]= fraction(a) + fraction((b - a) * rand(), RAND_MAX);
			}
		}
	}
}

//名称： matrix_create_upper_triangular 生成函数（上三角矩阵）
//功能：随机生成上三角矩阵
//参数：i,j:行列数  a,b:随机生成值的范围 
void matrix::matrix_create_upper_triangular(int i, int j, double a, double b) {
	if (i != j) {
        cout << "Error: Diagonal matrix must be square" << endl;
        return;
    }
	srand(time(NULL));
	matrix_create(i, j);
	for (int k = 0; k < row; k++) {
		for (int l = 0; l < col; l++) {
			if (k <= l) {
				data[k][l]= fraction(a) + fraction((b - a) * rand(), RAND_MAX);
			}
		}
	}
}

