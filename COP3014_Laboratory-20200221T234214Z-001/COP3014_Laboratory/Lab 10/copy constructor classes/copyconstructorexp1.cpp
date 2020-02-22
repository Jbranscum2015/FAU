#include <iostream>

using namespace std;

const int SIZE = 5;

class ARRAY_CLASS
{
public:
	ARRAY_CLASS();//default constructor
	void Add(int); //mutator
	void Print(); //accessor
	int * Get_Address(); //accessor
private:

	int *A;
	int count;
};

ARRAY_CLASS::ARRAY_CLASS()
{
	cout << "Default Constructor has been Called!\n";
	A = new int[SIZE];
	count = 0;
}

void ARRAY_CLASS::Add(int item)
{
	if (count<SIZE)
		A[count++] = item;
	else
		cout << "Array Full\n";
}

void ARRAY_CLASS::Print()
{
	for (int i = 0; i<count; i++)
		cout << "A[i] = " << A[i] << endl;
}



int * ARRAY_CLASS::Get_Address()
{
	return A;
}

int main()
{
	ARRAY_CLASS B;

	B.Add(1);
	B.Add(2);
	B.Add(3);
	B.Add(4);
	B.Add(5);
	B.Print();

	cout << endl << endl;

	ARRAY_CLASS A = B;

	A.Print();

	cout << "A holds address location = " << A.Get_Address()
		<< " and B holds address location " << B.Get_Address() << endl;

	return 0;
}
