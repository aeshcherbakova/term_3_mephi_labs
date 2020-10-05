#include <iostream>
#include "dialog.h"

using namespace lab2;

int main() {
	std::cout.precision(6);

	lab2::Hypocycloid test;
	if (!D_change_params(test)) return 0;

	int choice;
	while (choice = dialog())
		if (choice == 4) {
			if (!D_change_params(test)) break;
		}
		else if (!fptr[choice](test, std::cin, std::cout)) break;

	std::cout << "That's all, bye! :)" << std::endl;
	return 0;
}