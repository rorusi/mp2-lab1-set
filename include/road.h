#pragma once

#include "trafficlights.h"

class Road {
	TrafficLights TL;
public:
	Road(int n): TL(n) {}
	void Setup();
	void Movement();
};