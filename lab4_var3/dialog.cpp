#include "dialog.h"

namespace Tower_Defence {

	int (*fptr[])(Landscape&) = { quit, build_tower, build_wall, level_up_tower, level_up_castle, repair_wall, next_turn };

	const char* menu[]{
			"0. Quit the game",
			"1. Build new tower",
			"2. Build new wall",
			"3. Upgrade tower",
			"4. Upgrade castle",
			"5. Repair wall",
			"6. Continue"
	};

	const int NMsgs = sizeof(menu) / sizeof(menu[0]);


	int dialog(Landscape& land) {
		clear();
		print_map_in_console(land);

		const char* errmsg = "";
		int input;
		do {
			std::cout << errmsg << std::endl;
			errmsg = "You are wrong. Repeate, please!";
			for (int i = 0; i < NMsgs; ++i)
				std::cout << menu[i] << std::endl;
			if (!getNum(input, "\nMake your choice: --> ")) return 0;
		} while (input < 0 || input >= NMsgs);
		return input;
	}

	bool get_yes_no_answer() {
		while (!std::cin.eof()) {
			std::string s;
			std::getline(std::cin, s);
			if (s == "y" || s == "yes" || s == "Y" || s == "Yes")
				return true;
			if (s == "n" || s == "no" || s == "N" || s == "No")
				return false;
			std::cout << "Wrong answer. Try again --> ";
		}
		return false;
	}

	void clear() {
		std::cout << std::endl << std::endl;
		std::cout << "\x1B[2J\x1B[H";
	}

	void print_money(Landscape& land) {
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		std::cout << "Money: " << land.getMoney() << std::endl << std::endl; 
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
	}

	void click_enter() {
		std::cout << std::endl << "Click Enter to proceed" << std::endl;
		while (std::cin.get() != '\n') {}
		return;
	}


	void game_over() {
		std::cout << std::endl;
		std::cout << "                      ---------------------" << std::endl;
		std::cout << "                      |     GAME OVER!    |" << std::endl;
		std::cout << "                      ---------------------" << std::endl;
		// какой-нибудь рисунок надо
		// и вообще есть несколько вариантов, почему игра закрылась - поломка внутри проги / выиграл / проиграл / сам ушел, не закончив уровень
	}

	void game_won() {
		std::cout << std::endl;
		std::cout << "                      ---------------------" << std::endl;
		std::cout << "                      |      CONGRATS!    |" << std::endl;
		std::cout << "                      ---------------------" << std::endl;
	}

	
	int next_turn(Landscape& land) {
		std::stringstream ss;  // вывод логов в консоль
		try {
			if (land.make_turn(ss)) {
				std::cout << ss.str();
				game_won();
				return 0;
			}
		}
		catch (std::exception&) {  // только одно исключение - у замка кончилось здоровье
			std::cout << ss.str();
			game_over();
			return 0;
		}
		std::cout << ss.str();
		return 1;
	}

	int build_tower(Landscape& land) {
		try {
			int cost;
			cost = land.cost_new_tower(); // выкидывается, только если не хватает денег

			std::cout << "Input coordinates, where to build a new tower" << std::endl;
			int i, j;
			if (!getNum(i, "") || !getNum(j, "")) return 0;

			land.build_tower(i, j);  // выкидывается, если блокирует путь для пехоты или эта ячейка не равнина
			return 1;
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
			click_enter();
			return 1;
		}
	}

	int build_wall(Landscape& land) {
		try {
			int cost;
			cost = land.cost_new_wall(); // выкидывается, только если не хватает денег

			std::cout << "Input coordinates, where to build a new wall" << std::endl;
			int i, j;
			if (!getNum(i, "") || !getNum(j, "")) return 0;

			land.build_wall(i, j);  // выкидывается, если блокирует путь для пехоты или это не равнина
			return 1;
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
			click_enter();
			return 1;
		}
	}

	int level_up_tower(Landscape& land) {
		// пробегаемся по массиву башен, подсвечиваем каждую по очереди, выводим инфу и спрашиваем, если можно ее апгрейднуть
		for (std::vector<Tower>::const_iterator it = land.getTowers().begin(); it != land.getTowers().end(); it++) {
			clear();
			print_map_in_console(land, it->getCoord());  // выводим карту заново, подсвечивая эту башню
			std::cout << "Tower info: level: " << it->getLevel() << std::endl;
			try {
				int cost = land.cost_upgrade_tower(*it);   // если не хватает денег или макс уровень, то искл
				std::cout << "Do you want to upgrade this tower? (" << cost << " gold)" << std::endl;
				if (get_yes_no_answer()) {
					land.level_up_tower(it->getCoord());
					std::cout << "Tower upgraded successfully" << std::endl;
				}
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
			click_enter();
		}
		return 1;
	}

	int level_up_castle(Landscape& land) {
		// сначала вывод текущих характеристик замка
		const Castle* c = land.getCastle();

		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));

		std::cout << std::endl << "Your castle info: Level " << c->getLevel() << ", money: " << land.getMoney() << std::endl;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		std::cout << "Durability: " << c->getDurability() << "/" << c->getMaxDurability() << std::endl;
		std::cout << "Repair and revenue period: " << c->getSpeed() << std::endl; 

		int cost;
		try { cost = land.cost_upgrade_castle(); }
		catch (std::exception& ex) {   // елси не хватает денег или уровень уже макс
			std::cout << ex.what() << std::endl;
			click_enter();
			return 1;
		}

		std::cout << "Do you want to level up your castle? (" << cost << " gold)"<< std::endl;
		if (get_yes_no_answer()) {
			land.level_up_castle();
			std::cout << "Castle upgraded successfully" << std::endl;
		}
		return 1;
	}

	int repair_wall(Landscape& land) {
		// пробегаемся по массиву стен, подсвечиваем каждую по очереди, выводим инфу и спрашиваем, если можно ее починить
		for (std::list<Wall>::const_iterator it = land.getWalls().begin(); it != land.getWalls().end(); it++) {
			clear();
			print_map_in_console(land, it->getCoord());  // выводим карту заново, подсвечивая эту стену
			std::cout << "Wall info: health: " << it->getHealth() << "/" << it->getMaxHealth() << std::endl;
			try {
				int cost = land.cost_repair_wall(*it);
				std::cout << "Do you want to repair this wall? (" << cost << " gold)" << std::endl;
				if (get_yes_no_answer()) {
					land.repair_wall(it->getCoord());
					std::cout << "Wall repaired successfully" << std::endl;
				}
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
			// если здоровье полное, ничего не делаем
			click_enter();
		}
		return 1;
	}

	int quit(Landscape& land) {
		std::cout << "Are you sure?" << std::endl;
		if (get_yes_no_answer()) {
			std::cout << "That's all, bye! :)" << std::endl;
			return 0;
		}
		return 1;
	}
	
	void print_map_in_console(Landscape& land, int coord) {
		print_money(land);
		// подсвечиваем выбранную клетку желтым
		std::pair<char, Color>* field = land.make_colored_field(coord, Color::Green);
		int size = land.getSize();
		for (int i = 0; i < size; i++) {
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | (int)field[i].second));
			std::cout << field[i].first;
			if (i % land.getWidth() == land.getWidth() - 1)
				std::cout << std::endl;
		}
		std::cout << std::endl << std::endl;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
	}


}