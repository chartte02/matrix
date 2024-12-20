//文件： modify.cpp 
/*
void matrix_modify_name(string na);
void matrix_intercept_row(int r2,int r1);
void matrix_intercept_col(int c2,int c1);
void matrix_intercept_dia(int d);
*/

#include "matrix.h"
//名称：matrix_modify_data
//功能：修改i行j列元素
//参数：i，j：i行j列	data_:修改的数据值
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



//名称：matrix_intercept_row截取行函数
//功能：截取r1到r2行的矩阵并存储
//参数：r1，r2：r1行到r2行
void matrix::matrix_intercept_row(int r2, int r1 = 1) {     //仿制transpose的前端设计
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

    name = name +"row_i"; //这里名字怎么处理没想好
    matrix_store();
    matrix_output();
}




//名称：matrix_intercept_col截取列函数
//功能：截取c1到c2行的矩阵并存储
//参数: c1,c2:c1到c2列
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


//鍚嶇О锛歮atrix_intercept_dia 鎴彇瀵硅鍑芥暟
//鍔熻兘锛氭埅鍙杁浠ヤ笂鐨勬暟鎹紝鍏朵綑浠ラ浂琛ュ厖
//鍙傛暟锛歞 锛氬瑙掔嚎 锛堣瀹氫富瀵硅绾夸负0锛屽悜涓婁负姝ｏ紝鍚戜笅涓鸿礋锛�
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
