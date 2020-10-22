#include "dialog.h"

namespace lab3 {

	const char* menu[]{
		"0. Quit",
		"1. Initialize new time diagram", 
		"2. Add signals to time diagram",
		"3. Multiplicate time diagram",
		"4. Insert new time diagram in the existing",
		"5. Shift left",
		"6. Shift right"
	};


	const int NMsgs = sizeof(menu) / sizeof(menu[0]);

	int (*fptr[])(TimeDiagram&) = { NULL, set_new_td, add_signals, multiplicate, insert_new, shift_left, shift_right };


	int dialog() {
		const char* errmsg = "";
		int input;
		do {
			std::cout << errmsg << std::endl;
			errmsg = "You are wrong. Repeate, please!";
			for (int i = 0; i < NMsgs; ++i)
				std::cout << menu[i] << std::endl;
			if (!getNum(input, "\nMake your choice: --> ")) return 0;
		} while (input < 0 || input >= NMsgs);
		return input;
	}


	int set_new_td(TimeDiagram& td) {
		std::cout << "Input sequence of signals to initialize your time diagram: " << std::endl;
		try {	
			std::cin >> td; 
			std::cout << td << std::endl;
		}
		catch (std::ios_base::failure& f) {
			std::cout << "Error: " << f.what() << std::endl;
			return 0;
		}
		catch (std::exception& ex)
		{
			std::cout << "Error: " << ex.what() << std::endl;
		}
		return 1;
	}

	int add_signals(TimeDiagram& td) {
		std::cout << "Input sequence of signals to add: " << std::endl;
		TimeDiagram to_add;
		try {	
			std::cin >> to_add;
			td = td + to_add;
			std::cout << td << std::endl;
		}
		catch (std::ios_base::failure& f) {
			std::cout << "Error: " << f.what() << std::endl;
			return 0;
		}
		catch (std::exception& ex) {
			std::cout << "Error: " << ex.what() << std::endl;
		}
		return 1;
	}

	int multiplicate(TimeDiagram& td) {
		int k = 0;
		if (!getNum(k, "Input multilpier --> ")) return 0;
		try { 
			td *= k; 
			std::cout << td << std::endl;
		}
		catch (std::exception& ex) {
			std::cout << "Error: " << ex.what() << std::endl;
		}
		return 1;
	}

	int insert_new(TimeDiagram& td) {
		std::cout << "Input sequence of signals to add: " << std::endl;
		TimeDiagram to_add;
		try { std::cin >> to_add; }
		catch (std::ios_base::failure& f) {
			std::cout << "Error: " << f.what() << std::endl;
			return 0;
		}
		catch (std::exception& ex) {
			std::cout << "Error: " << ex.what() << std::endl;
			return 1;
		}

		int k = 0;
		if (!getNum(k, "Input offset --> ")) return 0;
		try {
			td(to_add, k);
			std::cout << td << std::endl;
		}
		catch (std::exception& ex) {
			std::cout << "Error: " << ex.what() << std::endl;
		}

		return 1;
	}

	int shift_left(TimeDiagram& td) {
		int k = 0;
		if (!getNum(k, "Input shift --> ")) return 0;
		try { 
			td <<= k; 
			std::cout << td << std::endl; 
		}
		catch (std::exception& ex) {
			std::cout << "Error: " << ex.what() << std::endl;
		}
		return 1;
	}

	int shift_right(TimeDiagram& td) {
		int k = 0;
		if (!getNum(k, "Input shift --> ")) return 0;
		try {
			td >>= k;
			std::cout << td << std::endl;
		}
		catch (std::exception& ex) {
			std::cout << "Error: " << ex.what() << std::endl;
		}
		return 1;
	}
}