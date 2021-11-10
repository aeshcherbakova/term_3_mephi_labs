#include "../include/All_Header.h" 

namespace Tower_Defence {
    int Light_Infantry::move(Landscape& land, std::stringstream& ss) {
        heal();
        int speed = getSpeed();
        for (int i = 0; i < speed; i++) {
            int coord = this->getCoord();
            int directions[4] = { land.right(coord), land.left(coord), land.up(coord), land.down(coord) };

            if (land.getDistLight(coord) == INF) {
                ss << "You've trapped LIGHT_INF (coord " << coord << ")!\n";
                return 1;
            }

            int next = coord;
            for (auto dir : directions)
                if (dir != -1 && land.getDistLight(dir) < land.getDistLight(next))
                    next = dir;
            this->setCoord(land, next);

            // сделали ход. Если пришли в замок, то наносим урон и самоуничтожаемся
            if (land.getDistLight(next) == 0) {
                float damage = getDamage();
                ss << "Light (coord " << next << ") damages Castle - " << damage << "\n";
                land.castle_receive_damage(damage, ss); // если замок умер, здесь выбрасывается искл
                return 0;
            }
        }
        return 1;
    }

}
