#include "dialog.h"
using namespace LottoSpace;

namespace LPF {
	generator::generator() {
		for (int i = 0; i < 90; i++)
			numbers.push_back(i + 1);
		srand((unsigned)time(nullptr));
	}

	int generator::generate() {
		int cur;
		int n;
		std::cout << "Generating number: ";
		for (int i = 0; i < 5; i++) {
			cur = rand() % numbers.size();
			n = numbers[cur];
			if (n < 10)
				std::cout << "0" << n;
			else
				std::cout << n;
			Sleep(100);
			std::cout << "\b \b\b \b";
		}
		numbers.erase(numbers.begin() + cur);
		std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
			<< "Generated number: " << n << std::endl;
		return n;

	}

	int play(std::vector<Lotto>& cards_v) {
		int f = 1;
		generator g;
		int barrel;
		Lotto karta1(3);
		Lotto karta2(3);
		while (f) {
			clr();
			std::cout << "Player 1:" << std::endl << karta1 << "Player2:" << std::endl << karta2;
			barrel = g.generate();
			karta1(barrel);
			karta2(barrel);
			wait();
			if (!karta1--) {
				if (!karta2--)
					std::cout << "Draw!" << std::endl;
				else
					std::cout << "Player 1 wins!" << std::endl;
				std::cout << "Press any key to return to main menu" << std::endl;
				wait();
				f = 0;
			}
			else {
				if (!karta2--) {
					std::cout << "Player 2 wins!" << std::endl;
					wait();
					f = 0;
				}
			}
		}
		return 1;
	}

	int P_Exit(std::vector<Lotto>& cards_v) {
		return 0;
	}

	std::string dialog() {
		std::stringstream s;
		s << "0. Exit" << std::endl
			<< "1. Add new card" << std::endl
			<< "2. Show cards" << std::endl
			<< "3. Take squares on all cards by barrel number" << std::endl
			<< "4. Play AutoLotto" << std::endl
			<< "Your choice: ";
		return s.str();
	}

	void clr() {
		std::cout << "\x1B[2J\x1B[H";
	}

	void wait() {
		std::cout << "Press any key to continue" << std::endl;
		_getch();
		std::cout << "\b \b";
	}

	int P_NewCard(std::vector<Lotto>& cards_v) {
		int a;
		clr();
		while (1) {
			std::cout << "Enter number of new cards or 0 to exit to main menu: ";
			std::cin >> a;
			if (!std::cin.good() || a < 0) {
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				std::cout << "Incorrect input!" << std::endl;
				Sleep(1000);
				clr();
			}
			else
				break;
		}
		if (a) {
			for (int i = 0; i < a; i++) {
				try {
					cards_v.push_back(*(new Lotto(3)));
				}
				catch (std::bad_alloc& ex) {
					std::cout << ex.what();
					return 0;
				}
			}
		}
		return 1;
	}

	int P_Place(std::vector<Lotto>& cards_v) {
		int a;
		while (1) {
			clr();
			std::cout << "Enter the number of a barrel or 0 to exit to main menu: ";
			std::cin >> a;
			if (!std::cin.good() || a < 0 || a > 90) {
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				std::cout << "Incorrect input!" << std::endl;
				Sleep(1000);
				clr();
			}
			else
				break;
		}
		if (a) {
			for (int i = 0; i < (signed)cards_v.size(); i++) {
				cards_v[i](a);
				if (!cards_v[i]--) {
					cards_v.erase(cards_v.begin() + i);
					std::cout << "Card " << i << " has been completed" << std::endl;
				}
			}
			std::cout << "Done!" << std::endl;
			wait();
		}
		return 1;
	}

	int P_Show(std::vector<Lotto>& cards_v) {
		int a;
		while (1) {
			clr();
			std::cout << "0. Return to main menu" << std::endl
				<< "1. Show all cards" << std::endl
				<< "2. Show one card by number" << std::endl
				<< "Your choice: ";
			std::cin >> a;
			if (!std::cin.good() || a < 0 || a > 2) {
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				std::cout << "Incorrect input!" << std::endl;
				Sleep(1000);
				clr();
			}
			else {
				switch (a) {
				case 0:
					return 1;
					break;
				case 1:
					clr();
					for (int i = 0; i < (signed)cards_v.size(); i++) {
						std::cout << "Card " << i << ":" << std::endl << cards_v[i];
					}
					wait();
					break;
				case 2:
					std::cout << "Enter card number from " << "0 to " << cards_v.size() - 1 << ": ";
					std::cin >> a;
					if (!std::cin.good() || a < 0 || a >(signed)cards_v.size()) {
						std::cin.clear();
						std::cin.ignore(INT_MAX, '\n');
						std::cout << "Incorrect input!" << std::endl;
						Sleep(1000);
						clr();
					}
					else {
						clr();
						std::cout << "Card " << a << ":" << std::endl << cards_v[a];
						wait();
					}
					break;
				}
			}
		}
		return 1;
	}
}