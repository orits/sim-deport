#include "sim_time.h"

bool sim_time::operator<(const sim_time& other) const {

	if (hour_ < other.hour_)
		return true;
	else if (hour_ == other.hour_)
	{
		if (minute_ < other.minute_)
			return true;
	}

	return false;
}

/* this function check if sim_time is valid, return true if yes else false */
bool sim_time::is_valid_time() const {
	return (hour_ >= 0 && hour_ < 24 && minute_ >= 0 && minute_ < 60);
}


sim_time sim_time::configure_data_to_time(string arrival_time) {
	string temp;
	replace(arrival_time.begin(), arrival_time.end(), ':', ' ');
	stringstream data_stream(move(arrival_time));

	int hour, minute;

	data_stream >> hour;
	data_stream >> minute;

	return sim_time(hour, minute);
}

float sim_time::difference_by_minute(const sim_time & start, const sim_time & end) {
	return  (((end.hour_ * hour_m) + end.minute_) - ((start.hour_ * hour_m) + start.minute_));
}

float sim_time::difference_by_hours(const float minutes) {
	return minutes / hour_m;
}

