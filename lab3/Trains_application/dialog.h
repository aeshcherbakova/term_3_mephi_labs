#pragma once

#include <iostream>
#include "Train/Train.h"


namespace Prog3C {

    template <class T>
	int getNum(T& a, const char* msg, std::istream& c = std::cin) {
		std::cout << msg;
		do {
			c >> a;
			if (c.eof()) {
				std::cout << std::endl << "End of input" << std::endl;
				return 0;                        
			}
			if (!c.good() || c.peek() != '\n') {  // input error     
				c.clear();
				c.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << std::endl << "Try again!" << std::endl;
			}
			else {
				c.ignore();  // delete 1 symbol ('\n') from stream
				return 1;
			}
		} while (1);
	}

	void set_train(train& main_train);
	int occupy_seats(train& main_train, int pass_num = 0);
	int input_num_of_pass(int& num, int upper_border);
	void get_train_occupancy_information(train& main_train);
	int train_is_full(train& tr);
	int output_where_to_put_passangers(train& tr, int num);
	int put_in_differrent_cars(train& tr, int num);
	void clr();

}