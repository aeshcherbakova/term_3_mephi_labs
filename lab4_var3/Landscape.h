#pragma once

#ifndef __LANDSCAPE__
#define __LANDSCAPE__ 

#define INF 10000

namespace Tower_Defence {

	enum class Color {
		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Brown = 6,
		LightGray = 7,
		DarkGray = 8,
		LightBlue = 9,
		LightGreen = 10,
		LightCyan = 11,
		LightRed = 12,
		LightMagenta = 13,
		Yellow = 14,
		White = 15
	};

	typedef enum class LandType {
		PLAIN, WATER, HILL,
		WALL, TOWER, CASTLE, DEN
	} LT;


	// ячейка на карте
	struct Cell {
		LandType type;
		int light_dist;
		int heavy_dist;
		int avia_dist;

		Cell(LandType b_type = LT::PLAIN);
		Cell(LandType b_type, int light, int heavy, int avia);
	};


	// самый главный класс - собсна, весь уровень
	class Landscape {


	private:
		int m_time;              // кол-во единиц времени (ходов), прошедшее с начала игры
		int m_width, m_height;
		Castle* m_castle;
		std::vector<Cell> m_map;    // двумерная матрица "схлопнулась" в одномерный массив

		Config* m_config;  // вся статическая инфа

		std::vector<Tower> m_towers;
		std::vector<Den>   m_dens;
		std::list<Wall>    m_walls;
		std::list<Enemy*>  m_enemies; 
	
	public:
		Landscape();
		~Landscape();

		int getWidth()  const noexcept { return m_width;  };
		int getHeight() const noexcept { return m_height; };
		int getMoney()  const noexcept { return m_castle->getMoney(); }
		int getTime()   const noexcept { return m_time; }
		const Castle*             getCastle() const noexcept { return m_castle; }
		const std::vector<Cell>&  getMap()    const noexcept { return m_map; }
		const std::vector<Tower>& getTowers() const noexcept { return m_towers; }
		const std::list<Wall>&    getWalls()  const noexcept { return m_walls; }
		const std::list<Enemy*>& getEnemies() const noexcept { return m_enemies; }
		int getDistLight(int coord) const noexcept { return m_map[coord].light_dist; }
		int getDistHeavy(int coord) const noexcept { return m_map[coord].heavy_dist; }
		int getDistAvia (int coord) const noexcept { return m_map[coord].avia_dist;  }

		void add_enemy(Enemy* en);
		
		

		int cost_new_wall()       const;
		int cost_new_tower()      const;
		int cost_upgrade_castle() const;
		int cost_upgrade_tower(const Tower&) const;
		int cost_repair_wall(const Wall&)    const;

		int can_build_smth(int i, int j) const; 

		void repair_wall(int coord);
		void build_wall (int i, int j);
		void build_tower(int i, int j);
		void level_up_tower(int coord);
		void level_up_castle();

		int getSize() const noexcept { return m_width * m_height; }
		int index(int i, int j) const noexcept { return (i* m_width + j); };
		float distance(int a, int b) const noexcept;

		std::pair<char, Color>* make_colored_field(int coord = -1, Color color = Color::White) const noexcept;
		bool make_turn(std::stringstream&);

		// методы для перемещения по карте
		// возвращают индекс в одномерном массиве ячеек, если выход за границу, то возвр исключение
		int right(int) const noexcept;
		int left(int) const noexcept;
		int up(int) const noexcept;
		int down(int) const noexcept;
		
		void wall_receive_damage(int coord, float damage, std::stringstream& ss);
		void castle_receive_damage(float damage, std::stringstream&);
		void shoot_hero (Enemy*, float damage, std::stringstream&);
		void shoot_enemy(Enemy*, float damage, std::stringstream&);


	private:
		// чтение из конфигов
		void load_map();
		void load_dens();
		void read_auras(std::ifstream& fin, std::vector<Aura*>& vec);

		// метод вычисления расстояния от замка (для всех трех типов)
		void path_for_light();
		void path_for_heavy();
		void path_for_avia();

		bool check_dens_empty() const noexcept;

	};

}

#endif __LANDSCAPE__

