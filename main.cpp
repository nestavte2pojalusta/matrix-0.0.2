#include"stdafx.h"
#include<iostream>
#include<sstream>
#include<string>

using namespace std;

bool read_numb_elements(unsigned int &str, unsigned int &col)
{
	string razmer;
	char op; bool sucsses = true;
	unsigned int str_t, col_t;
	getline(cin, razmer);
	istringstream stream(razmer);
	if (stream >> str_t && stream >> op && op == ',' && stream >> col_t) {
		str = str_t;
		col = col_t;

		return true;;
	}

	return false;
}

bool read(double **matrix, unsigned int str, unsigned  int col)
{
	int read_matrix_numb = 0;
	for (unsigned int i = 0; i < str; i++)
	{
		string row;
		getline(cin, row);
		istringstream stream(row);
		for (unsigned int j = 0; j < col; j++)
		{
			if (stream >> matrix[i][j]) { read_matrix_numb++; }
		}
	}
	if (read_matrix_numb == str * col) return true;
	else return false;
}

void print(double **matrix, unsigned int str, unsigned int col)
{
	for (unsigned int i = 0; i < str; i++)
	{
		cout << endl;
		for (unsigned int j = 0; j < col; j++)
		{
			if (matrix[i][j] == -0.0) { cout << 0 << " "; }
			else { cout << matrix[i][j] << " "; }
		}
	}
}

void del(double ** matrix, unsigned int str)
{
	for (unsigned int i = 0; i < str; i++)
	{
		delete[] matrix[i];
	}
	delete matrix;
}

double** creat(unsigned int str, unsigned int col)
{
	double ** mat3 = new double*[str];
	for (unsigned int i = 0; i < str; i++)
	{
		mat3[i] = new double[col];
	}
	return mat3;
}

void add(double ** &mat3, double ** mat1, double ** mat2, unsigned int str, unsigned int col)
{
	mat3 = new double *[str];

	for (unsigned int i = 0; i < str; i++)
	{
		mat3[i] = new double[col];
		for (unsigned int j = 0; j < col; j++)
		{
			mat3[i][j] = mat1[i][j] + mat2[i][j];
		}
	}
}

void sub(double ** &mat3, double ** mat1, double ** mat2, unsigned int str, unsigned int col)
{
	mat3 = new double *[str];
	for (unsigned int i = 0; i < str; i++)
	{
		mat3[i] = new double[col];
		for (unsigned int j = 0; j < col; j++)
		{
			mat3[i][j] = mat1[i][j] - mat2[i][j];
		}
	}
}

void mul(double ** mat1, double ** mat2, double ** & mat3, unsigned int str, unsigned int col, unsigned int col1)
{
	mat3 = new double *[str];
	for (unsigned int i = 0; i < str; i++)
	{
		mat3[i] = new double[col];
		for (unsigned int j = 0; j < col; j++)
		{
			double res = 0;
			for (unsigned int k = 0; k < col1; k++)
			{
				res += mat1[i][k] * mat2[k][j];
			}
			mat3[i][j] = res;
		}
	}
}

void T(double ** & mat3, double **matrix1, unsigned int col1, unsigned int str1)
{
	mat3 = new double *[col1];
	for (unsigned int i = 0; i < col1; ++i)
	{
		mat3[i] = new double[str1];
		for (unsigned int j = 0; j < str1; ++j)
		{
			mat3[i][j] = matrix1[j][i];
		}
	}
}

void min_matrix(double ** mat, double **n_mat, unsigned int i, unsigned int j, unsigned int N)
{
	unsigned int k = 0; unsigned int  g;
	for (unsigned int i1 = 0; i1<N - 1; i1++)
	{
		if (i1 == i)
		{
			k = 1;
		}
		g = 0;
		for (unsigned int j1 = 0; j1< N - 1; j1++)
		{
			if (j1 == j)
			{
				g = 1;
			}
			n_mat[i1][j1] = mat[i1 + k][j1 + g];
		}
	}
}

