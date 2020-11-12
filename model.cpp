#include "model.h"
#include "trooper.h"
#include "chopper.h"
#include "truck.h"
#include "trooper_factory.h"
#include "chopper_factory.h"
#include "truck_factory.h"

model* model::instance_ = nullptr;

model::model() : timer_(0) {
	vehicle_factories_list_.push_back(shared_ptr<vehicle_factory>(new trooper_factory(trooper::static_class_name())));
	vehicle_factories_list_.push_back(shared_ptr<vehicle_factory>(new chopper_factory(chopper::static_class_name())));
	vehicle_factories_list_.push_back(shared_ptr<vehicle_factory>(new truck_factory(truck::static_class_name())));
	warehouse_list_.push_back(shared_ptr<warehouse>(new warehouse("frankfurt", point(40, 10))));
	sim_object_list_.push_back(shared_ptr<sim_object>(warehouse_list_.back().get()));
	warehouse_list_.back()->inventory_update(100000);
}

bool model::is_vehicle_exist(const string& vehicle_name) const {
	for (const auto& v : vehicle_list_) {
		if (v->get_name() == vehicle_name)
			return true;
	}
	return false;
}

bool model::is_warehouse_exists(const string & warehouse_name) const {
	for (const auto& w : warehouse_list_) {
		if (w->get_name() == warehouse_name)
			return true;
	}
	return false;
}

model& model::get_instance() {
	if (instance_ == nullptr)
		instance_ = new model();

	return  *instance_;
}

void model::go() {
	shared_ptr<truck> t_truck;

	for (const auto& vehicle : vehicle_list_) {
		/* if vehicle is truck */
		if (vehicle->class_name() == truck::static_class_name()) {
			t_truck = static_pointer_cast<truck>(vehicle);
			if (t_truck->get_state() != vehicle::off_road) {
				t_truck->update();
				if (t_truck->has_reached_destination()) {
					t_truck->parked();
					t_truck->unload();
				}
			}
		}

		/* if vehicle is trooper or chopper */
		else
			vehicle->update();
	}

	++timer_;
}

void model::create_new_vehicle(string vehicle_name, string type_of_vehicle, string warehouse_name) { /* create new trooper */
	for (const auto& warehouse : warehouse_list_) {
		if (warehouse->get_name() == warehouse_name) {
			for (const auto& factory : vehicle_factories_list_) {
				if (factory->get_factory_name() == type_of_vehicle) {
					vehicle_list_.push_back(shared_ptr<vehicle>(factory->create_vehicle(vehicle_name, warehouse->get_location(), trooper::max_speed)));
					static_pointer_cast<trooper>(vehicle_list_.back())->set_patrol(move(get_warehouse_locations()));
					sim_object_list_.push_back(shared_ptr<sim_object>(vehicle_list_.back().get()));
					return;
				}
			}
		}
	}



}

void model::create_new_vehicle(string vehicle_name, string type_of_vehicle, point& initial_location) { /* create new truck/chopper */
	for (const auto& factory : vehicle_factories_list_) {
		if (factory->get_factory_name() == type_of_vehicle) {
			if (type_of_vehicle == chopper::static_class_name())
				vehicle_list_.push_back(shared_ptr<vehicle>(factory->create_vehicle(vehicle_name, initial_location, chopper::min_speed)));
			else if (type_of_vehicle == truck::static_class_name())
				vehicle_list_.push_back(shared_ptr<vehicle>(factory->create_vehicle(vehicle_name, initial_location, truck::min_speed)));

			sim_object_list_.push_back(shared_ptr<sim_object>(vehicle_list_.back().get()));
			break;
		}
	}
}

void model::create_new_warehouse(const string & name, const point location) {
	warehouse_list_.push_back(make_shared<warehouse>(name, location));
	sim_object_list_.push_back(shared_ptr<sim_object>(warehouse_list_.back().get()));
}

bool model::check_crates_load(point location, int crates_load) {
	crates_load *= -1;
	for (const auto& w : warehouse_list_) {
		if (w->get_location() == location) {
			w->inventory_update(crates_load);
			return true;
		}
	}
	return false;
}

void model::status() const {
	list<shared_ptr<sim_object>>::const_iterator it;
	for (it = sim_object_list_.begin(); it != sim_object_list_.end(); ++it)
	{
		(*it)->to_string();
	}
}

void model::return_to_stopped() {
	for (const auto& vehicle : vehicle_list_) {
		if (vehicle->get_state() == vehicle::stop_hard) {
			vehicle->stop();
		}
	}
}

bool model::is_tropper_at_range(const point current_location) const {
	for (const auto& vehicle : vehicle_list_) {
		if (vehicle->class_name() == "Trooper" && abs(current_location.distance(vehicle->get_location())) <= trooper::range)
			return true;
	}
	return false;
}

void model::attach(observer* new_observer) {
	view_list_.push_back(shared_ptr<observer>(new_observer));
}

void model::detach(observer* old_observer) {
	view_list_.remove(shared_ptr<observer>(old_observer));
}

void model::notify() {
	auto iterator = view_list_.begin();

	while (iterator != view_list_.end()) {
		(*iterator)->update();
		++iterator;
	}
}

string model::sim_object_at_point(const point& x_point, const point& y_point) const {
	for (const auto& obj : sim_object_list_) {
		if (obj->get_location().is_at_rang(x_point, y_point))
			return obj->get_name();
	}
	return string();
}

shared_ptr<warehouse> model::get_warehouse_by_point(const point point) const {
	for (const auto& warehouse : warehouse_list_) {
		if (warehouse->get_location() == point)
			return warehouse;
	}
	return nullptr;
}


shared_ptr<vehicle> model::get_vehicle_by_name(string vehicle_name) const {
	for (const auto& vehicle : vehicle_list_) {
		if (vehicle->get_name() == vehicle_name)
			return vehicle;
	}
	return nullptr;
}

shared_ptr<sim_object> model::get_sim_object_by_name(string object_name) const {
	
	for (const auto& obj : sim_object_list_) {
		if (obj->get_name() == object_name)
			return obj;
	}
	return nullptr;
}

vector<pair<point, string>> model::get_warehouse_locations() const {
	vector<pair<point, string>> warehouse_locations;
	warehouse_locations.reserve(warehouse_list_.size());
	for (const auto& warehouse : warehouse_list_)
		warehouse_locations.push_back(make_pair(warehouse->get_location(), warehouse->get_name()));

	return move(warehouse_locations);
}
