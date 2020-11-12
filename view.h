#pragma once
#include <iostream>
#include "observer.h"
#include "point.h"


class view : public observer
{	
	private:
		point origin_point_;
		unsigned int size_, scale_;
		enum default_state { default_scale = 2, default_size = 25, origin_x = -10, origin_y = -10 };

	public:
		explicit view();
		virtual ~view() = default;
		void update() override;

		void set_origin(const point& new_point) { origin_point_ = new_point; }
		void set_scale(const unsigned int new_scale) { scale_ = new_scale; }
		void set_size(const unsigned int new_size) { size_ = new_size; }
		void reset_to_default() { origin_point_ = point(origin_x, origin_y); size_ = default_size; scale_ = default_scale; }
		void draw() const;
};

