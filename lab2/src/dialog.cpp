#include "dialog.h"

namespace lab2 {

	const char* menu[]{
		"0. Quit",
		"1. Calculate coordinates of a point",
		"2. Calculate radius of curvature",
		"3. Calculate sectorial area",
		"4. Create new hypocycloid"
	};

	const int NMsgs = sizeof(menu) / sizeof(menu[0]);

	int (*fptr[])(const Hypocycloid&, std::istream&, std::ostream&) = { NULL, D_find_point, D_curvature_radius, D_sectorial_area };


	int D_input_angle(double& alpha, std::istream& istr, std::ostream& ostr) {
		// the angle can be negative, zero or even very large, in short, there are no restrictions
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
		// the function returned -1 if division by zero occurred
		if (res == -1) ostr << "Curvature radius cannot be calculated in this point :/" << std::endl;
		else ostr << "Curvature radius = " << res << std::endl;
		return 1;
	}

	int D_sectorial_area(const Hypocycloid& h, std::istream& istr, std::ostream& ostr) {
		double alpha = 0;
		if (!D_input_angle(alpha, istr, ostr)) return 0;
		double res = h.area(alpha);
		ostr << "Area of the sector = " << res << std::endl;
		return 1;
	}

	// dialog function for creating a new hypocycloid (in fact, we just change the state of the old one)
	int D_change_params(Hypocycloid& h, std::istream& istr, std::ostream& ostr) {
		double R = 0, r = 0, d = 0;
		// иchange outer radius
		do {
			ostr << "Input extern radius --> ";
			if (!getNum(R, istr)) return 0;
			try { h.setR_EX(R); }
			catch (std::exception& ex) { R = 0, ostr << ex.what() << std::endl; }
		} while (R == 0);

		// change inner radius
		do {
			ostr << "Input intern radius --> ";
			if (!getNum(r, istr)) return 0;
			try { h.setR_IN(r); }
			catch (std::exception& ex) { r = 0, ostr << ex.what() << std::endl; }
		} while (r == 0);

		// changing the distance d (setD does not throw exceptions, so you can do it without a loop)
		ostr << "Input distance from main point on the inner circle to the centre of the outer circle --> ";
		if (!getNum(d, istr)) return 0;
		h.setD(d);

		// вывод параметров новой гипоциклоиды, типа и ограничивающих радиусов
		print_parameters(h, ostr);
		return 1;
	}

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

	// display of all parameters of the hypocycloid, depending only on the radii and d
	void print_parameters(const Hypocycloid& h, std::ostream& c) {
		c << std::endl << "Your hypocycloid parameters:" << std::endl;
		c << "R = " << h.getR_EX() << ", r = " << h.getR_IN() << ", d = " << h.getD() << std::endl;

		const char* s = h.type();
		c << "Type: " << s << std::endl;

		Point res = h.limiting_radii();
		c << "External radius = " << res.x << ", internal radius = " << res.y << std::endl;
	}
}