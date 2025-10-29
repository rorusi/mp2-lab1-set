#include <iostream>
#include <locale.h>
#include "tset.h"

using namespace std;

class Road {
	int n;
	TSet Red, Yellow, Green;
public:
	Road::Road(int _n) : Red(_n), Yellow(_n), Green(_n)
	{
		n = _n;
	}
	int Road::GetAmount()
	{
		return n;
	}
	void Road::Setup()
	{
		int reds;
		cout << "Сколько светофоров горят красным?" << endl;
		cin >> reds;
		cout << endl;
		if ((reds > n)||(reds < 0)) throw - 1;

		for (int i = 0; i < n; i++) Green.InsElem(i);

		for (int i = 0; i < reds; i++)
		{
			int number;
			cout << "Какой светофор горит красным? (Начиная с 0)" << endl;
			cin >> number;
			cout << endl;
			if ((number > n)||(number < 0)) throw - 1;

			Red.InsElem(number);
			Green.DelElem(number);
		}
	}
	void Road::SwitchColour()
	{
		for (int i = 0; i < n; i++)
		{
			if (Red.IsMember(i))
			{
				Red.DelElem(i);
				Yellow.InsElem(i);
			}
			else
				if (Yellow.IsMember(i))
				{
					Yellow.DelElem(i);
					Green.InsElem(i);
				}
				else
					if (Green.IsMember(i))
					{
						Green.DelElem(i);
						Red.InsElem(i);
					}
		}
	}
	void Road::Print()
	{
		cout << "Светофоры, горящие красным: " << Red << endl;
		cout << "Светофоры, горящие желтым: " << Yellow << endl;
		cout << "Светофоры, горящие зеленым: " << Green << endl;
	}
};

int main() 
{
	setlocale(LC_ALL, "Russian");

	int n;
	cout << "Сколько светофоров на дороге?" << endl;
	cin >> n;
	cout << endl;
	Road road(n);

	road.Setup();
	road.Print();

	int c;
	cout << "Сколько раз переключится цвет светофоров?" << endl;
	cin >> c;
	cout << endl;
	for (int i = 0; i < c; i++)
	{
		cout << endl;
		road.SwitchColour();
		road.Print();
		cout << endl;
	}

	return 0;
}