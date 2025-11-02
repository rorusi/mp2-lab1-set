#include "tset.h"

class TrafficLights {
	int n;
	TSet RedCar, YellowCar, GreenCar;
	TSet RedWalk, GreenWalk;
public:
	TrafficLights(int _n) : RedCar(_n), YellowCar(_n), GreenCar(_n),
		RedWalk(_n), GreenWalk(_n)
	{
		n = _n;
	}
	void Setup();
	void SwitchLights();
	void Print();
};