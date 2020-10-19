#include "TimeDiagram_dynamic.h"

namespace lab3 {

	//    #############         СТРУКТУРА СИГНАЛ          #############

	// конструктр сигнала (если не указана длительность, то берем 1)
	Signal::Signal(const int state, const int duration) {
		if (state != 1 && state != X && state != 0)
			throw std::invalid_argument("invalid state!");
		if (duration < 0)
			throw std::invalid_argument("invalid duration!");

		this->state = state;
		this->duration = duration;
	};

	// оператор присваивания
	Signal& Signal::operator=(const Signal& other) noexcept {
		state = other.state;
		duration = other.duration;
		return *this;
	}

	// перегруженный оператор ++ (префиксный), добавляет 1 к длительности сигнала (состояние не меняется)
	Signal& Signal::operator ++() {
		duration++;
		return *this;
	}






	//    #############         КОНСТРУКТОРЫ          #############

	// очистка диаграммы (private) offset - начиная с какого номера элемента занулять массив
	TimeDiagram& TimeDiagram::erase(const int offset) {
		for (int i = offset; i < num_of_signals; i++)
			signals[i] = Signal();   // сброс сигнала в {0, 0} конструктором по умолчанию
		num_of_signals = 0;
		return *this;
	}

	// увеливеличение размера массива (private)
	TimeDiagram& TimeDiagram::resize(const int new_size) {
		if (new_size <= size_of_array)
			throw std::invalid_argument("invalid size of array");
		Signal* sig = new Signal[new_size];
		for (int i = 0; i < num_of_signals; i++)
			sig[i] = signals[i];
		delete[] signals;
		size_of_array = new_size;
		signals = sig;
		return *this;
	}

	// конструктор по умолчанию
	TimeDiagram::TimeDiagram() noexcept {
		size_of_array = 10;
		signals = new Signal[size_of_array];
		num_of_signals = 0;
	}

	// конструктор создания диаграммы с постоянным сигналом на всю длину
	TimeDiagram::TimeDiagram(const int state) {
		size_of_array = num_of_signals = 1;
		signals = new Signal[size_of_array];
		try { signals[0] = Signal(state, max_duration); }
		catch (...) { delete[] signals; signals = nullptr; throw; }
	}

	// копирующий конструктор
	TimeDiagram::TimeDiagram(const TimeDiagram& TD) noexcept {
		num_of_signals = TD.num_of_signals;
		size_of_array = TD.size_of_array;
		signals = new Signal[size_of_array];
		for (int i = 0; i < num_of_signals; i++)
			signals[i] = TD.signals[i];
	}

	// перемещающий конструктор
	TimeDiagram::TimeDiagram(TimeDiagram&& TD) noexcept {
		std::swap(size_of_array, TD.size_of_array);
		std::swap(num_of_signals, TD.num_of_signals);
		std::swap(signals, TD.signals);
	} 

	// конструктор с инициализацией готовым массивом сигналов
	// здесь size - количество ненулевых сигналов в массиве, а не выделенная под arr память
	TimeDiagram::TimeDiagram(const Signal arr[], const int size) {
		this->set_Signals(arr, size);
	}


	// конструктор ввода диаграммы в виде строки ASCII символов
	TimeDiagram::TimeDiagram(const std::string s) {
		num_of_signals = 0;
		int temp_duration = 0;

		size_of_array = s.size();
		signals = new Signal[size_of_array];  // выделяем память с запасом, укорачивать не будем, пусть остается
		for (auto ch : s) {
			if (ch != '0' && ch != '1' && ch != 'X') {
				delete[] signals;
				signals = nullptr;
				num_of_signals = size_of_array = 0;
				throw std::invalid_argument("incorrect input!");
			}
			if (temp_duration == max_duration) return;

			temp_duration++;
			if (ch == 'X') ch = '2';
			if (num_of_signals && signals[num_of_signals - 1].state == ch - '0')
				++signals[num_of_signals - 1];
			else signals[num_of_signals++] = { ch - '0', 1 };
		}
	}





	//    #############         ГЕТТЕРЫ И СЕТТЕРЫ          #############


