#pragma once
#include <list>
#include <memory>
#include <mutex>
#include <condition_variable>
#include "subject.h"
#include "view.h"
#include "sim_object.h"
#include "warehouse.h"
#include "vehicle_factory.h"
#include "input_route.h"
#include <vector>


using namespace std;

class model : public subject
{
	private:
		static model* instance_;
		list<shared_ptr<observer>> view_list_;
		list<shared_ptr<sim_object>> sim_object_list_;
		list<shared_ptr<warehouse>> warehouse_list_;
		list<shared_ptr<vehicle>> vehicle_list_;
		list<shared_ptr<vehicle_factory>> vehicle_factories_list_;
		unsigned int timer_;

		model();
		~model() = default;
		
		void reset_timer() { timer_ = 0; }

	public:
		
		model(const model&) = delete;
		model(const model&&) = delete;

		model& operator= (model&) = delete;
		model& operator= (model&&) = delete;

		static model& get_instance();

		void go();

		void create_new_vehicle(string vehicle_name, string type_of_vehicle, string warehouse_name);

		void create_new_vehicle(string vehicle_name, string state, point& initial_location);

		void create_new_warehouse(const string& name, const point location);

		bool check_crates_load(point location, int crates_load);

		void status() const;

		bool is_vehicle_exist(const string& vehicle_name) const;

		bool is_warehouse_exists(const string& warehouse_name) const;

		void return_to_stopped();

		bool is_tropper_at_range(const point current_location) const;

		void attach(observer* new_observer) override;

		void detach(observer* old_observer) override;

		void notify() override;

		string sim_object_at_point(const point& x_point, const point& y_point) const;

		shared_ptr<warehouse> get_warehouse_by_point(const point point) const;

		shared_ptr<vehicle> get_vehicle_by_name(string vehicle_name) const;

		shared_ptr<sim_object> get_sim_object_by_name(string object_name) const;

		vector<pair<point, string>> get_warehouse_locations() const;

		void reset_sim_object();

		unsigned int get_timer() const { return timer_; };
		
		friend class model_destroyer;
};

