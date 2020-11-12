#pragma once
#include "vehicle_factory.h"
#include "trooper.h"

class trooper_factory : public vehicle_factory
{
	public:
		explicit trooper_factory(const string& factory_name) : vehicle_factory(factory_name) { }
		trooper* create_vehicle(string vehicle_name, point start_location, float speed) override { return new trooper(vehicle_name, start_location, speed); }
};