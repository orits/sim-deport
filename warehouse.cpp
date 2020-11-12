#include "warehouse.h"

void warehouse::update() {

}

/* this function is update inventory by sim_time and case quantity. */
void warehouse::inventory_update(unsigned int case_quantity) {
	inventory_ += case_quantity;
}