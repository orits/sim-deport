#pragma once
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

/**
 * this object represent sim_time in 'Hoogie Boogie'.
 */

class sim_time
{
private:
	unsigned int hour_; /* hour time */
	unsigned int minute_; /* minute time */
	enum  minute_conv { hour_m = 60, day_h = 24 }; /* hour_m - how many minute at one hour, day_h - how many hours at one day */
public:
	sim_time(unsigned int hour = 0, unsigned int minute = 0) : hour_(hour), minute_(minute) {} /* default c'tor */
	sim_time(const sim_time& other) = default; /* copy c'tor */
	sim_time(sim_time&&) = default; /* move c'tor */
	~sim_time() = default; /*  d'tor */

	/* this operator is to equal this sim_time with other sim_time */
	sim_time& operator=(const sim_time& other) { hour_ = other.hour_; minute_ = other.minute_; return *this; };

	/* this operator is to equal this sim_time with other sim_time and after that delete the other sim_time */
	sim_time& operator=(sim_time&&) = default;

	/* this operator is to compare this sim_time with other sim_time */
	bool operator<(const sim_time& other) const;

	/* this function check if sim_time is valid, return true if yes else false */
	bool is_valid_time() const;

	/* this static function is helper c'tor initializer to the sim_time from a string, return sim_time. */
	static sim_time configure_data_to_time(string arrival_time);

	/* this static function is check the difference between two dates by minutes */
	static float difference_by_minute(const sim_time& start, const sim_time& end);
	
	static float difference_by_hours(const float minutes);
};