#include "pch.h"
#include "Hypocycloid.h"

namespace lab2 {

	const char* exceptions[]{
		"External radius must be bigger than 0",
		"Internal radius must be bigger than 0",
		"Internal radius must be less than external",
		"Coefficient must be bigger than 0"
	};

	// конструкторы
	Hypocycloid::Hypocycloid(double k) {
		if (k <= 0) throw std::exception(exceptions[3]);
		r_ex = k, r_in = 1, d = 1;
	}

	Hypocycloid::Hypocycloid(double R, double r) {
		if (R <= 0) throw std::exception(exceptions[0]);
		if (r <= 0) throw std::exception(exceptions[1]);
		if (r >= R) throw std::exception(exceptions[2]);
		r_ex = R, r_in = r, d = r;    // если d не указано, по умолчанию считаем гипоциклоиду обыкновенной
	}

	Hypocycloid::Hypocycloid(double R, double r, double d) {
		if (R <= 0) throw std::exception(exceptions[0]);
		if (r <= 0) throw std::exception(exceptions[1]);
		if (r >= R) throw std::exception(exceptions[2]);
		r_ex = R, r_in = r, Hypocycloid::d = d;
	}


	// сеттеры
	Hypocycloid& Hypocycloid::setR_EX(double R) {
		if (R <= 0) throw std::exception(exceptions[0]);
		r_ex = R;
		return *this;
	}
	
	Hypocycloid& Hypocycloid::setR_IN(double r) {
		if (r >= r_ex) throw std::exception(exceptions[2]);
		if (r <= 0) throw std::exception(exceptions[1]);
		r_in = r;
		return *this;
	}


	// другие методы

	// функция возвращает тип гипоциклоиды: обыкновенная, если d = r; удлиненная, если d > r; укороченная, если d < r
	const char* Hypocycloid::type() const {
		const char* s = "";
		if (d < r_in) s = "Shortened";
		else if (d > r_in) s = "Elongated";
		else s = "Ordinary";
		return s;
	}

	// функция возвращет радиус кривизны гипоциклоиды в зависимости от угла поворота альфа
	// если происходит деление на ноль, возвращает -1
	double Hypocycloid::curvature_radius(double alpha) const {
		double cosine = (alpha == 0) ? 1 : cos(r_ex * alpha / r_in);
		double numerator = pow(r_in * r_in + d * d - 2 * d * r_in * cosine, 1.5);
		if (numerator == 0) return 0;
		double denominator = -pow(r_in, 3) + d * d * (r_ex - r_in) - d * r_in * (r_ex - 2 * r_in) * cosine;
		if (denominator == 0) return -1;
		double res = (r_ex - r_in) * numerator / abs(denominator);
		return res;
	}

	// функция возвращает секториальную площадь гипоциклоиды в зависимости от угла поворота альфа внутреннего круга
	double Hypocycloid::area(double alpha) const {
		if (alpha == 0) return 0;
		double sine = sin(r_ex * alpha / r_in);
		double bracket = alpha * (r_ex - r_in - d * d / r_in) + d * (r_ex - 2 * r_in) * sine / r_ex;
		return (r_ex - r_in) * bracket / 2;
	}

	// функция возвращает координаты точки, принадлежащей циклоиде в пдск, соответствующей углу альфа
	// просто подставляем этот угол в параметрическую формулу (проверено по построителю)
	Point Hypocycloid::point_from_angle(double alpha) const {
		double x = (r_ex - r_in) * cos(alpha) + d * cos(alpha * (r_ex - r_in) / r_in);
		double y = (r_ex - r_in) * sin(alpha) - d * sin(alpha * (r_ex - r_in) / r_in);
		Point res = { x, y };
		return res;
	}

}


