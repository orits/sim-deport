#include "input_route.h"

/* default c'tor */
input_route::input_route() : node_(" "), arrival_time_(), case_quantity_(0), departure_time_() {

}

/*  c'tor */
input_route::input_route(string node, sim_time arrival_time, int case_quantity, sim_time departure_time) : node_(move(node)), arrival_time_(arrival_time), case_quantity_(case_quantity), departure_time_(departure_time) {

}

/* move c'tor */
input_route::input_route(input_route&& rhs) : node_(move(rhs.node_)), arrival_time_(move(rhs.arrival_time_)), case_quantity_(rhs.case_quantity_), departure_time_(move(rhs.departure_time_)) {

}

/* copy assignment */
input_route& input_route::operator=(const input_route& other) {
	node_ = other.node_;
	arrival_time_ = other.arrival_time_;
	case_quantity_ = other.case_quantity_;
	departure_time_ = other.departure_time_;
	return *this;
}
