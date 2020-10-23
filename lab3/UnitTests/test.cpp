#include "gtest/gtest.h"
#include "..\Dynamic\TimeDiagram_dynamic.h"

using namespace lab3;

TEST(SignalConstructor, InitConstructor) {
	Signal sig(1, 3);
	ASSERT_EQ(1, sig.state);
	ASSERT_EQ(3, sig.duration);

	Signal sig2(X);
	ASSERT_EQ(2, sig2.state);
	ASSERT_EQ(1, sig2.duration);
	
	ASSERT_ANY_THROW(Signal sig3(5, 5));
	ASSERT_ANY_THROW(Signal sig4(0, -5));
}

TEST(TimeDiagramConstructor, DefaultConstructor) {
	lab3::TimeDiagram td;
	ASSERT_EQ(0, td.get_Temp_Duration());
	ASSERT_EQ(Signal(0, 0), td.get_Signals()[0]);
}

TEST(TimeDiagramConstructor, StringConstructor) {
	std::string s1("1100XX10X");
	lab3::TimeDiagram td(s1);
	ASSERT_EQ(9, td.get_Temp_Duration());
	ASSERT_EQ(6, td.get_Num_of_Signals());
	ASSERT_EQ(Signal(X, 2), td.get_Signals()[2]);

	std::string s2("15010100");
	ASSERT_ANY_THROW(lab3::TimeDiagram td2(s2));

	std::string s3('1', 151);
	ASSERT_ANY_THROW(lab3::TimeDiagram td3(s3));

	std::string s4("");
	TimeDiagram td4(s4);
	ASSERT_EQ(0, td4.get_Num_of_Signals());
}

TEST(TimeDiagramConstructor, ConstantConstructor) {
	lab3::TimeDiagram td(1);
	ASSERT_EQ(td.get_Max_Duration(), td.get_Temp_Duration());
	ASSERT_EQ(1, td.get_Num_of_Signals());
	ASSERT_EQ(Signal(1, td.get_Max_Duration()), td.get_Signals()[0]);

	ASSERT_ANY_THROW(lab3::TimeDiagram td2(-1));
}

TEST(TimeDiagramConstructor, ArrayConstructor) {
	Signal signals[5] = { Signal(1, 5), Signal(0, 1), Signal(X, 3), Signal(X, 4), Signal(1, 4) };
	TimeDiagram td(signals, 5);
	ASSERT_EQ(17, td.get_Temp_Duration());
	ASSERT_EQ(4, td.get_Num_of_Signals());
	ASSERT_EQ(Signal(X, 7), td.get_Signals()[2]);
}

TEST(TimeDiagramOperator, ConcatOperator) {
	std::string s1("1111000XX00X");
	std::string s2("XX1110X0XX");
	TimeDiagram td = TimeDiagram(s1) + TimeDiagram(s2);

	ASSERT_EQ(s1.size() + s2.size(), td.get_Temp_Duration()); 
	ASSERT_EQ(10, td.get_Num_of_Signals());
	ASSERT_EQ(Signal(1, 3), td.get_Signals()[5]);

	std::string s3('0', 140);
	ASSERT_ANY_THROW(TimeDiagram td2 = TimeDiagram(s1) + TimeDiagram(s3));
}

TEST(TimeDiagramOperator, MultiplicationOperator) {
	std::string s("1111000XX00XX1");
	TimeDiagram td(s);
	td *= 2;

	ASSERT_EQ(s.size() * 2, td.get_Temp_Duration());
	ASSERT_EQ(11, td.get_Num_of_Signals());
	ASSERT_EQ(Signal(X, 2), td.get_Signals()[7]); 
	ASSERT_ANY_THROW(td *= -1);
	ASSERT_ANY_THROW(td *= 8);
}

TEST(TimeDiagramOperator, InsertOperator) {
	std::string s1("1111000XX00XX1"); 
	std::string s2("XX1110X0XX");
	TimeDiagram td1(s1);
	TimeDiagram td2(s2);

	ASSERT_ANY_THROW(TimeDiagram res1 = td1(td2, -8));
	ASSERT_ANY_THROW(TimeDiagram res2 = td1(td2, 15));

	TimeDiagram res3 = td1(td2, 8);
	ASSERT_EQ(8, res3.get_Num_of_Signals());
	ASSERT_EQ(s2.size() + 8, res3.get_Temp_Duration());
	ASSERT_EQ(Signal(X, 3), res3.get_Signals()[2]);

	TimeDiagram res4 = res3(td2, 0); 
	ASSERT_EQ(6, res4.get_Num_of_Signals());
	ASSERT_EQ(s2.size(), res4.get_Temp_Duration());
	ASSERT_EQ(Signal(0, 1), res4.get_Signals()[2]);
}

TEST(TimeDiagramOperator, ShiftOperators) {
	std::string s("1111000XX00XX1");

	TimeDiagram left = TimeDiagram(s) <<= 6;
	ASSERT_EQ(5, left.get_Num_of_Signals());
	ASSERT_EQ(s.size() - 6, left.get_Temp_Duration());
	ASSERT_EQ(Signal(0, 1), left.get_Signals()[0]);

	TimeDiagram rigth = TimeDiagram(s) >>= 6;
	ASSERT_EQ(7, rigth.get_Num_of_Signals());
	ASSERT_EQ(s.size() + 6, rigth.get_Temp_Duration());
	ASSERT_EQ(Signal(X, 6), rigth.get_Signals()[0]);

	ASSERT_ANY_THROW(left >>= -1);
	ASSERT_ANY_THROW(rigth <<= -5);
}


int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
