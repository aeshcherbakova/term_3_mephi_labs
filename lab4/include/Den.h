#pragma once

#ifndef __DEN__
#define __DEN__


namespace Tower_Defence {

	class Den : public Building {
	private:
		std::queue<std::pair<int, Enemy*>> schedule;


	public:
		Den(int coord = 0) : Building(coord) {};  // очередь потом будет заполняться через метод add_enemy
		~Den();

		void add_enemy(std::pair<int, Enemy*> en) noexcept { schedule.push(en); }
		bool is_empty() const noexcept { return schedule.empty(); }

		void turn(Landscape&, std::stringstream&);


	};



}


#endif __DEN__