	TimeDiagram& TimeDiagram::set_Signals(const Signal* arr, const int size) {
		if (size <= 0)
			throw std::length_error("invalid length of signals array");
		int temp_dur = 0;
		int i = 0;
		// считаем, сколько памяти надо выделить
		for (; i < size && temp_dur < max_duration; i++)
			temp_dur += arr[i].duration;

		num_of_signals = i;
		// если в уже созданной диаграмме памяти выделено меньше, то удаляем и выделяем заново
		if (size_of_array < i) {
			delete[] signals;
			size_of_array = i;
			signals = new Signal[size_of_array];
		}
		for (int j = 0; j < num_of_signals; j++)
			signals[j] = arr[j];
		if (temp_dur > max_duration) 
			signals[num_of_signals - 1].duration -= (temp_dur - max_duration);
		return *this;
	}

	int TimeDiagram::get_Temp_Duration() const noexcept {
		int dur = 0;
		for (int i = 0; i < num_of_signals; i++)
			dur += signals[i].duration;
		return dur;
	}


	//    #############         ПЕРЕГРУЖЕННЫЕ ОПЕРАТОРЫ          #############


	std::ostream& operator << (std::ostream& ostr, const TimeDiagram& td) noexcept {
		// случай пустой диаграммы
		if (!td.num_of_signals) {
			ostr << "Time diagram is empty" << std::endl;
			return ostr;
		}

		const Signal* sig_ptr = td.signals;
		std::string str_1 = "", str_0 = "", str_X = "";

		int temp_duration = 0;
		// формирование строк, отображающих сигналы
		for (int i = 0; i < td.num_of_signals; i++, sig_ptr++) {
			temp_duration += sig_ptr->duration;
			if (sig_ptr->state == 1) {
				str_1 += std::string(sig_ptr->duration, '_');
				str_0 += std::string(sig_ptr->duration, ' ');
				str_X += std::string(sig_ptr->duration, ' ');
			}
			else if (sig_ptr->state == 0) {
				str_1 += std::string(sig_ptr->duration, ' ');
				str_0 += std::string(sig_ptr->duration, '_');
				str_X += std::string(sig_ptr->duration, ' ');
			}
			else if (sig_ptr->state == X) {
				str_1 += std::string(sig_ptr->duration, ' ');
				str_0 += std::string(sig_ptr->duration, ' ');
				str_X += std::string(sig_ptr->duration, '_');
			}
		}

		// непосредственно вывод диаграммы
		ostr << "  ^" << std::endl;
		ostr << "  |" << std::endl;
		ostr << "  |" << std::endl;
		ostr << " 1|";
		ostr << str_1 << std::endl;
		ostr << "  |" << std::endl;
		ostr << " X|";
		ostr << str_X << std::endl;
		ostr << "  |" << std::endl;
		ostr << " 0|";
		ostr << str_0 << std::endl;
		ostr << "  |" << std::string(temp_duration + 2, '-') << '>' << std::endl;

		return ostr;
	}


	// ввод в виде строки ASCII символов, использует соответствующий конструктор
	std::istream& operator >> (std::istream& istr, TimeDiagram& td) {
		std::string input;
		if (getline(istr, input).eof())
			throw std::ios_base::failure("end of input");
		try { td = TimeDiagram(input); }
		catch (...) { throw; }
		return istr;
	}


	// оператор присваивания
	TimeDiagram& TimeDiagram::operator=(const TimeDiagram& TD)noexcept {
		if (this != &TD) {
			size_of_array = num_of_signals = TD.num_of_signals;
			if (signals) delete[] signals;
			signals = new Signal[size_of_array];
			for (int i = 0; i < num_of_signals; i++)
				signals[i] = TD.signals[i];
		}
		// в противном случае происходит самоприсваивание, ничего делать не надо
		return *this;
	}


	// оператор сложения (новая диаграмма просто пририсовывается к первой справа, если переполнение, то обрезается)
	TimeDiagram TimeDiagram::operator+(const TimeDiagram& other) const {
		if (!num_of_signals) return other;
		if (!other.get_Num_of_Signals()) return *this;

		Signal sig_arr[2 * max_duration];
		int i = 0, j = 0;
		for (; i < num_of_signals; i++)
			sig_arr[i] = signals[i];
		// если на стыке одинаковые сигналы, сливаем их в один
		const Signal* other_sig = other.get_Signals();
		if (sig_arr[i - 1].state == other_sig[0].state) {
			sig_arr[i - 1].duration += other_sig[0].duration;
			j = 1;
		}
		for (; j < other.num_of_signals; i++, j++)
			sig_arr[i] = other_sig[j];

		// нам здесь не нужно считать длительность получившейся диаграммы, если она слишком большая, то будет обрезана в конструкторе
		try { TimeDiagram res(sig_arr, i); return res; }
		catch (...) { throw; }
	}


