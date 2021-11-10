#pragma once

namespace lab0 {
	// row in a matrix
	struct Line {
		int n;           
		double* a;      
	};

	// input one value of any type
	template <class T>
	int getNum(T& a) {
		std::cin >> a;
		if (!std::cin.good())   // input error / end of file
			return -1;
		return 1;
	}


	inline int isgreater(double a, double b) {
		return a > b;
	}


	inline int isless(double a, double b) {
		return a < b;
	}

	Line* input(int&);  
	void output(const char* msg, Line a[], int m); 
	Line* erase(Line*& a, int m);  
	int minmax(Line a[], int m, double&);  
	double minmax(double a[], int m, int(*f)(double, double));   
}
