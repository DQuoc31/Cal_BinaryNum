#include <iostream>
using namespace std;

const int size = 8;

char* Copy(char* a)
{
	char* res = new char[8];
	for (int i = 0; i < 8; i++)
		res[i] = a[i];

	return res;
}

char* GetNegative(char* a)
{
	char* res = new char[8];
	for (int i = 0; i < 8; i++)
		res[i] = a[i];
	if (res[0] == '0')
	{
		for (int i = 0; i < 8; i++)
		{
			if (res[i] == '0')
				res[i] = '1';
			else res[i] = '0';
		}

		for(int i = 7; i >= 0; i--)
			if (res[i] == '0')
			{
				res[i] = '1';
				for (int j = i + 1; j < 8; j++)
					res[j] = '0';
				break;
			}
	}
	else
	{
		for (int i = 7; i >= 0; i--)
			if (res[i] == '1')
			{
				res[i] = '0';
				for (int j = i + 1; j < 8; j++)
					res[j] = '1';
				break;
			}

		for (int i = 0; i < 8; i++)
		{
			if (res[i] == '0')
				res[i] = '1';
			else res[i] = '0';
		}
	}

	return res;
}

char* Plus(char* a, char* b)
{
	char* res = new char[8];
	int carry = 0;
	for (int i = 7; i >= 0; i--)
	{
		res[i] = a[i] + b[i] - '0';
		res[i] += carry;
		carry = 0;
		if (res[i] > '1')
		{
			carry = 1;
			res[i] -= 2;
		}
	}

	if ((a[0] == '0' && b[0] == '0' && res[0] == '1') || (a[0] == '1' && b[0] == '1' && res[0] == '0'))
		return NULL;

	return res;
}

char* Minus(char* a, char* b)
{
	return Plus(a, GetNegative(b));
}

void ShiftRight(char* a)
{
	for (int i = 7; i > 0; i--)
		a[i] = a[i - 1];
	a[0] = '0';
}

void ShiftLeft(char* a)
{
	for (int i = 0; i < 7; i++)
		a[i] = a[i + 1];
	a[7] = '0';
}

char* Multi(char* x, char* y)
{
	char* q = Copy(x);
	char* m = Copy(y);
	char* a = new char[8];
	for (int i = 0; i < 8; i++) a[i] = '0';
	char q1 = '0';

	for (int i = 0; i < 8; i++)
	{
		if (q1 == '0' && q[7] == '1')
			a = Minus(a, m);

		if (q1 == '1' && q[7] == '0')
			a = Plus(a, m);

		q1 = q[7];

		ShiftRight(q);
		q[0] = a[7];

		ShiftRight(a);
		if (a[1] == '1')
			a[0] = '1';
	}

	char* res = new char[16];
	for (int i = 0; i < 16; i++)
		if (i < 8)
			res[i] = a[i];
		else
			res[i] = q[i - 8];

	return res;
}

pair<char*, char*> Divide(char* a, char* b)
{
	bool dau = 0;
	char* Q;
	char* M;
	char* A = new char[8];
	for (int i = 0; i < 8; i++) A[i] = '0';

	if (a[0] != b[0])
		dau = 1;

	if (a[0] == '1')
		Q = GetNegative(a);
	else Q = Copy(a);

	if (b[0] == '1')
		M = GetNegative(b);
	else M = Copy(b);

	for (int i = 0; i < 8; i++)
	{
		ShiftLeft(A);
		A[7] = Q[0];
		ShiftLeft(Q);

		A = Minus(A, M);
		if (A[0] == '1')
			A = Plus(A, M);
		else
			Q[7] = '1';
	}

	if (dau == 1)
	{
		A = GetNegative(A);
		Q = GetNegative(Q);
	}
	cout << dau << ' ';
	return { A, Q };
}

void display(char* a, int n)
{
	if (a == NULL)
		cout << "Ket qua bi tran so";
	else 
		for (int i = 0; i < n; i++)
			cout << a[i];
	cout << '\n';
}

int main()
{
	char* x = new char[8];
	char* y = new char[8];

	cout << "Nhap so nhi phan (8bit, bu 2) X: ";
	for (int i = 0; i < 8; i++)
		cin >> x[i];

	cout << "Nhap so nhi phan (8bit, bu 2) Y: ";
	for (int i = 0; i < 8; i++)
		cin >> y[i];

	char* res = Plus(x, y);
	if (res == NULL)
		cout << "Tong bi tran so\n";
	else
	{
		cout << "Tong 2 so X, Y la: ";
		display(res, 8);
	}

	res = Minus(x, y);
	if (res == NULL)
		cout << "Hieu bi tran so\n";
	else
	{
		cout << "Hieu 2 so X, Y la: ";
		display(res,8);
	}

	res = Multi(x, y);
	cout << "Tich 2 so X, Y la: ";
	display(res,16);

	pair<char*, char*> ans = Divide(x, y);
	cout << "Thuong 2 so X, Y la: ";
	display(ans.second,8);
	cout << "Phan du la: ";
	display(ans.first,8);
}

//01101001
//11001101