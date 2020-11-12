#include "point.h"

// multiply point by const float (point*const float);
point operator*(const float m, point p) {
	return p * m;
};

// Distance to another point.  Pythagorean thm.
float point::distance(const point& other) const {
	const auto xd = xval - other.xval;
	const auto yd = yval - other.yval;
	return sqrt(xd * xd + yd * yd);
}

bool point::is_at_rang(const point& start, const point& end) const {
	/*return ((xval >= start.xval && xval < start.yval && yval >= end.xval && yval < end.yval)
		   || (xval >= start.xval && xval < start.yval && yval + 1 >= end.xval && yval < end.yval));*/
	return (xval >= start.xval && xval < start.yval && yval >= end.xval && yval < end.yval);
}


