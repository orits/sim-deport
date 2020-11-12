#include <iostream>
#include "controller.h"
#include "model.h"

using namespace std;
class model_destroyer {
	public:
	~model_destroyer() { delete model::instance_; }
} md;

int main(int argc, char* argv[]) {

	cout.setf(ios::fixed,ios::floatfield);
	cout.precision(2);

	controller controller;
	controller.run(argc, argv);

	return 0;
}