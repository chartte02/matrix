//�ļ��� modify.cpp 
/*
void matrix_modify_name(string na);
void matrix_intercept_row(int r2,int r1);
void matrix_intercept_col(int c2,int c1);
void matrix_intercept_dia(int d);
*/

#include "matrix.h"
//���ƣ�matrix_modify_data
//���ܣ��޸�i��j��Ԫ��
//������i��j��i��j��	data_:�޸ĵ�����ֵ
void matrix::matrix_modify_data(int i,int j,double data_) {
    int r = i - 1,c = j - 1;
    for(int k = 0; k < row; k++) {
        for(int l = 0; l < col; l++) {
            if(k == r && l == c) {
                data[k][l] = data_;
                return;
            }
        }
    }
    return;
}



//���ƣ�matrix_intercept_row��ȡ�к���
//���ܣ���ȡr1��r2�еľ��󲢴洢
//������r1��r2��r1�е�r2��
void matrix::matrix_intercept_row(int r2, int r1 = 1) {     //����transpose��ǰ�����
    int r_1 = r1 - 1,r_2 = r2 - 1;
    if(matrix_search(name)==-1) {
        cout<<"Not Found"<<endl;
        return;
    }
    matrix_create(list[matrix_search(name)].row + r_1 - r_2, list[matrix_search(name)].col);
    for(int k = r_1; k <= r_2; k++) {
        for(int t = 0; t < col; t++) {
            data[k][t] = list[matrix_search(name)].data[k][t];
        }
    }

    name = name +"row_i"; //����������ô����û���
    matrix_store();
    matrix_output();
}




//���ƣ�matrix_intercept_col��ȡ�к���
//���ܣ���ȡc1��c2�еľ��󲢴洢
//����: c1,c2:c1��c2��
void matrix::matrix_intercept_col(int c2,int c1=1) {
    int c_1 == c1 - 1, c_2 = c2 - 1;
    if(matrix_search(name)==-1) {
        cout<<"Not Found"<<endl;
        return;
    }
    matrix_create(list[matrix_search(name)].row,list[matrix_search(name)].col+c_1-c_2);
    for(int k=0;k<row;k++) {
        for(int t=c_1;t<=c_2;t++) {
            data[k][t]=list[matrix_search(name)].data[k][t];
        }
    }
    name=name+"col_i";
    matrix_store();
    matrix_output();
}


//名称：matrix_intercept_dia 截取对角函数
//功能：截取d以上的数据，其余以零补充
//参数：d ：对角线 （规定主对角线为0，向上为正，向下为负）
void matrix::matrix_intercept_dia(int d) {
    if(matrix_search(name)==-1) {
        cout<<"Not Found"<<endl;
        return;
    }
    matrix_create(list[matrix_search(name)].row,list[matrix_search(name)].col);
    if(d>=0) {
        for(int k=0;k<row;k++) {
            for(int t=d+k;t<col;t++) {
                data[k][t]=list[matrix_search(name)].data[k][t];
            }
        }
    }

    else {
        for(int k=0;k<row;k++) {
            for(int t=(k+d>0?k+d:0);t<col;t++) {
                data[k][t]=list[matrix_search(name)].data[k][t];
            }
        }
    }
    return;
}
