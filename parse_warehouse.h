#pragma once
#include <fstream>  
#include <numeric>
#include <iterator>
#include "input_warehouse.h"
#include "point.h"

#include <vector>

using namespace std;
/**
 * this object represent parse_route data that relevant to the 'Hoogie Boogie'.
 *  not allowed - copy c'tor, copy assignment, move c'tor, move assignment.
 */

class parse_warehouse
{
private:
	const unsigned int number_of_lines_;  /* represent the sub deliver count */
	vector<input_warehouse> warehouses_;  /* represent the result after parse_route the data */
	bool is_valid_data_; /* represent if the data is valid */
	static unsigned int object_count_; /* counter all the c'tor that create */

	/* represent the number of character warehouse can be. */
	enum character { c_max = 12 };

	/* this enum is for order at the route indexs */
	enum input_index { i_node = 0, i_location_x = 1, i_location_y = 2, i_inventory = 3 }; /* represent the iteration of simulation max value can be. */

	/* this function is a private, helper to the c'tor, return true or false. */
	bool check_valid_name(const string& cs);

public:

	explicit parse_warehouse(ifstream& file, const string input_name); /* default c'tor */
	parse_warehouse(const parse_warehouse& other) = delete; /* delete copy c'tor */
	parse_warehouse(parse_warehouse&&) = delete; /* delete move c'tor */
	~parse_warehouse() = default; /* d'tor */

	parse_warehouse& operator=(parse_warehouse&) = delete; /* delete copy assignment */
	parse_warehouse& operator=(parse_warehouse&&) = delete; /* delete move assignment */

	/* this function is a accessor to route_, return vector<input_route>. */
	vector<input_warehouse> get_warehouses() const { return warehouses_; }

	/* this function is a accessor to is_valid_data_, return true or false. */
	bool get_is_valid_data() const { return  is_valid_data_; }

	/* this static function is helper c'tor initializer to the numbers of line in a file, return int. */
	static int configure_num_lines(ifstream& file);
};

