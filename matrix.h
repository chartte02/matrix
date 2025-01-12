
//�ļ���matrix.h
#ifndef matrix_h

#define matrix_h
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

extern int n;//���о������ 
extern bool fraction_fail;
extern bool calculate_success;
extern int precision;

class fraction {
public:	
	long long num, den;//���ӣ���ĸ
	
	long long gcd (long long a, long long b) {//�����Լ�� 
		if(a < b){
			swap(a,b);
		}
		long long c;
		while(b){
			c = a % b;
			a = b;
			b = c;
		}
		return a;
	}
	void fraction_reduct() {//�������� 
		if (num && den){
			long long x = gcd(abs(num), den);
			num = num / x;
			den = den / x;
		}
		else {
			den = 1ll;
		}
	}
	long long abs(long long x){//ȡ����ֵ 
		if (x < 0) {
			return -1 * x;
		}
		return x;
	}
	fraction(long long n = 1ll, long long d = 1ll) : num(n), den(d) {//���캯��
		if (den == 0){
			fraction_fail = 1;
			cout << "Error : the denominator is 0 " << endl;
			return;
		}
		if (den < 0){
			den = den * -1;
			num = num * -1;
		}
		fraction_reduct();
	}
	fraction(int n) : num(n), den(1ll) {}//intתfraction
	fraction(double n){//doubleתfraction 
		den = 1 * pow(10, precision);
		num = n * pow(10, precision);
		fraction_reduct();
	}
	void fraction_create(){//���ɺ��� 
		if (den == 0){
			fraction_fail = 1;
			cout << "Error : the denominator is 0 " << endl;
			return;
		}
		if (den < 0){
			den = den * -1;
			num = num * -1;
		}
		fraction_reduct();
	}
	fraction& operator=(const fraction &other){//��ֵ��������� 
		den = other.den;
		num = other.num;
	}
	fraction operator+(const fraction &other){//+��������� 
		double x = double(*this) + double(other);
		fraction result(x);
		return result;
	}
	fraction operator-(const fraction &other){//-��������� 
		double x = double(*this) - double(other);
		fraction result(x);
		return result;
	}
	fraction operator-(){//-��������� 
		fraction result(- num, den);
		return result;
	}
	fraction operator*(const fraction &other){//*��������� 
		double x = double(*this) * double(other);
		fraction result(x);
		return result;
	}
	fraction operator*(const int &other){//*��������� 
		double x = double(*this) * other;
		fraction result(x);
		return result;
	}
	fraction operator/(const fraction &other){// / ��������� 
		if (other.num == 0){
			calculate_success = false;
			return *this;
		}
		double x = double(*this) / double(other);
		fraction result(x);
		return result;
	}
	fraction& operator+=(const fraction &other){//+=
		double x = double(*this) + double(other);
		fraction result(x);
		num = result.num;
		den = result.den;
		return *this;
	}
	fraction& operator-=(const fraction &other){//-=
		double x = double(*this) - double(other);
		fraction result(x);
		num = result.num;
		den = result.den;
		return *this;
	}
	explicit operator bool() const {//fractionתbool 
        return num != 0; // ���磬���Ӳ�Ϊ��ʱ��Ϊ true
    }
    operator double() const {
        return static_cast<double>(num) / den;
    }
	friend ostream& operator<<(ostream &os, const fraction &obj){//��������� 
		if (obj.den != 1){
			os << obj.num << '/' << obj.den;
		} else{
			os << obj.num;
		}
		return os;
	}
	friend istream& operator>>(istream &in, fraction &obj){//���������� 
		string str;
		in >> str;
		int k = str.size();
		long long x = 0, y = 0;
		int sign = 0;
		int lenx = 0, leny = 0;
		bool flagf = 1, flagx = 0, flagy = 0;
		for (int i = 0; i < k; i++){
			if (str[i] == '-') {
				sign ++;
			} else if (str[i] == '/'){
				flagf = 0;
			} else if (str[i] == '.' && flagf){
				flagx = 1;
			} else if (str[i] == '.' && !flagf){
				flagy = 1;
			} else {
				if (flagf) {
					x = 10 * x + (str[i] - '0');
					if (flagx){
						lenx ++;
					}
				} else {
					y = 10 * y + (str[i] - '0');
					if (flagy){
						leny ++;
					}
				}
			} 
		}
		if (flagf){
			if (sign % 2){
				obj.num = -1 * x;
				obj.den = 1ll;
			} else{
				obj.num = x;
				obj.den = 1ll;
			}		
		} else {
			if (sign % 2){
				obj.num = -1 * x;
				obj.den = y;
			} else{
				obj.num = x;
				obj.den = y;
			}	
		}
		if (flagx) {
			for (int i = 0; i < lenx; i++){
				obj.den *= 10;
			} 
		}
		if (flagy) {
			for (int i = 0; i < leny; i++){
				obj.num *= 10;
			} 
		}
		obj.fraction_create();
		return in;
	}
	bool operator==(const fraction &other){
		if (den == other.den && num == other.num){
			return 1;
		}
		return 0;
	}
	bool operator!=(const fraction &other){
		if (den == other.den && num == other.num){
			return 0;
		}
		return 1;
	}
};

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
	vec operator/(const fraction &other){//*��������� 
		vec result(n);
		for (int i = 0; i < n; i++) {
			result.data[i] = data[i] / other;
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

class matrix {
public:
    string name;//����
    int No;//���
    int row, col;//����
    fraction **data;//Ԫ�ض�ά����

    matrix(int r = 0, int c = 0) : row(r), col(c) {} // Ĭ�Ϲ��캯��
    matrix(const matrix &other); // �������캯��
    matrix& operator=(const matrix &other); // ���ظ�ֵ�����
    bool operator==(const matrix& other); //������������
    matrix operator+(const matrix& other);// ���ؼӷ������
    matrix operator-(const matrix& other);// ���ؼ��������
    matrix operator*(const matrix& other);// ���س˷������
    matrix operator^(int k);//�����������
    ~matrix(); // ��������

    void matrix_create(int r = 0, int c = 0);//���ɺ����������
    void matrix_create_E (int order);//���ɺ�������λ����
	void matrix_create_1(int order,int i, int j);//���ɺ��������Ⱦ���1��
	void matrix_create_2(int order,int i, fraction k);//���ɺ��������Ⱦ���2��
	void matrix_create_3(int order,int i, int j, fraction k);//���ɺ��������Ⱦ���3��
	void matrix_create_random(int i, int j, double a, double b);//���ɺ������������
	void matrix_create_diagonal(int i, int a,int b);//���ɺ���������ԽǾ���
	void matrix_create_upper_triangular(int i, int a, int b);//���ɺ�������������Ǿ���
	void matrix_cin_diagonal(int i);//�û�����Խ�����Ԫ�صĶԽǾ���
	void matrix_scalar(int i, fraction k);//�Խ�����Ԫ��Ϊk�Ĵ�������

    void matrix_store(); // �洢�������������
    void matrix_input();//���뺯�� ����ά����
    void matrix_display(int no_name = 0, int type = 0);//�������������������󣩣�����洢��

    matrix matrix_transpose();//ת�þ���
    matrix matrix_inverse();//�����
    matrix matrix_simplify_1();//����Ϊ�н����ξ���
    matrix matrix_simplify_2(int *the_number_of_pivots=nullptr);//����Ϊ���н����ξ���
    matrix matrix_simplify_3(int *the_number_of_pivots);
    fraction matrix_det();//����ʽ
    matrix matrix_adjoint();//�������
    matrix matrix_ortho_gs();//������
    matrix matrix_R();//QR�ֽ��е�R 
    matrix matrix_eigenvalue();//����ֵ 

    void matrix_modify_name(string na);//�޸����� 
    matrix matrix_intercept_row(const matrix&m,int r1,int r2);//�н�ȡ 
    matrix matrix_intercept_col(const matrix&m,int c1,int c2);//�н�ȡ 
    matrix matrix_intercept_dia(const matrix &m,int d);//�Խǽ�ȡ 
    void matrix_modify();
    void matrix_intercept();
    matrix create_argumentation(const matrix&m1,const matrix &m2);
    void matrix_modify_data(int i,int j,fraction data_);

    void solve_system_of_linear_equtions(matrix &m1, matrix &m2);
};

int matrix_search (string na); //���Һ��� �������ַ��ر�ţ�
void transpose(); //ת�ú�����ǰ�ˣ�
void matrix_calculate();//���㺯����ǰ�ˣ�
void det();//����ʽ��ǰ�ˣ�
void output();//���������ǰ�ˣ�
void del();//ɾ������
void clear();//��պ���
void oth();//������ 
void eig();//����ֵ 
void modify();//�޸ĺ��� 
void intercept();//��ȡ���� 
void adjoint(); //���㺯��
void inverse();//����� 
void create();//���ɺ��� 
void solve(); 
#endif

