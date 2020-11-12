#include "chopper.h"


void chopper::update() {
	vehicle::update();
}

bool chopper::attack(const bool is_tropper_at_range) {
	
	stop();
	
	if (!is_tropper_at_range) {
		if(range_attack_ + 1 < max_attack)
			range_attack_++;
		return true;
	}

	if (range_attack_ > 0)
		range_attack_--;

	return false;
}

void chopper::set_course(const float course, const float speed) {
	vehicle::set_course(course);
	set_speed(speed);
}

void chopper::set_position(const point&& position, const float speed) {
	vehicle::set_destination(destination);
	set_speed(speed);
}

void chopper::to_string() const {
	cout << "Chopper "; vehicle::to_string(); cout << "on course " << get_course() << " deg, speed " << get_speed() << "km/h" << endl;
}
