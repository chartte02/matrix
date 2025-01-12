//文件：calculate.cpp
/*
各种计算函数
transpose、calculate 
*/
#include "matrix.h"

extern vector<matrix> matlist;//矩阵数组
extern int n;
extern bool calculate_success;

//加法运算符重载
matrix matrix::operator+(const matrix& other) {
	matrix result(row, col);
	result.matrix_create(row, col);
	if (row != other.row || col != other.col) {
        cout << "Error: Matrix dimensions must agree for addition." << endl;
        calculate_success = false;
        return result; // 返回零矩阵 
    }
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			result.data[i][j] = data[i][j] + other.data[i][j];
		}
	}
	return result;
}

//减法运算符重载
matrix matrix::operator-(const matrix& other) {
	matrix result(row, col);
	result.matrix_create(row, col);
	if (row != other.row || col != other.col) {
        cout << "Error: Matrix dimensions must agree for subtraction." << endl;
        calculate_success = false;
        return result; // 返回零矩阵 
    }
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			result.data[i][j] = data[i][j] - other.data[i][j];
		}
	}
	return result;
}

//乘法运算符重载
matrix matrix::operator*(const matrix& other) {
	matrix result(row, other.col);
	result.matrix_create(row, other.col);
	if (col != other.row) {
		cout << "Error: Matrix dimensions must agree for multiplication." << endl;
        calculate_success = false;
        return result; // 返回零矩阵 
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

//幂运算符重载
matrix matrix::operator^(int k) {
	matrix result(row, col);
	result.matrix_create(row, col);
	if (row != col || k < 0) {
		cout << "Error: Matrix dimensions must agree for power operations." << endl;
        calculate_success = false;
        return result; // 返回零矩阵
	}
	//初始化为单位矩阵
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

//名称：matrix_simplify_1化简函数
//功能：将矩阵化简为行阶梯形矩阵并存储
//参数：无
//返回值：行阶梯形矩阵 
matrix matrix::matrix_simplify_1() {
	matrix temp;
	temp.matrix_create(); 
	temp = *this;
//	temp.name = name + "_1S";//用于命名化简后得到的行阶梯型矩阵
	int num = 0;//用于确定行阶梯已经到达哪一行
	for (int i = 0; i < col; i++) {
		for (int j = num; j < row; j++) {
			if (temp.data[j][i]) {//第i列第j行元素不为0
				for (int k = j + 1; k < row; k++) {
					matrix ele;
					ele.matrix_create_3(row, k + 1, j + 1, fraction(0) - temp.data[k][i] / temp.data[j][i]);//生成第三种初等矩阵
					temp = ele * temp;
				}
				if (num != j) {
					for (int l = i; l < col; l++) {
						fraction x;
						x = temp.data[num][l];
						temp.data[num][l] = temp.data[j][l];
						temp.data[j][l] = x;
					}
				}
				num++;
				break;
			}
		}
	}
	return temp;
}

//名称：matrix_simplify_2化简函数
//功能：将矩阵化简为简化行阶梯形矩阵并存储
//参数：无
//返回值：简化行阶梯形矩阵
matrix matrix::matrix_simplify_2(int *the_number_of_pivots) {
	matrix temp;
	temp.matrix_create(); 
	temp = *this;
//	temp.name = name + "_2S";//用于命名化简后得到的行阶梯型矩阵
	int num = 0;//用于确定行阶梯已经到达哪一行
	for (int i = 0; i < col; i++) {
		for (int j = num; j < row; j++) {
			if (temp.data[j][i]) {//第i列第j行元素不为0
				for (int k = j + 1; k < row; k++) {
					matrix ele;
					ele.matrix_create_3(row, k + 1, j + 1, fraction(0) - temp.data[k][i] / temp.data[j][i]);//生成第三种初等矩阵
					temp = ele * temp;
				}
				if (num != j) {
					for (int l = i; l < col; l++) {
						fraction x;
						x = temp.data[num][l];
						temp.data[num][l] = temp.data[j][l];
						temp.data[j][l] = x;
					}
				}
				matrix ele3;
				ele3.matrix_create_1(col,num + 1,i + 1);
				temp=temp * ele3;
				num++;
				break;
			}
		}
	}
	for (int i = 0; i < row; i++) {
		for (int j = i; j < col; j++) {
			if (temp.data[i][j]) {
				matrix ele1;
				ele1.matrix_create_2(row, i + 1, fraction(1) / temp.data[i][j]);
				temp = ele1 * temp;
				for (int k = i - 1; k >= 0; k--) {
					matrix ele2;
					ele2.matrix_create_3(row, k + 1, i + 1, fraction(0) - temp.data[k][j]);
					temp = ele2 * temp;
				}
				break;
			}
		}
	}
	*the_number_of_pivots = num;
	return temp;
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


//名称：matrix_det行列式函数
//功能：求出方阵行列式的值
//参数：无
//返回值：矩阵的行列式（double） 
fraction matrix::matrix_det() {
	matrix temp = matrix_simplify_1();//化简矩阵为上三角矩阵
	fraction result(1);
	for (int i = 0; i < row; i++) {
		result = result * temp.data[i][i];//对角线元素值积
	}
	return result;
}

//名称：matrix_transpose转置函数
//功能：转置矩阵 
//参数：无
//返回值：转置后的矩阵 
matrix matrix::matrix_transpose() {
	matrix temp;
	temp.matrix_create(col, row);
	for (int i = 0; i < col; i++) {
	    for (int j = 0; j < row; j++) {
			temp.data[i][j] = data[j][i];//行列调换
	    }
	}
	return temp;
}

//名称：matrix_matrix_inverse逆矩阵函数
//功能：矩阵求逆 
//参数：无
//返回值：逆矩阵
matrix matrix::matrix_inverse() {
	matrix Inverse;
	Inverse.matrix_create(row, col);
	if (row != col)  {
		cout << "Error: Matrix dimensions must agree for inverse operations." << endl;
        calculate_success = false;
        return Inverse; // 返回零矩阵
	}
	else if (matrix_det() == fraction(0)) {
		cout << "Error: Det = 0" << endl;//不可逆，不符合要求，退出
		calculate_success = false;
		return Inverse;
	}
	else {
		Inverse.matrix_create_E(row);
		matrix temp;
		temp.matrix_create(); 
		temp = *this;
		int num = 0;//用于确定行阶梯已经到达哪一行
		for (int i = 0; i < col; i++) {
			for (int j = num; j < row; j++) {
				if (temp.data[j][i]) {//第i列第j行元素不为0
					matrix ele2;
					ele2.matrix_create_2(row, j + 1, fraction(1) / temp.data[j][i]);//生成第二种初等矩阵
					temp = ele2 * temp;
					Inverse = ele2 * Inverse;
					for (int k = 0; k < row; k++) {	
						if (k != j) {
							matrix ele3;
							ele3.matrix_create_3(row, k + 1, j + 1, - temp.data[k][i]);//生成第三种初等矩阵
							temp = ele3 * temp;
							Inverse = ele3 * Inverse;
						}
					}
					if (num != j) {
						for (int l = i; l < col; l++) {
							fraction x, y;
							x = temp.data[num][l];
							temp.data[num][l] = temp.data[j][l];
							temp.data[j][l] = x;
							y = Inverse.data[num][l];
							Inverse.data[num][l] = Inverse.data[j][l];
							Inverse.data[j][l] = y;
						}
					}
					num++;
					break;
				}
			}
		}
//		if (temp == matrix_simplify_2()){
//			return Inverse;	
//		}
//		else {
//			matrix_simplify_2().matrix_display(1);
//			temp.matrix_display(1);
//			cout << "Error" << endl;
//			return Inverse;
//		}
		return Inverse;
	}
}

//名称：matrix_adjoint 伴随矩阵
//功能：计算伴随矩阵
//参数：无
matrix matrix::matrix_adjoint(){
	fraction det=matrix_det();
    if(det==fraction(0)) {
    	cout << "Error: Det = 0" << endl;
        return matrix();
    }

	matrix temp=matrix_inverse();
    matrix adjoint;
    adjoint.matrix_create(row, col);
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			adjoint.data[i][j]=det*temp.data[i][j];
		}
	}
    return adjoint;
}

//名称：transpose转置函数（前端） 
//功能：转置矩阵 
//参数：无
void transpose() {
	cout << "Please enter your matrix name : ";
	string na;
    cin >> na;
	if (matrix_search(na) == -1){
	    cout << "Not Found" << endl; // 如果没有找到，输出提示
	    return;
	}
	else {
		matrix temp = matlist[matrix_search(na)].matrix_transpose();
		temp.name = matlist[matrix_search(na)].name + " ^ T";
		temp.matrix_display();
	}
}

//名称：det行列式函数（前端） 
//功能：求出方阵行列式的值
//参数：无
void det() {
	cout << "Please enter your matrix name : ";
	string na;
    cin >> na;
	if (matrix_search(na) == -1){
	    cout << "Not Found" << endl; // 如果没有找到，输出提示
	    return;
	}
	else if (matlist[matrix_search(na)].row != matlist[matrix_search(na)].col) {
		cout << "Not a square matrix" << endl;//不是方阵，不符合要求，退出
		return;
	}
	else {
		if (matlist[matrix_search(na)].matrix_det() == fraction(0)){
			cout << 0 << endl;
		}
		else {
			cout << matlist[matrix_search(na)].matrix_det() << endl;
		}
	}
}

//名称：matrix_calculate 计算函数
//功能：完成用户有关矩阵运算的算式 
//参数：无
void matrix_calculate() {
	string line;
	bool store = false;
	cout << "Please enter a one-line calculation (separated by spaces): " << endl;
	cout << "For example : m3 = m1 ^ -1 * m2 ^ T + m2 * m1 (m3 will be stored)" << endl;
	cout << "or : m1 * m2 + m2 ^ 2 * m1 ^ -1 (calculate only)" << endl;
	getline(cin, line);
	
	// 创建一个字符串流对象
	istringstream iss(line);
	string word;
	vector<string> mat;
	vector<string> op;
	matrix temp;
	temp.matrix_create(); 

    // 使用循环读取每个单词
	while (iss >> word) {
		if (word == "+" || word == "-" || word == "*" || word == "^"){
			op.push_back(word); 
		} else if (word == "="){
			store = true;
		} else {
			mat.push_back(word);
		}
	}
	if (op.size() >= mat.size()){
		cout << "Error" << endl;
		return;
	}
	vector<matrix> mat_cal;//将名字转化为矩阵 
	for (int i = store; i < mat.size(); i++){
		if (i - store < op.size() && op[i - store] == "^" && matrix_search(mat[i]) != -1){
			matrix temp;
			temp.matrix_create();
			temp = matlist[matrix_search(mat[i])];
			while (i - store < op.size() && op[i - store] == "^"){
				if (mat[i + 1] == "T"){
					temp = temp.matrix_transpose();
					op.erase(op.begin() + i - store);
					mat.erase(mat.begin() + i + 1);
					continue;
				}
				if (mat[i + 1] == "-1"){
					temp = temp.matrix_inverse();
					if (!calculate_success){
						calculate_success = true;
						return;
					}
					op.erase(op.begin() + i - store);
					mat.erase(mat.begin() + i + 1);
					continue;
				}
				else{
					try {
						int x = stoi(mat[i + 1]);
						temp = temp ^ x;
						if (!calculate_success){
							calculate_success = true;
							return;
						}
						op.erase(op.begin() + i - store);
						mat.erase(mat.begin() + i + 1);
						continue;
					}
					catch (const invalid_argument& e) {
	    				cerr << "Invalid argument: " << "power operation" << endl;
	    				return;
	    			}
				}
			}
			mat_cal.push_back(temp); 
		} else if (matrix_search(mat[i]) == -1){
			cout << "Not Found " << mat[i] << endl;
			return;
		}
		mat_cal.push_back(matlist[matrix_search(mat[i])]);
	}
	
	for (int i = 0; i < op.size() && op.size() > 0; i++) {//*
		if (op[i] == "*") {
			mat_cal[i] = mat_cal[i] * mat_cal[i + 1];
			if (calculate_success){
				op.erase(op.begin() + i);
				mat.erase(mat.begin() + i + 1);
				mat_cal.erase(mat_cal.begin() + i + 1);
				i--;
			} else{
				calculate_success = true;
				return;
			}
		}
	}
	while (op.size() > 0) {//+-
//		cout << "Current operation: " << op[0] << endl;
		if (op[0] == "+") {
			mat_cal[0] = mat_cal[0] + mat_cal[1];
			if (calculate_success){
				op.erase(op.begin());
				mat.erase(mat.begin() + 1);
				mat_cal.erase(mat_cal.begin() + 1);
			} else{
				calculate_success = true;
				return;
			}
		}
		else if (op[0] == "-") {
			mat_cal[0] = mat_cal[0] - mat_cal[1];
			if (calculate_success){
				op.erase(op.begin());
				mat.erase(mat.begin() + 1);
				mat_cal.erase(mat_cal.begin() + 1);
			} else{
				calculate_success = true;
				return;
			}
		}
		else {
			cout << "Error" << endl;
			return;
		}
	}
	temp = mat_cal[0];
	if (store) {
		temp.name = mat[0];
		temp.matrix_display();
		temp.matrix_store();
	}
	else {
		temp.matrix_display(1);
	}
	return;
}

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
