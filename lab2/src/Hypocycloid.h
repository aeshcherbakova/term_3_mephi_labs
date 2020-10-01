#ifndef _HYPOCYCLOID_
#define _HYPOCYCLOID_

#include <iostream>
#include <math.h>
#include <limits>

namespace lab2 {

	const char* exceptions[];   //массив диагностических сообщений об ошибках
	const char* menu[];         //меню
	extern const int NMsgs;     //выбор номера альтернативы из меню


	// структура Point задает координаты точки на плоскости
	struct Point {
		double x, y; // координаты точки на плоскости
		Point(double x0 = 0, double y0 = 0) :x(x0), y(y0) {}   // пустой конструктор, просто чтобы мусора не было

		// перегрузка оператора, чтобы меньше писать в тестах (public по умолчанию)
		friend bool operator==(const Point& a, const Point& b) {
			return (a.x == b.x && a.y == b.y);
		}
	};


	class Hypocycloid {

	private:
		double r_ex, r_in;   // радиусы внешней/направл€ющей (external) и внутренней/производ€щей (internal) окружностей
		double d;            // рассто€ние от точки, описывающей гипоциклоиду, до центра производ€щего круга

	public:
		// конструкторы
		Hypocycloid(double k = 3);  // пустой конструктор, определ€етс€ коэффициентом k - отношением внешнего радиуса к внутреннему
		Hypocycloid(double R, double r);
		Hypocycloid(double R, double r, double d);

		// сеттеры
		Hypocycloid& setR_EX(double R);
		Hypocycloid& setR_IN(double r);        
		Hypocycloid& setD(double d) { Hypocycloid::d = d; return *this; }    // вроде как нет ограничений

		// геттеры
		double getR_EX() const { return r_ex; }
		double getR_IN() const { return r_in; }
		double getD() const { return d; }

		// другие методы
		const char* type() const;
		// функци€ возвращает радиусы ограничивающих гипоциклоиду окружностей
		// возвращаемые радиусы записаны в структуру "точка" - сначала внешний, а потом внутренний
		Point limiting_radii() const { return { abs(r_ex - r_in + d), abs(r_ex - r_in - d) }; }  
		Point point_from_angle(double alpha) const;
		double curvature_radius(double alpha) const;
		double area(double alpha) const;

	};  // class Hypocycloid


	// шаблон функций ввода одного значени€ произвольного типа
	template <class T>
	int getNum(T& a, std::istream& c = std::cin) {
		do {
			c >> a;
			if (c.eof()) return 0;     // обнаружен конец файла
			if (!c.good()) {          // обнаружена ошибка ввода     
				c.clear();
				c.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			} else return 1;
		} while (1);
	}


	// функци€ вывода на экран параметров гипоциклоиды (которые не завис€т от угла)
	void print_parameters(const Hypocycloid& h, std::ostream& c);


	// массив диалоговых функций
	int (*fptr[])(const Hypocycloid&, std::istream&, std::ostream&);

	int D_find_point(const Hypocycloid&, std::istream & = std::cin, std::ostream & = std::cout),
		D_curvature_radius(const Hypocycloid&, std::istream & = std::cin, std::ostream & = std::cout),
		D_sectorial_area(const Hypocycloid&, std::istream & = std::cin, std::ostream & = std::cout);

	// другие диалоговые функции
	int dialog(std::istream& istr = std::cin, std::ostream& ostr = std::cout);
	int D_change_params(Hypocycloid&, std::istream & = std::cin, std::ostream & = std::cout);
	int D_input_angle(double&, std::istream& = std::cin, std::ostream& = std::cout);
}

#endif
