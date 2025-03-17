#include <iostream>
using namespace std;

char* toBin(unsigned int x){
	char* a = new char[32];
	int i = 31;

	while (x > 0){
		if (x % 2 == 1)
			a[i] = '1';
		else a[i] = '0';
		i--;
		x /= 2;
	}

	while (i >= 0){
		a[i] = '0';
		i--;
	}
	return a;
}

unsigned int toDec(char* a){
	unsigned int ans = 0;
	for (int i = 0; i < 32; i++)
	{
		ans *= 2;
		ans += a[i] - '0';
	}
	return ans;
}

void displayBin(char*& a){
	for (int i = 0; i < 32; i++){
		cout << a[i];
		if (i % 8 == 7)
			cout << ' ';
	}
	cout << '\n';
}

int main(){

	unsigned int x;
	cout << "Nhap so nguyen x: ";
	cin >> x;
	char* ans = toBin(x);
	displayBin(ans);

	char* y = new char[32];
	cout << "Nhap day nhi phan y: ";
	for (int i = 0; i < 32; i++)
		cin >> y[i];
	cout << toDec(y);
}

//11111111111111111111111111111111
