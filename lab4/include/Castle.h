#pragma once

#ifndef __CASTLE__
#define __CASTLE__

namespace Tower_Defence {


	class Castle : public Building {
	
	private:
		int m_level;              // ������� �����
		float m_durability;       // ������� ���������
		int m_money;              // ���-�� ������ � ������������ ������ � ������ ������

		int m_repair_and_revenue_cooldown;
		std::vector<Castle_Level_Info>& m_table;    // ������� ���������� �� ������� ����� (�������� �� �������)

	public: 
		
		Castle(std::vector<Castle_Level_Info>& info, int coord = 0, int money = 0);
		~Castle();  // ����� �� ������ ������� �� ����

		
		int getLevel() const noexcept { return m_level; }
		int getMoney() const noexcept { return m_money; }
		int getSpeed() const noexcept { return m_table[m_level].repair_time; }
		float getDurability()    const noexcept { return m_durability; }
		float getMaxDurability() const noexcept { return m_table[m_level].max_durability; }
		const std::vector<Castle_Level_Info>& getTable() const noexcept { return m_table; }

		void buy_anything(int cost);  // ���������� ����������, ���� ������������ �����
	
		void receive_damage(float damage, std::stringstream&);    // �������� ���� �� ����� 

		void turn(Landscape&, std::stringstream&);
		void level_up();
		int cost_upgrade() const;
		

	private:
		void repair();

	};

}

#endif __CASTLE__
