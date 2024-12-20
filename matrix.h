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
#include <iomanip>
#include <algorithm>
using namespace std;

extern int n;//���о������ 
extern bool fraction_fail;
extern bool calculate_success;

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
			return -x;
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
		int len, x;
		x = n / 1;
		for (len = 0; ; len++){
			x = n / 1;
			if (n != x){
				n *= 10;
			
				den *= 10;
			} else{
				break;
			}
		}
		num = n;
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
		fraction result(num * other.den + den * other.num, den * other.den);
		return result;
	}
	fraction operator-(const fraction &other){//-��������� 
		fraction result(num * other.den - den * other.num, den * other.den);
		return result;
	}
	fraction operator-(){//-��������� 
		fraction result(- num, den);
		return result;
	}
	fraction operator*(const fraction &other){//*��������� 
		fraction result(num * other.num, den * other.den);
		return result;
	}
	fraction operator/(const fraction &other){// / ��������� 
		if (other.num == 0){
			calculate_success = false;
			return *this;
		}
		fraction result(num * other.den, den * other.num);
		return result;
	}
	fraction& operator+=(const fraction &other){//+=
		num = num * other.den + den * other.num;
		den = den * other.den;
		fraction_reduct();
		return *this;
	}
	fraction& operator-=(const fraction &other){//-=
		num = num * other.den - den * other.num;
		den = den * other.den;
		fraction_reduct();
		return *this;
	}
	explicit operator bool() const {//fractionתbool 
        return num != 0; // ���磬���Ӳ�Ϊ��ʱ��Ϊ true
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

//template <typename T>
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
    void matrix_create_diagonal(int i,int j, double a,double b);//���ɺ���������ԽǾ���
    void matrix_create_upper_triangular(int i, int j, double a, double b);//���ɺ�������������Ǿ���

    void matrix_store(); // �洢�������������
    void matrix_input();//���뺯�� ����ά����
    void matrix_display(int no_name = 0);//�������������������󣩣�����洢��

    matrix matrix_transpose();//ת�þ���
    matrix matrix_inverse();//�����
    matrix matrix_simplify_1();//����Ϊ�н����ξ���
    matrix matrix_simplify_2(int *the_number_of_pivots=nullptr);//����Ϊ���н����ξ���
    void matrix_simplify_3();
    fraction matrix_det();//����ʽ

    void matrix_modify_name(string na);
    void matrix_intercept_row(int r2,int r1);
    void matrix_intercept_col(int c2,int c1);
    void matrix_intercept_dia(int d);
    void matrix_modify();
    void matrix_intercept();
    void create_argumentation(const matrix&m1,const matrix &m2);
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
#endif
