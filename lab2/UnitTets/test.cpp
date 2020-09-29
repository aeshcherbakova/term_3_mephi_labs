#include "pch.h"
#include "../src/Hypocycloid.h"
#include "../src/Hypocycloid.cpp"

// “естирование конструкторов
TEST(HypocycloidConstructor, DefaultConstructor)
{
	lab2::Hypocycloid h1;
	ASSERT_EQ(1, h1.getR_EX());
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
	ASSERT_ANY_THROW(lab2::Hypocycloid(7, -5, 9));
}

// тестирование сеттеров
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

// тестирование других методов

/*
int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
*/

