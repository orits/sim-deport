#include "truck.h"


truck::~truck() {
	

}


void truck::update() {
	if (get_state() != stop_hard) {
		if (is_attacked_ && get_state() == moving_to) {
			stop();
			return;
		}
		if (get_state() == moving_to && !is_attacked_)
			if(has_reached_destination() || current_route_index_ == 0)
				set_destination(move(warehouses_to_unload_.at(current_route_index_)));
		
		vehicle::update();
	}
}

void truck::set_destination(const point && warehouse_destination) {
	vehicle::set_destination(move(warehouse_destination));
	update_current_speed();
}

void truck::attacked() {
	set_state(off_road);
	set_move(movement_default);
	is_attacked_ = true;
	crates_ = 0;
}

void truck::unload() {
	const unsigned int crates_unload = route_.at(current_route_index_).get_case_quantity();
	crates_ = (crates_ <= crates_unload) ? 0 : crates_ - crates_unload;
	if (current_route_index_ < route_.size() - 1)
		current_route_index_++;
}


void truck::update_current_speed() {
	const point s = warehouses_to_unload_.at(current_route_index_);
	const point d = warehouses_to_unload_.at(current_route_index_ + 1);

	const float time = sim_time::difference_by_hours(sim_time::difference_by_minute((route_.at(current_route_index_))['d'], route_.at(current_route_index_ + 1)['a']));
	const float  length = d.distance(s);
	current_route_index_++;
	set_speed(length / time);
}

unsigned int truck::clac_next_time() {
	return sim_time::difference_by_minute((*route_.begin())['d'], route_.at(1)['a']);
}



void truck::to_string() const {
	string status_to_string;

	switch (get_state()) {
	case vehicle::moving_to:
		switch (get_movement()) {
			case course:
				status_to_string = "on course";
				break;
			case position:
				status_to_string = "on position";
				break;
			case destination:
				status_to_string = "on destination";
				break;
			default: ;
		}
		break;
	case vehicle::parked:
		status_to_string = "parked at";
		break;
	case stopped:
		status_to_string = "Stopped";
		break;
	default: ;
	}

	cout << "Truck "; vehicle::to_string(); cout << "to " << status_to_string << ", Crates : " << crates_ << endl;
}
