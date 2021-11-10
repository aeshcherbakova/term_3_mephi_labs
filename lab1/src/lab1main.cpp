#include <iostream>
#include "lab1.h"

using namespace lab1;

int main() {
	Matrix* matr = input();

	if (!matr) {
		std::cout << "Incorrect data :(" << std::endl;
		return 1;
	}

	// input of new matrix
	Matrix* new_matr = change_items_in_matrix(matr);
	if (!new_matr) {
		std::cout << "Error in allocate memory" << std::endl;
		erase(matr);
		return 1;
	}

	// output of source and changed matrices if no errors with memory
	output("Source matrix:", matr);
	output("Changed matrix:", new_matr);

	
	erase(matr);
	erase(new_matr);
	return 1;
}
