#pragma once

#ifndef __CONFIG__
#define __CONFIG__

namespace Tower_Defence {

	struct WallInfo {
		int cost;
		int repair_cost;
		float max_health;
	};

	struct Castle_Level_Info {
		float max_durability; // максимальная прочность
		float repair_percent; // процент, на который восстанавливается здоровье
		int repair_time;      // скорость ремонта (время, за которое восстанавливается 10% от максимальной прочности)
		int revenue;	      // доходность (период доходности равен периоду восстановления прочности)
		int cost;             // стоимость текущего уровня
	};

	struct Tower_Level_Info {
		float radius;
		float damage;
		float speed;
		int cost; // стоимость текущего уровня	
	};

	struct Config {
	public:
		enemy_type_info m_enemy_chars[6];  // инфа про врагов достается отсюда
		WallInfo m_wall_info;              // инфа про стены
		std::vector<Castle_Level_Info> m_castle_info;        // уровни замка
		std::vector<Tower_Level_Info>  m_towers_info;        // уровни башен

	public:
		Config();
		~Config() {};  // вроде здесь ничего не надо

	private:
		void load_castle_table();
		void load_walls_info();
		void load_enemies_chars();
		void load_towers_table();
	};

}

#endif __CONFIG__
