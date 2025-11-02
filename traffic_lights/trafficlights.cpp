#include "trafficlights.h"

void TrafficLights::Setup() {
	for (int i = 0; i < n; i++)
	{
		GreenCar.InsElem(i);
		RedWalk.InsElem(i);
	}
	int r;
	cout << "Сколько автомобильных светофоров горят красным?" << endl;
	cin >> r;
	cout << endl;
	if ((r > n) || (r < 0)) throw - 1;
	for (int i = 0; i < r; i++) {
		int ind;
		cout << "Какой светофор красный (начиная с 0)?" << endl;
		cin >> ind;
		cout << endl;
		if ((ind >= n) || (ind < 0)) throw - 1;
		GreenCar.DelElem(ind);
		RedCar.InsElem(ind);
		RedWalk.DelElem(ind);
		GreenWalk.InsElem(ind);
	}
}

void TrafficLights::SwitchLights() {
	int fl = 2;
	for (int i = 0; i < n; i++) {
		if (GreenCar.IsMember(i)) {
			fl = 1;
			break;
		}
	}
	for (int i = 0; i < n; i++) {
		switch (fl) {
		case 1:
			if (RedCar.IsMember(i))
			{
				RedCar.DelElem(i);
				YellowCar.InsElem(i);
				GreenWalk.DelElem(i);
				RedWalk.InsElem(i);
			}
			else
			{
				GreenCar.DelElem(i);
				RedCar.InsElem(i);
				RedWalk.DelElem(i);
				GreenWalk.InsElem(i);
			}
			break;
		case 2:
			if (YellowCar.IsMember(i)) {
				YellowCar.DelElem(i);
				GreenCar.InsElem(i);
			}
			break;
		}
	}
}
void TrafficLights::Print() {
	cout << "Автомобильные светофоры, которые горят" << endl << "Красным: "
		<< RedCar << "Желтым: " << YellowCar << "Зеленым: " 
		<< GreenCar << endl;
	cout << "Пешеходные светофоры, которые горят" << endl << "Красным: "
		<< RedWalk << "Зеленым: " << GreenWalk << endl;	
}