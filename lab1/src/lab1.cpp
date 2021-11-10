#include <iostream>
#include "lab1.h"

namespace lab1 {

	//const int MAX_INT = pow(2, 8 * sizeof(int) - 1) - 1;
	const int MAX_INT = std::numeric_limits<int>::max();


	// input number of rows and columns in matrix + ouput error message
	// 1 - success, 0 - error
	bool input_size(const char* msg, int& dest) {
		const char* pr = "";    // future error message
		do {
			std::cout << pr << std::endl << msg;
			pr = "You are wrong. Repeat, please!";
			getNum(dest);
			/*if (getNum(dest) < 0) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			} */
		} while (dest < 1);
		return 1;
	}


	// creating new array of non-zero items 
	NZItem* new_array(NZItem*& arr, int size) {
		try {
			arr = new NZItem[size];
		}
		catch (std::bad_alloc& ba) {
			std::cout << "Too big array: " << size << "items; " << ba.what() << std::endl;
			return nullptr;
		}
		return arr;
	}



	// input of rectangular sparse matrix
	Matrix* input() {
		Matrix* matr = new Matrix({ 0, 0, 0, nullptr });

		// input num of rows and cols
		input_size("Enter number of rows in matrix ---> ", matr->m);
		input_size("Enter number of columns in matrix ---> ", matr->n);

		std::cout << MAX_INT;
		if (matr->n > MAX_INT / matr->m ||  matr->n * matr->m > 20) {
			std::cout << "If you want to input all matrix, type '1', if you want to input only not zero items, input '2' --> ";
			int ans = 0;
			const char* pr = "";
			do {
				std::cout << pr << std::endl;
				pr = "You must input only '1' or '2'";
				if (getNum(ans) < 0) return nullptr;
			} while (ans != 1 && ans != 2);

			if (ans == 1 && !input_all_matrix(matr)) return nullptr;
			else if (ans == 2 && !input_only_not_zeros(matr)) return nullptr;
		}
		else if (!input_all_matrix(matr)) return nullptr;

		return matr;
	}



	// free allocated memory of matrix
	void erase(Matrix *matr) {
		delete[] matr->items;
		delete matr;
	}



	// outuput matrix into console
	void output(const char* msg, Matrix* matr) {
		std::cout << std::endl << msg << std::endl;
		// std::cout.setf(std::ios::fixed);    // output in decimal format 
		int count = 0;
		for (int i = 0; i < matr->m; ++i) {
			for (int j = 0; j < matr->n; ++j)
				if (matr->items[count].row == i && matr->items[count].column == j) {
					std::cout << matr->items[count].value << " ";
					count++;
				}
				else std::cout << "0 ";
			std::cout << std::endl;
		}
	}


	// allocating memory and inputting matrix for manual input
	// returns 1 - success, 0 - alloc error or input error
	// if memory error, marix is erased
	int input_all_matrix(Matrix* matr) {
		// allocate momry for 20% or 50% of number of elements 
		int size = 0;
		// if user wants matrix bigger then max_int

		if (matr->n > MAX_INT / matr->m) size = 1000000;
		else {
			int full_size = matr->n * matr->m;
			size = (full_size > 100) ? (full_size / 10) : (full_size / 2 + 1);
		}
		do {
			// allocate memoty for array; divide size by 2 if error
			if (!new_array(matr->items, size)) size /= 2;
		} while (!matr->items && size > 1);

		if (!matr->items) {
			std::cout << "Problems with memory allocation :(" << std::endl;
			return 0;
		}


		double temp;
		for (int i = 0; i < matr->m; i++) {
			std::cout << "Enter items for matrix line #" << (i + 1) << ":" << std::endl;
			for (int j = 0; j < matr->n; j++) {
				if (getNum(temp) < 0) {   // input error
					erase(matr);
					return 0;
				}
				// write only non-zero items
				if (temp != 0) {
					// add memory if not enough
					if (matr->NZ_items == size) {
						int add_items = 5;
						NZItem* new_arr = nullptr;
						do {
							new_arr = resize_array(matr->items, size, size + add_items--);
						} while (!new_arr && add_items > 0);
						if (!new_arr) {
							// memory not allocated even for 1 item - erase, return error
							std::cout << "Too many items :(" << std::endl;
							erase(matr);
							return 0;
						}
						matr->items = new_arr;
						size += add_items + 1;
					}

					// memory allocated successfully, add new non-zero item
					matr->items[matr->NZ_items] = { i, j, temp };
					matr->NZ_items++;
				}
			}
		}

		return 1;
	}


