//�ļ���matrix.cpp 
#include "matrix.h"

extern vector<matrix> matlist;//��������
extern int n;//���о������ 
extern bool fraction_fail;
extern bool calculate_success;

// �������캯��
matrix::matrix(const matrix &other) {
	name = other.name;
    row = other.row;
    col = other.col;
	No = other.No;

    // �����µ��ڴ�
	data = new fraction*[row];
    if (!data) {
    	cout << "Error: memory is full" << endl;
		return; 
	}
	
    for (int i = 0; i < row; i++) {
        data[i] = new fraction[col];
        for (int j = 0; j < col; j++) {
            data[i][j] = other.data[i][j]; // ��������
        }
    }
}

// ��ֵ���������
matrix& matrix::operator=(const matrix &other) {
    if (this != &other) { // ��ֹ���Ҹ�ֵ
        // �ͷžɵ��ڴ�
        for (int i = 0; i < row; i++) {
            delete[] data[i];
        }
        delete[] data;

        // ��������
        name = other.name;
        row = other.row;
        col = other.col;
		No = other.No;
        // �����µ��ڴ�
        data = new fraction*[row];
//!�˴�δ���new 
        for (int i = 0; i < row; i++) {
            data[i] = new fraction[col];
//!�˴�δ���new
            for (int j = 0; j < col; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }
    return *this;
}

//������������
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

// ��������
matrix::~matrix() {
    for (int i = 0; i < row; i++) {
        delete[] data[i];
		data[i] = NULL;//������ 
    }
    delete[] data;
	data = NULL;//������ 
}

