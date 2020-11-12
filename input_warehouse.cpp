#include "input_warehouse.h"

/* default c'tor */
input_warehouse::input_warehouse() : node_(" "), location_(), inventory_(0) {

}

/*  c'tor */
input_warehouse::input_warehouse(string node, point location, int inventory) : node_(node), location_(location), inventory_(inventory) {

}

/* move c'tor */
input_warehouse::input_warehouse(input_warehouse&& rhs) : node_(move(rhs.node_)), location_(move(rhs.location_)), inventory_(move(rhs.inventory_)) {

}

/* copy assignment */
input_warehouse& input_warehouse::operator=(const input_warehouse& other) {
	node_ = other.node_;
	location_ = other.location_;
	inventory_ = other.inventory_;
	return *this;
}
