#pragma once
#include "point.h"

class traek_base
{
	protected:
		float course_;
		float speed_;
		point position_;
		point destination_;
		bool is_polar_, is_cartesian_;
		enum state { traek_default = 0 };
	public:
		traek_base() : course_(traek_default), speed_(traek_default), position_(traek_default) ,is_polar_(false), is_cartesian_(false){};
		virtual ~traek_base();

		virtual float get_course() const { return course_; }
		virtual float get_speed() const { return speed_; }
		virtual point get_position() const { return position_; }

		static float clac_speed(const float time, const float length_road) { return length_road / time; }
};