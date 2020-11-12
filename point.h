#pragma once
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include  "cmath"

using namespace  std;

/**
 * this object represent point in R 2.
 */
class point
{
private:
	float xval, yval;
public:
	// Constructor uses default arguments to allow calling with zero, one,
	// or two values.
	point(const float x = 0.00, const float y = 0.00) : xval(x), yval(y) {}; /* default c'tor */
	point(const point& other) : xval(other.xval), yval(other.yval) {}; /* copy c'tor */
	point(point&& other) = default; /* move c'tor */
	~point() = default; /* d'tor */

	// Accessors for x or y.
	float get_x() const { return xval; };
	float get_y() const { return yval; };

	// Distance to another point.  Pythagorean thm.
	float distance(const point& other) const;

	// Add or subtract or equal or multiply two points.
	point operator+(const point& other) const { return point(xval + other.xval, yval + other.yval); };
	point operator-(const point& other) const { return point(xval - other.xval, yval - other.yval); };
	point operator*(const point& other) const { return point(xval * other.xval, yval * other.yval); };
	point& operator=(const point& other) { xval = other.xval; yval = other.yval; return *this; };
	point& operator=(point&& other) = default;
	bool operator==(const point& other) const { return  (xval == other.xval && yval == other.yval); }

	// is point at rang.
	bool is_at_rang(const point& start, const point& end) const;

	// Move the existing point.
	void move(const point& p) { xval += p.xval; yval += p.yval; };

	// multiply point by const float (point*const float);
	point operator*(const float d) const { return point(d * xval, d * yval); };
	

	// Print the point on the stream. 
	friend ostream& operator<<(ostream& out, const point& p) { out << "(" << p.xval<< ", " << p.yval << ")"; return out; };

	// multiply other point by const float (m * p);
	friend point operator*(float m, point p);
};


