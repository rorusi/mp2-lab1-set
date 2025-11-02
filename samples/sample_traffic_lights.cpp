#include "road.h"
#include <locale.h>

int main() 
{
	setlocale(LC_ALL, "Russian");

	int n;
	cout << "Сколько светофоров на дороге?" << endl;
	cin >> n;
	cout << endl;
	Road road(n);

	road.Setup();
	road.Movement();

	return 0;
}