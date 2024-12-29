//文件：create.cpp
/*
各种生成矩阵函数
*/
#include "matrix.h"

extern vector<matrix> matlist;//矩阵数组
extern int n;

void create() {
	while(true) {
		cout << "Please input your choice:" << endl;
		cout << "1 -- create a matrix with all the elements are made randomly."<<endl;
		cout << "2 -- create a diagonal matrix with all the elements of the principle diagonal are made randomly."<<endl;
		cout << "3 -- create an upper matrix with all the elements are made randomly"<<endl;
		cout << "4 -- create a diagonal matrix. "<<endl;
		cout << "5 -- create a scalar matrix"<<endl;
		cout << "6 -- create an argumented matrix"<<endl;
		cout << "0 -- exit"<<endl;
		int choice;
		cin >> choice;
			if(choice == 1) {
				int row, col;
				double a,b;
				matrix m;
				string name;
				cout << "Please input the name:"<<endl;
				cin >> name;
				cout << "Please input the row number:" << endl;
				cin >> row;
				cout << "Please input the column number:" << endl;
				cin >> col;
				cout << "Please input the lower bound:" << endl;
				cin >> a;
				cout << "Please input the upper bound:" << endl;
				cin >> b;
				m.matrix_create_random(row,col,a,b);
				m.matrix_modify_name(name);
				m.matrix_store();
				m.matrix_display(1,1);
			}
			else if(choice == 2) {
				int order;
				double a,b;
				matrix m;
				string name;
				cout << "Please input the name:"<<endl;
				cin >> name;
				cout << "Please input the order:" << endl;
				cin >> order;
				cout << "Please input the lower bound:" << endl;
				cin >> a;
				cout << "Please input the upper bound:" << endl;
				cin >> b;
				m.matrix_create_diagonal(order,a,b);
				m.matrix_modify_name(name);
				m.matrix_store();
				m.matrix_display(1,1);
			}
			else if(choice == 3) {
				int order;
				double a,b;
				matrix m;
				string name;
				cout << "Please input the name:"<<endl;
				cin >> name;
				cout << "Please input the order:" << endl;
				cin >> order;
				cout << "Please input the lower bound:" << endl;
				cin >> a;
				cout << "Please input the upper bound:" << endl;
				cin >> b;
				m.matrix_create_upper_triangular(order,a,b);
				m.matrix_modify_name(name);
				m.matrix_store();
				m.matrix_display(1,1);
			}
			else if(choice == 4) {
				int order;
				string name;
				cout << "Please input the name:"<<endl;
				cin >> name;
				cout << "Please input the order:" << endl;
				cin >> order;
				matrix m;
				m.matrix_cin_diagonal(order);
				m.matrix_modify_name(name);
				m.matrix_store();
				m.matrix_display(1,1);
			}
			else if(choice == 5) {
				int order;
				string name;
				int k;
				cout << "Please input the name:"<<endl;
				cin >> name;
				cout << "Please input the order:" << endl;
				cin >> order;
				cout << "Please input the value on the diagonal:" << endl;
				cin >> k;
				matrix m;
				m.matrix_scalar(order,k);
				m.matrix_modify_name(name);
				m.matrix_store();
				m.matrix_display(1,1);
			}
			else if(choice == 6) {
				string name;
				cout << "Please input the name of the argumented matrix."<<endl;
				cin >> name;
				cout << "Please input the name of the tow matrixes you want to create an argumented matrix:"<<endl;
				string name1,name2;
				cin >> name1;
				cin >> name2;
				matrix m;
				m.create_argumentation(matlist[matrix_search(name1)],matlist[matrix_search(name2)]);
				m.matrix_modify_name(name);
				m.matrix_store();
			}
			else if(choice == 0) {
				return;
			}
			else {
				cout << "Wrong input, please input the correct choice:"<<endl;
			}

	}
}

void adjoint() {
	cout << "Please input the name of the matrix:"<<endl;
	string name;
	cin >> name;
	cout << "Please input the new name of the matrix:"<<endl;
	string newname;
	cin >> newname;
	matrix m;
	m=matlist[matrix_search(name)].matrix_adjoint();
	m.matrix_modify_name(name);
	m.matrix_store();
}

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
//参数：i:行列数  a,b:随机生成值的范围
void matrix::matrix_create_diagonal(int i, int a, int b) {
	if (a > b) swap(a, b);
	srand(time(NULL));
	matrix_create(i, i);
	for (int k = 0; k < row; k++) {
		int num = a + rand() % (b - a + 1);
		int dem= a + rand() % (b - a + 1);
		while (dem == 0) {
			dem = a + rand() % (b - a + 1);
		}
		data[k][k] = fraction(num, dem);
	}
}

//名称： matrix_create_upper_triangular 生成函数（上三角矩阵）
//功能：随机生成上三角矩阵
//参数：i:行列数  a,b:随机生成值的范围
void matrix::matrix_create_upper_triangular(int i, int a, int b) {
	if (a > b) swap(a, b);
	srand(time(NULL));
	matrix_create(i, i);
	for (int k = 0; k < row; k++) {
		for (int l = 0; l < col; l++) {
			if (k <= l) {
				int num = a + rand() % (b - a + 1);
				int dem = a + rand() % (b - a + 1);
				while (dem == 0) {
					dem = a + rand() % (b - a + 1);
				}
				data[k][l] = fraction(num, dem);
			}
		}
	}
}

//名称： matrix_cin_diagonal
//功能：生成对角线上元素为用户输入的数的对角矩阵
//参数：i:行列数
void matrix::matrix_cin_diagonal(int i) {
	fraction* diag;
	diag = new fraction[i];
	for (int j = 0; j < i; j++) {
		cin >> diag[j];
	}
	matrix_create(i, i);
	for (int k = 0; k < row; k++) {
		data[k][k] = diag[k];
	}
	delete[] diag;
}

//名称： matrix_scalar
//功能：生成对角线上元素为k的数量矩阵
//参数：i:行列数  k：对角线上的元素值
void matrix::matrix_scalar(int i, fraction k) {
	matrix_create(i, i);
	for (int l = 0; l < row; l++) {
		data[l][l] = k;
	}
}
