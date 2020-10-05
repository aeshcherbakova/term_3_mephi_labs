#pragma once

#include <iostream>
#include <limits>
#include "../Hypocycloid/Hypocycloid.h"

namespace lab2 {

	const char* menu[];         //меню
	extern const int NMsgs;     //выбор номера альтернативы из меню


	// шаблон функций ввода одного значения произвольного типа
	template <class T>
	int getNum(T& a, std::istream& c = std::cin) {
		do {
			c >> a;
			if (c.eof()) return 0;                        // обнаружен конец файла
			if (!c.good() || c.peek() != '\n') {          // обнаружена ошибка ввода     
				c.clear();
				c.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else return 1;
		} while (1);
	}


	// функция вывода на экран параметров гипоциклоиды (которые не зависят от угла)
	void print_parameters(const Hypocycloid& h, std::ostream& c);


	// массив диалоговых функций
	int (*fptr[])(const Hypocycloid&, std::istream&, std::ostream&);

	int D_find_point(const Hypocycloid&, std::istream & = std::cin, std::ostream & = std::cout),
		D_curvature_radius(const Hypocycloid&, std::istream & = std::cin, std::ostream & = std::cout),
		D_sectorial_area(const Hypocycloid&, std::istream & = std::cin, std::ostream & = std::cout);

	// другие диалоговые функции
	int dialog(std::istream& istr = std::cin, std::ostream& ostr = std::cout);
	int D_change_params(Hypocycloid&, std::istream & = std::cin, std::ostream & = std::cout);
	int D_input_angle(double&, std::istream & = std::cin, std::ostream & = std::cout);

}
