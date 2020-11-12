#pragma once
#include "sim_time.h"
#include "point.h"

/**
 * this object represent input_route is a helper class for create a the route data at the graph in 'Hoogie Boogie'.
 */

class input_warehouse
{
private:
	string node_;			/* represent the node name */
	point location_;		/* represent the location */
	unsigned int inventory_;

public:
	input_warehouse(); /* default c'tor */
	input_warehouse(string node, point location, int inventory); /*  c'tor */
	input_warehouse(const input_warehouse& other) : node_(other.node_), location_(other.location_), inventory_(other.inventory_) {} /* copy c'tor */
	input_warehouse(input_warehouse&& rhs); /* move c'tor */
	~input_warehouse() = default; /* d'tor */


	input_warehouse& operator=(const input_warehouse& other); /* copy assignment */
	input_warehouse& operator=(input_warehouse&& other) = default; /* move assignment */

	/* this function is a accessor to case_quantity_, return int. */
	int get_inventory() const { return inventory_; }

	/* this function is a accessor to to node_, return string. */
	const string& get_node() const { return node_; }


	point get_location() const { return location_; }
	/* this function is a mutator to case_quantity_, didn't return value. */
	void set_inventory(int new_inventory) { inventory_ = new_inventory; }
};