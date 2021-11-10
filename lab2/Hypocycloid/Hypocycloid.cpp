#include "pch.h"
#include "Hypocycloid.h"

namespace lab2 {

	const char* exceptions[]{
		"External radius must be bigger than 0",
		"Internal radius must be bigger than 0",
		"Internal radius must be less than external",
		"Coefficient must be bigger than 0"
	};

	Hypocycloid::Hypocycloid(double k) {
		if (k <= 0) throw std::exception(exceptions[3]);
		r_ex = k, r_in = 1, d = 1;
	}

	Hypocycloid::Hypocycloid(double R, double r) {
		if (R <= 0) throw std::exception(exceptions[0]);
		if (r <= 0) throw std::exception(exceptions[1]);
		if (r >= R) throw std::exception(exceptions[2]);
		r_ex = R, r_in = r, d = r;    // if d is not specified, by default we consider the ordinary hypocycloid
	}

	Hypocycloid::Hypocycloid(double R, double r, double d) {
		if (R <= 0) throw std::exception(exceptions[0]);
		if (r <= 0) throw std::exception(exceptions[1]);
		if (r >= R) throw std::exception(exceptions[2]);
		r_ex = R, r_in = r, Hypocycloid::d = d;
	}


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


	// the function returns the type of hypocycloid: ordinary, if d = r; elongated if d> r; truncated if d <r
	const char* Hypocycloid::type() const {
		const char* s = "";
		if (d < r_in) s = "Shortened";
		else if (d > r_in) s = "Elongated";
		else s = "Ordinary";
		return s;
	}

	// return the radius of curvature of the hypocycloid depending on the rotation angle alpha
	// if division by zero, returns -1
	double Hypocycloid::curvature_radius(double alpha) const {
		double cosine = (alpha == 0) ? 1 : cos(r_ex * alpha / r_in);
		double numerator = pow(r_in * r_in + d * d - 2 * d * r_in * cosine, 1.5);
		if (numerator == 0) return 0;
		double denominator = -pow(r_in, 3) + d * d * (r_ex - r_in) - d * r_in * (r_ex - 2 * r_in) * cosine;
		if (denominator == 0) return -1;
		double res = (r_ex - r_in) * numerator / abs(denominator);
		return res;
	}

	// calculate sectorial area of the hypocycloid depending on the rotation angle alpha of the inner circle
	double Hypocycloid::area(double alpha) const {
		if (alpha == 0) return 0;
		double sine = sin(r_ex * alpha / r_in);
		double bracket = alpha * (r_ex - r_in - d * d / r_in) + d * (r_ex - 2 * r_in) * sine / r_ex;
		return (r_ex - r_in) * bracket / 2;
	}

	//calculate coordinates of the point belonging to the cycloid in pdsk, corresponding to the angle alpha
	// just substitute this angle into the parametric formula (checked by the builder)
	Point Hypocycloid::point_from_angle(double alpha) const {
		double x = (r_ex - r_in) * cos(alpha) + d * cos(alpha * (r_ex - r_in) / r_in);
		double y = (r_ex - r_in) * sin(alpha) - d * sin(alpha * (r_ex - r_in) / r_in);
		Point res = { x, y };
		return res;
	}

}