#include "matrix.h"
extern vector<matrix> matlist;
extern int n;//现有矩阵个数 
extern bool fraction_fail;
extern bool calculate_success;
	
class vec{
public:
	fraction *data;
	int n;
	fraction norm;
	vec(int n = 0): n(n){
		data = new fraction [n];//申请row个数组指针空间 
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
        delete[] data; // 释放内存
    }
    vec(const vec &other){//拷贝构造函数 
		n = other.n;
		norm = other.norm;
        // 分配新的内存
        data = new fraction[n];
        for (int i = 0; i < n; i++) {
            data[i] = other.data[i];
        }
	}
	vec& operator=(const vec &other){//赋值运算符重载 
        delete[] data;
		n = other.n;
		norm = other.norm;
        // 分配新的内存
        data = new fraction[n];
        for (int i = 0; i < n; i++) {
            data[i] = other.data[i];
        }
    	return *this;
	}
	vec operator+(const vec &other){//+运算符重载 
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
	vec operator-(const vec &other){//+运算符重载 
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
	vec operator-(){//-运算符重载 
		vec result(n);
		for (int i = 0; i < n; i++) {
			result.data[i] = -data[i];
		}
		return result;
	}
	vec operator*(const fraction &other){//*运算符重载 
		vec result(n);
		for (int i = 0; i < n; i++) {
			result.data[i] = data[i] * other;
		}
		return result;
	}
	vec operator/(const fraction &other){//*运算符重载 
		vec result(n);
		for (int i = 0; i < n; i++) {
			result.data[i] = data[i] / other;
		}
		return result;
	}
	fraction operator*(const vec &other){//*运算符重载 
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
