#include "road.h"

void Road::Setup() {
	TL.Setup();
}

void Road::Movement() {
	TL.Print();
	int n;
	cout << "Сколько смен цвета светофоров произошло? " << endl;
	cin >> n;
	cout << endl;
	if (n < 0) throw - 1;
	for (int i = 0; i < n; i++) {
		TL.SwitchLights();
		cout << "#" << (i + 1) << endl;
		TL.Print();
	}
}