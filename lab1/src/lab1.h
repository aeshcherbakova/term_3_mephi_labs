#pragma once
#include <limits>

namespace lab1 {

	// struct for storing non-zero item place and value
	typedef struct NotZeroItem {
		int row, column;    
		double value;       
	}NZItem;


	 typedef struct Sparse_Matrix {
		int m, n;           // num of rows and columns in matrix
		int NZ_items;       // num of non-zero items
		NZItem* items;      // array of non-zero items
	}Matrix;


	// template for inpup one value of any type
	template <class T>
	int getNum(T& a) {
		std::cin >> a;
		if (!std::cin.good()) {   // input error or end of file
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		return 1;
	}



	// template for changing dynamic array's length
	template <class T>
	T* resize_array(T* arr, int old_size, int new_size) {
		if (!arr) return nullptr;

		T* new_array = nullptr;
		try {
			new_array = new T[new_size];
		}
		catch (std::bad_alloc& ba) {
			std::cout << "Too big array: " << ba.what() << std::endl;
			return nullptr;
		}

		for (int i = 0; i < old_size; i++)
			new_array[i] = arr[i];
		delete[] arr;    
		return new_array;
	}


	// template for swapping values of any type
	template <class T>
	void swap(T& a, T& b) {
		T x = a;
		a = b;
		b = x;
	}


	// swap item in array with its previous item
	inline NZItem* swap_left(NZItem* temp) {
		NZItem a = *temp;
		*temp = *(temp - 1);
		*(temp - 1) = a;
		return temp - 1;
	}


	// function prorotypes
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