	// input matrix in format (row, column, value) of non-zeros
	// return 1 - success, 0 - memory/input error
	int input_only_not_zeros(Matrix* matr) {
		std::cout << "Input number of not zero items --> ";
		const char* pr = "";    // future error message
		do {
			std::cout << pr << std::endl;
			pr = "Number of not zero items must be bigger than 0";
			if (getNum(matr->NZ_items) < 0) return 0;
		} while (matr->NZ_items <= 0);

		// check num of non-zeros smaller then matrix size
		if (matr->NZ_items > matr->m * matr->n) matr->NZ_items = matr->m * matr->n;
		if(!new_array(matr->items, matr->NZ_items)) return 0;     // memory alloc

		// input non-zeros
		for (int i = 0; i < matr->NZ_items; i++) {
			std::cout << "Input row, column and value of not zero item #" << i + 1 << " --> ";
			NZItem* temp = matr->items + i;
			if (getNum(temp->row) < 0 || getNum(temp->column) < 0 || getNum(temp->value) < 0) {
				// input error
				erase(matr);
				return 0;
			}

			// check indices in bounds
			if (temp->row < 0 || temp->row > matr->m - 1) {
				std::cout << "Row of item must be >= 0 and < number of rows in matrix!" << std::endl;
				i--;
				continue;
			}
			if (temp->column < 0 || temp->column > matr->n - 1) {
				std::cout << "Column of item must be >= 0 and < number of columns in matrix!" << std::endl;
				i--;
				continue;
			}
			if (!temp->value) {
				std::cout << "This item must be not zero!" << std::endl;
				i--;
				continue;
			}

			// input sorting
			while (temp > matr->items && temp->row < (temp - 1)->row) {
				temp = swap_left(temp);
			}
			while (temp > matr->items && temp->column < (temp - 1)->column) {
				temp = swap_left(temp);
			}
		}
		return 1;
	}



	// creating new matrix:
	// swap i and j elements, where i - index of first element in row, bigger its previous
	// j - index of last element in row, smaller its previuos
	Matrix* change_items_in_matrix(Matrix* matr) {

		// create frame for new matrix, check memory is enough
		Matrix* new_matr = new Matrix({ matr->m, matr->n, matr->NZ_items, nullptr });
		if(!new_array(new_matr->items, new_matr->NZ_items)) return nullptr;

		// main alorithm
		// result - i and j indices of columns + 2 pointers on elements to swap. If index = 0, pointer is null
		int I = -1, J = -1;
		NZItem* I_ptr = nullptr, * J_ptr = nullptr;
		NZItem* new_matr_ptr = new_matr->items;
		NZItem* ptr = matr->items;            // iterator
		int start_line_offset = 0;   // shift of pointer (first non-zero in this row)
		int end_line_offset = 0;     // shift of pointer (last non-zero in this row)

		for (int i = 0; i < matr->m; ++i) {
			// if all non-zero checked, end loop 
			if (start_line_offset == matr->NZ_items) break;
			ptr = matr->items + start_line_offset;
			if (ptr->row != i) continue;     // if there no non-zero items, go to next row
			new_matr_ptr = new_matr->items + start_line_offset;

			// we are sure that non-zero in this row exists
			I_ptr = find_I_item_in_a_row(matr, ptr, i, I);

			// go to first non-zero in next row
			while (ptr < matr->items + matr->NZ_items - 1 && (ptr + 1)->row == i) ptr++;
			end_line_offset = ptr - matr->items;    // remember index of last non-zero in this row
			// ptr points on last non-zero in this line; we are ready to find J

			J_ptr = find_J_item_in_a_row(matr, ptr, i, J);

			//std::cout << std::endl << "row = " << i << " I = " << I << " J = " << J << std::endl;
			
			// copy from old array to new with swap 
			// copy all from start_ptr to next_row_ptr 
			// 4 variants of swap

			// (1) I or J not exist, do nothing 
			if (I == -1 || J == -1) 
				simple_copy(matr->items, new_matr->items, start_line_offset, end_line_offset);

			// (2) one of I or J = 0, another != 0 -> shift
			else if (I_ptr && !J_ptr || J_ptr && !I_ptr) {
				// check which is zero
				NZItem* not_zero = nullptr;
				int zero_column = -1;
				if (I_ptr) { not_zero = I_ptr; zero_column = J; }
				else { not_zero = J_ptr; zero_column = I; }

				ptr = matr->items + start_line_offset;
				//new_matr_ptr = new_matr->items + temp_line_offset;
				int flag = false;    // flag = 0 when nonn-zero is not moved, = 1 after moving
				for (int k = start_line_offset; k <= end_line_offset; k++, ptr++, new_matr_ptr++) {

					// find first non-zero element on the left of our non-zero
					// variants: ptr - last in matrix / last in row / last before place where to insert
					if (!flag && (k == end_line_offset || (ptr + 1)->column >= zero_column || (ptr + 1)->row != i)) {
						// copy current value if it's non-zero 
						if (ptr->column != not_zero->column) {
							*new_matr_ptr = { i, ptr->column, ptr->value };
							new_matr_ptr++;
						}

						// insert non-zero
						*new_matr_ptr = { i, zero_column, not_zero->value };
						flag = true;   // for non inserting it several times
					}
					// don't copy non-zero
					else if (ptr->column == not_zero->column)
						new_matr_ptr--;
					// if we are far from I and J, copy ordinarily
					else *new_matr_ptr = { i, ptr->column, ptr->value };
				}
			}

			else {
				// (3) I != 0 and J != 0 - swap values in old matrix, copy to new and swap in old again
				if (I_ptr && J_ptr) swap(I_ptr->value, J_ptr->value);

				
				// (4) I = 0 and J = 0 - do nothing
				simple_copy(matr->items, new_matr->items, start_line_offset, end_line_offset);

				// swap I and J in old matrix 
				if (I_ptr && J_ptr) swap(I_ptr->value, J_ptr->value);
			}
			
			start_line_offset = ++end_line_offset;
		}

		return new_matr;
	}


