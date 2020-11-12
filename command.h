#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include "sim_object.h"

using namespace std;

constexpr unsigned max_arguments = 6;

class command
{	public:
		enum index { zero = 0, one = 1, two = 2, three = 3, four = 4, five = 5, six = 6 };

	private:
		unsigned int numbers_of_arg_;
		vector<string> tokens_;
		string current_command_;

		bool is_view_command();
		bool is_controller_command();
		bool is_vehicle_command();

		enum size  { min_size = 6, max_size = 30, c_max = 12 };
		

		enum state_view { default_s = 0, show = 1, size = 2, zoom = 3, pan = 4, view = 5 };
		map<state_view, string> enum_map_view = { {default_s, "default"}, {show, "show"}, {size, "size"}, {zoom, "zoom"}, {pan, "pan"}, {view, "view"} };

		enum state_controller { exit = 0, status = 1, go = 2, create = 3 };
		map<state_controller, string> enum_map_controller = { {exit, "exit"}, {status, "status"}, {go, "go"}, {create, "create"} };

		enum state_vehicle { course = 0, position = 1, destination = 2, attack = 3, stop = 4 };
		map<state_vehicle, string> enum_map_vehicle = { {course, "course"}, {position, "position"}, {destination, "destination"}, {attack, "attack"}, {stop, "stop"} };
	public:
		explicit command(string input_str);
		command(const command& other) = default;
		~command() = default;

		string get_current_comment() const { return current_command_; }
		int numbers_of_arg() const { return  numbers_of_arg_; }
		bool is_valid();
		bool is_valid_name(const string& cs);
		bool is_valid_number(const unsigned int index) const
		{
			return all_of(tokens_[index].begin(),tokens_[index].end(),[](char c) { return isdigit(c) || c == '+' || c == '-' || c == '.'; });
			//return find_if(tokens_[index].begin(), tokens_[index].end(), [](char c) { return !isdigit(c); }) == tokens_[index].end();
		}

		/* this function is a accessor to route_, return vector<input_route>. */
		string get_token_at_index(const unsigned int index) const { return (index >= tokens_.capacity()) ? string() : tokens_[index]; }
};