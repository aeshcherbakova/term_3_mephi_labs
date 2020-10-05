#pragma once

#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows

#include <strstream>
#include <cmath>

namespace lab2 {

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
		double r_ex, r_in;   // радиусы внешней/направляющей (external) и внутренней/производящей (internal) окружностей
		double d;            // расстояние от точки, описывающей гипоциклоиду, до центра производящего круга

	public:
		// конструкторы
		Hypocycloid(double k = 3);  // пустой конструктор, определяется коэффициентом k - отношением внешнего радиуса к внутреннему
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
		// функция возвращает радиусы ограничивающих гипоциклоиду окружностей
		// возвращаемые радиусы записаны в структуру "точка" - сначала внешний, а потом внутренний
		Point limiting_radii() const { return { abs(r_ex - r_in + d), abs(r_ex - r_in - d) }; }
		Point point_from_angle(double alpha) const;
		double curvature_radius(double alpha) const;
		double area(double alpha) const;

	};  // class Hypocycloid


} // lab2 namespace
