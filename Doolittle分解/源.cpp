#include<iostream>

using namespace std;
void LU_decom(double **a, double *b, int n)
{
	//L[30][30]、u[30][30]分别记录单位下三角，上三角矩阵
	//max：消元时，列绝对值最大数，m为最大数所在行
	//t为临时变量，在换行中使用，m记录最大行时使用
	//sum:求解LU的列、行时使用

	int i, j, k, r, m;
	double max, t, sum;
	double L[30][30], u[30][30], x[30];
	for (k = 0; k <n; k++)//此处k<n
	{
		//列主元(主对角线上出现0时，可调用此函数)
		max = a[k][k];
		for (i = k + 1; i < n; i++)
		{
			for (i = k + 1; i < n; i++)
			{
				if (fabs(a[i][k]) > fabs(max))
				{
					max = a[i][k];
					m = i;
				}

			}
		}
		//行交换及LU分解
		if (fabs(max) < 1e-8) cout << "这是奇异矩阵" << endl;//此处应该跳出LU 分解
		else
		{
			/*
			for (j = 0; j < n; j++)
			{
			t = a[m][j];
			a[m][j] = a[k][j];
			a[k][j] = t;
			}
			*/

			//求解U的k行，L的k列
			for (i = 0; i < n; i++)
			{
				sum = 0;
				for (j = 0; j < k; j++)
					sum += L[k][j] * u[j][i];
				u[k][i] = a[k][i] - sum;
			}
			for (i = 0; i < n; i++)
			{
				sum = 0;
				for (j = 0; j < k; j++)
					sum += L[i][j] * u[j][k];
				L[i][k] = (a[i][k] - sum) / u[k][k];
			}
		}
	}

	//输出矩阵L
	for (i = 0; i < 3; i++)
	{

		for (j = 0; j < 3; j++)
			cout << L[i][j] << " , ";
		cout << endl;
	}
	//输出矩阵U
	for (i = 0; i < 3; i++)
	{

		for (j = 0; j < 3; j++)
			cout << u[i][j] << " , ";
		cout << endl;
	}

	//回代，求解Y
	for (k = 0; k < n; k++)
	{
		if (fabs(a[k][k]) < 1e-6)cout << "这是奇异矩阵" << endl;
		else
		{
			sum = 0;
			x[k] = b[k];
			for (i = 0; i < k; i++)
				sum += L[k][i] * x[i];
			x[k] = b[k] - sum;
		}
	}
	//回代，求解X
	for (k = n - 1; k >= 0; k--) //k>0
	{
		if (fabs(u[k][k]) < 1e-6)cout << "这是奇异矩阵" << endl;
		else
		{
			sum = 0;
			for (i = k + 1; i < n; i++)
				sum += u[k][i] * b[i];
			b[k] = (x[k] - sum) / u[k][k];
		}
	}

	//输出矩阵的解
	cout << "矩阵的解为：" << endl;
	for (j = 0; j < 3; j++)
		cout << b[j] << " , ";


}



int main()
{
	int n = 3;
	int i, j;
	double **A = NULL;
	double *B = NULL;
	A = new double *[n];             //为*A申请n行
	for (int i = 0; i < n; i++)       //为**A申请n列  
		A[i] = new double[n];
	B = new double[n];

	cout << "(Doolittle分解法解线性方程) " << endl;
	cout << "请输入系数矩阵A，以空格分隔:" << endl;

	/*输入矩阵A[][]*/
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			cin >> A[i][j];
	}

	cout << "请输入矩阵B，以空格分隔:" << endl;
	for (i = 0; i < n; i++)
		cin >> B[i];

	/*调用Doolittle分解法求解*/
	LU_decom(A, B, 3);
	system("pause");
	return 0;
}

