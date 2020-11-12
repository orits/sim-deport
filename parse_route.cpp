#include "parse_route.h"
#include "nexception.h"
#include <iostream>


unsigned int parse_route::object_count_ = 0; /* initializer static variable to 0 */

/* this function is a private, helper to the c'tor, return true or false. */
bool parse_route::check_valid_name(const string& cs) {
	const auto functor = [](char ch) { return ((!((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A'))) && (!(ch == ' '))); };
	return none_of(cs.begin(), cs.end(), functor);
}

/* default c'tor */
parse_route::parse_route(ifstream& file, const string input_name, bool is_running) : deliver_id_(object_count_++), number_of_sub_deliver_(configure_num_lines(file)) {

	bool error = false;
	auto begin_input = new char[256];
	stringstream err;
	unsigned int line_count = 0;
	int total_quantity = 0;
	is_valid_data_ = true;

	while (file.getline(begin_input, 256, '\n') && line_count < number_of_sub_deliver_ && is_valid_data_) {
		string input_str = begin_input;
		stringstream line_stream(input_str);

		string buf;                 // Have a buffer string
		vector<string> tokens; // Create vector to hold our words

		while (getline(line_stream, buf, ','))
			tokens.push_back(buf);


		string node;
		sim_time arrival_time;
		int case_quantity = 0;
		sim_time departure_time;

		node = move(tokens[i_node]);
		transform(node.begin(), node.end(), node.begin(), ::tolower);
		try {
			if (node.length() > c_max || !check_valid_name(node)) {
				err << "Invalid input_route in file <" << input_name << "> at line <" << line_count << "> .\n";
				error = true;
			}

			if (line_count == 0 && !error) {
				departure_time = sim_time::configure_data_to_time(move(tokens[i_arrival_time]));
				arrival_time = departure_time;
			}

			if (line_count != 0 && !error) {

				stringstream sq(move(tokens[i_case_quantity]));
				sq >> case_quantity;
				if (case_quantity < 0) {
					err << "Invalid input_route in file <" << input_name << "> at line <" << line_count << "> .\n";
					error = true;
				}
				else {
					arrival_time = sim_time::configure_data_to_time(tokens[i_arrival_time]);

					int diff_time = sim_time::difference_by_minute(route_.at(line_count - 1)['d'], arrival_time);
					if (diff_time < 0) {
						err << "Invalid input_route in file <" << input_name << "> at line <" << line_count << "> .\n";
						error = true;
					}

					departure_time = sim_time::configure_data_to_time(tokens[i_departure_time]);
					diff_time = sim_time::difference_by_minute(arrival_time, departure_time);
					if (diff_time < 0) {
						err << "Invalid input_route in file <" << input_name << "> at line <" << line_count << "> .\n";
						error = true;
					}
				}
			}

			if (error) {
				const auto tmp = err.str();
				auto cstr = tmp.c_str();
				throw nexception(cstr);
			}
		}
		catch (const nexception& e) {
			cerr << e.what();
			if (!is_running)
				exit(EXIT_FAILURE);
		}

		route_.push_back(move(input_route(node, arrival_time, case_quantity, departure_time)));
		total_quantity += case_quantity;

		if (error)
			is_valid_data_ = false;
		else
			is_valid_data_ = true;

		line_count++;
		route_[0].set_case_quantity(total_quantity);
	}
}

/* this static function is helper c'tor initializer to the numbers of line in a file, return int. */
int parse_route::configure_num_lines(ifstream & file) {
	// skip when bad
	if (file.bad()) return 0;
	// save state
	std::istream::iostate state_backup = file.rdstate();
	// clear state
	file.clear();
	std::istream::streampos pos_backup = file.tellg();

	file.seekg(0);
	size_t line_cnt;
	size_t lf_cnt = static_cast<size_t>(count(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), '\n'));
	line_cnt = lf_cnt;
	// if the file is not end with '\n' , then line_cnt should plus 1  
	file.unget();
	if (file.get() != '\n') { ++line_cnt; }

	// recover state
	file.clear(); // previous reading may set eofbit
	file.seekg(pos_backup);
	file.setstate(state_backup);

	return line_cnt;
}