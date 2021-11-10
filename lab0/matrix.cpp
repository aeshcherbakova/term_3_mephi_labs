#include <iostream>
#include "matrix.h"

namespace lab0 {

	// input all matrix
	Line* input(int& rm) {
		const char* pr = "";    // future error message
		Line* lines = nullptr;  
		int m;                  // num of lines in matrix
		// input num of lines 
		do {
			std::cout << pr << std::endl;
			std::cout << "Enter number of lines: ---> ";
			pr = "You are wrong. Repeat, please!";
			if (getNum(m) < 0) return nullptr;  // input error / end of file
		} while (m < 1);

		// allocate memory for lines array
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
				if (getNum(lines[i].n) < 0) {   // input error / end of file
					erase(lines, i);   // free allocated memory
					return nullptr;
				}
			} while (lines[i].n < 1);

			// allocate memory for elements array in each line
			try {
				lines[i].a = new double[lines[i].n];
			}
			catch (std::bad_alloc& ba) {
				std::cout << "------ too many items in matrix: " << ba.what() << std::endl;
				erase(lines, i);
				return nullptr;
			}

			// input line elements
			std::cout << "Enter items for matrix line #" << (i + 1) << ":" << std::endl;
			for (int j = 0; j < lines[i].n; j++) {
				if (getNum(lines[i].a[j]) < 0) {
					erase(lines, i + 1);
					return nullptr;
				}
			}
		}

		rm = m;
		return lines;
	}


	void output(const char* msg, Line lines[], int m) {
		std::cout << std::endl << msg << std::endl;
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < lines[i].n; ++j)
				std::cout << lines[i].a[j] << "  ";
			std::cout << std::endl;
		}
	}


	Line* erase(Line*& lines, int m) {
		for (int i = 0; i < m; ++i)
			delete[] lines[i].a;
		delete[] lines;
		return nullptr;
	}



	// find minimum from lines's maxes
	int minmax(struct Line lines[], int m, double &res) {
		double* s = nullptr;
		try {
			s = new double[m];  // array of max elements in each line
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


	// find min/max element in array
	double minmax(double a[], int m, int(*f)(double, double)) {
		double res = a[0];
		for (int i = 0; i < m; i++)
			if (f(a[i], res) > 0)
				res = a[i];
		return res;
	}

}
