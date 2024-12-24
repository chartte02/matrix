//�ļ���manage.cpp 
/*
���롢��������ҡ��洢��չʾ����
input��output��search��store��display 
*/
#include "matrix.h"

int n = 0;//���о������ 
vector<matrix> matlist(0);//��������
bool fraction_fail = 0;
bool calculate_success = true;

// ���ƣ�matrix_search ���Һ�������֪���֣� 
// ���ܣ�����matlist�е�ͬ������ 
// ���������֣��ַ����� 
// ����ֵ����ţ�int�� 
int matrix_search(string na) {
	for (int i = 0; i < n; i++) {
        if (matlist[i].name == na) {
            return i;
        }
    } 
    return -1;
}

// ���ƣ�matrix_store �洢������������� 
// ���ܣ��洢��matlist����
// ��������
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

// ���ƣ�matrix_display �����������ά���� ������洢�� 
// ���ܣ������ǰ���������Ԫ�� 
// ��������
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

// ���ƣ�matrix_input ���뺯������ά���� 
// ���ܣ������������ƣ��У��У���ȫ��Ԫ�أ����洢��matlist����
// ��������
void matrix::matrix_input() {
    cout << "Name : "; 
	cin >> name;//��������
	if (matrix_search(name) == -1){//�¾���
		cout << "Row : " ;
		while (true) {
            cin >> row;
            if (cin.fail() || row <= 0) {
                cout << "Wrong input (must be a positive digit)" << endl;
                cin.clear(); // �����������״̬
                cin.ignore(100, '\n'); // ���Դ�������
                cout << "Row: ";
            } else {
                break; // ������Ч���˳�ѭ��
            }
        }
		cout << "Column : " ;
		while (true) {
            cin >> col;
            if (cin.fail() || col <= 0) {
                cout << "Wrong input (must be a positive digit)" << endl;
                cin.clear(); // �����������״̬
                cin.ignore(100, '\n'); // ���Դ�������
                cout << "Column : ";
            } else {
                break; // ������Ч���˳�ѭ��
            }
        }
		cout << "Please enter matrix elements line by line (in decimal form)" << "\n";
		matrix_create(row, col);//�������ɺ��� 
	    for (int i = 0; i < row; i++) {
	        for (int j = 0; j < col; j++) {
				cin >> data[i][j];//����data
				if (cin.fail()) {
        			cout << "Wrong input (must be of double type)" << endl;
        			cin.clear(); // �����������״̬
					cin.ignore(100, '\n'); 
        			return;
    			}
    			if (fraction_fail) {
        			cin.clear(); // �����������״̬
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

// ���ƣ�output ���������ǰ�ˣ�
// ���ܣ����ָ�����Ƶľ��������Ԫ�� 
// ��������
void output() {
	cout << "Please enter your matrix name : ";
	string na;
    cin >> na;
	if (matrix_search(na) == -1){
	    cout << "Not Found" << endl; // ���û���ҵ��������ʾ
	    return;
	}
	else {
		matlist[matrix_search(na)].matrix_display();
	}
}

// ���ƣ�del ɾ��������ǰ�ˣ�
// ���ܣ�ɾ��ָ�����Ƶľ��������Ԫ�� 
// ��������
void del(){
	cout << "Please enter your matrix name : ";
	string name;
    cin >> name;
	if (matrix_search(name) == -1){
	    cout << "Not Found" << endl; // ���û���ҵ��������ʾ
	    return;
	}
	else {
		matlist.erase(matlist.begin() + matrix_search(name));
		cout << "Your matrix " << name << " has been deleted" << endl;
		n--;
	}
}

// ���ƣ�clear ��պ�����ǰ�ˣ�
// ���ܣ����matlist�е����о��� 
// ��������
void clear(){
	matlist.clear();
	n = 0;
}

