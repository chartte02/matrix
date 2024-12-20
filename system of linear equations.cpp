#include"matrix.h"
bool is_all_zero(const matrix&m);

//默认行相等
void matrix::solve_system_of_linear_equtions( matrix&m1, matrix&m2) {
   if(is_all_zero(m2)) {

      //nonhomogeneous_linear_equation();
      matrix_create(m1.row,1);

      if(m1.col==m1.row) {
         if(m1.matrix_det()!=0) {
            for(int i=0;i<m1.row;i++) {
               data[i][0]=0;
            }
            cout<<"The system has the unique solution"<<endl;
            output();
            return;
         }
      }
      else {
         int *the_number_of_pivots;
         m1.matrix_simplify_2(the_number_of_pivots);
         matrix solution[*the_number_of_pivots];
         for(int i=0;i<m1.col-*the_number_of_pivots;i++) {
            for(int j=0;j<m1.row;j++) {
               solution[i].data[j][0]=-m1.data[j][*the_number_of_pivots+i];
            }
            solution[i].data[*the_number_of_pivots+i][0]=1;
         }
         cout<<"The system has infinitely many solutions"<<endl;
        cout<<"One set of the bases of the solution is:"<<endl;
         for(int i=0;i<*the_number_of_pivots;i++) {
            cout<<"(";
            for(int j=0;j<m1.row;j++) {
               cout<<solution[i].data[j]<<" ";
            }
            cout<<")T"<<endl;
         }
      }

   }

   else {
      //homogeneous_linear_equation();
      if(m1.col==m1.row) {
         if(m1.matrix_det()!=0) {
            matrix temp[m1.row];
            for(int i=0;i<m1.row;i++) {
             temp[i]=m1;
            }

            for(int i=0;i<m1.col;i++) {
               for(int j=0;j<m1.row;j++) {
                  temp[i].data[j][i]=m2.data[j][0];
               }
            }

            matrix solution;
            solution.matrix_create(m1.row,1);
            for(int i=0;i<m1.row;i++) {
               solution.data[i][0]=temp[i].matrix_det()/m1.matrix_det();
            }
            cout<<"The system has the unique solution"<<endl;
            solution.matrix_display();
            return;
         }
      }

      matrix temp;
       int *the_number_of_pivots;
      temp.create_argumentation(m1,m2);
      temp.matrix_simplify_2(the_number_of_pivots);
         matrix solution[temp.col-1-*the_number_of_pivots];
         for(int i=0;i<temp.col-1-*the_number_of_pivots;i++) {
            for(int j=0;j<m1.row;j++) {
               solution[i].data[j][0]=-temp.data[j][*the_number_of_pivots+i];
            }
            solution[i].data[*the_number_of_pivots+i][0]=1;
         }
         cout<<"The system has infinitely many solutions"<<endl;
      cout<<"One of the special solution is:"<<endl;
      cout<<"(";
      for(int i=0;i<temp.col;i++) {
         cout<<temp.data[i][temp.col-1]<<" ";
      }
      cout<<")T"<<endl;
        cout<<"One set of the bases of the solution is:"<<endl;
         for(int i=0;i<*the_number_of_pivots;i++) {
            cout<<"(";
            for(int j=0;j<m1.row;j++) {
               cout<<solution[i].data[j]<<" ";
            }
            cout<<")T"<<endl;
         }

   }
}

bool is_all_zero(const matrix&m) {
   for(int i=0;i<m.row;i++) {
      if(m.data[i][0]!=0)
         return false;
   }
   return true;
}

matrix matrix::matrix_simplify_2(int *the_number_of_pivots=nullptr) {
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
               ele.matrix_create_3(row, k + 1, j + 1, -temp.data[k][i] / temp.data[j][i]);//生成第三种初等矩阵
               temp = ele * temp;
            }
            if (num != j) {
               for (int l = i; l < col; l++) {
                  double x;
                  x = temp.data[num][l];
                  temp.data[num][l] = temp.data[j][l];
                  temp.data[j][l] = x;
               }
            }
            matrix ele3;
            ele3.matrix_create_1(col,num+1,i+1);
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
            ele1.matrix_create_2(row, i + 1, 1 / temp.data[i][j]);
            temp = ele1 * temp;
            for (int k = i - 1; k >= 0; k--) {
               matrix ele2;
               ele2.matrix_create_3(row, k + 1, i + 1, -temp.data[k][j]);
               temp = ele2 * temp;
            }
            break;
         }
      }
   }
   *the_number_of_pivots=num;
   return temp;

}