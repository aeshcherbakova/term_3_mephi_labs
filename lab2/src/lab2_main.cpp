#include <iostream>
#include "Hypocycloid.h"

int main() {
	lab2::Hypocycloid test(5, 3, 2);
	if (!lab2::D_change_params(test)) return 0;

	int choice;
	while (choice = lab2::dialog())
		if (choice == 4) {
			if (!lab2::D_change_params(test)) break;
		}
		else if (!lab2::fptr[choice](test, std::cin, std::cout)) break;

	std::cout << "That's all, bye! :)";
	return 0;
}