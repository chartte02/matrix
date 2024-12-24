#include"matrix.h"

extern vector<matrix> matlist;//��������

//���ƣ������������
//���ܣ�������������������������
//��������������matrix�;��󣬰���ǰ��˳������
matrix matrix::create_argumentation(const matrix&m1,const matrix &m2) {
    matrix temp;
    if(m1.row!=m2.row) {
        cout<<"The numbers of the rows of the two matrixes must be the same"<<endl;
        return temp;
    }
    temp.row=m1.row;
    temp.col=m1.col+m2.col;
    temp.matrix_create(row,col);
    for(int i=0;i<row;i++) {
        for(int j=0;j<m1.col;j++) {
            temp.data[i][j]=m1.data[i][j];
        }
        for(int j=m1.col;j<temp.col;j++) {
            temp.data[i][j]=m2.data[i][j-m1.col];
        }
    }
    return temp;
}


//���ƣ�matrix_modify_data
//���ܣ��޸�i��j��Ԫ��
//������i��j��i��j��
//     data_:�޸ĵ�����ֵ
void matrix::matrix_modify_data(int i,int j,fraction data_) {
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


 //���ƣ�matrix_intercept_row��ȡ�к���
 //���ܣ���ȡ����m�����r1��r2�еľ���
 //������m:�������
 //    r1��r2��r1�е�r2��
matrix matrix::matrix_intercept_row(const matrix&m,int r1,int r2) {
    int r_1=r1-1,r_2=r2-1;
    r_1=r_1<r_2?r_1:r_2;
    matrix temp;
    temp.matrix_create(r2-r1,m.col);
    for(int k=r_1;k<=r_2;k++) {
        for(int t=0;t<col;t++) {
            temp.data[k-r_1][t]=m.data[k][t];
        }
    }
    return temp;
}


 //���ƣ�matrix_intercept_col��ȡ�к���
 //���ܣ���ȡc1��c2�еľ��󲢴洢
 //����: c1,c2:c1��c2��
matrix matrix::matrix_intercept_col(const matrix&m,int c1,int c2) {
    matrix temp;
    int c_1=c1-1,c_2=c2-1;
    c_1=c_1<c_2?c_1:c_2;
    temp.matrix_create(m.row,c2-c1);
    for(int t = 0;t < m.row;t++) {
        for(int k = c_1;k<=c_2;k++) {
            temp.data[t][k-c_1]=m.data[t][k];
        }
    }
    return temp;
}

//���ƣ�matrix_intercept_dia ��ȡ�ԽǺ���
//���ܣ���ȡd���ϵ����ݣ��������㲹��
//������d ���Խ��� ���涨���Խ���Ϊ0������Ϊ��������Ϊ����
matrix matrix::matrix_intercept_dia(const matrix &m,int d) {
    matrix temp;
    temp.matrix_create(m.row,m.col);
    if(d>=0) {
        for(int k=0;k<row;k++) {
            for(int t=d+k;t<col;t++) {
                temp.data[k][t]=m.data[k][t];
            }
        }
    }

    else {
        for(int k=0;k<row;k++) {
            for(int t=(k+d>0?k+d:0);t<col;t++) {
                temp.data[k][t]=m.data[k][t];
            }
        }
    }
    return temp;
}
