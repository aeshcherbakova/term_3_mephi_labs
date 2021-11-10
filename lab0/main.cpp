#include <iostream>
#include "matrix.h"

using namespace lab0;

// ��������� ��� ���������� ����������� ����� ���������� ��������� ������ ������ �������

int main() {
	Line* arr = nullptr;   // �������� ������
	int m;                 // ���-�� ����� � �������
	double res;            // ���������� ���������

	arr = input(m);        //���� �������
	if (!arr) {
		std::cout << "Incorrect data" << std::endl;
		return 1;
	}

	// ���������� ���������� ����������
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