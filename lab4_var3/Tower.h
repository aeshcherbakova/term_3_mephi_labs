#pragma once

#ifndef __TOWER__
#define __TOWER__




namespace Tower_Defence {

	class Tower : public Building {
	private:
		int m_level;     // уровень башни
		float m_cooldown;      // сколько ходов осталось до выстрела
		std::vector<Tower_Level_Info>& m_table;  // вся инфа об уровнях

	public:
		Tower(int coord, std::vector<Tower_Level_Info>& info);
		~Tower() {};


		int getLevel() const noexcept { return m_level; }
		const std::vector<Tower_Level_Info>& getInfo() const noexcept { return m_table; }

		void turn(Landscape&, std::stringstream&);
		int level_up();
		int cost_upgrade() const;


	};

}

#endif __TOWER__