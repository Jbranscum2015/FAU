#include <vector>
#include <iostream>
using namespace std;

class coordinate
{
public:
	double x, y;
};

int main()
{
	vector<coordinate> moves;
	coordinate C;

	for (unsigned int i = 0; i<10; i++)
	{
		C.x = i * 2.386;
		C.y = i * 4.87;
		moves.push_back(C);
	}

	for (unsigned int j = 0; j<moves.size(); j++)
	{
		cout << "Coordinate in cell  " << j << moves[j].x << ", " << moves[j].y << endl;
	}

	moves.clear();

	return 0;

}
