#include "controller.h"
#include "nexception.h"
#include "command.h"
#include "trooper.h"
#include "chopper.h"
#include "truck.h"
#include "parse_route.h"
#include "parse_warehouse.h"

void controller::create_truck(string truck_name ,vector<input_route> route) {
	point initial_location = model::get_instance().get_sim_object_by_name(route.begin()->get_node())->get_location();
	model::get_instance().create_new_vehicle(truck_name, truck::static_class_name(), initial_location);
	auto t_truck = static_pointer_cast<truck>(model::get_instance().get_vehicle_by_name(truck_name));
	
	/* update route */
	t_truck->set_route(route);

	/* update delivery location */
	t_truck->set_warehouses_locations(move(get_warehouse_locations(route)));

	/* update crates */
	model::get_instance().check_crates_load(initial_location, route.begin()->get_case_quantity());
	t_truck->load(route.begin()->get_case_quantity());

	/* update state & movement */
	t_truck->set_state(vehicle::moving_to);
	t_truck->set_move(vehicle::destination);

	/* update */
	t_truck->update();
}

void controller::create_warehouse(vector<input_warehouse> warehouses) {
	for (const auto& w : warehouses) {
		model::get_instance().create_new_warehouse(w.get_node(), w.get_location());
		model::get_instance().get_warehouse_by_point(w.get_location())->inventory_update(w.get_inventory());
	}
}

vector<point> controller::get_warehouse_locations(const vector<input_route>& route) const {
	vector<point> warehouse_locations;
	warehouse_locations.reserve(route.size());
	for(const auto& input : route)
		warehouse_locations.push_back(model::get_instance().get_sim_object_by_name(input.get_node())->get_location());

	return move(warehouse_locations);
}

controller::controller() : view_(make_shared<view>()){
	model::get_instance().attach(view_.get());
}

void controller::read_commands_phrase() {

	do {
		command valid_command(queue_commands_.front());
		string vehicle_name = valid_command.get_token_at_index(0);

		if(model::get_instance().is_vehicle_exist(vehicle_name) && model::get_instance().get_vehicle_by_name(vehicle_name)->get_state() != vehicle::stop_hard) {
			if (valid_command.get_current_comment() == "course") {

				float course = stof(valid_command.get_token_at_index(2));
				float speed;

				if (!valid_command.get_token_at_index(3).empty()) {
					speed = stof(valid_command.get_token_at_index(3));
					model::get_instance().get_vehicle_by_name(vehicle_name)->set_course(course, speed);
				}
				else
				{
					model::get_instance().get_vehicle_by_name(vehicle_name)->set_course(course);
				}

				model::get_instance().get_vehicle_by_name(vehicle_name)->set_move(vehicle::course);
			}

			else if (valid_command.get_current_comment() == "position" || valid_command.get_current_comment() == "destination") {

				float speed;
				point destination_point;

				if (valid_command.get_current_comment() == "position") {
					destination_point = point(stof(valid_command.get_token_at_index(2)), stof(valid_command.get_token_at_index(3)));
					if (!valid_command.get_token_at_index(4).empty())
						speed = stof(valid_command.get_token_at_index(4));
					model::get_instance().get_vehicle_by_name(vehicle_name)->set_move(vehicle::position);
				}
				else {
					string destination = valid_command.get_token_at_index(2);
					destination[0] = tolower(destination[0]);
					destination_point = model::get_instance().get_sim_object_by_name(destination)->get_location();
					if (!valid_command.get_token_at_index(3).empty())
						speed = stof(valid_command.get_token_at_index(3));
					model::get_instance().get_vehicle_by_name(vehicle_name)->set_move(vehicle::destination);
				}

				if (!valid_command.get_token_at_index(3).empty() || !valid_command.get_token_at_index(4).empty()) {
					model::get_instance().get_vehicle_by_name(vehicle_name)->set_speed(speed);
				}

				model::get_instance().get_vehicle_by_name(vehicle_name)->set_destination(move(destination_point));
			}

			else if (valid_command.get_current_comment() == "attack") {

				string target_name = valid_command.get_token_at_index(2);

				point from = model::get_instance().get_sim_object_by_name(vehicle_name)->get_location();
				point to = model::get_instance().get_sim_object_by_name(target_name)->get_location();

				shared_ptr<vehicle> source, target;
				float distance = from.distance(to);
				source = model::get_instance().get_vehicle_by_name(vehicle_name);
				target = model::get_instance().get_vehicle_by_name(target_name);

				shared_ptr<chopper> source_chopper = static_pointer_cast<chopper>(source);
				shared_ptr<truck> target_truck = static_pointer_cast<truck>(target);

				unsigned int range = source_chopper->get_range_attack();
				bool is_tropper_at_range = model::get_instance().is_tropper_at_range(target_truck->get_location());
				bool attack_success = false;

				if (distance <= static_cast<float>(range)) {

					attack_success = source_chopper->attack(is_tropper_at_range);

					if (attack_success)
						target_truck->attacked();
					else {
						// attack failed.
					}
				}
				else
				{
					source_chopper->stop();
					if (!attack_success)
						source_chopper->dec_range();
					else
						source_chopper->inc_range();
				}
			}

			/* stop - hard stop, kill all commend for this vehicle at this current time. */
			else if (valid_command.get_current_comment() == "stop")
				model::get_instance().get_vehicle_by_name(vehicle_name)->hard_stop();
		}
		
		queue_commands_.pop();

	} while (!queue_commands_.empty());

	model::get_instance().return_to_stopped();
}

