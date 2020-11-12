#pragma once
#include "vehicle.h"

class vehicle_factory
{
	private:
		string factory_name_;
	
	public:
		vehicle_factory(const string& factory_name) : factory_name_(move(factory_name)) {}
		virtual ~vehicle_factory() = default;
		string get_factory_name() const { return factory_name_; }
		virtual vehicle* create_vehicle(string vehicle_name, point start_location, float speed) = 0;
		

		
};