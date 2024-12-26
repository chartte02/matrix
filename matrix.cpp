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

//�ӷ����������
matrix matrix::operator+(const matrix& other) {
	matrix result(row, col);
	result.matrix_create(row, col);
	if (row != other.row || col != other.col) {
        cout << "Error: Matrix dimensions must agree for addition." << endl;
        calculate_success = false;
        return result; // ��������� 
    }
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			result.data[i][j] = data[i][j] + other.data[i][j];
		}
	}
	return result;
}

//�������������
matrix matrix::operator-(const matrix& other) {
	matrix result(row, col);
	result.matrix_create(row, col);
	if (row != other.row || col != other.col) {
        cout << "Error: Matrix dimensions must agree for subtraction." << endl;
        calculate_success = false;
        return result; // ��������� 
    }
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			result.data[i][j] = data[i][j] - other.data[i][j];
		}
	}
	return result;
}

//�˷����������
matrix matrix::operator*(const matrix& other) {
	matrix result(row, other.col);
	result.matrix_create(row, other.col);
	if (col != other.row) {
		cout << "Error: Matrix dimensions must agree for multiplication." << endl;
        calculate_success = false;
        return result; // ��������� 
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < other.col; j++) {
			for (int k = 0; k < col; k++) {
				result.data[i][j] += data[i][k] * other.data[k][j];
			}
		}
	}
	return result;
}

//�����������
matrix matrix::operator^(int k) {
	matrix result(row, col);
	result.matrix_create(row, col);
	if (row != col || k < 0) {
		cout << "Error: Matrix dimensions must agree for power operations." << endl;
        calculate_success = false;
        return result; // ���������
	}
	//��ʼ��Ϊ��λ����
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (i == j) {
				result.data[i][j] = 1;
			}
			else result.data[i][j] = 0;
		}
	}
	matrix tmp(*this);
	for (int i = 1; i <= k; i++) {
		result = result * tmp;
	}
	
	return result;
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