	// копирование диаграммы mult раз (если переполнение, то обрезается, исключения не выкидываются)
	TimeDiagram& TimeDiagram::operator*=(const int mult) {
		if (mult < 1) throw std::invalid_argument("invalid multiplier");
		// копируем исходное состояние this
		TimeDiagram copy(*this);
		for (int cnt = 1; cnt < mult; cnt++)
			*this = *this + copy;
		return *this;
	}


	// замена диаграммы начиная с времени offset на другую диаграмму
	TimeDiagram& TimeDiagram::operator()(const TimeDiagram& other, const int offset) {
		int temp_duration = this->get_Temp_Duration();
		if (offset < 0 || offset > temp_duration)
			throw std::invalid_argument("invalid offset");

		// обрезаем исходную диаграмму до длительности offset
		int difference = temp_duration - offset;
		for (int i = num_of_signals - 1; i >= 0 && difference > 0; i--)
			if (signals[i].duration <= difference) {
				difference -= signals[i].duration;
				signals[i] = Signal();
				num_of_signals--;
			}
			else {
				signals[i].duration -= difference;
				break;
			}

		*this = *this + other;
		return *this;
	}



	// сдвиг диаграммы на shift влево
	// кусок длительностью shift слева просто исчезает, справа добавляются нули
	TimeDiagram& TimeDiagram::operator<<=(const int shift) {
		if (shift <= 0)
			throw std::invalid_argument("shift must be bigger than zero");

		// сначала идем слева направо и считаем, сколько сигналов надо будет удалить
		int temp_shift = 0, num_to_delete = 0;
		while (temp_shift < shift && signals[num_to_delete].duration) {
			temp_shift += signals[num_to_delete].duration;
			num_to_delete++;
		}

		int difference = temp_shift - shift;
		// если разница ноль, то сдвигаемся на num_to_delete и больше не паримся
		// если разница больше нуля, то сдвигаем на (num_to_delete - 1), а последний оставшийся укорачиваем
		// длительность последнего сигнала после укорачивания будет равна именно difference

		if (difference < 0) return this->erase();
		if (difference) {
			num_to_delete--;
			signals[num_to_delete].duration = difference;
		}
		for (int i = 0; i < num_of_signals; i++)
			// тернарный оператор не работает, видимо, его тоже надо переопределять, но мне лень разбираться
			if (i + num_to_delete >= max_duration)
				signals[i] = Signal();
			else
				signals[i] = signals[i + num_to_delete];
		num_of_signals -= num_to_delete;
		return *this;
	}


	// сдвиг диаграммы на shift вправо
	// как я поняла, образовавшееся пустое место слева надо просто заполнить нулями
	TimeDiagram& TimeDiagram::operator>>=(const int shift) {
		if (shift <= 0) throw std::invalid_argument("shift must be bigger than zero");
		if (!num_of_signals) return *this;

		int temp_duration = shift;
		int new_num_of_signals = num_of_signals;
		int i = 0;

		for (; i < num_of_signals && temp_duration <= max_duration; i++)
			temp_duration += signals[i].duration;
		// если переполнилась длительность, укорачиваем/зануляем текущий элемент и зануляем все следующие
		if (temp_duration >= max_duration) {
			new_num_of_signals = i;
			signals[i - 1].duration -= (temp_duration - max_duration);
			// зануляем все последующие сигналы
			this->erase(i);
		}

		// просто сдвиг вправо на 1 элемент
		num_of_signals = new_num_of_signals;
		if (num_of_signals == size_of_array) this->resize(size_of_array + 1);
		for (int i = num_of_signals; i > 0; i--)
			signals[i] = signals[i - 1];
		num_of_signals++;

		signals[0] = Signal(0, shift);

		return *this;
	}

}
