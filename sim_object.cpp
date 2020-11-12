#include "sim_object.h"





sim_object::~sim_object() {
}

map<sim_object::objects, string> sim_object::create_enum_map_objects() {
	map<objects, string> m = { {warehouse_obj, "Warehouse"}, {truck_obj, "Truck"}, {trooper_obj, "State_trooper"}, {chopper_obj, "Chopper"} };
	return m;
}
