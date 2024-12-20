//文件：calculate.cpp
/*
各种计算函数
transpose、calculate 
*/
#include "matrix.h"

extern vector<matrix> matlist;//矩阵数组
extern int n;
extern bool calculate_success;

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
matrix matrix::matrix_simplify_2(*int the_number_of_pivots=nullptr) {
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
	*the_number_of_pivots=num;
	return temp;
}

////名称：matrix_simplify_3化简函数
////功能：将矩阵化简为相抵标准型并存储
////参数：无
//void matrix::matrix_simplify_3() {
//	if (matrix_search(name) == -1) {
//		cout << " Not Found" << endl;//如果没有找到，输出提示
//		return;
//	}
//	else {
//		matrix temp;
//		temp.data = new double* [row];
//		for (int i = 0; i < row; i++) {
//			temp.data[i] = new double[col];
//		}
//		temp = *this;
//		temp.name = name + "_3S";//用于命名化简后得到的行阶梯型矩阵
//		int num = 0;//用于确定行阶梯已经到达哪一行
//		for (int i = 0; i < col; i++) {
//			for (int j = num; j < row; j++) {
//				if (temp.data[j][i]) {//第i列第j行元素不为0
//					for (int k = j + 1; k < row; k++) {
//						matrix ele;
//						ele.matrix_create_3(row, k + 1, j + 1, -temp.data[k][i] / temp.data[j][i]);//生成第三种初等矩阵
//						temp = ele * temp;
//					}
//					if (num != j) {
//						for (int l = i; l < col; l++) {
//							double x;
//							x = temp.data[num][l];
//							temp.data[num][l] = temp.data[j][l];
//							temp.data[j][l] = x;
//						}
//					}
//					num++;
//					break;
//				}
//			}
//		}
//		matrix TEMP;
//		TEMP.matrix_create(row, col);//生成一个零矩阵
//		for (int i = 0; i < num; i++) {
//			TEMP.data[i][i] = 1;//将零矩阵改为一个秩为行阶梯形矩阵非零行数num减一
//		}
//		TEMP.matrix_store();//存储
//		TEMP.matrix_output();
//		cout << "\n";
//	}
//}


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
	else if (matrix_det() == 0) {
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
							ele3.matrix_create_3(row, k + 1, j + 1, fraction(0) - temp.data[k][i]);//生成第三种初等矩阵
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
		if (matlist[matrix_search(na)].matrix_det() == 0){
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

