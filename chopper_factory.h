#pragma once
#include "vehicle_factory.h"
#include "chopper.h"

class chopper_factory : public vehicle_factory
{
	public:
		explicit chopper_factory(const string& factory_name) : vehicle_factory(factory_name) {}
		chopper* create_vehicle(string vehicle_name, point start_location, float speed) override { return new chopper(vehicle_name, start_location); }
};