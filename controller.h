#pragma once
#include "model.h"
#include <queue>
#include "command.h"
#include "input_warehouse.h"

class controller
{
	private:
		shared_ptr<view> view_;
		queue<command> queue_commands_;

		void create_truck(string truck_name, vector<input_route> route);
		void create_warehouse(vector<input_warehouse> warehouses);
		vector<point> get_warehouse_locations(const vector<input_route>& route) const;
	public:
		controller();
		~controller() = default;

		void read_commands_phrase();
		void run(int argc, char* argv[]);
};

