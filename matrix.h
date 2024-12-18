//�ļ���matrix.h
#ifndef matrix_h

#define matrix_h
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cstdlib> 
#include <ctime>
#include <iomanip>

using namespace std;

class matrix {
public:
	string name;//���� 
	int No;//��� 
	int row, col;//���� 
	double **data;//Ԫ�ض�ά���� 
    
	matrix(int r = 0, int c = 0) : row(r), col(c) {} // Ĭ�Ϲ��캯��
	matrix(const matrix &other); // �������캯��
	matrix& operator=(const matrix &other); // ���ظ�ֵ�����
	matrix operator+(const matrix& other);// ���ؼӷ������
	matrix operator-(const matrix& other);// ���ؼ��������
	matrix operator*(const matrix& other);// ���س˷������
	matrix operator^(int k);//�����������
	~matrix(); // ��������
	
	void matrix_create(int r = 0, int c = 0);//���ɺ����������
	void matrix_create_1(int order,int i, int j);//���ɺ��������Ⱦ���1��
	void matrix_create_2(int order,int i, double k);//���ɺ��������Ⱦ���2��
	void matrix_create_3(int order,int i, int j, double k);//���ɺ��������Ⱦ���3��
	void matrix_create_random(int i, int j, double a, double b);//���ɺ������������
	
	void matrix_store(); // �洢�������������
	void matrix_input();//���뺯�� ����ά���� 
	void matrix_display(int no_name = 0);//�������������������󣩣�����洢��
	
	matrix matrix_transpose();//ת�þ���
	matrix matrix_simplify_1();//����Ϊ�н����ξ���
	void matrix_simplify_2();
	void matrix_simplify_3();
	double matrix_det();//����ʽ 
	
};

int matrix_search (string na); //���Һ��� �������ַ��ر�ţ�
void transpose(); //ת�ú�����ǰ�ˣ� 
void matrix_calculate();//���㺯����ǰ�ˣ� 
void det();//����ʽ��ǰ�ˣ�
void output();//���������ǰ�ˣ�
void del();//ɾ������
void clear();//��պ���
#endif

