12.17
新增：

新函数：

徐家萌：

	matrix matrix_simplify_1();//化简为行阶梯形矩阵
	void matrix_simplify_2();
	void matrix_simplify_3();
	double matrix_det();//行列式
 
金超：

	void matrix_create_random(int i, int j, double a, double b);//生成函数（随机矩阵）
 
曾卓凡：

	void transpose(); //转置函数（前端） 
	void det();//行列式（前端）
	void output();//输出函数（前端）
	void del();//删除函数
	void clear();//清空函数

 
新功能：

	cout << "delete -- to delete a matrix" << endl;
	cout << "clear -- to clear all matrix" << endl;
	cout << "cal -- to start calculating(+ - * ^ T)" << endl;
	cout << "det -- to calculate the determinant of your matrix " << endl; 

调整：

	将代码模块化：
	头文件matrix.h
	源文件matrix—类定义 manage—矩阵管理 calculate—矩阵计算 create—矩阵生成 main—主函数
	Transpose原函数拆分为两部分（后端与前端，下同）
	Det原函数拆分
 	Simplify_1 返回矩阵而非void
	Display 与 output函数彻底区分
	Calculate函数加入转置运算，优先级，输入方式同幂运算

需求：

	阅读此文档，并且知晓以后修改/查找函数应该分模块来，这样不用一下子传一堆文件
	分数需求（待定）（这个实在不行就曾卓凡来）
	一名专职找bug的组员（待定）（文/徐？ 确定之后可以和曾卓凡详谈）
	Modify模块（金超）（可加入增广矩阵功能？）
	Create模块（随机对角矩阵，上三角矩阵，单位矩阵）（和后两个比算简单的，有意愿者可以练手）
	逆矩阵（待定）
	解线性方程（待定）（这俩不着急）
	Main完善（这个曾卓凡来吧）
