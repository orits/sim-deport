#pragma once
#include <exception>   
#include <string>
using namespace std;

/**
 * this object represent exception in 'simCyber'.
* no need operator= because no two simulation.
 * no need copy c'tor because can't duplicate simulation.
 */
class nexception : public exception
{
private:
	const string message_;
public:
	nexception(const string& message) : message_(message) {}
	virtual const char* what() const throw() { return message_.c_str(); }
	virtual ~nexception() throw() {}
};