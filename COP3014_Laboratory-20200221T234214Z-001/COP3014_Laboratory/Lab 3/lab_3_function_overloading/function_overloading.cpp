//jared branscum
//1/27/17
//lab 3 fucntion overlaoding

#include <iostream>
#include <string>

using namespace std;

void swap(string &a, string &b) {
	string temp = a;
	a = b;
	b = temp;

}

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

void swap(char &a, char &b) {
	char temp = a;
	a = b;
	b = temp;
}



int main(){
	string x = "111", y = "222";
	char r = '1', s = '2';
	int a = 111, b = 222;
	
	cout << "original strings: x = " << x << " y = " << y << endl;
	cout << "original integers: a = " << a << " b = " << b << endl;
	cout << "original characters: r = " << r << " s = " << s << endl;

	swap(x, y);
	swap(r, s);
	swap(a, b);

	cout << "swap with strings: x = " << x << " y = " << y << endl;
	cout << "swap with integers: a = " << a << " b = " << b << endl;
	cout << "swap with characters: r = " << r << " s = " << s << endl;


	return 0;
}