#include <iostream>

using namespace std;

const int SIZE = 5;

class ARRAY_CLASS
{
public:
	ARRAY_CLASS();//default constructor
	~ARRAY_CLASS(); //destructor
	//ARRAY_CLASS(const ARRAY_CLASS &);//copy constructor
	void Add(int); //mutator
	void Print(); //accessor
	int * Get_Address(); //accessor
	void DeAllocate(); //mutator
private:

	int *A;
	int count;
};

ARRAY_CLASS::ARRAY_CLASS()
{
	cout << "Default constructor has been called\n";
	A = new int[SIZE];
	count = 0;
}

//ARRAY_CLASS::ARRAY_CLASS(const ARRAY_CLASS & Org)
//{
//	cout << "The Copy Constructor has been Called!\n";
//
//	count = Org.count;
//
//	A = new int[SIZE];
//
//	for (int i = 0; i<count; i++)
//	{
//		A[i] = Org.A[i];
//	}
//}



ARRAY_CLASS::~ARRAY_CLASS()
{
	cout << "The Destructor has been Called!\n";
	delete[] A;
	A = 0;
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

void ARRAY_CLASS::DeAllocate()
{
	delete[] A;
	A = 0;
	count = 0;
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

	ARRAY_CLASS A = B;

	cout << "A holds address location = " << A.Get_Address()
		<< " and B holds address location " << B.Get_Address() << endl;

	B.DeAllocate();
	A.Print();

	return 0;

}