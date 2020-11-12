#include "vehicle.h"


vehicle::~vehicle() {

}

void vehicle::update() {
	point point_diff;

	if (is_cartesian_) {
		const auto radius = location_.distance(position_);
		/* target reached check */
		if (speed_ >= radius) {
			location_ = position_;
			return;
		}

		course_ = atan2((position_.get_y() - location_.get_y()), (position_.get_x() - location_.get_x()));

		if (course_ < 0.0f) 
			course_ = M_PI * 2.0f + course_;
		
		/* new difference for x,y */
		point_diff = point(speed_ * cos(course_), speed_ * sin(course_));

		/* update current x,y */
		location_.move(point_diff);
	}
	else {
		/* polar params */
		point_diff = point((speed_ / 100) * cos(course_), (speed_ / 100) * sin(course_));
		location_.move(point_diff);
	}
}

void vehicle::set_course(const float new_course, const float new_speed) {
	is_cartesian_ = false;
	is_polar_ = true;
	course_ = new_course;

	/* simDepot to standard 2D coordinate system */
	if (new_course >= 0 && new_course <= 90)
		course_ = 90 - new_course;
	else 
		course_ = 360 + 90 - new_course;
	
	course_ = course_* M_PI / 180;
	speed_ = new_speed;
}

vehicle::state vehicle::get_state_by_string(string& state_string) const {
	for (const auto& state : enum_map_ ) {
		if (state.second == state_string)
			return state.first;
	}
	return  enum_map_.end()->first;
}
