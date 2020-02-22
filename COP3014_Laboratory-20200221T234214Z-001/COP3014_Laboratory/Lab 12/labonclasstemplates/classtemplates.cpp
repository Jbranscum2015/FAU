#include <iostream>
#include <string>

using namespace std;

const int SIZE = 5;

class test {
public:
	int x;
};

/*********************************************************************/
// Class declaraton for Array_Class
/*********************************************************************/

template <class New_Type>
class Array_Class
{
public:
	Array_Class();
	~Array_Class();
	void Add(New_Type item);
	int Search(New_Type item);
	void Remove(New_Type item);
	bool Is_Full();
	bool Is_Empty();
	void Print();
private:
	New_Type *A;
	int count;
};

/*********************************************************************/
// Class definitions for the member function of Array_Class
/*********************************************************************/

template <class New_Type>
Array_Class<New_Type>::Array_Class()
{
	cout << "You are inside the default constructor\n";
	cout << "New_Type has a size of " << sizeof(New_Type) << " bytes\n\n";
	count = 0;
	A = new New_Type[SIZE];
}

template <class New_Type>
Array_Class<New_Type>::~Array_Class()
{
	cout << "The Destructor has been called\n\n";
	delete[] A;
	count = 0;
	A = 0;
}

template <class New_Type>
void Array_Class<New_Type>::Add(New_Type item)
{
	if (count<SIZE)
	{
		A[count++] = item;
	}
	else
	{
		cout << "Array is Full\n";
	}
}


template <class New_Type>
int Array_Class<New_Type>::Search(New_Type item)
{
	int i;

	for (i = 0; i<count; i++)
	{
		if (item == A[i])
		{
			return i;
		}
	}
	return -1;
}

template <class New_Type>
void Array_Class<New_Type>::Print()
{
	int i;

	for (i = 0; i<count; i++)
	{
		cout << "A[i" << i << "] = " << A[i] << endl;
	}
}
template <class New_Type>
void Array_Class<New_Type>::Remove(New_Type item) {
	int loc;
	loc = Search(item);
	//if target is not in the list
	if (loc != -1)
	{
		for (int i = 0; i < count; i++) {
			loc = Search(item);
			if (loc != -1) {
				for (int i = loc; i < count-1; i++) {
					A[i] = A[i + 1];
				}
				//decrements count
				count--;
			}
		}
	}
}

template <class New_Type>
bool Array_Class<New_Type>::Is_Empty() {
	return count == 0;
}



template <class New_Type>
bool Array_Class<New_Type>::Is_Full() {
	return count == SIZE;
}

int main()
{
	int loc;
	Array_Class<string> my_Strings;
	my_Strings.Add("Hello");
	my_Strings.Add("GoodBye");
	my_Strings.Add("ComeHere");
	my_Strings.Add("SayNo");
	my_Strings.Add("SayYes");
	Array_Class<int> my_Ints;
	my_Ints.Add(1);
	my_Ints.Add(2);
	my_Ints.Add(3);
	my_Ints.Add(4);
	my_Ints.Add(5);
	Array_Class<char> my_Chars;
	if (my_Chars.Is_Empty()) {
		my_Chars.Add('a');
		my_Chars.Add('b');
		my_Chars.Add('c');
		my_Chars.Add('d');
		my_Chars.Add('e');
		my_Chars.Add('f');
		my_Chars.Add('g');
	}
	

	if (my_Chars.Is_Full()) {
		cout << endl << "its full" << endl;
	}


	my_Strings.Print();
	my_Strings.Remove("SayYes");
	my_Strings.Print();
	my_Ints.Print();
	my_Chars.Print();


	loc = my_Strings.Search("SayYes");
	cout << endl << loc << endl;
	loc = my_Strings.Search("No");
	cout << endl << loc << endl;

	return 0;
}