#include "trooper.h"


point trooper::next_patrol_location() {
	bool is_visited = false;
	int min_index = 0;
	float length = 0;
	string name;

	for(int unsigned i = 1; i < patrol_.size(); i++)	{
		if(!is_visit_patrol_[i])	{
			is_visited = true;
			if (i == 1) {
				length = abs(location_.distance(patrol_[i].first));
				name = patrol_[i].second;
				min_index = i;
				continue;
			}
			auto temp_location = abs(location_.distance(patrol_[i].first));
			if (length > temp_location || (length == temp_location && name > patrol_[i].second)) {
				length = temp_location;
				name = patrol_[i].second;
				min_index = i;
			}
		}
	}

	if(is_visited)	{
		is_visit_patrol_[min_index] = true;
		heading_ = patrol_[min_index].second;
		return patrol_[min_index].first;
	}

	is_come_back_ = true;
	return start_from_;
}

trooper::~trooper() {

}

void trooper::update() {
	if(get_state() != stop_hard){
		if (is_come_back_ && get_movement() == destination) {
			stop();
			return;
		}
		if (get_movement() == destination && !is_come_back_)
			set_destination(next_patrol_location());

		vehicle::update();
	}
}

void trooper::set_destination(const point&& warehouse_destination) {
	vehicle::set_destination(move(warehouse_destination));
	set_speed(max_speed);
}

void trooper::set_position(const point&& position) {
	vehicle::set_destination(move(position));
}

void trooper::set_course(const float course) {
	vehicle::set_course(course);
}

void trooper::set_course(const float course, const float speed) {

}
