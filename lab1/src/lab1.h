#pragma once
#include <limits>

namespace lab1 {


	// структура для хранения положения и значения каждого ненулевого элемента
	typedef struct NotZeroItem {
		int row, column;    // номер строки и столбца ненулевого элемента матрицы
		double value;       // значение ненулевых элементов матрицы
	}NZItem;



	// структура сильно разреженной матрицы
	 typedef struct Sparse_Matrix {
		int m, n;           // кол-во строк и столбцов матрицы
		int NZ_items;       // кол-во ненулевых элементов
		NZItem* items;      // массив ненулевых элементов
	}Matrix;



	// шаблон функций ввода одного значения произвольного типа
	template <class T>
	int getNum(T& a) {
		std::cin >> a;
		if (!std::cin.good()) {   // обнаружена ошибка ввода или конец файла
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		//	return -1;
		return 1;
	}



	// шаблон функции изменения размера динамического массива
	template <class T>
	T* resize_array(T* arr, int old_size, int new_size) {
		// если исходный массив пустой, сразу выходим
		if (!arr) return nullptr;

		// создаем новый массив 
		T* new_array = nullptr;
		try {
			new_array = new T[new_size];
		}
		catch (std::bad_alloc& ba) {
			std::cout << "Too big array: " << ba.what() << std::endl;
			return nullptr;
		}

		// копирование данных из старого массива в новый
		for (int i = 0; i < old_size; i++)
			new_array[i] = arr[i];
		delete[] arr;     // удаление старого массива
		return new_array;
	}


	// шаблон функции перемены мест двух переменных
	template <class T>
	void swap(T& a, T& b) {
		T x = a;
		a = b;
		b = x;
	}


	// поменять местами элемент массива с предыдущим
	inline NZItem* swap_left(NZItem* temp) {
		NZItem a = *temp;
		*temp = *(temp - 1);
		*(temp - 1) = a;
		return temp - 1;
	}


	// прототипы функций
	bool input_size(const char * msg, int &dest);
	NZItem* new_array(NZItem*& arr, int size);
	Matrix* input();
	void erase(Matrix* matr);
	void output(const char* msg, Matrix* matr);
	int input_all_matrix(Matrix* matr);
	int input_only_not_zeros(Matrix* matr);
	Matrix* change_items_in_matrix(Matrix* matr);
	NZItem* find_I_item_in_a_row(Matrix* matr, NZItem*& ptr, int temp_row, int& I);
	NZItem* find_J_item_in_a_row(Matrix* matr, NZItem*& ptr, int temp_row, int& J);
	void simple_copy(NZItem* old_array, NZItem* new_array, int start_offset, int finish_offset);

}
