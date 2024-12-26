#include "matrix.h"

extern vector<matrix> matlist;
extern int n;//现有矩阵个数 
extern bool fraction_fail;
extern bool calculate_success;

void show_help();
void show_list();

int main() {
	cout << "Welcome to the Matrix Calculator" << endl << endl;
	show_help(); // 显示帮助信息
	cout << endl;
	cout << "help -- to get function list" << endl;//help的功能 
	while (true) {
		string function;
		cout << endl;
		cout << "Please enter the function : ";
		cin >> function;
	    if (function == "help") {
			show_help(); // 显示帮助信息
	    } else if (function == "input") {
			matrix temp;
			temp.matrix_input();
		} else if (function == "output") {
		    output();
		} else if (function == "delete") {
		    del();
		} else if (function == "clear") {
		    clear();
		} else if (function == "create") {
		    cout << "Please enter your matrix kind : ";
		    string kind;
		    //未完成 
		} else if (function == "trans") {
		    transpose();
		} else if (function == "cal") {
			cin.ignore(100, '\n');
			matrix_calculate();
		} else if (function == "mod") {

		} else if (function == "det") {
			det();
		} else if (function == "oth") {
			oth();
		} else if (function == "eig") {
			eig();
		} else if (function == "list") {
		    show_list();
		} else if (function == "exit") {
		    return 0;
		} else {
		    cout << "Invalid command. " << endl;
		    cout << "help -- to get function list" << endl;
		}
	}
	return 0;
}

void show_help() {//菜单栏 
	cout << "input -- to input a matrix" << endl;
	cout << "delete -- to delete a matrix" << endl;
	cout << "clear -- to clear all matrix" << endl;
	cout << "output -- to output the matrix you searched" << endl;
	cout << "trans -- to transpose your matrix" << endl;
	cout << "cal -- to start calculating(+ - * ^ T -1)" << endl;
	cout << "det -- to calculate the determinant of your matrix " << endl; 
	cout << "list -- to get matrix name list" << endl; 
	cout << "exit -- to end the program" << endl;
}

void show_list() {//矩阵列表栏 
	cout << "There are " << n << " existing matrices. " << endl;
	if (n == 0) {
		return;
	} else if (n == 1) {
		cout << "The existing matrices is: " << endl;
		for (int i = 0; i < n; i++){
			cout << matlist[i].name << " " ;
		}
	} else {
		cout << "The existing matrices are: " << endl;
		for (int i = 0; i < n; i++){
			cout << matlist[i].name << " " ;
		}
	}
}

