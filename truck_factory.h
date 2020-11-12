#pragma once
#include "vehicle_factory.h"
#include "truck.h"

class truck_factory : public vehicle_factory
{
	public:
		explicit truck_factory(const string& factory_name) : vehicle_factory(factory_name) {}
		truck* create_vehicle(string vehicle_name, point start_location, float speed) override { return new truck(vehicle_name, start_location, speed); }
};
