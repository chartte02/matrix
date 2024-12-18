/*头文件：
 void matrix_modify_name(string na);
 void matrix_intercept_row(int r2,int r1);
 void matrix_intercept_col(int c2,int c1);
 void matrix_intercept_dia(int d);
void matrix::matrix_create_random(int i, int j,double a,double b) ;
void matrix::matrix_modify()

void matrix::matrix_intercept()
 */

// 加一个
// #include <algorithm>

#include"matrix.h"

vector<matrix> list(0);//矩阵数组

//名称：创造增广矩阵
//功能：生成输入两个矩阵的增广矩阵
//参数：输入两个matrix型矩阵，按照前后顺序生成
void matrix::create_argumentation(const matrix&m1,const matrix &m2) {
    if(m1.row!=m2.row) {
        cout<<"The numbers of the rows of the two matrixes must be the same"<<endl;
        return;
    }
    row=m1.row;
    col=m1.col+m2.col;
    matrix_create(row,col);
    for(int i=0;i<row;i++) {
        for(int j=0;j<m1.col;j++) {
            data[i][j]=m1.data[i][j];
        }
        for(int j=m1.col;j<col;j++) {
            data[i][j]=data[i][j-m1.col];
        }
    }
    matrix_store();
   matrix_output();
    return;
}


//作用：生成截取矩阵
//     可截取行，列，对角
void matrix::matrix_intercept() {
    cout<<"please input the name of the matrix you want to intercept:"<<endl;
    string name_;
    cin>>name_;
    if(matrix_search(name_)==-1) {
        cout<<"Not found"<<endl;
        return;
    }
    cout<<"please input the pattern you want to intercept(row or column or diagonal)"<<endl;
    string pattern_;
    if(pattern_=="row") {
        cout<<"please input the row you want to intercept(from r1 to r2):"<<endl;
        int r1,r2;
        while(!(cin>>r1>>r2)) {
            cin.clear();
            cin.ignore();
            cout<<"Incorrect input,please input as an integer again:"<<endl;
        }
        matrix_intercept_row(r1,r2);
    }
    else if(pattern_=="column") {
        cout<<"please input the column you want to intercept(from r1 to r2):"<<endl;
        int r1,r2;
        while(!(cin>>r1>>r2)) {
            cin.clear();
            cin.ignore();
            cout<<"Incorrect input,please input as an integer again:"<<endl;
        }
        matrix_intercept_col(r1,r2);
    }
    else if(pattern_=="diagonal") {
        cout<<"please input the dianonal you want to intercept:"<<endl;
        cout<<" 0 represents the main diagonal"<<endl;
        cout<<"positive number represents the diagonal above the main diagonal"<<endl;
        cout<<"negative number represents the diagonal down the main diagonal"<<endl;
        int d;
        while(cin>>d){
            cin.clear();
            cin.ignore();
            cout<<"Incorrect input,please input as an integer again:"<<endl;
        }
        matrix_intercept_dia(d);
    }
}


//作用：更改已有矩阵的值或名字
void matrix::matrix_modify() {
    string name_;
    cout<<"please input your the name of the matrix you want to modify:"<<endl;
    cin>>name_;
   if(matrix_search(name_)==-1) {
       cout<<"Not found"<<endl;
       return;
   }
    cout<<"please input the thing you want to modify:(name or value)"<<endl;
    string choice;
    cin>>choice;
    if(choice == "name") {
        auto it = find(list.begin(),list.end(),name);
        cout<<"please input the new name:"<<endl;
        string new_name;
        cin>>new_name;
        (*it).name = new_name;
        return;
    }
    else if(choice == "value") {
        int i,j;
        double data_;
        cout<<"please input the row and column number:"<<endl;
        cin>>i>>j;
        cout<<"please input the new value:"<<endl;
        cin>>data_;
        matrix_modify_data(i,j,data_);
        return;
    }
    else {
        cout<<"incorrect input"<<endl;
        return;
    }

}

 //名称：matrix_modify_data
 //功能：修改i行j列元素
 //参数：i，j：i行j列
 //     data_:修改的数据值
 void matrix::matrix_modify_data(int i,int j,double data_) {
     int r=i-1,c=j-1;
     for(int k=0;k<row;k++) {
         for(int l=0;l<col;l++) {
             if(k==r && l==c) {
                 data[k][l]=data_;
                 return;
             }
         }
     }
     return;
 }


 //名称：matrix_intercept_row截取行函数
 //功能：截取r1到r2行的矩阵并存储
 //参数：r1，r2：r1行到r2行
 void matrix::matrix_intercept_row(int r2,int r1=1) {     //仿制transpose的前端设计
     int r_1=r1-1,r_2=r2-1;
     if(matrix_search(name)==-1) {
         cout<<"Not Found"<<endl;
         return;
     }
     matrix_create(list[matrix_search(name)].row+r_1-r_2,list[matrix_search(name)].col);
     for(int k=r_1;k<+r_2;k++) {
         for(int t=0;t<col;t++) {
             data[k][t]=list[matrix_search(name)].data[k][t];
         }
     }

     name=name+"row_i"; //这里名字怎么处理没想好
     matrix_store();
     matrix_output();
 }




 //名称：matrix_intercept_col截取列函数
 //功能：截取c1到c2行的矩阵并存储
 //参数: c1,c2:c1到c2列
 void matrix::matrix_intercept_col(int c2,int c1=1) {
     int c_1=c1-1,c_2=c2-1;
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
//
// void matrix::matrix_create_random(int i, int j,double a,double b) {
//      srand(time(NULL));
//      matrix_create(i,j);
//      for(int k=0;k<row;k++) {
//          for(int l=0;l<col;l++) {
//              data[k][l]=a+(b-a)*rand()/((double) RAND_MAX);
//          }
//      }
//
//  }