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
		float max_durability; // ������������ ���������
		float repair_percent; // �������, �� ������� ����������������� ��������
		int repair_time;      // �������� ������� (�����, �� ������� ����������������� 10% �� ������������ ���������)
		int revenue;	      // ���������� (������ ���������� ����� ������� �������������� ���������)
		int cost;             // ��������� �������� ������
	};

	struct Tower_Level_Info {
		float radius;
		float damage;
		float speed;
		int cost; // ��������� �������� ������	
	};

	struct Config {
	public:
		enemy_type_info m_enemy_chars[6];  // ���� ��� ������ ��������� ������
		WallInfo m_wall_info;              // ���� ��� �����
		std::vector<Castle_Level_Info> m_castle_info;        // ������ �����
		std::vector<Tower_Level_Info>  m_towers_info;        // ������ �����

	public:
		Config();
		~Config() {};  // ����� ����� ������ �� ����

	private:
		void load_castle_table();
		void load_walls_info();
		void load_enemies_chars();
		void load_towers_table();
	};

}

#endif __CONFIG__
