#include <iostream>
#include "matrix.h"

namespace lab0 {

	// функция ввода всей матрицы
	Line* input(int& rm) {
		const char* pr = "";    // будущее сообщение об ошибке
		Line* lines = nullptr;  // динамический массив строк матрицы
		int m;                  // кол-во строк матрицы
		// сначала вводим кол-во строк
		do {
			std::cout << pr << std::endl;
			std::cout << "Enter number of lines: ---> ";
			pr = "You are wrong. Repeat, please!";
			if (getNum(m) < 0) return nullptr;  // обнаружена ошибка ввода или конец файла
		} while (m < 1);

		// выделяем память под массив структур - строк матрицы
		try {
			lines = new Line[m];
		}
		catch (std::bad_alloc& ba) {
			std::cout << "------ too many rows in matrix: " << ba.what() << std::endl;
			return nullptr;
		}

		for (int i = 0; i < m; i++) {
			pr = "";
			do {
				std::cout << pr << std::endl;
				std::cout << "Enter number of items in line #" << (i + 1) << " ---> ";
				pr = "You are wrong. Repeat, please!";
				if (getNum(lines[i].n) < 0) {   // обнаружена ошибка ввода или конец файла
					erase(lines, i);   // освобождение памяти, занятой ранее введенными стркоами
					return nullptr;
				}
			} while (lines[i].n < 1);

			// теперь выделяем память под элементы новой строки
			try {
				lines[i].a = new double[lines[i].n];
			}
			catch (std::bad_alloc& ba) {
				std::cout << "------ too many items in matrix: " << ba.what() << std::endl;
				erase(lines, i);
				return nullptr;
			}

			// теперь вводим сами элементы строки
			std::cout << "Enter items for matrix line #" << (i + 1) << ":" << std::endl;
			for (int j = 0; j < lines[i].n; j++) {
				if (getNum(lines[i].a[j]) < 0) {
					erase(lines, i + 1);
					return nullptr;
				}
			}
		}

		// формируем результат - количество строк в матрице
		rm = m;
		return lines;
	}


	// функция вывода матрицы
	void output(const char* msg, Line lines[], int m) {
		std::cout << std::endl << msg << std::endl;
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < lines[i].n; ++j)
				std::cout << lines[i].a[j] << "  ";
			std::cout << std::endl;
		}
	}



	// функция освобождения занятой памяти
	Line* erase(Line*& lines, int m) {
		for (int i = 0; i < m; ++i)
			delete[] lines[i].a;
		delete[] lines;
		return nullptr;
	}



	// функция вычисления главного результата
	int minmax(struct Line lines[], int m, double &res) {
		double* s = nullptr;
		try {
			s = new double[m];  // вектор для получения max элементов в строке - по строкам
		}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what() << std::endl;
			return 1;
		}

		for (int i = 0; i < m; i++)
			s[i] = minmax(lines[i].a, lines[i].n, isgreater);
		res = minmax(s, m, isless);
		delete[] s;
		return 0;
	}



	// функция вычисления min/max элемента вектора
	double minmax(double a[], int m, int(*f)(double, double)) {
		double res = a[0];
		for (int i = 0; i < m; i++)
			if (f(a[i], res) > 0)
				res = a[i];
		return res;
	}

}
