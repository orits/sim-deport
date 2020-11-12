#include "view.h"
#include "model.h"

view::view() : origin_point_(-10, -10), size_(default_size), scale_(default_scale) {

}


void view::update() {

}

void view::draw() const {
	cout << "Display size: " << size_ << ", scale: " << scale_ << ", origin: " << origin_point_ << endl;

	//spaces between each indicator
	int seperator = 3;
	//diff between each indicator
	int step_indicator = (seperator * scale_);
	//X axis start
	int start_x_indicator = origin_point_.get_x();
	//Y axis end
	int last_y_indicator = origin_point_.get_y() + (scale_*(size_ - 1));
	//Scan direction is left to right, starting from above
	int start_scan_range_x = origin_point_.get_x();
	int start_scan_range_y = last_y_indicator + scale_;

	for (unsigned i = size_; i > 0; i--) {

		//Y axis
		//Y axis indicators
		//indicator has to be printed:
		if ((i - 1) % seperator == 0) {
			//number length = 1 (0-9)
			if (-1 < last_y_indicator && last_y_indicator < 10) std::cout << "   ";
			//number length = 2 (-9 to -1 , 10 to 99)
			if ((last_y_indicator > 9 && last_y_indicator < 100) || (-10 < last_y_indicator && last_y_indicator < 0)) std::cout << "  ";
			//number length = 3 (-99 to -10 , 100 to 999)
			if (last_y_indicator > 99 || (-100 < last_y_indicator && last_y_indicator < -9)) std::cout << " ";
			//number length = 4 ( -999 to -100 , 1000 to 9999)
			std::cout << last_y_indicator;
		}
		//else
		else {
			std::cout << "   |";
		}
		//decrease Y indicator for next iteration
		last_y_indicator -= scale_;

		//content
		for (int j = size_; j > 0; j--) {

			//calculate limits of scan ranges by round_single_cell_size
			int end_scan_range_x = start_scan_range_x + scale_;
			int end_scan_range_y = start_scan_range_y - scale_;
			//now we have defined ranges to scan, using ObjectinRange we will find if there are any objects
			//scan direction from above to bottom and left to right therefore:
			//end_scan_range_y < start_scan_range_y but start_scan_range_x < end_scan_range_x
			std::string found = model::get_instance().sim_object_at_point(point(start_scan_range_x, end_scan_range_x), point(end_scan_range_y, start_scan_range_y));
			if (found.size() >= 2) {
				//place shorted port name
				found[0] = toupper(found[0]);
				cout << found[0];
				cout << found[1];
			}
			else {
				//empty space
				std::cout << ". ";
			}
			//inner loop move right across X axis
			start_scan_range_x += scale_;
		}
		//outer loop move down across Y axis
		start_scan_range_y -= scale_;
		//reset X every loop
		start_scan_range_x = origin_point_.get_x();
		std::cout << std::endl;
	}

	//X axis
	for (unsigned i = 0; i < size_%seperator + size_ / seperator; i++) {

		//origin x indicator

		if (i == 0) {
			//number length = 1 (0-9)
			if (-1 < start_x_indicator && start_x_indicator < 10) std::cout << "     ";
			//number length = 2 (-9 to -1 , 10 to 99)
			else if ((9 < start_x_indicator && start_x_indicator < 100) || (-10 < start_x_indicator && start_x_indicator < 0)) std::cout << "    ";
			//number length = 3 (-99 to -10 , 100 to 999)
			else if ((99 < start_x_indicator && start_x_indicator < 1000) || (-100 < start_x_indicator && start_x_indicator < -9)) std::cout << "   ";
			//number length = 4 ( -999 to -100 , 1000 to 9999)
			else std::cout << "  ";
		}
		std::cout << start_x_indicator;

		//other X axis indicators
		int next_x_indicator = start_x_indicator + step_indicator;
		//X axis indicators compatability
		if (-1 < next_x_indicator && next_x_indicator < 10) std::cout << "     ";
		//number length = 2 (-9 to -1 , 10 to 99)
		else if ((9 < next_x_indicator  && next_x_indicator < 100) || (-10 < next_x_indicator && next_x_indicator < 0)) std::cout << "    ";
		//number length = 3 (-99 to -10 , 100 to 999)
		else if ((99 < next_x_indicator && next_x_indicator < 1000) || (-100 < next_x_indicator && next_x_indicator < -9)) std::cout << "   ";
		//number length = 4 ( -999 to -100 )
		else std::cout << " ";
		//increase start indicator represents moving across X axis
		start_x_indicator = next_x_indicator;

	}
	std::cout << std::endl;
}
