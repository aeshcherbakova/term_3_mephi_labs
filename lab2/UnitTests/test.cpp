#include "pch.h"
#include "../Hypocycloid/Hypocycloid.h"

TEST(HypocycloidConstructor, DefaultConstructor)
{
	lab2::Hypocycloid h1;
	ASSERT_EQ(3, h1.getR_EX());
	ASSERT_EQ(1, h1.getR_IN());
	ASSERT_EQ(1, h1.getD());
}

TEST(HypocycloidConstructor, InitConstructors)
{
	lab2::Hypocycloid h2(5);
	ASSERT_EQ(5, h2.getR_EX());
	ASSERT_EQ(1, h2.getR_IN());
	ASSERT_EQ(1, h2.getD());

	lab2::Hypocycloid h3(5, 3);
	ASSERT_EQ(5, h3.getR_EX());
	ASSERT_EQ(3, h3.getR_IN());
	ASSERT_EQ(3, h3.getD());

	lab2::Hypocycloid h4(12, 3, 2);
	ASSERT_EQ(12, h4.getR_EX());
	ASSERT_EQ(3, h4.getR_IN());
	ASSERT_EQ(2, h4.getD());
}

TEST(HypocycloidConstructor, TestException)
{
	ASSERT_ANY_THROW(lab2::Hypocycloid(0));
	ASSERT_ANY_THROW(lab2::Hypocycloid(0, 5));
	ASSERT_ANY_THROW(lab2::Hypocycloid(-6, 5));
	ASSERT_ANY_THROW(lab2::Hypocycloid(7, 10));
	ASSERT_ANY_THROW(lab2::Hypocycloid(7, 0));
	
	try { lab2::Hypocycloid(7, -5, 9); }
	catch (std::exception& err) {
		std::cout << err.what();
		EXPECT_EQ(err.what(), std::string("Internal radius must be bigger than 0"));
	}
	catch (...) { FAIL() << "Expected other exception"; }
	//ASSERT_ANY_THROW(lab2::Hypocycloid(7, -5, 9));
}

TEST(HypocycloidMethods, Setters)
{
	lab2::Hypocycloid h;
	h.setR_EX(10);
	ASSERT_EQ(10, h.getR_EX());
	h.setR_IN(9);
	ASSERT_EQ(9, h.getR_IN());
	h.setD(5);
	ASSERT_EQ(5, h.getD());

	ASSERT_ANY_THROW(h.setR_EX(-5));
	ASSERT_ANY_THROW(h.setR_IN(10));
	ASSERT_ANY_THROW(h.setR_IN(0));
	ASSERT_ANY_THROW(h.setR_IN(-12));
}

TEST(HypocycloidMethods, Parameters)
{
	lab2::Hypocycloid a;
	lab2::Hypocycloid b(5, 4, 6);
	lab2::Hypocycloid c(5, 4, 3);

	ASSERT_STREQ("Ordinary", a.type());
	ASSERT_STREQ("Elongated", b.type());
	ASSERT_STREQ("Shortened", c.type());

	ASSERT_EQ(lab2::Point(3, 1), a.limiting_radii());
	ASSERT_EQ(lab2::Point(7, 5), b.limiting_radii());
	ASSERT_EQ(lab2::Point(4, 2), c.limiting_radii());
}

TEST(HypocycloidMethods, Angle)
{
	const double err = 0.0001;
	double pi = 3.14159;
	lab2::Hypocycloid a;
	lab2::Hypocycloid b(10, 2, 3);
	lab2::Hypocycloid c(5, 4);

	ASSERT_NEAR(8, a.curvature_radius(pi), err);   
	ASSERT_NEAR(0.2857, b.curvature_radius(0), err);
	ASSERT_NEAR(5.0612, c.curvature_radius(2), err);

	ASSERT_NEAR(3, a.point_from_angle(0).x, err);
	ASSERT_NEAR(0, a.point_from_angle(0).y, err);
	ASSERT_NEAR(-5.388378, b.point_from_angle(3).x, err);
	ASSERT_NEAR(2.738678, b.point_from_angle(3).y, err);
	ASSERT_NEAR(-3, c.point_from_angle(-4 * pi).x, err);
	ASSERT_NEAR(0, c.point_from_angle(-4 * pi).y, err);

	ASSERT_NEAR(0, a.area(0), err);
	ASSERT_NEAR(29.191129, b.area(0.5 * pi), err);
	ASSERT_NEAR(-10.624769, c.area(2 * pi), err);
}


int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}