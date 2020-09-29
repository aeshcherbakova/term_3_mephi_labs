//#include <exception>
#include <strstream>
#include <cmath>
#include "Hypocycloid.h"

namespace lab2 {

	const char* exceptions[]{
		"External radius must be bigger than 0",
		"Internal radius must be bigger than 0",
		"Internal radius must be less than external"
	};

	const char* menu[]{
		"0. Quit",
		"1. Calculate coordinates of a point",
		"2. Calculate radius of curvature",
		"3. Calculate sectorial area",
		"4. Create new hypocycloid"
	};

	const int NMsgs = sizeof(menu) / sizeof(menu[0]);

	int (*fptr[])(const Hypocycloid&, std::istream&, std::ostream&) = { NULL, D_find_point, D_curvature_radius, D_sectorial_area };


	// конструкторы
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
	Hypocycloid& Hypocycloid::setR_IN(double r) {
		if (r >= r_ex) throw std::exception(exceptions[2]);
		if (r <= 0) throw std::exception(exceptions[1]);
		r_in = r;
		return *this;
	}

	Hypocycloid& Hypocycloid::setR_EX(double R) {
		if (R <= 0) throw std::exception(exceptions[0]);
		r_ex = R;
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
	double Hypocycloid::curvature_radius(double alpha) const {
		double cosine = cos(r_ex * alpha / r_in);
		double numerator = pow(r_in * r_in + d * d - 2 * d * r_in * cosine, 3 / 2);
		double denominator = -pow(r_in, 3) + d * d * (r_ex - r_in) - d * r_in * (r_ex - 2 * r_in) * cosine;
		return (r_ex - r_in) * numerator / abs(denominator);
	}

	// функция возвращает секториальную площадь гипоциклоиды в зависимости от угла поворота альфа внутреннего круга
	double Hypocycloid::area(double alpha) const {
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


	// *******    просто функции вне класса    *******


	// вывод на экран всех параметров гипоциклоиды, зависящих только от радиусов и d
	void print_parameters(const Hypocycloid& h, std::ostream& c) {
		c << std::endl << "Your hypocycloid parameters:" << std::endl;
		c << "R = " << h.getR_EX() << ", r = " << h.getR_IN() << ", d = " << h.getD()<< std::endl;

		// вывод типа гипоциклоиды
		const char* s = h.type();
		c << "Type: " << s << std::endl;
		// delete[] s;

		// вывод на экран результат вычисления ограничивающих радиусов
		Point res = h.limiting_radii();
		c << "External radius = " << res.x << ", internal radius = " << res.y << std::endl;
	}



	//  ****    диалоговые функции   ****

	int D_input_angle(double& alpha, std::istream& istr, std::ostream& ostr) {
		// угол может быть отрицательным, нулевым или вообще очень большим, короче, нет ограничений
		ostr << "Input angle from starting point --> ";
		if (!getNum(alpha, istr)) return 0;
		return 1;
	}

	int D_find_point(const Hypocycloid& h, std::istream& istr, std::ostream& ostr) {
		double alpha = 0;
		if (!D_input_angle(alpha, istr, ostr)) return 0;   
		Point res = h.point_from_angle(alpha);
		ostr << "Result: (" << res.x << ", " << res.y << ")" << std::endl;
		return 1;
	}

	int D_curvature_radius(const Hypocycloid& h, std::istream& istr, std::ostream& ostr) {
		double alpha = 0;
		if (!D_input_angle(alpha, istr, ostr)) return 0;
		double res = h.curvature_radius(alpha);
		ostr << "Curvature radius = " << res << std::endl;
		return 1;
	}

	int D_sectorial_area(const Hypocycloid& h, std::istream& istr, std::ostream& ostr) {
		double alpha = 0;
		if (!D_input_angle(alpha, istr, ostr)) return 0;
		double res = h.area(alpha);
		ostr << "Area of the sector = " << res << std::endl;
		return 1;
	}

	// диалоговая функция создания новой гипоциклоиды (по факту просто изменяем состояние старой)
	int D_change_params(Hypocycloid& h, std::istream& istr, std::ostream& ostr) {
		double R = 0, r = 0, d = 0;
		// изменение внешнего радиуса
		do {
			ostr << "Input extern radius --> ";
			if (!getNum(R, istr)) return 0;
			try { h.setR_EX(R); }
			catch (std::exception& ex) { R = 0, ostr << ex.what() << std::endl; }
		}  while (R == 0);

		// изменение внутреннего радиуса
		do {
			ostr << "Input intern radius --> ";
			if (!getNum(r, istr)) return 0;
			try { h.setR_IN(r); }
			catch (std::exception& ex) { r = 0, ostr << ex.what() << std::endl; }
		} while (r == 0);

		// изменение расстояния d (setD не выкидывает исключений, так что без цикла можно)
		ostr << "Input distance from main point on the inner circle to the centre of the outer circle --> ";
		if (!getNum(d, istr)) return 0;
		h.setD(d);

		// вывод параметров новой гипоциклоиды, типа и ограничивающих радиусов
		print_parameters(h, ostr);
		return 1;
	}

	//функция для выбора правильной альтернативы, возвращает номер правильной альтернативы
	int dialog(std::istream& istr, std::ostream& ostr) {
		const char* errmsg = "";
		int input;
		do {
			ostr << errmsg << std::endl;
			errmsg = "You are wrong. Repeate, please!";
			for (int i = 0; i < NMsgs; ++i)
				ostr << menu[i] << std::endl;
			ostr << std::endl << "Make your choice: --> ";
			if (!getNum(input)) return 0;
		} while (input < 0 || input >= NMsgs);
		return input;
	}



}




