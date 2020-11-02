#include "dialog.h"

using namespace Prog3C;

int main() {

	std::cout << "Creating a new train..." << std::endl;
	train tr;
	while(tr.get_length() == 1) 
		set_train(tr);
	int num = 0;
	while (1) {
		clr();
		get_train_occupancy_information(tr);
		
		if (tr.seats_left() == 0) {
			if (!train_is_full(tr)) return 0;
			continue;
		}

		if (!input_num_of_pass(num, tr.seats_left())) return 0;

		if (output_where_to_put_passangers(tr, num))
			while (occupy_seats(tr, num) == -1);
		else put_in_differrent_cars(tr, num);
	}
	return 0;
}