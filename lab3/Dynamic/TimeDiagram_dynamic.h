#pragma once

#include <string>
#include <iostream>
#include <stdexcept>

#define X 2   // undefined level of signal (just to be int not char)

namespace lab3 {

	struct Signal {
		int state;           // 1/0/2 (2 = X - undefined state)
		int duration;

		Signal() : state(0), duration(0) {};   // default constructor
		Signal(const int state, const int duration = 1);
		Signal(Signal& other) : state(other.state), duration(other.duration) {}; // copy constructor

		Signal& operator=(const Signal& other) noexcept;   // assignmet operator
		Signal& operator ++();
		friend bool operator==(const Signal& a, const Signal& b) {
			return (a.state == b.state && a.duration == b.duration);
		}
	};


	class TimeDiagram {

	private:
		static const int max_duration = 150;
		int size_of_array;             // size of memory already allocated
		int num_of_signals;            // number of elements in signals array
		Signal* signals = nullptr;     // array of signals

		TimeDiagram& erase(const int offset = 0);
		TimeDiagram& resize(const int new_size);

	public:

		// constructors
		TimeDiagram() noexcept;                              // default constructor
		TimeDiagram(const int state);                        // constant signal
		TimeDiagram(const Signal* arr, const int size);     // initializing with arra
		TimeDiagram(const TimeDiagram& TD) noexcept;         // copy constructor
		TimeDiagram(TimeDiagram&& TD) noexcept;
		TimeDiagram(const std::string s);                    // ASCII-string


		~TimeDiagram() { if (signals) delete[] signals; }        // destructor

		// setters & getters
		TimeDiagram& set_Signals(const Signal* arr, int length);
		int get_Max_Duration()   const noexcept { return max_duration; };
		int get_Temp_Duration()  const noexcept;
		int get_Num_of_Signals() const noexcept { return num_of_signals; };
		const Signal* get_Signals() const noexcept { return signals; };

		// overloaded operators
		friend std::ostream& operator << (std::ostream& ostr, const TimeDiagram& td) noexcept;
		friend std::istream& operator >> (std::istream& istr, TimeDiagram& td);
		TimeDiagram& operator=(const TimeDiagram& TD) noexcept;
		TimeDiagram operator+(const TimeDiagram& other) const;
		TimeDiagram& operator*=(const int mult);
		TimeDiagram& operator()(const TimeDiagram& other, const int offset);

		// shifts to left/right
		TimeDiagram& operator<<=(const int shift);
		TimeDiagram& operator>>=(const int shift);
	};

}
