#pragma once
#include <fstream>  
#include <numeric>
#include <iterator>
#include "input_route.h"
#include <vector>

using namespace std;
/**
 * this object represent parse_route data that relevant to the 'Hoogie Boogie'.
 *  not allowed - copy c'tor, copy assignment, move c'tor, move assignment.
 */

class parse_route
{
private:
	const unsigned int deliver_id_; /* represent the deliver id */
	const unsigned int number_of_sub_deliver_;  /* represent the sub deliver count */
	vector<input_route> route_;  /* represent the result after parse_route the data */
	bool is_valid_data_; /* represent if the data is valid */

	static unsigned int object_count_; /* counter all the c'tor that create */

	/* represent the number of character warehouse can be. */
	enum character { c_max = 12 };

	/* this enum is for order at the route indexs */
	enum input_index { i_node = 0, i_arrival_time = 1, i_case_quantity = 2, i_departure_time = 3 }; /* represent the iteration of simulation max value can be. */

	/* this function is a private, helper to the c'tor, return true or false. */
	bool check_valid_name(const string& cs);

public:

	explicit parse_route(ifstream& file, const string input_name, bool is_running); /* default c'tor */
	parse_route(const parse_route& other) = delete; /* delete copy c'tor */
	parse_route(parse_route&&) = delete; /* delete move c'tor */
	~parse_route() = default; /* d'tor */

	parse_route& operator=(parse_route&) = delete; /* delete copy assignment */
	parse_route& operator=(parse_route&&) = delete; /* delete move assignment */

	/* this function is a accessor to route_, return vector<input_route>. */
	vector<input_route> get_route() const { return route_; }

	/* this function is a accessor to is_valid_data_, return true or false. */
	bool get_is_valid_data() const { return  is_valid_data_; }

	/* this static function is helper c'tor initializer to the numbers of line in a file, return int. */
	static int configure_num_lines(ifstream& file);
};

