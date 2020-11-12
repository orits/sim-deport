#pragma once
#include "vehicle.h"

class chopper : public vehicle
{
	private:
		enum range_attack { min_attack = 2, max_attack = 20 };
		
		unsigned int range_attack_;
	public:
		chopper(string vehicle_name, point start_location) : vehicle(move(vehicle_name), move(start_location), min_speed), range_attack_(min_attack) { };
		~chopper() = default;

		void update() override;

		bool attack(bool is_tropper_at_range);

		unsigned int get_range_attack() const { return  range_attack_; }

		void set_course(const float course, const float speed) override;

		void set_position(const point&& position, const float speed);

		void inc_range() { range_attack_++; }

		void dec_range() { range_attack_ = (range_attack_ > min_attack) ? range_attack_- 1 : range_attack_; }

		/* this function is print the chopper, didn't return a value. */
		void to_string() const override;

		string class_name() const override { return "Chopper"; }

		static string static_class_name() { return "Chopper"; }

		enum speed { min_speed = 0, max_speed = 170 };
};