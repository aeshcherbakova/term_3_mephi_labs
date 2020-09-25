#include <iostream>
#include "lab1.h"


namespace lab1 {


	// функция ввода размеров матрицы с выводом сообщений об ошибке
	// 1 - выполнено успешно, 0 - ошибка
	bool input_size(const char* msg, int& dest) {
		const char* pr = "";    // будущее сообщение об ошибке
		do {
			std::cout << pr << std::endl << msg;
			pr = "You are wrong. Repeat, please!";
			if (getNum(dest) < 0) return 0;
		} while (dest < 1);
		return 1;
	}



	// функция создания массива ненулей размера size
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



	// функция ввода прямоугольной разреженной матрицы
	Matrix* input() {
		Matrix* matr = new Matrix({ 0, 0, 0, nullptr });

		// сначала вводятся размеры прямоугольной матрицы
		if (!input_size("Enter number of rows in matrix ---> ", matr->m)) return nullptr;
		if (!input_size("Enter number of columns in matrix ---> ", matr->n)) return nullptr;

		if (matr->n > 2147483647 / matr->m ||  matr->n * matr->m > 20) {
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



	// функция освобождения занятой памяти
	void erase(Matrix *matr) {
		delete[] matr->items;
		delete matr;
	}



	// функция вывода в консоль матрицы
	void output(const char* msg, Matrix* matr) {
		std::cout << std::endl << msg << std::endl;
		// std::cout.setf(std::ios::fixed);    // вывод строго в десятичном формате (выглядит неровно, тк нули остаются нулями, без знаков после запятой)
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



	// функия выделения памяти и ввода матрицы для варианта ввода полностью вручную
	// возвращет 1, если все удачно, и 0, если не хватает памяти / проблема со вводом
	// если проблема с пямятью, матрица из функции выходит уже очищенная
	int input_all_matrix(Matrix* matr) {
		// сначала выделяем память под 20% или 50% от кол-ва элементов
		int size = 0;
		// если человеку приспичило сделать матрицу больше, чем вмещает инт
		if (matr->n > 2147483647 / matr->m) size = 1000000;
		else {
			int full_size = matr->n * matr->m;
			size = (full_size > 100) ? (full_size / 10) : (full_size / 2 + 1);
		}
		do {
			// выделяем память под массив, если неудача, уменьшаем количество элементов в 2 раза
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
				if (getNum(temp) < 0) {   // проблема с вводом числа
					erase(matr);
					return 0;
				}
				// записываем только ненули
				if (temp != 0) {
					// расширитель памяти, если изначально выделили недостаточно
					if (matr->NZ_items == size) {
						int add_items = 5;
						NZItem* new_arr = nullptr;
						do {
							new_arr = resize_array(matr->items, size, size + add_items--);
						} while (!new_arr && add_items > 0);
						if (!new_arr) {
							// не выделилась память даже под один элемент, завершение
							std::cout << "Too many items :(" << std::endl;
							erase(matr);
							return 0;
						}
						matr->items = new_arr;
						size += add_items + 1;
					}

					// память успешно выделилась, вставляем новый ненулевой элемент
					matr->items[matr->NZ_items] = { i, j, temp };
					matr->NZ_items++;
				}
			}
		}

		return 1;
	}



	// функция для ввода матрицы в формате (row, column, value) только ненулей
	// возвращает 1, если все удачно, и 0, если не хватает памяти / проблема со вводом
	int input_only_not_zeros(Matrix* matr) {
		std::cout << "Input number of not zero items --> ";
		const char* pr = "";    // будущее сообщение об ошибке
		do {
			std::cout << pr << std::endl;
			pr = "Number of not zero items must be bigger than 0";
			if (getNum(matr->NZ_items) < 0) return 0;
		} while (matr->NZ_items <= 0);

		// если человеку приспичит впихнуть 1000 элементов в матрицу 5*5
		if (matr->NZ_items > matr->m * matr->n) matr->NZ_items = matr->m * matr->n;
		if(!new_array(matr->items, matr->NZ_items)) return 0;     // выделение памяти

		// ввод самих чисел
		for (int i = 0; i < matr->NZ_items; i++) {
			std::cout << "Input row, column and value of not zero item #" << i + 1 << " --> ";
			NZItem* temp = matr->items + i;
			if (getNum(temp->row) < 0 || getNum(temp->column) < 0 || getNum(temp->value) < 0) {
				// проблема с вводом числа
				erase(matr);
				return 0;
			}

			// проверки на случай, если пользователь тупой
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

			// сортировка вставками (сначала сдвигаем до нужного ряда)
			while (temp > matr->items && temp->row < (temp - 1)->row) {
				temp = swap_left(temp);
			}
			while (temp > matr->items && temp->column < (temp - 1)->column) {
				temp = swap_left(temp);
			}
		}
		return 1;
	}



	// функция создания новой матрицы:
	// поменяв в каждой строке местами i-ый и j-ый элементы, где i – индекс первого элемента строки матрицы, превышающего предыдущий, 
	// а j – индекс последнего элемента строки матрицы, меньшего, чем предыдущий.
	Matrix* change_items_in_matrix(Matrix* matr) {

		// создаем каркас новой матрицы, следим, чтобы память не кончилась
		Matrix* new_matr = new Matrix({ matr->m, matr->n, matr->NZ_items, nullptr });
		if(!new_array(new_matr->items, new_matr->NZ_items)) return nullptr;

		// собственно, основной алгоритм
		// результатом выполнения будут 2 числа - I и J номера столбцов, а также 2 указателя
		// указатели на эти ячейки, которые надо поменять местами. Если ноль, то указатель пустой, если не ноль, то указатель рабочий
		int I = -1, J = -1;
		NZItem* I_ptr = nullptr, * J_ptr = nullptr;
		NZItem* new_matr_ptr = new_matr->items;
		NZItem* ptr = matr->items;            // указатель, который будет бегать по массиву 
		int start_line_offset = 0;   // сдвиг указателя относительно начала массива (первый неноль в данной строке)
		int end_line_offset = 0;     // сдвиг указателя относительно начала массива (последний неноль в данной строке)

		for (int i = 0; i < matr->m; ++i) {
			// если рассмотрели уже все ненули, а матрица не кончилась, завершаем цикл
			if (start_line_offset == matr->NZ_items) break;
			ptr = matr->items + start_line_offset;
			if (ptr->row != i) continue;     // если в данной строке нет ненулей, переходим на следующую
			new_matr_ptr = new_matr->items + start_line_offset;

			// на этом моменте можем быть уверенными, что в строке есть ненулевой элемент
			I_ptr = find_I_item_in_a_row(matr, ptr, i, I);

			// переводим указатель на первый в следующей строке неноль
			while (ptr < matr->items + matr->NZ_items - 1 && (ptr + 1)->row == i) ptr++;
			end_line_offset = ptr - matr->items;    // Запоминаем номер последнего ненуля в данной строке
			// теперь ptr указывает на последний неноль в строке, мы готовы искать J

			J_ptr = find_J_item_in_a_row(matr, ptr, i, J);

			//std::cout << std::endl << "row = " << i << " I = " << I << " J = " << J << std::endl;
			
			// копируем из старого массива в новый с учетом перемен мест
			// копируем все от start_ptr до next_row_ptr 
			// 4 варианта, как придется менять местами:

			// (1) если один из I или J не существует, тогда пропускаем и ничего не делаем
			if (I == -1 || J == -1) 
				simple_copy(matr->items, new_matr->items, start_line_offset, end_line_offset);

			// (2) вариант - один ноль, второй не ноль, надо сдвигать (самое сложное копирование)
			else if (I_ptr && !J_ptr || J_ptr && !I_ptr) {
				// заранее разбираемся, кто ноль, а кто не ноль
				NZItem* not_zero = nullptr;
				int zero_column = -1;
				if (I_ptr) { not_zero = I_ptr; zero_column = J; }
				else { not_zero = J_ptr; zero_column = I; }

				ptr = matr->items + start_line_offset;
				//new_matr_ptr = new_matr->items + temp_line_offset;
				int flag = false;    // флаг = 0, пока неноль не перемещен, = 1 после перемещения
				for (int k = start_line_offset; k <= end_line_offset; k++, ptr++, new_matr_ptr++) {

					// неноль надо впихнуть на место нуля - находим ближайший слева от него неноль
					// сюда входят случаи: ptr - последний в матрице / последний в строке / последний перед тем, куда надо вставить тот
					if (!flag && (k == end_line_offset || (ptr + 1)->column >= zero_column || (ptr + 1)->row != i)) {
						// сначала копируем текущее значение, если это не not_zero
						if (ptr->column != not_zero->column) {
							*new_matr_ptr = { i, ptr->column, ptr->value };
							new_matr_ptr++;
						}

						// после него вставляем not_zero
						*new_matr_ptr = { i, zero_column, not_zero->value };
						flag = true;   // чтобы случайно не вставить несколько раз
					}
					// неноль, который перемещаем, копировать не надо
					else if (ptr->column == not_zero->column)
						new_matr_ptr--;
					// если мы далеко от I и J, тогда копируем обычным способом
					else *new_matr_ptr = { i, ptr->column, ptr->value };
				}
			}

			else {
				// (3) если оба не нули, меняем местами значения в ячейках в исходной матрице, копируем в новую, потом меняем в исходной обратно
				// короче, пользуемся тем, что у нас сохранены указатели на эти ячейки, нам не нужно искать их заново
				if (I_ptr && J_ptr) swap(I_ptr->value, J_ptr->value);

				
				// (3) если оба нуля, то ничего не делаем
				simple_copy(matr->items, new_matr->items, start_line_offset, end_line_offset);

				// возвращаем I и J в исходной матрице на место
				if (I_ptr && J_ptr) swap(I_ptr->value, J_ptr->value);
			}
			
			start_line_offset = ++end_line_offset;
		}

		return new_matr;
	}



	// идея: не нужно перебирать каждый элемент строки подряд, достаточно рассматривать только каждый неноль и двух его соседей (то есть смотрим на тройки)
	// рассматриваем строку, пока в ней не закончатся ненули
	// пользуемся тем, что внутри массива ненулей числа отсортированы, как они расположены в строке - слева направо
	// еще идея: так как спрашивают только первый и последний, нам не надо рассматривать все промежуточные ненули
	// такой метод будет плох, только если вся строка состоит из равных ненулевых чисел (но это вряд ли, тк матрица разреженная)



	// функция находит номер I столбца элемента (первый, который больше, чем предыдущий)
	// если это ноль, возвращает нулевой указатель, если не ноль, то действующий указатель
	NZItem* find_I_item_in_a_row(Matrix* matr, NZItem *&ptr, int temp_row, int& I) {
		// слева направо ищем первый больший предыдущего
		while (ptr < matr->items + matr->NZ_items && ptr->row == temp_row) {
			int column = ptr->column;
			// если ptr не крайний слева, сравниваем значение с левым соседом
			if (column != 0) {
				NZItem* prev = (ptr == matr->items) ? nullptr : (ptr - 1);
				double left_value = (prev && prev->row == temp_row && prev->column == column - 1) ? prev->value : 0;

				// смотрим, что больше, и меняем I, если повезло
				if (ptr->value > left_value) {
					I = column;
					return ptr;
				}
			}

			// если ptr не крайний справа, сравниваем значение с правым соседом
			if (column != matr->n - 1) {
				NZItem* next = (ptr == matr->items + matr->NZ_items) ? nullptr : (ptr + 1);
				double right_value = (next && next->row == temp_row && next->column == column + 1) ? next->value : 0;

				// смотрим, что больше, и меняем I
				if (right_value > ptr->value) {
					I = column + 1;
					return (right_value ? next : nullptr);
				}
			}
			ptr++;
		}
		ptr--;
		I = -1;
		return nullptr;  // если не нашлось такого числа
	}



	// функция находит номер J столбца элемента (последний, который меньше, чем предыдущий)
	// если это ноль, возвращает нулевой указатель, если не ноль, то действующий указатель
	NZItem* find_J_item_in_a_row(Matrix* matr, NZItem*& ptr, int temp_row, int& J) {
		for (; ptr >= matr->items && ptr->row == temp_row; ptr--) {
			int column = ptr->column;

			// если ptr не крайний справа, сравниваем значение с правым соседом
			if (column != matr->n - 1) {
				NZItem* next = (ptr == matr->items + matr->NZ_items - 1) ? nullptr : (ptr + 1);
				double right_value = (next && next->row == temp_row && next->column == column + 1) ? next->value : 0;

				// смотрим, что больше, и меняем J
				if (right_value < ptr->value) {
					J = column + 1;
					return (right_value ? next : nullptr);
				}
			}

			// если ptr не крайний слева, сравниваем значение с левым соседом
			if (column != 0) {
				NZItem* prev = (ptr == matr->items) ? nullptr : (ptr - 1);
				double left_value = (prev && prev->row == temp_row && prev->column == column - 1) ? prev->value : 0;

				// смотрим, что больше, и меняем I, если повезло
				if (ptr->value < left_value) {
					J = column;
					return ptr;
				}
			}
		}
		J = -1;
		return nullptr;
	}



	// функция копирования нескольких ненулей из старого массива в новый без изменений
	void simple_copy(NZItem *old_array, NZItem* new_array, int start_offset, int finish_offset) {
		for (int i = start_offset; i <= finish_offset; i++) {
			NZItem* temp = old_array + i;
			new_array[i] = { temp->row, temp->column, temp->value };
		}
	}
}
