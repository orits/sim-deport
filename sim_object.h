#pragma once
#include "point.h"
#include <map>

class sim_object
{
	protected:
		string name_;		/* represent the sin object name */
		point location_;	/* represent the sin object location */

	public:
		sim_object(string name, const point location) : name_(name), location_(location) { }
		virtual ~sim_object() = 0;

		virtual void update() = 0;

		/* this function is a accessor for name_. */
		string get_name() const { return name_; }

		point get_location() const { return location_; }

		virtual void to_string() const = 0 ;

		virtual string class_name() const = 0;

		enum objects { warehouse_obj = 0, truck_obj = 1, trooper_obj = 2, chopper_obj = 3 };
		
		static map<objects, string> create_enum_map_objects();
};