#include <iostream>
#include "matrix.h"

using namespace lab0;

// program for calculating the smallest among the largest elements of each row of the matrix

int main() {
	Line* arr = nullptr;   
	int m;                 // num of rows in matrix
	double res;            // result

	arr = input(m);       
	if (!arr) {
		std::cout << "Incorrect data" << std::endl;
		return 1;
	}

	if (minmax(arr, m, res)) {
		std::cout << "Error in allocate memory" << std::endl;
		erase(arr, m);
		return 1;
	}

	output("Source matrix:", arr, m);
	std::cout << "Result: " << res << std::endl;
	erase(arr, m); 
	return 0;
}