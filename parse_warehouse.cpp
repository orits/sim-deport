#include "parse_warehouse.h"
#include "nexception.h"
#include <iostream>


unsigned int parse_warehouse::object_count_ = 0; /* initializer static variable to 0 */

/* this function is a private, helper to the c'tor, return true or false. */
bool parse_warehouse::check_valid_name(const string& cs) {
	const auto functor = [](char ch) { return ((!((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A'))) && (!(ch == ' '))); };
	return none_of(cs.begin(), cs.end(), functor);
}

/* default c'tor */
parse_warehouse::parse_warehouse(ifstream& file, const string input_name) : number_of_lines_(configure_num_lines(file))
{
	bool error = false;
	auto begin_input = new char[256];
	stringstream err;
	unsigned int line_count = 0;
	is_valid_data_ = true;

	while (file.getline(begin_input, 256, '\n') && line_count < number_of_lines_ && is_valid_data_) {
		string input_str = begin_input;
		replace(input_str.begin(), input_str.end(), '(', ' ');
		replace(input_str.begin(), input_str.end(), ')', ' ');
		stringstream line_stream(input_str);

		string buf;                 // Have a buffer string
		vector<string> tokens; // Create vector to hold our words

		while (getline(line_stream, buf, ','))
			tokens.push_back(buf);


		string node;			/* represent the node name */
		point location;		/* represent the location */
		unsigned int inventory;

		node = move(tokens[i_node]);
		transform(node.begin(), node.end(), node.begin(), ::tolower);
		try {
			if (node.length() > c_max || !check_valid_name(node)) {
				err << "Invalid warehouses in file <" << input_name << "> at line <" << line_count << "> .\n";
				error = true;
			}

			if (!error) {
				float x, y;
				stringstream sq1(move(tokens[i_location_x]));
				sq1 >> x;

				stringstream sq2(move(tokens[i_location_y]));
				sq2 >> y;

				location = point(x, y);

				stringstream sq3(move(tokens[i_inventory]));
				sq3 >> inventory;
			}

			if (error) {
				const auto tmp = err.str();
				auto cstr = tmp.c_str();
				throw nexception(cstr);
			}
		}
		catch (const nexception& e) {
			cerr << e.what();
			exit(EXIT_FAILURE);
		}

		warehouses_.push_back(move(input_warehouse(node, location, inventory)));

		if (error)
			is_valid_data_ = false;
		else
			is_valid_data_ = true;

		line_count++;
	}
}

	


/* this static function is helper c'tor initializer to the numbers of line in a file, return int. */
int parse_warehouse::configure_num_lines(ifstream & file) {
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