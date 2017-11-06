#include<iostream>

using namespace std;
void LU_decom(double **a, double *b, int n)
{
	//L[30][30]��u[30][30]�ֱ��¼��λ�����ǣ������Ǿ���
	//max����Ԫʱ���о���ֵ�������mΪ�����������
	//tΪ��ʱ�������ڻ�����ʹ�ã�m��¼�����ʱʹ��
	//sum:���LU���С���ʱʹ��

	int i, j, k, r, m;
	double max, t, sum;
	double L[30][30], u[30][30], x[30];
	for (k = 0; k <n; k++)//�˴�k<n
	{
		//����Ԫ(���Խ����ϳ���0ʱ���ɵ��ô˺���)
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
		//�н�����LU�ֽ�
		if (fabs(max) < 1e-8) cout << "�����������" << endl;//�˴�Ӧ������LU �ֽ�
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

			//���U��k�У�L��k��
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

	//�������L
	for (i = 0; i < 3; i++)
	{

		for (j = 0; j < 3; j++)
			cout << L[i][j] << " , ";
		cout << endl;
	}
	//�������U
	for (i = 0; i < 3; i++)
	{

		for (j = 0; j < 3; j++)
			cout << u[i][j] << " , ";
		cout << endl;
	}

	//�ش������Y
	for (k = 0; k < n; k++)
	{
		if (fabs(a[k][k]) < 1e-6)cout << "�����������" << endl;
		else
		{
			sum = 0;
			x[k] = b[k];
			for (i = 0; i < k; i++)
				sum += L[k][i] * x[i];
			x[k] = b[k] - sum;
		}
	}
	//�ش������X
	for (k = n - 1; k >= 0; k--) //k>0
	{
		if (fabs(u[k][k]) < 1e-6)cout << "�����������" << endl;
		else
		{
			sum = 0;
			for (i = k + 1; i < n; i++)
				sum += u[k][i] * b[i];
			b[k] = (x[k] - sum) / u[k][k];
		}
	}

	//�������Ľ�
	cout << "����Ľ�Ϊ��" << endl;
	for (j = 0; j < 3; j++)
		cout << b[j] << " , ";


}



int main()
{
	int n = 3;
	int i, j;
	double **A = NULL;
	double *B = NULL;
	A = new double *[n];             //Ϊ*A����n��
	for (int i = 0; i < n; i++)       //Ϊ**A����n��  
		A[i] = new double[n];
	B = new double[n];

	cout << "(Doolittle�ֽⷨ�����Է���) " << endl;
	cout << "������ϵ������A���Կո�ָ�:" << endl;

	/*�������A[][]*/
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			cin >> A[i][j];
	}

	cout << "���������B���Կո�ָ�:" << endl;
	for (i = 0; i < n; i++)
		cin >> B[i];

	/*����Doolittle�ֽⷨ���*/
	LU_decom(A, B, 3);
	system("pause");
	return 0;
}

