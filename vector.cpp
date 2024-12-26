#include "matrix.h"
extern vector<matrix> matlist;
extern int n;//���о������ 
extern bool fraction_fail;
extern bool calculate_success;
	
class vec{
public:
	fraction *data;
	int n;
	fraction norm;
	vec(int n = 0): n(n){
		data = new fraction [n];//����row������ָ��ռ� 
		if (!data) {
	    	cout << "Error: memory is full" << endl;
			return; 
		}
		for (int i = 0; i < n; i++) {
			data[i] = 0;
	    }
	    norm = 0;
	}
	~vec() {
        delete[] data; // �ͷ��ڴ�
    }
    vec(const vec &other){//�������캯�� 
		n = other.n;
		norm = other.norm;
        // �����µ��ڴ�
        data = new fraction[n];
        for (int i = 0; i < n; i++) {
            data[i] = other.data[i];
        }
	}
	vec& operator=(const vec &other){//��ֵ��������� 
        delete[] data;
		n = other.n;
		norm = other.norm;
        // �����µ��ڴ�
        data = new fraction[n];
        for (int i = 0; i < n; i++) {
            data[i] = other.data[i];
        }
    	return *this;
	}
	vec operator+(const vec &other){//+��������� 
		vec result(n);
		if (n != other.n){
			cout << "Error: Vector dimensions must agree for addition." << endl;
        	calculate_success = false;
        	return result; 
		}
		for (int i = 0; i < n; i++) {
			result.data[i] = data[i] + other.data[i];
		}
		return result;
	}
	vec operator-(const vec &other){//+��������� 
		vec result(n);
		if (n != other.n){
			cout << "Error: Vector dimensions must agree for subtraction." << endl;
        	calculate_success = false;
        	return result; 
		}
		for (int i = 0; i < n; i++) {
			result.data[i] = data[i] - other.data[i];
		}
		return result;
	}
	vec operator-(){//-��������� 
		vec result(n);
		for (int i = 0; i < n; i++) {
			result.data[i] = -data[i];
		}
		return result;
	}
	vec operator*(const fraction &other){//*��������� 
		vec result(n);
		for (int i = 0; i < n; i++) {
			result.data[i] = data[i] * other;
		}
		return result;
	}
	fraction operator*(const vec &other){//*��������� 
		fraction result = fraction(0);
		if (n != other.n){
			cout << "Error: Vector dimensions must agree for multiplication." << endl;
        	calculate_success = false;
        	return fraction(0); 
		}
		for (int i = 0; i < n; i++) {
			result += data[i] * other.data[i];
		}
		return result;
	}
	void get_norm(){
		norm = 0;
		double x = 0;
		for (int i = 0; i < n; i++) {
			x += data[i] * data[i];
		}
		x = sqrt(x);
		norm = fraction(x);
	}
};

matrix matrix::matrix_ortho_gs(){
	matrix result(row, col);
	result.matrix_create(row, col);
	vector<vec> bef(col);
	vector<vec> aft(col);
	for (int i = 0; i < col; i++){
		bef[i] = vec(row);
		aft[i] = vec(row);
		for (int j = 0; j < row; j++){
			bef[i].data[j] = data[j][i];
			aft[i].data[j] = data[j][i];
		}
	}
	for (int i = 0; i < col; i++){
		for (int j = 0; j < i; j++){
			aft[i] = aft[i] - aft[j] * ((bef[i] * aft[j]) / (aft[j] * aft[j]));
		}
		aft[i].get_norm();
	}
	for (int i = 0; i < col; i++){
		aft[i] = aft[i] * (fraction(1) / aft[i].norm);
		for (int j = 0; j < row; j++){
			result.data[j][i] = aft[i].data[j];
		}
		
	}
	return result;
}

void oth(){
	cout << "Please enter your matrix name : ";
	string na;
    cin >> na;
	if (matrix_search(na) == -1){
	    cout << "Not Found" << endl; // ���û���ҵ��������ʾ
	    return;
	}
	else {
		matrix temp = matlist[matrix_search(na)].matrix_ortho_gs();
		temp.name = matlist[matrix_search(na)].name + "_oth";
		temp.matrix_display(0,1);
	}
}

matrix matrix::matrix_R(){
	matrix temp;
	temp.matrix_create();
	temp = matrix_ortho_gs();
	return temp.matrix_inverse() * (*this);
}

void eig_iteration(matrix &m){
	m = m.matrix_R() * m.matrix_ortho_gs();
}

matrix matrix::matrix_eigenvalue(){
	matrix t;
	t.matrix_create();
	t = *this;
	for (int i = 0; i < 100; i++){
		eig_iteration(t);
	}
	return t;
}

void eig(){
	cout << "Please enter your matrix name : ";
	string na;
    cin >> na;
	if (matrix_search(na) == -1){
	    cout << "Not Found" << endl; // ���û���ҵ��������ʾ
	    return;
	}
	if (matlist[matrix_search(na)].row != matlist[matrix_search(na)].col){
		cout << "Not a square matrix" << endl;//���Ƿ��󣬲�����Ҫ���˳�
		return;
	}
	else {
		matrix temp1 = matlist[matrix_search(na)].matrix_eigenvalue();
//		matrix temp2;//�������� 
//		temp2.matrix_create(temp1.row, temp1.row);
//		for (int k = 0; k < temp1.row; k++) {
//			temp2.data[k][k] = temp1.data[k][k];
//		}
		temp1.name = matlist[matrix_search(na)].name + "_eig";
		temp1.matrix_display(0, 1);
		for (int i = 0; i < temp1.row; i++){
			cout << double(temp1.data[i][i]) << endl;
		}
		return;
	}
}
