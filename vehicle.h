#pragma once
#define _USE_MATH_DEFINES
#include <string>
#include <iostream>
#include <cmath>
#include "sim_object.h"
#include "traek_base.h"
#include <map>

class vehicle : public sim_object, private traek_base
{
	public: enum state { stopped = 0, parked = 1, off_road = 2, moving_to = 3, stop_hard = 4 ,invalid_state = 5 };
			enum movement { course = 0, position = 1, destination = 2, movement_default = 3 };
	private:

		state current_state_;
		movement current_movement_;
		map<state, string> enum_map_ = { {stopped, "Stopped"}, {parked, "Parked"}, {off_road, "Off road"}, {moving_to, "Moving"}, {stop_hard, "Stopped"} };
		map<string, state> enum_map_flip_ = { {"Stopped", stopped}, {"Parked", parked}, {"Off road", off_road}, {"Moving", moving_to} };
	
	public:
		explicit vehicle(string vehicle_name, const point& start_location, float speed) : sim_object(move(vehicle_name), start_location), traek_base(), current_state_(stopped), current_movement_(movement_default){ }
		vehicle(const vehicle& other) = delete;
		vehicle(vehicle&& other) = delete;
		virtual ~vehicle() = 0;

		vehicle& operator= (const vehicle& other) = delete;
		vehicle& operator= (const vehicle&& other) = delete;


		virtual  void update() override;
		virtual void stop() { current_state_ = stopped; current_movement_ = movement_default; course_ = traek_default; speed_ = traek_default, position_ = traek_default; }
		virtual void hard_stop() { current_state_ = stop_hard; current_movement_ = movement_default; course_ = traek_default; speed_ = traek_default, position_ = traek_default; }
		bool has_reached_destination() const { return  position_ == location_; }
		
		virtual void set_destination(const point&& new_destination) { current_state_ = moving_to; current_movement_ = destination; is_cartesian_ = true; is_polar_ = false; position_ = new_destination; }
		virtual void set_course(const float new_course) { current_state_ = moving_to; current_movement_ = position; is_cartesian_ = false; is_polar_ = true;  course_ = new_course; }
		virtual void set_course(const float new_course, const float new_speed);
		void set_speed(const float speed) { speed_ = speed; }
		state get_state_by_string(string& state_string) const;
		
		float get_course() const override { return traek_base::get_course(); }
		float get_speed() const override { return traek_base::get_speed(); }
		point get_position() const override { return traek_base::get_position(); }

		state get_state() const { return current_state_; }
		movement get_movement() const { return current_movement_; }

		void set_state(const state new_state) { current_state_ = new_state; }
		void set_move(const movement new_move) { current_movement_ = new_move; }

		/* this function is print the vehicle, didn't return a value. */
		void to_string() const override { cout << uppercase << name_[0] << nouppercase << name_.substr(1) << " at " << location_ << ", Heading "; };
};

