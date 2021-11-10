#pragma once

namespace lab0 {
	// ��������� ��� ������� ������ �������
	struct Line {
		int n;           // ���-�� ��������� � ������
		double* a;       // ������ ���������
	};


	// ������ ������� ����� ������ �������� ������������� ����
	template <class T>
	int getNum(T& a) {
		std::cin >> a;
		if (!std::cin.good())   // ���������� ������ ����� ��� ����� �����
			return -1;
		return 1;
	}


	// ������� ������� ��������
	inline int isgreater(double a, double b) {
		return a > b;
	}


	// ������� ������� ��������
	inline int isless(double a, double b) {
		return a < b;
	}


	// ��������� �������
	Line* input(int&);  // ���� �������
	void output(const char* msg, Line a[], int m);   // ����� �������
	Line* erase(Line*& a, int m);   // ������������ ������� ������
	int minmax(Line a[], int m, double&);  // ���������� �������� ����������
	double minmax(double a[], int m, int(*f)(double, double));   // ���������� min/max �������� ������� �������
}
