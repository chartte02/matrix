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

matrix matrix_ortho_gs(const matrix &m){
	matrix result(m.row, m.col);
	result.matrix_create(m.row, m.col);
	vector<vec> bef(m.col);
	vector<vec> aft(m.col);
	for (int i = 0; i < m.col; i++){
		bef[i] = vec(m.row);
		aft[i] = vec(m.row);
		for (int j = 0; j < m.row; j++){
			bef[i].data[j] = m.data[j][i];
			aft[i].data[j] = m.data[j][i];
		}
	}
	for (int i = 0; i < m.col; i++){
		for (int j = 0; j < i; j++){
			aft[i] = aft[i] - aft[j] * ((bef[i] * aft[j]) / (aft[j] * aft[j]));
		}
		aft[i].get_norm();
	}
	for (int i = 0; i < m.col; i++){
		aft[i] = aft[i] * (fraction(1) / aft[i].norm);
		for (int j = 0; j < m.row; j++){
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
		matrix temp = matrix_ortho_gs(matlist[matrix_search(na)]);
		temp.name = matlist[matrix_search(na)].name + "_oth";
		temp.matrix_display(0,1);
	}
}

