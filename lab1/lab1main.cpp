/*
¬ариант 10
»з входного потока вводитс€ пр€моугольна€ сильно разреженна€ матрица вещественных чисел [aij], i = 1..m, j = 1..n.  
«начени€ m и n заранее не известны и ввод€тс€ из входного потока.
—формировать новую матрицу, помен€в в каждой строке местами i-ый и j-ый элементы, где i Ц индекс первого элемента строки матрицы, превышающего предыдущий, 
а j Ц индекс последнего элемента строки матрицы, меньшего, чем предыдущий.
»сходную и полученную матрицы вывести в выходной поток с необходимыми комментари€ми.
*/

#include <iostream>
#include "lab1.h"

using namespace lab1;

int main() {
	Matrix* matr = input();

	if (!matr) {
		std::cout << "Incorrect data :(" << std::endl;
		return 1;
	}

	// составление новой матрицы
	Matrix* new_matr = change_items_in_matrix(matr);
	if (!new_matr) {
		std::cout << "Error in allocate memory" << std::endl;
		erase(matr);
		return 1;
	}

	// вывод исходной и полученной матриц, если с пам€тью не возникло проблем
	output("Sourced matrix:", matr);
	output("Changed matrix:", new_matr);

	
	erase(matr);
	erase(new_matr);
	return 1;
}