void controller::run(int argc, char * argv[]) {
	ifstream current_reading_file;
	bool error_reading_file = true;
	vector<vector<input_route>> routes_;
	vector<input_warehouse> warehouses;
	string file_name(argv[1]);

	try {
		if (file_name != "-w")
			throw nexception("\n *** the main arguments not by the format ***\n");
	}
	catch (const nexception& e) {
		cerr << e.what();
		exit(1);
	}

	for (int i = 2; i <= argc - 1; i++) {
		file_name = argv[i];
		if(i == 2) { /* w */
			
			current_reading_file.open(file_name);
			if (!current_reading_file) {
				cerr << "File " << file_name << " not found/open correctly.\n";
			}
			else {
				error_reading_file = false;
				create_warehouse(parse_warehouse(current_reading_file, file_name).get_warehouses());
				current_reading_file.close();
				continue;
			}
		}

		if (file_name == "-t") 
			continue;

		current_reading_file.open(file_name);
		if (!current_reading_file) {
			cerr << "File " << file_name << " not found/open correctly.\n";
		}
		else {
			error_reading_file = false;
			string name = file_name.substr(0, file_name.size() - 4);
			routes_.push_back(parse_route(current_reading_file, name, false).get_route());
			create_truck(name,routes_.back());
			current_reading_file.close();
		}
	}

	if (!error_reading_file)	{
		string input_str;
		while (true) {
			try {
				cout << "Time " << model::get_instance().get_timer() << ": Enter Command: ";
				getline(cin, input_str);
				command command(input_str);

				if (command.numbers_of_arg() == 0 || !command.is_valid()) { /* invalid command exception */
					string invalid_command;
					invalid_command = "Invalid command - ";
					invalid_command += command.get_current_comment();
					throw nexception(invalid_command); 
				}

				string current_command = command.get_current_comment();

				if (current_command == "exit") {
					break;
				}
					

				/* view comments */

				if (current_command == "default")
					view_->reset_to_default();

				else if (current_command == "size")
					view_->set_size(stoi(command.get_token_at_index(1)));

				else if (current_command == "zoom")
					view_->set_scale(stoi(command.get_token_at_index(1)));

				else if (current_command == "pan")
				{
					float x = stof(command.get_token_at_index(1));
					float y = stof(command.get_token_at_index(2));
					view_->set_origin(point(x, y));
				}
					

				else if (current_command == "show")
					view_->draw();

				/* model comments */

				else if (current_command == "status")
					model::get_instance().status();

				else if (current_command == "go") {
					if (!queue_commands_.empty())
						read_commands_phrase();

					model::get_instance().go();
				}

				else if (current_command == "create") {

					const auto vehicle_name = command.get_token_at_index(1);
					const auto vehicle_type = command.get_token_at_index(2);
					string warehouse_name;

					if(model::get_instance().is_vehicle_exist(vehicle_name)) {
						string invalid_command;
						invalid_command = "Invalid command - ";
						invalid_command += command.get_current_comment();
						invalid_command += " vehicle already exists!";
						throw nexception(invalid_command);
					}

					if (vehicle_type  == trooper::static_class_name()) {
						warehouse_name = command.get_token_at_index(3);
						warehouse_name[0] = tolower(warehouse_name[0]);
						if (!model::get_instance().is_warehouse_exists(warehouse_name)) {
							string invalid_command;
							invalid_command = "Invalid command - ";
							invalid_command += command.get_current_comment();
							invalid_command += " warehouse isn't exists!";
							throw nexception(invalid_command);
						}
					}
						

					/* create new trooper */
					if (vehicle_type == trooper::static_class_name())
						model::get_instance().create_new_vehicle(vehicle_name, vehicle_type, warehouse_name);

					/* create new chopper */
					else if (vehicle_type == chopper::static_class_name()) {
						point point(stof(command.get_token_at_index(3)), stof(command.get_token_at_index(4)));
						model::get_instance().create_new_vehicle(vehicle_name, vehicle_type, point);
					}
				}

				else
					queue_commands_.push(command);
			}
			catch (const nexception& e) {
				cout << e.what() << endl;
			}
		}
	}
	else
		cerr << "ERROR, None of your files are valid!" << endl;
}
