#pragma once
#include <utility>
#include "vehicle.h"
#include "input_route.h"
#include "traek_base.h"
#include <vector>

class truck : public vehicle
{
	private:
		unsigned int crates_;
		unsigned int current_route_index_;
		bool is_attacked_;
		vector<input_route> route_;
		vector<point> warehouses_to_unload_;

	public:
		explicit truck(string vehicle_name, point start_location, float speed) : vehicle(move(vehicle_name), start_location, speed), crates_(0), current_route_index_(0), is_attacked_(false) {};
		~truck();

		void update() override;

		void set_destination(const point&& warehouse_destination) override;

		void stop() override { vehicle::stop(); set_state(off_road); }
		
		void attacked();

		void parked() { set_state(vehicle::parked); }

		void load(const unsigned int crates_load) { crates_ += crates_load; }

		void unload();

		void update_current_speed();

		void set_route(vector<input_route> new_route) { route_ = move(new_route); }

		void set_warehouses_locations(const vector<point> warehouse_location) { warehouses_to_unload_ = warehouse_location; }

		unsigned int get_route_index() const { return current_route_index_; }

		unsigned int clac_next_time();

		//unsigned int clac_next_length_route();

		/* this function is print the truck, didn't return a value. */
		void to_string() const override;

		string class_name() const override { return "Truck"; }

		static string static_class_name() { return "Truck"; }

		enum speed { min_speed = 0 };
};

