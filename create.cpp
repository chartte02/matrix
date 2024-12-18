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
	data = new double *[row];//����row������ָ��ռ� 
	if (!data) {
    	cout << "Error: memory is full" << endl;
		return; 
	}
	for (int i = 0; i < row; i++) {
		data[i] = new double [col];//����col������ָ��ռ�
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

// ���ƣ�matrix_create_2 ���ɺ��������Ⱦ���2��
// ���ܣ���õڶ�����Ⱦ��� E(i(k))
// ������order: �������  	r:r�� 		k: k��
void matrix::matrix_create_2 (int order, int i, double k) {
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
void matrix::matrix_create_3 (int order, int i, int j, double k) {
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

void matrix::matrix_create_random(int i, int j,double a,double b) {
	srand(time(NULL));
    matrix_create(i,j);
    for(int k=0;k<row;k++) {
        for(int l=0;l<col;l++) {
            data[k][l]=a+(b-a)*rand()/((double) RAND_MAX);
        }
    }
}
