//�ļ���create.cpp
/*
�������ɾ�����
*/
#include "matrix.h"

extern vector<matrix> matlist;//��������
extern int n;

// ���ƣ�matrix_create ���ɺ���������� 
// ���ܣ�������֪�к��е������ 
// �������У��� 
void matrix::matrix_create(int r, int c) {//�˴�Ĭ��ֵ��Ϊ0
	row = r;
	col = c;
	data = new fraction *[row];//����row������ָ��ռ� 
	if (!data) {
    	cout << "Error: memory is full" << endl;
		return; 
	}
	for (int i = 0; i < row; i++) {
		data[i] = new fraction [col];//����col������ָ��ռ�
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

// ���ƣ�matrix_create_1 ���ɺ��������Ⱦ���1��
// ���ܣ���õ�һ����Ⱦ��� E(i,j)
// ������order��������� 	r,c: r��c��
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

// ���ƣ�matrix_create_E ���ɺ�������λ����
// ���ܣ���õ�һ����Ⱦ��� E(i,j)
// ������order��������� 	r,c: r��c��
void matrix::matrix_create_E (int order) {
    matrix_create(order, order);
    for (int i = 0; i < order; i++) {
        data[i][i] = 1;
    }
}

// ���ƣ�matrix_create_2 ���ɺ��������Ⱦ���2��
// ���ܣ���õڶ�����Ⱦ��� E(i(k))
// ������order: �������  	r:r�� 		k: k��
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

// ���ƣ�matrix_create_3 ���ɺ��������Ⱦ���3��
// ���ܣ���ȡ��������Ⱦ���E(i,j(k))
// ������order���������		r,c:r��c�� 		k��k��
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

//���ƣ� matrix_create_random ���ɺ������������
//���ܣ�������ɾ���
//������i,j:������  a,b:�������ֵ�ķ�Χ 
void matrix::matrix_create_random(int i, int j, double a, double b) {
	srand(time(NULL));
    matrix_create(i,j);
    for(int k=0;k<row;k++) {
        for(int l=0;l<col;l++) {
            data[k][l]= fraction(a) + fraction((b - a) * rand(), RAND_MAX);
        }
    }
}

//���ƣ� matrix_create_diagonal ���ɺ������ԽǾ���
//���ܣ�������ɶԽǾ���
//������i:������  a,b:�������ֵ�ķ�Χ 
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

//���ƣ� matrix_create_upper_triangular ���ɺ����������Ǿ���
//���ܣ�������������Ǿ���
//������i:������  a,b:�������ֵ�ķ�Χ 
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

//���ƣ� matrix_cin_diagonal
//���ܣ����ɶԽ�����Ԫ��Ϊ�û���������ĶԽǾ���
//������i:������ 
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

//���ƣ� matrix_scalar
//���ܣ����ɶԽ�����Ԫ��Ϊk����������
//������i:������  k���Խ����ϵ�Ԫ��ֵ
void matrix::matrix_scalar(int i, fraction k) {
	matrix_create(i, i);
	for (int l = 0; l < row; l++) {
		data[l][l] = k;
	}
}
