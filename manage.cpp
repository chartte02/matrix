//文件：manage.cpp 
/*
输入、输出、查找、存储、展示函数
input、output、search、store、display 
*/
#include "matrix.h"

int n = 0;//现有矩阵个数 
vector<matrix> matlist(0);//矩阵数组
bool fraction_fail = 0;
bool calculate_success = true;

// 名称：matrix_search 查找函数（已知名字） 
// 功能：查找matlist中的同名函数 
// 参数：名字（字符串） 
// 返回值：编号（int） 
int matrix_search(string na) {
	for (int i = 0; i < n; i++) {
        if (matlist[i].name == na) {
            return i;
        }
    } 
    return -1;
}

// 名称：matrix_store 存储函数（任意矩阵） 
// 功能：存储于matlist数组
// 参数：无
void matrix::matrix_store() {
	if (matrix_search(name) == -1){
		No = n;
		matlist.push_back(*this);
		cout << "Your matrix " << name << " has been stored" << endl;
		n++;
	}
	else {
		cout << "This matrix already exists." <<endl;
	}
}

// 名称：matrix_display 输出函数（二维矩阵） （无需存储） 
// 功能：输出当前矩阵的所有元素 
// 参数：无
void matrix::matrix_display(int no_name, int type) {
	if (!no_name) {
		cout << name << endl;
	}
	if (type){
		for (int i = 0; i < row; i++) {
        	for (int j = 0; j < col; j++) {
        	    cout << double(data[i][j]) << "\t";
        	} 
        	cout << endl;
    	}
    	return;
	}
	for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << data[i][j] << "\t";
        } 
        cout << endl;
	}
}

// 名称：matrix_input 输入函数（二维矩阵） 
// 功能：输入矩阵的名称，行，列，和全部元素，并存储于matlist数组
// 参数：无
void matrix::matrix_input() {
    cout << "Name : "; 
	cin >> name;//输入名称
	if (matrix_search(name) == -1){//新矩阵
		cout << "Row : " ;
		while (true) {
            cin >> row;
            if (cin.fail() || row <= 0) {
                cout << "Wrong input (must be a positive digit)" << endl;
                cin.clear(); // 清除输入流的状态
                cin.ignore(100, '\n'); // 忽略错误输入
                cout << "Row: ";
            } else {
                break; // 输入有效，退出循环
            }
        }
		cout << "Column : " ;
		while (true) {
            cin >> col;
            if (cin.fail() || col <= 0) {
                cout << "Wrong input (must be a positive digit)" << endl;
                cin.clear(); // 清除输入流的状态
                cin.ignore(100, '\n'); // 忽略错误输入
                cout << "Column : ";
            } else {
                break; // 输入有效，退出循环
            }
        }
		cout << "Please enter matrix elements line by line (in decimal form)" << "\n";
		matrix_create(row, col);//调用生成函数 
	    for (int i = 0; i < row; i++) {
	        for (int j = 0; j < col; j++) {
				cin >> data[i][j];//输入data
				if (cin.fail()) {
        			cout << "Wrong input (must be of double type)" << endl;
        			cin.clear(); // 清除输入流的状态
					cin.ignore(100, '\n'); 
        			return;
    			}
    			if (fraction_fail) {
        			cin.clear(); // 清除输入流的状态
					cin.ignore(100, '\n'); 
					fraction_fail = 0;
        			return;
    			}
	        }
	    }
		matrix_store(); 
	}
	else {
		cout << "This matrix already exists. If you want to modify the matrix, please enter 'mod'." <<endl;
	}
}

// 名称：output 输出函数（前端）
// 功能：输出指定名称的矩阵的所有元素 
// 参数：无
void output() {
	cout << "Please enter your matrix name : ";
	string na;
    cin >> na;
	if (matrix_search(na) == -1){
	    cout << "Not Found" << endl; // 如果没有找到，输出提示
	    return;
	}
	else {
		matlist[matrix_search(na)].matrix_display();
	}
}

// 名称：del 删除函数（前端）
// 功能：删除指定名称的矩阵的所有元素 
// 参数：无
void del(){
	cout << "Please enter your matrix name : ";
	string name;
    cin >> name;
	if (matrix_search(name) == -1){
	    cout << "Not Found" << endl; // 如果没有找到，输出提示
	    return;
	}
	else {
		matlist.erase(matlist.begin() + matrix_search(name));
		cout << "Your matrix " << name << " has been deleted" << endl;
		n--;
	}
}

// 名称：clear 清空函数（前端）
// 功能：清空matlist中的所有矩阵 
// 参数：无
void clear(){
	matlist.clear();
	n = 0;
}

