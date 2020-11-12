#include "command.h"
#include <locale>


bool command::is_view_command() {
	string& command = tokens_[zero];
	if (command == enum_map_view.at(default_s) && numbers_of_arg_ == one)
		return true;

	if (command == enum_map_view.at(size) && numbers_of_arg_ == two) {
		if (is_valid_number(one)) {
			if (stoi(tokens_[one]) >= min_size && stoi(tokens_[one]) <= max_size)
				return true;
		}
	}

	if (command == enum_map_view.at(zoom) && numbers_of_arg_ == two) {
		if (is_valid_number(one)) {
			if (stoi(tokens_[one]) > 0)
				return true;
		}
	}

	if (command == enum_map_view.at(pan) && numbers_of_arg_ == three) {
		if (is_valid_number(one) && is_valid_number(two))
			return true;
	}

	if (command == enum_map_view.at(show) && numbers_of_arg_ == one)
		return true;

	if (command == enum_map_view.at(view) && numbers_of_arg_ == one)
		return true;

	return false;
}

bool command::is_controller_command() {
	string& command = tokens_[zero];
	string vehicle_name;
	string vehicle;
	if(numbers_of_arg_ >= two)
		vehicle_name = tokens_[one];
	if(numbers_of_arg_ >= three)
		vehicle = tokens_[two];
	

	if (command == enum_map_controller.at(exit) && numbers_of_arg_ == one)
		return true;

	if (command == enum_map_controller.at(status) && numbers_of_arg_ == one)
		return true;

	if (command == enum_map_controller.at(go) && numbers_of_arg_ == one)
		return true;

	if (command == enum_map_controller.at(create) ) {
		if (vehicle == sim_object::create_enum_map_objects().at(sim_object::trooper_obj) && numbers_of_arg_ == four) { /* is create #trooper# */
			if (vehicle_name.length() <= c_max && is_valid_name(vehicle_name))
				return true;
		}
		else if (vehicle == sim_object::create_enum_map_objects().at(sim_object::chopper_obj) && numbers_of_arg_ == five) {  /* is create #chopper# */
			if (is_valid_number(three) && is_valid_number(four))
				return true;
		}
	}

	return false;
}

bool command::is_vehicle_command() {
	string command;
	if (numbers_of_arg_ >= two)
		 command = tokens_[one];

	if (numbers_of_arg_ < two)
		return false;

	if (command == enum_map_vehicle.at(course) && numbers_of_arg_ == four)
		return true;

	if (command == enum_map_vehicle.at(position) && numbers_of_arg_ == five)
		return true;

	if (command == enum_map_vehicle.at(destination) && (numbers_of_arg_ == four || numbers_of_arg_ == three))
		return true;

	if (command == enum_map_vehicle.at(attack) && numbers_of_arg_ == three)
		return true;

	if (command == enum_map_vehicle.at(stop) && numbers_of_arg_ == two)
		return true;

	return false;
}

command::command(string input_str) : numbers_of_arg_(0), current_command_(input_str){
	//input_str.erase(remove(input_str.begin(), input_str.end(), ','), input_str.end());
	replace(input_str.begin(), input_str.end(), ',', ' ');
	replace(input_str.begin(), input_str.end(), '(', ' ');
	replace(input_str.begin(), input_str.end(), ')', ' ');

	stringstream line_stream(input_str);

	string buf;                 // Have a buffer string

	while (getline(line_stream, buf, ' ')) {
		if(buf == "")
			continue;

		tokens_.push_back(buf);
		numbers_of_arg_++;
	}
}

bool command::is_valid() {
	if (is_view_command() || is_controller_command()) {
		current_command_ = tokens_[zero];
		return true;
	}
	if (is_vehicle_command()) {
		current_command_ = tokens_[one];
		return true;
	}
	return false;
}

/* , return true or false. */
bool command::is_valid_name(const string& cs) {
	const auto functor = [](char ch) { return ((!((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A'))) && (!(ch == ' '))); };
	return none_of(cs.begin(), cs.end(), functor);
}