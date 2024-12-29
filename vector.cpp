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
	    cout << "Not Found" << endl; // 如果没有找到，输出提示
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
//	eig_iteration(t);
//	if (t == *this && t.col > 1){
//		for (int i = 0; i < t.row; i++){
//			t.data[i][0] = t.data[i][0] + t.data[i][1];
//		}
//	}
	for (int i = 0; i < 10000; i++){
		eig_iteration(t);
	}
	return t;
}
void eig_vec(matrix &pri, matrix &m);
void eig(){
	cout << "Please enter your matrix name : ";
	string na;
    cin >> na;
	if (matrix_search(na) == -1){
	    cout << "Not Found" << endl; // 如果没有找到，输出提示
	    return;
	}
	if (matlist[matrix_search(na)].row != matlist[matrix_search(na)].col){
		cout << "Not a square matrix" << endl;//不是方阵，不符合要求，退出
		return;
	}
	else {
		matrix temp1 = matlist[matrix_search(na)].matrix_eigenvalue();
//		temp1.name = matlist[matrix_search(na)].name + "_eig";
//		temp1.matrix_display(0, 1);
//		for (int i = 0; i < temp1.row; i++){
//			cout << double(temp1.data[i][i]) << endl;
//		}
		eig_vec(matlist[matrix_search(na)], temp1);
		return;
	}
}

void eig_vec(matrix &pri, matrix &m){
	double lamda[m.row];
	for (int i = 0; i < m.row; i++){
		lamda[i] = double(m.data[i][i]);
		cout << "lamda " << i + 1 << " = " << lamda[i] << endl;
	}
	sort(lamda, lamda + m.row);
	fraction unique[m.row] = {0};
	int len = 1;
	unique[0] = fraction(lamda[0]);
    for (int i = 1; i < m.row; i++) {
    	double x = lamda[i] - lamda[i - 1];
    	if (x > 0.0001){
    		unique[len] = fraction(lamda[i]);
        	len++;
		} 
    }
//    for (int i = 1; i < m.row && double(lamda[i] - lamda[i - 1]) > 0.01; i++) {	
//    	unique[len] = fraction(lamda[i]);
//        len++;
//        cout << 114;
//    }
	for (int i = 0; i < len; i++){
		matrix temp1, temp2, temp3;
		int pivot_count;
		temp3.matrix_create(m.row, m.col);
		temp2.matrix_create(m.row, m.col);
		temp1.matrix_scalar(m.row, unique[i]);
		cout << double(unique[i]) << " eigenvector is :" << endl;
		temp2 = temp1 - pri;
		temp3 = temp2.matrix_simplify_3(&pivot_count);
//		cout << pivot_count;
//		cout<<len<<endl;
		matrix ans;
		ans.matrix_create(m.row, m.col - pivot_count);
		for (int i = 0; i < m.col - pivot_count; i++){
			for (int j = 0; j < pivot_count; j++){
				ans.data[j][i] = -temp3.data[j][i + pivot_count];
			}
			ans.data[pivot_count][i] = fraction(1); 
		}
		ans = ans.matrix_transpose();
		for (int i = 0; i < ans.row; i++) {
			cout << "[";
        	for (int j = 0; j < ans.col; j++) {
            	cout << double(ans.data[i][j]);
				if (j < ans.col - 1) cout << ", ";
        	} 
        	cout << "]^T";
        	cout << endl;
		}
	}
}

//名称：matrix_simplify_3化简函数
//功能：将矩阵化简为简化行阶梯形矩阵并存储
//参数：无
//返回值：简化行阶梯形矩阵
matrix matrix::matrix_simplify_3(int *the_number_of_pivots) {
	matrix temp;
	temp.matrix_create(); 
	temp = *this;
	int num = 0;//用于确定行阶梯已经到达哪一行
	vector<vec> bef(row);
	for (int i = 0; i < row; i++){
		bef[i] = vec(col);
		for (int j = 0; j < col; j++){
			bef[i].data[j] = data[i][j];
		}
	}
	for (int i = 0; i < col; i++) {
		if (double(bef[i].data[i]) < 0.0001 && double(bef[i].data[i]) > -0.0001){
			bef[i].data[i] = fraction(0);
			bool flag = 1;
			for (int j = i + 1; j < row; j++) {
				if(bef[j].data[i]){
					vec	temp;
					temp = bef[j];
					bef[j] = bef[i];
					bef[i] = temp;
					flag = 0;
					break;
				}
			}
			if (flag)	continue;
		}	
		bef[num] = bef[num] / bef[num].data[i];
		for (int j = 0; j < row; j++) {
			if (j != num){
				bef[j] = bef[j] - bef[num] * bef[j].data[i];
			}
		}
		num++;
	}
	*the_number_of_pivots = num;
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			temp.data[i][j] = bef[i].data[j];
		}
	}
	return temp;
}
