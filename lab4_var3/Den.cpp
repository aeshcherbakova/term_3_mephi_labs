#include "All_Header.h"

namespace Tower_Defence {

	Den::~Den() {
		while (!schedule.empty()) {
			delete schedule.front().second;
			schedule.pop();
		}
	}

	void Den::turn(Landscape& land, std::stringstream& ss) {
		while (!schedule.empty() && land.getTime() == schedule.front().first) {
			// это просто вывод текста
			ET type = schedule.front().second->getType();
			ss << "Den (coord " << this->getCoord() << ") release " << static_cast<int>(type);
			// если герой, выводим ауры

			const std::vector<Aura*>* auras = schedule.front().second->getAuras();
			if (auras) {
				ss << ", auras: ";
				for (auto aura : *auras)
					ss << static_cast<int>(aura->getType()) << ", ";
			}
			ss << "\n";

			// это функция
			land.add_enemy(schedule.front().second);
			schedule.pop();
		}
	}

}