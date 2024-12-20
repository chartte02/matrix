//ÎÄ¼ş£º modify.cpp 
/*
void matrix_modify_name(string na);
void matrix_intercept_row(int r2,int r1);
void matrix_intercept_col(int c2,int c1);
void matrix_intercept_dia(int d);
*/

#include "matrix.h"
//Ãû³Æ£ºmatrix_modify_data
//¹¦ÄÜ£ºĞŞ¸ÄiĞĞjÁĞÔªËØ
//²ÎÊı£ºi£¬j£ºiĞĞjÁĞ	data_:ĞŞ¸ÄµÄÊı¾İÖµ
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



//Ãû³Æ£ºmatrix_intercept_row½ØÈ¡ĞĞº¯Êı
//¹¦ÄÜ£º½ØÈ¡r1µ½r2ĞĞµÄ¾ØÕó²¢´æ´¢
//²ÎÊı£ºr1£¬r2£ºr1ĞĞµ½r2ĞĞ
void matrix::matrix_intercept_row(int r2, int r1 = 1) {     //·ÂÖÆtransposeµÄÇ°¶ËÉè¼Æ
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

    name = name +"row_i"; //ÕâÀïÃû×ÖÔõÃ´´¦ÀíÃ»ÏëºÃ
    matrix_store();
    matrix_output();
}




//Ãû³Æ£ºmatrix_intercept_col½ØÈ¡ÁĞº¯Êı
//¹¦ÄÜ£º½ØÈ¡c1µ½c2ĞĞµÄ¾ØÕó²¢´æ´¢
//²ÎÊı: c1,c2:c1µ½c2ÁĞ
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


//åç§°ï¼šmatrix_intercept_dia æˆªå–å¯¹è§’å‡½æ•°
//åŠŸèƒ½ï¼šæˆªå–dä»¥ä¸Šçš„æ•°æ®ï¼Œå…¶ä½™ä»¥é›¶è¡¥å……
//å‚æ•°ï¼šd ï¼šå¯¹è§’çº¿ ï¼ˆè§„å®šä¸»å¯¹è§’çº¿ä¸º0ï¼Œå‘ä¸Šä¸ºæ­£ï¼Œå‘ä¸‹ä¸ºè´Ÿï¼‰
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
