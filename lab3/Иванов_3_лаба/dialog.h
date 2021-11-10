#pragma once

#include "windows.h"
#include <random>
#include <conio.h>
#include "lotto/lotto.h"

using namespace LottoSpace;

namespace LPF {

	class generator {
	private:
		std::vector<int> numbers;
	public:
		generator();
		int generate();
	};
	int P_NewCard(std::vector<Lotto>& cards_v);
	int P_Show(std::vector<Lotto>& cards_v);
	int P_Place(std::vector<Lotto>& cards_v);
	int play(std::vector<Lotto>& cards_v);
	int P_Exit(std::vector<Lotto>& cards_v);
	std::string dialog();
	void clr();
	void wait();
}
