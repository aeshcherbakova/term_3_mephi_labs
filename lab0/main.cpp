#include <iostream>
#include "matrix.h"

using namespace lab0;

// программа для вычисления наименьшего среди наибольших элементов каждой строки матрицы

int main() {
	Line* arr = nullptr;   // исходный массив
	int m;                 // кол-во строк в матрице
	double res;            // полученный результат

	arr = input(m);        //ввод матрицы
	if (!arr) {
		std::cout << "Incorrect data" << std::endl;
		return 1;
	}

	// вычисление требуемого результата
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