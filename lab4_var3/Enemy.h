#pragma once
#ifndef __ENEMY__
#define __ENEMY__

namespace Tower_Defence {

	typedef enum class EnemyType {
		LIGHT,
		HEAVY,
		AVIATION,
		LIGHT_HERO,
		HEAVY_HERO,
		AVIATION_HERO
	}ET;


	// тип врага + ассоциативный массив его характеристик
	typedef std::pair<EnemyType, std::map<std::string, float>> enemy_type_info;

	class Enemy {
	private:
		EnemyType type;
		float     health;  // максимальное здоровье будет доставаться из исходной таблицы
		int       heal_cooldown;  // время до восстановления здоровья
		int       coord;
		
		std::vector<Aura*> exerted_auras;
		std::map<std::string, float>& all_info;   // инфа с изначальными хар-ками



	public:
		Enemy(enemy_type_info&, int coord);
		~Enemy() {};  // ауры удаляюся в деструкторе героев
		
		float getHealth()       const noexcept { return health; }
		int   getCoord()        const noexcept { return coord; }
		int   getHealCooldown() const noexcept { return heal_cooldown; }
		int   getSpeed()  const noexcept;
		float getDamage() const noexcept;
		ET    getType()   const noexcept { return type; }
		const std::map<std::string, float>& getInfo() const noexcept { return all_info; }
		const std::vector<Aura*>* getExertedAuras() const noexcept;

		void undegro_aura(Aura* aura) noexcept { exerted_auras.push_back(aura); }
		void release_from_auras()     noexcept { exerted_auras.clear(); }
		void receive_damage(float damage);

		virtual const std::vector<Aura*>* getAuras() const noexcept { return nullptr; };  // это нужно, чтобы отличать героев от негероев

		void setCoord(Landscape& land, int coord);
		void heal() noexcept;

		virtual int move(Landscape&, std::stringstream&) = 0;
	};
}

#endif __ENEMY__