double det(double ** mat, unsigned int N)
{
	unsigned int i = 0;
	double deter = 0;
	unsigned int M = N - 1;
	char step = 1;

	double ** n_mat;
	n_mat = new double *[N];
	for (unsigned int i = 0; i < N; i++)
	{
		n_mat[i] = new double[N];
	}

	if (N < 1)
	{
		del(n_mat, N);
		cout << "fail(1x1 matrix ?)";
	}
	if (N == 1)
	{
		deter = mat[0][0];

		return(deter);
	}
	if (N == 2)
	{
		deter = mat[0][0] * mat[1][1] - (mat[1][0] * mat[0][1]);
		del(n_mat, N);
		return(deter);
	}
	if (N>2)
	{
		for (i = 0; i<N; i++)
		{
			min_matrix(mat, n_mat, i, 0, N);
			deter = deter + step * mat[i][0] * det(n_mat, M);
			step = -step;
		}
	}
	del(n_mat, N);
	return(deter);
}

void R(double ** & mat3, double ** matrix1, unsigned int str1, unsigned int col1, bool &print)
{
	mat3 = new double *[str1];
	auto matR = creat(str1, col1);
	double deter = det(matrix1, str1);
	if (deter != 0)
	{
		auto n_mat = creat(str1, col1);
		for (unsigned int i = 0; i < str1; i++)
		{
			mat3[i] = new double[col1];
			for (unsigned int j = 0; j < col1; j++)
			{

				min_matrix(matrix1, n_mat, i, j, str1);
				double d = det(n_mat, (str1 - 1));
				matR[i][j] = d * pow((-1), (i + j)) * (1.0 / deter);
			}
		}
		del(n_mat, str1);
		T(mat3, matR, str1, col1);
		del(matR, str1);
	}
	else
	{
		print = false;
		cout << "fail R , det = 0";
	}
}

int main()
{
	unsigned int str1, col1;
	unsigned int str2, col2;
	double **matrix1 = nullptr;
	bool mat1 = false, mat2 = false;
	double **matrix2 = nullptr;
	char op = 'n';
	if (read_numb_elements(str1, col1))
	{
		matrix1 = creat(str1, col1);
		if (read(matrix1, str1, col1))
		{
			mat1 = true;
			cin >> op;
			cin.get();
		}
		else cout << "fail input";
	}
	if (op == '+' || op == '-' || op == '*')
	{
		if (read_numb_elements(str2, col2))
		{
			matrix2 = creat(str2, col2);
			if (read(matrix2, str2, col2))
			{
				mat2 = true;
			}
			else
			{
				cout << "fail input";
				return 0;
			}
		}
		switch (op)
		{
		case '+':
			if (str1 == str2 && col1 == col2)
			{
				double ** mat3;
				add(mat3, matrix1, matrix2, str1, col1);
				print(mat3, str1, col1);
				del(mat3, str1);
			}
			else
			{
				cout << "fail";
				break;
			}
			break;
		case '-':
			if (str1 == str2 && col1 == col2)
			{
				double ** mat3;
				sub(mat3, matrix1, matrix2, str1, col1);
				print(mat3, str1, col1);
				del(mat3, str1);
			}
			else
			{
				cout << "fail";
				break;
			}
			break;
		case '*':
			if (col1 == str2)
			{
				double ** mat3;
				mul(matrix1, matrix2, mat3, str1, col2, col1);
				print(mat3, str1, col2);
			}
			else
			{
				cout << "fail";
				break;
			}
			break;

		}
	}
	else if (op == 'T')
	{
		double ** mat3;
		T(mat3, matrix1, col1, str1);
		print(mat3, col1, str1);
		del(mat3, col1);

	}
	else if (op == 'R')
	{
		bool print_t = true;
		double ** mat3;
		R(mat3, matrix1, str1, col1, print_t);
		if (print_t)
		{
			print(mat3, str1, col1);
			del(mat3, str1);
		}
	}
	cin.get();
	if (mat1)
	{
		del(matrix1, str1);
	}
	if (mat2)
	{
		del(matrix2, str2);
	}
	return 0;
}
