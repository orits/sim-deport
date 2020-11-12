#pragma once
#include "vehicle.h"
#include <vector>
#include "warehouse.h"

class trooper : public vehicle
{
private:
	bool is_come_back_;
	point start_from_;
	string heading_;
	vector<pair<point, string>> patrol_;
	vector<bool> is_visit_patrol_;

	point next_patrol_location();
public:
	explicit trooper(string vehicle_name, point start_location, float speed = max_speed) : vehicle(vehicle_name, start_location, speed), is_come_back_(false), start_from_(start_location), heading_("") { };
	~trooper();

	void update() override;

	void set_patrol(vector<pair<point, string>> patrol) { patrol_ = move(patrol); is_visit_patrol_ = move(vector<bool>(patrol_.size(), false)); heading_ = patrol_.at(0).second; }

	void set_destination(const point&& warehouse_destination) override;

	void set_position(const point&& position);

	void set_course(const float course) override;

	void set_course(const float course, const float speed) override;

	/* this function is print the trooper, didn't return a value. */
	void to_string() const override { cout << "State_trooper "; vehicle::to_string(); cout << "to " << heading_ << ", speed " << get_speed() << " km/h" << endl; }

	string class_name() const override { return "State_trooper"; }

	static string static_class_name() { return "State_trooper"; }

	enum speed { min_speed = 0, max_speed = 90 };

	enum range { range = 10 };
};

