#include"matrix.h"
bool is_all_zero(const matrix&m);

//默认行相等
 void matrix::solve_system_of_linear_equtions( matrix&m1, matrix&m2) {
    if(is_all_zero(m2)) {
       //homogeneous_linear_equation();
       matrix_create(m1.col,1);

       if(m1.col==m1.row) {
          if(m1.matrix_det()!=fraction(0)) {
             for(int i=0;i<m1.row;i++) {
                data[i][0]=0;
             }
             cout<<"The system has the unique solution"<<endl;
             matrix_display();
             return;
          }
          else {
             int the_number;
             int *the_number_of_pivots=&the_number;
             m1=m1.matrix_simplify_2(the_number_of_pivots);
             matrix solution[m1.col-*the_number_of_pivots];
             for(int i=0;i<m1.col-*the_number_of_pivots;i++) {
                solution[i].matrix_create(m1.col,1);
             }
             for(int i=0;i<m1.col-*the_number_of_pivots;i++) {
                for(int j=0;j<m1.row;j++) {
                   solution[i].data[j][0]=fraction(-1)*m1.data[j][*the_number_of_pivots+i];
                }
                solution[i].data[*the_number_of_pivots+i][0]=fraction(1);
             }
             cout<<"The system has infinitely many solutions"<<endl;
             cout<<"One set of the bases of the solution is:"<<endl;
             for(int i=0;i<m1.col-*the_number_of_pivots;i++) {
                cout<<"( ";
                for(int j=0;j<m1.col;j++) {
                   cout<<solution[i].data[j][0]<<" ";
                }
                cout<<")T"<<endl;
             }
             return;
          }

       }
    }
       else {
          //nonhomogeneous_linear_equation();
          if(m1.col==m1.row) {
             if(m1.matrix_det()!=fraction(0)) {
                matrix temp[m1.row];
                for(int i=0;i<m1.row;i++) {
                   temp[i].matrix_create(m1.row,m1.col);
                   temp[i]=m1;
                }

                for(int i=0;i<m1.col;i++) {
                   for(int j=0;j<m1.row;j++) {
                      temp[i].data[j][i]=m2.data[j][0];
                   }
                }

                matrix solution;
                solution.matrix_create(m1.col,1);
                for(int i=0;i<m1.row;i++) {
                   solution.data[i][0]=temp[i].matrix_det()/m1.matrix_det();
                }
                cout<<"The system has the unique solution"<<endl;
                solution.matrix_display();
                return;
             }
          }

          matrix temp;
          temp.matrix_create();
          int the_number;
          int *the_number_of_pivots=&the_number;
          temp=m1.create_argumentation(m1, m2);
          matrix mm=temp;

          temp=temp.matrix_simplify_2(the_number_of_pivots);
          mm=mm.matrix_simplify_1();
          for(int i=0;i < mm.row - the_number+1;i++) {
             if(mm.data[the_number-1+i][mm.col-1]!=fraction(0)) {
                cout<<"The system doesn't have solution."<<endl;
                return;
             }
          }
          matrix solution[temp.col-1-*the_number_of_pivots];
          for(int i=0;i<temp.col-1-*the_number_of_pivots;i++) {
             solution[i].matrix_create(m1.col,1);
          }
          for(int i=0;i<temp.col-1-*the_number_of_pivots;i++) {
             for(int j=0;j<m1.row;j++) {
                solution[i].data[j][0]=fraction(-1)*temp.data[j][*the_number_of_pivots+i];
             }
             solution[i].data[*the_number_of_pivots+i][0]=fraction(1);
          }

          cout<<"The system has infinitely many solutions"<<endl;
          cout<<"One of the special solution is:"<<endl;
          cout<<"( ";
          for(int i=0;i<temp.row;i++) {
             cout<<temp.data[i][temp.col-1]<<" ";
          }
          for(int i=temp.row;i<temp.col-1;i++) {
             cout<<0<<" ";
          }
          cout<<")T"<<endl;
          cout<<"One set of the bases of the solution is:"<<endl;
          for(int i=0;i<temp.col-1-*the_number_of_pivots;i++) {
             cout<<"(";
             for(int j=0;j<m1.col;j++) {
                cout<<solution[i].data[j][0]<<" ";
             }
             cout<<")T"<<endl;
          }
       }
    }


bool is_all_zero(const matrix&m) {
   for(int i=0;i<m.row;i++) {
      if(m.data[i][0]!=fraction(0))
         return false;
   }
   return true;
}