	// idea: don't chech every element, we can check only non-zeros and their left and right neighbours for all non-zeros in row
	// use that non-zeros array is sorted as values are placed in a row - left to right
	// one nore idea: we need only first and last non-zeros, so we don't need to check values berween them
	// it would be unefficient only if row contains only equal non-zeros (unlikely, cause matrix is sparse) 


	// find I - index of column where first nz if bigger then previous
	// if value = 0, return nullptr, if != 0, return pointer to this element
	NZItem* find_I_item_in_a_row(Matrix* matr, NZItem *&ptr, int temp_row, int& I) {
		// left to right find first element bigger previous
		while (ptr < matr->items + matr->NZ_items && ptr->row == temp_row) {
			int column = ptr->column;
			// if ptr is not left, compare with left neighbour
			if (column != 0) {
				NZItem* prev = (ptr == matr->items) ? nullptr : (ptr - 1);
				double left_value = (prev && prev->row == temp_row && prev->column == column - 1) ? prev->value : 0;

				// check which is bigger and change I if it is
				if (ptr->value > left_value) {
					I = column;
					return ptr;
				}
			}

			// if ptr is not right, compare with right neighbour
			if (column != matr->n - 1) {
				NZItem* next = (ptr == matr->items + matr->NZ_items) ? nullptr : (ptr + 1);
				double right_value = (next && next->row == temp_row && next->column == column + 1) ? next->value : 0;

				// check which is bigger and change I
				if (right_value > ptr->value) {
					I = column + 1;
					return (right_value ? next : nullptr);
				}
			}
			ptr++;
		}
		ptr--;
		I = -1;
		return nullptr;  // if not found
	}



	// find index J of last element bigger then previous 
	// if value = 0, return nullptr, if != 0, return pointer to this element
	NZItem* find_J_item_in_a_row(Matrix* matr, NZItem*& ptr, int temp_row, int& J) {
		for (; ptr >= matr->items && ptr->row == temp_row; ptr--) {
			int column = ptr->column;

			// if ptr not right, compare with right neigbour
			if (column != matr->n - 1) {
				NZItem* next = (ptr == matr->items + matr->NZ_items - 1) ? nullptr : (ptr + 1);
				double right_value = (next && next->row == temp_row && next->column == column + 1) ? next->value : 0;

				// change J if it's bigger
				if (right_value < ptr->value) {
					J = column + 1;
					return (right_value ? next : nullptr);
				}
			}

			// if ptr not left, compare to left neighbour
			if (column != 0) {
				NZItem* prev = (ptr == matr->items) ? nullptr : (ptr - 1);
				double left_value = (prev && prev->row == temp_row && prev->column == column - 1) ? prev->value : 0;

				// change J if it's bigger
				if (ptr->value < left_value) {
					J = column;
					return ptr;
				}
			}
		}
		J = -1;
		return nullptr;
	}



	// copy several non-zeros from old array to new
	void simple_copy(NZItem *old_array, NZItem* new_array, int start_offset, int finish_offset) {
		for (int i = start_offset; i <= finish_offset; i++) {
			NZItem* temp = old_array + i;
			new_array[i] = { temp->row, temp->column, temp->value };
		}
	}
}
