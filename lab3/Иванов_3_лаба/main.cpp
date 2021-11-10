#include "dialog.h"

using namespace LottoSpace;
using namespace LPF;

int main() {
	int (*dp[5])(std::vector<Lotto>&) = { P_Exit, P_NewCard, P_Show, P_Place, play };
	std::vector<Lotto> cards;
	int a;
	do {
		clr();
		while (1) {
			std::cout << dialog();
			std::cin >> a;
			if (!std::cin.good() || a < 0 || a > 4) {
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				std::cout << "Incorrect input!" << std::endl;
				Sleep(1000);
				clr();
			}
			else
				break;
		}
	} while (dp[a](cards));
	std::cout << "Goodbye!" << std::endl;
	wait();
	return 0;
}