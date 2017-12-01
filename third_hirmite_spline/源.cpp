#include <iostream>
using namespace std;

void scanf_data(double ** &a, double ** &temp_a, double *&b, double * &first_order, double &x, int &n);
void calc_input_a(double **a, double **temp_a, const int n);
void calc_input_b(double *b, double **temp_a, double * first_order, const int n);
double * LU_decom(double **a, double *b, const int n);
void calc_insert_value(double **temp_a, double *m, double x, const int n);
void delete_arr(double ** &a, double **& temp_a, double *&first_order, double *&b);

int main()
{
	int n = 4;						//	���ݵĸ���
	double **a = NULL;				//	a : �����Ǿ���
	double  *b = NULL;				//	b : ����
	double **temp_a = NULL;			//	x,f(x) : ����
	double *first_order = NULL;		//	first_order : �̶��߽�����
	double x = 0;					//	�������ֵ
	double *m = NULL;

	//��������
	scanf_data(a, temp_a, b, first_order, x, n);

	//׷�Ϸ���ⷽ����
	m = LU_decom(a, b, n);

	//�����ֵ���
	calc_insert_value(temp_a, m, x, n);

	//�ͷſռ�
	delete_arr(a, temp_a, first_order, b);
	delete[]m;

	getchar();
	getchar();
	return 0;
}

void calc_insert_value(double **temp_a, double *m, double x, const int n)
{
	cout << "\n***********������************\n";

	int i = 0;
	for (i = 0; i < n - 1; i++)
	{
		if (temp_a[0][i] < x && x < temp_a[0][i + 1])
		{
			break;
		}
	}
	if (i == n - 1)
	{
		cout << "sorry , I cann't calculate this value!\n";
		exit(0);
	}
	//cout << " i = "<<i << endl;

	double y1 = temp_a[1][i];
	double y2 = (temp_a[1][i + 1] - temp_a[1][i]) / (temp_a[0][i + 1] - temp_a[0][i]) *(x - temp_a[0][i]);
	double y3 = (m[i + 1] / 6.0 + m[i] / 3.0)*(temp_a[0][i + 1] - temp_a[0][i])*(x - temp_a[0][i]);
	double y4 = (m[i] / 2)*(x - temp_a[0][i])*(x - temp_a[0][i]);
	double y5 = (m[i + 1] - m[i]) / (temp_a[0][i + 1] - temp_a[0][i]) / 6 * pow((x - temp_a[0][i]), 3);

	cout << "ans = " << y1 + y2 - y3 + y4 + y5;
}
void scanf_data(double ** &a, double ** &temp_a, double *&b, double * &first_order, double &x, int &n)
{
	cout << "********��������ֵ�ĸ���:**********\n";
	cin >> n;

	a = new double *[n];
	b = new double[n];
	temp_a = new double *[2];
	first_order = new double[2];

	cout << "\n\n********��������" << n << "��x,Ȼ������" << n << "��f(x):**********\n";
	for (size_t i = 0; i < n; i++)
	{
		a[i] = new double[n];
		if (i < 2)
			temp_a[i] = new double[n];
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> temp_a[i][j];
		}
	}

	cout << "\n\n********�����������߽��һ�׵���ֵ**********\n";
	cin >> first_order[0] >> first_order[1];

	cout << "\n\n********��Ҫ�����x��ֵ**********\n";
	cin >> x;

	//��������ֵ
	calc_input_a(a, temp_a, n);

	//���������Ҷ���
	calc_input_b(b, temp_a, first_order, n);

	//for (int i = 0; i < n ; i++)
	//{
	//	cout <<"\n" <<b[i] << " ";
	//}
	//cout << endl;
}
void  calc_input_a(double **a, double **temp_a, const int n)
{
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			a[i][j] = 0;
		}
	}
	a[0][0] = 2;	 a[0][1] = 1;
	a[n - 1][n - 2] = 1;	 a[n - 1][n - 1] = 2;
	for (size_t i = 1; i < n - 1; i++)
	{
		a[i][i - 1] = (temp_a[0][i] - temp_a[0][i - 1]) / (temp_a[0][i + 1] - temp_a[0][i - 1]);
		a[i][i] = 2;
		a[i][i + 1] = (temp_a[0][i + 1] - temp_a[0][i]) / (temp_a[0][i + 1] - temp_a[0][i - 1]);
	}

	//cout << "---------\n";
	//for (size_t i = 0; i < n; i++)
	//{
	//	for (size_t j = 0; j < n; j++)
	//	{
	//		cout << a[i][j] << " ";
	//	}
	//	cout << endl;
	//}
}

// wait 
void calc_input_b(double *b, double **temp_a, double * first_order, const int n)
{
	double temp_forward = 0;
	double temp_back = (temp_a[1][1] - temp_a[1][0]) / (temp_a[0][1] - temp_a[0][0]);
	b[0] = 6 * (temp_back - first_order[0]) / (temp_a[0][1] - temp_a[0][0]);
	int i = 0;
	for (i = 1; i < n - 1; i++)
	{
		temp_forward = temp_back;
		temp_back = (temp_a[1][i + 1] - temp_a[1][i]) / (temp_a[0][i + 1] - temp_a[0][i]);
		b[i] = 6 * (temp_back - temp_forward) / (temp_a[0][i + 1] - temp_a[0][i - 1]);
	}

	b[i] = 6 * (first_order[1] - temp_back) / (temp_a[0][i] - temp_a[0][i - 1]);

}
double * LU_decom(double **a, double *b, const int n)
{
	double *l = new double[n];
	double *r = new double[n];
	double *f = new double[n];
	// ����LU�ֽ⣻ 
	// lΪL�ĴζԽǣ�L�����Խ�Ϊ1
	// r,f ΪU���ϰ�ǵ�ֵ
	for (int i = 0; i < n; i++)
	{
		for (int j = i - 1; j <= i + 1 && j < n; j++)
		{
			if (j == -1)
				continue;
			if (j == i + 1)
				f[i] = a[i][j];
			else if (j == i)
				if (i == 0)
					r[i] = a[i][i];
				else
					r[i] = a[i][i] - l[i] * f[i - 1];
			else
				l[i] = a[i][j] / r[i - 1];

		}
	}

	// x,y 
	double *y = new double[n];
	double *x = new double[n];

	for (int i = 0; i < n; i++)
		if (i == 0)
			y[i] = b[i];
		else
			y[i] = b[i] - l[i] * y[i - 1];

	for (int i = n - 1; i > -1; i--)
		if (i == n - 1)
			x[i] = y[i] / r[i];
		else
			x[i] = (y[i] - f[i] * x[i + 1]) / r[i];


	delete[] l;
	delete[] r;
	delete[] f;
	delete[] y;
	return x;
}

void delete_arr(double ** &a, double **& temp_a, double *&first_order, double *&b)
{
	delete[]a;
	delete[]b;
	delete[]temp_a;
	delete[]first_order;
}