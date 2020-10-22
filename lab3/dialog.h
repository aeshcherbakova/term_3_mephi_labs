#pragma once

#include <iostream>
#include <limits>
//#include "Static\TimeDiagram_static.h"
#include "Dynamic\TimeDiagram_dynamic.h"

namespace lab3 {

	// template for input of one value of arbitrary type
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

	int dialog();

	// array of dialog fu
	int (*fptr[])(TimeDiagram&);

	int add_signals (TimeDiagram&);
	int set_new_td  (TimeDiagram&);
	int multiplicate(TimeDiagram&); 
	int insert_new  (TimeDiagram&);
	int shift_left  (TimeDiagram&);
	int shift_right (TimeDiagram&);

}