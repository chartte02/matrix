#include <iostream>
#include "matrix.h"
using namespace std;

/*头文件里复制下面声明
        void get_matrix_1(int order,int r, int c);
         void get_matrix_2(int order,int r, int k);
            void get_matrix_3(int order,int r, int c, int k);
 */

//参数：order：矩阵阶数
//     r,c: r行c列
//功能：获得第一类初等矩阵E(i,j)
void matrix::get_matrix_1(int order,int r,int c) {

    data = new double *[order];//申请order个数组指针空间
    for (int i = 0; i < order; i++) {
        data[i] = new double [order];//申请order个数组指针空间
        if (!data[i]) {
            cout << "Cannot create a new matrix because memory is full" << endl;
            return;
        }

    }
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
            if(i==j&&i!=r&&i!=c) data[i][j] = 1;
            else if(i==c||j==r) data[i][j] = 1;
            else data[i][j] = 0;
        }
    }

}

//参数：order: 矩阵阶数
//    r:r行 k: k倍
//功能：获得第二类初等矩阵 E(i(k))
void matrix::get_matrix_2(int order,int r,int k) {

    data = new double *[order];//申请order个数组指针空间
    for (int i = 0; i < order; i++) {
        data[i] = new double [order];//申请order个数组指针空间
        if (!data[i]) {
            cout << "Cannot create a new matrix because memory is full" << endl;
            return;
        }

    }
    for (int i = 0; i < order; i++) {
      for (int j = 0; j < order; j++) {
      if(i==j&&i!=r)
        data[i][j]=1;
      else if(i==r&&j==r) data[i][j]=k;
      else data[i][j] = 0;

      }

    }
}

//参数：order：矩阵阶数
//     r,c:r行c列 k：k倍
//功能：获取第三类初等矩阵E(i,j(k))
void matrix::get_matrix_3(int order,int r,int c,int k) {

    data = new double *[order];//申请order个数组指针空间
    for (int i = 0; i < order; i++) {
        data[i] = new double [order];//申请order个数组指针空间
        if (!data[i]) {
            cout << "Cannot create a new matrix because memory is full" << endl;
            return;
        }

    }
    for (int i = 0; i < order; i++) {
      for (int j = 0; j < order; j++) {
        if(i==j) data[i][j] = 1;
        else if(i==r&&j==c) data[i][j] = k;
        else data[i][j] = 0;
      }
      }

}

