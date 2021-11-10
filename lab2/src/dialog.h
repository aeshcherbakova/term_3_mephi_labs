#pragma once

#include <iostream>
#include <limits>
#include "../Hypocycloid/Hypocycloid.h"

namespace lab2 {

	const char* menu[];         
	extern const int NMsgs;     // num of alternatives in menu


	template <class T>
	int getNum(T& a, std::istream& c = std::cin) {
		do {
			c >> a;
			if (c.eof()) return 0;                      
			if (!c.good() || c.peek() != '\n') {           
				c.clear();
				c.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else return 1;
		} while (1);
	}


	// function for displaying hypocycloid parameters (which do not depend on the angle)
	void print_parameters(const Hypocycloid& h, std::ostream& c);


	//array of dialog functions
	int (*fptr[])(const Hypocycloid&, std::istream&, std::ostream&);

	int D_find_point(const Hypocycloid&, std::istream & = std::cin, std::ostream & = std::cout),
		D_curvature_radius(const Hypocycloid&, std::istream & = std::cin, std::ostream & = std::cout),
		D_sectorial_area(const Hypocycloid&, std::istream & = std::cin, std::ostream & = std::cout);

	// other dialog functions
	int dialog(std::istream& istr = std::cin, std::ostream& ostr = std::cout);
	int D_change_params(Hypocycloid&, std::istream & = std::cin, std::ostream & = std::cout);
	int D_input_angle(double&, std::istream & = std::cin, std::ostream & = std::cout);

}
