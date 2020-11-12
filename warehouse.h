#pragma once
#include <string>
#include <map>
#include "sim_time.h"
#include "sim_object.h"
#include "vehicle.h"
#include <vector>

using namespace std;

/**
 * this object represent warehouse in 'Hoogie Boogie'.
 * is a data class.
 * not allowed -  move c'tor.
 */

class warehouse : public sim_object
{
	private:
		unsigned int inventory_;  /* represent the warehouse inventory history */
		vector<vehicle> parking_;		/* represent the warehouse parking spots. */
	public:
		explicit warehouse(const string& name, const point location) : sim_object(name, location), inventory_(0) { } /* default c'tor */
		warehouse(const warehouse& other) : sim_object(other.name_, other.location_), inventory_(other.inventory_) {} /* copy c'tor */
		warehouse(warehouse&& other) = delete; /* delete move c'tor */
		~warehouse() = default; /* d'tor */

		warehouse& operator=(const warehouse& other) = default; /* copy assignment */
		warehouse& operator=(warehouse&& other) = default; /* move assignment */

		/* this function is update this warehouse to the next run. */
		virtual void update() override;
		
		/* this function is update inventory by sim_time and case quantity. */
		void inventory_update(unsigned int case_quantity);

		/* this operator is to equal this warehouse with other warehouse by name. */
		bool operator==(const warehouse& other) const { return (name_ == other.name_) ? true : false; };

		/* print the warehouse on screen */
		friend ostream& operator<<(ostream& os, const warehouse& warehouse) { os << "#|" << warehouse.name_ << "|#"; return os; }

		/* this function is print the warehouse, didn't return a value. */
		virtual void to_string() const override { cout << "Warehouse " << uppercase << name_[0] << nouppercase << name_.substr(1) << " at position " << location_ << ", Inventory: " << inventory_ << endl; }

		string class_name() const override { return "Warehouse"; }

		static string static_class_name() { return "Warehouse"; }
};