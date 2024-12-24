//fraction
#include "matrix.h"
#include <algorithm>

bool fraction_fail = 0;
extern bool calculate_success;

class fraction {
public:	
	long long num, den;//·Ö×Ó£¬·ÖÄ¸
	double fra;
	
	long long gcd (long long a, long long b) {
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
	void fraction_reduct() {
		num = num / gcd(num, den);
		den = den / gcd(num, den);
	}
	fraction(double n = 1ll, double d = 1ll) : num(n), den(d) {
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
		fra = num / den;
	}
	fraction& operator=(const fraction &other){
		den = other.den;
		num = other.num;
		fra = other.fra;
	}
	fraction operator+(const fraction &other){
		fraction result(num * other.den + den * other.num, den * other.den);
		return result;
	}
	fraction operator-(const fraction &other){
		fraction result(num * other.den - den * other.num, den * other.den);
		return result;
	}
	fraction operator*(const fraction &other){
		fraction result(num * other.num, den * other.den);
		return result;
	}
	fraction operator/(const fraction &other){
		if (other.num == 0){
			calculate_success = false;
			return *this;
		}
		fraction result(num * other.num, den * other.num);
		return result;
	}
	friend ostream& operator<<(ostream &os, const fraction &obj){
		if (obj.den != 1){
			os << obj.num << '/' << obj.den;
		} else{
			os << obj.num;
		}
		return os;
	}
	friend istream& operator>>(istream &in, fraction &obj){
		string str;
		in >> str;
		int k = str.size();
		long long x, y;
		int sign = 0;
		bool flag = 1;
		for (int i = 0; i < k; i++){
			if (str[i] == '-') {
				sign ++;
			} else if (str[i] == '/'){
				flag = 0;
			} else {
				if (flag) {
					x = 10 * x + (str[i] - '0');
				}
				else {
					y = 10 * y + (str[i] - '0');
				}
			} 
		}
		if (flag){
			obj.num = x;
			obj.den = 1ll;
		} else {
			if (sign % 2){
				obj.num = -1 * x;
				obj.den = y;
			} else{
				obj.num = x;
				obj.den = y;
			}	
		}
		obj.fraction_reduct();
		obj.fra = obj.num / obj.den;
		return in;
	}
};
