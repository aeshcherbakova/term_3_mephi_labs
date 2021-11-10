#pragma once

#define WIN32_LEAN_AND_MEAN          

#include <strstream>
#include <cmath>

namespace lab2 {

	struct Point {
		double x, y; // pdsk coordinates
		Point(double x0 = 0, double y0 = 0) :x(x0), y(y0) {} 

		friend bool operator==(const Point& a, const Point& b) {
			return (a.x == b.x && a.y == b.y);
		}
	};


	class Hypocycloid {

	private:
		double r_ex, r_in;   // exteranl and internal circles' radii
		double d;            // distance from the point describing the hypocycloid to the center of the generating circle

	public:
		// constructors
		Hypocycloid(double k = 3);  // empty constructor, determined by the coefficient k - the ratio of the outer radius to the inner radius
		Hypocycloid(double R, double r);
		Hypocycloid(double R, double r, double d);

		// setters
		Hypocycloid& setR_EX(double R);
		Hypocycloid& setR_IN(double r);
		Hypocycloid& setD(double d) { Hypocycloid::d = d; return *this; } 

		// getters
		double getR_EX() const { return r_ex; }
		double getR_IN() const { return r_in; }
		double getD() const { return d; }

		const char* type() const;
		// function returns the radii of the circles bounding the hypocycloid
		// the returned radii are written into the "point" structure - first outer, then inner
		Point limiting_radii() const { return { abs(r_ex - r_in + d), abs(r_ex - r_in - d) }; }
		Point point_from_angle(double alpha) const;
		double curvature_radius(double alpha) const;
		double area(double alpha) const;

	};  // class Hypocycloid


} // lab2 namespace