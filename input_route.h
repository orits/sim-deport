#pragma once
#include "sim_time.h"

/**
 * this object represent input_route is a helper class for create a the route data at the graph in 'Hoogie Boogie'.
 */

class input_route
{
private:
	string node_;			/* represent the node name */
	sim_time arrival_time_;     /* represent the arrival time to the node */
	int case_quantity_;		/* represent the case quantity that need to add to inventory */
	sim_time departure_time_;	/* represent the departure time from the node */

public:
	input_route(); /* default c'tor */
	input_route(string node_, sim_time arrival_time, int case_quantity, sim_time departure_time); /*  c'tor */
	input_route(const input_route& other) : node_(other.node_), arrival_time_(other.arrival_time_), case_quantity_(other.case_quantity_), departure_time_(other.departure_time_) {} /* copy c'tor */
	input_route(input_route&& rhs); /* move c'tor */
	~input_route() = default; /* d'tor */


	input_route& operator=(const input_route& other); /* copy assignment */
	input_route& operator=(input_route&& other) = default; /* move assignment */

	/* this function is a accessor to case_quantity_, return int. */
	int get_case_quantity() const { return case_quantity_; }

	/* this function is a accessor to arrival_time_ and departure_time_, return sim_time. */
	sim_time operator[](const char c_time) const { return (c_time == 'a') ? arrival_time_ : departure_time_; }

	/* this function is a accessor to to node_, return string. */
	const string& get_node() const { return node_; }

	/* this function is a mutator to case_quantity_, didn't return value. */
	void set_case_quantity(int new_case_quantity) { case_quantity_ = new_case_quantity; }
};

