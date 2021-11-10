#include "../include/All_Header.h" 

namespace Tower_Defence {

    Aviation::Aviation(enemy_type_info& type_info, int coord) :
        Enemy(type_info, coord),
        ammunition((int)type_info.second.find("ammunition")->second) {}
    
    int Aviation::move(Landscape& land, std::stringstream& ss) {
        heal();
        int speed = getSpeed();
        for (int i = 0; i < speed; i++) {
            int coord = this->getCoord();

            if (ammunition > 1) {  // всегда оставляем один снаряд для замка
                // за один ход можно и стрелять в стены, и летать
                for (std::list<Wall>::const_iterator it = land.getWalls().begin(); it != land.getWalls().end(); it++) {
                    if (land.distance(coord, it->getCoord()) <= getRadius()) {
                        float damage = getDamage();
                        ss << "Avia (coord " << coord << ") damages Wall (coord " << it->getCoord() << ") - " << damage;
                        land.wall_receive_damage(it->getCoord(), damage, ss);
                        ammunition--;
                        break;
                    }
                }
            }

            int directions[4] = { land.right(coord), land.left(coord), land.up(coord), land.down(coord) };
            int next = coord;
            for (auto dir : directions)
                if (dir != -1 && land.getDistAvia(dir) < land.getDistAvia(next))
                    next = dir;
            this->setCoord(land, next);

            // сделали ход. Если пришли в замок, то наносим урон и самоуничтожаемся
            if (land.getDistAvia(getCoord()) == 0) {
                float damage = getDamage();
                ss << "Heavy (coord " << next << ") damages Castle - " << damage << "\n";
                land.castle_receive_damage(damage, ss); // если замок умер, здесь выбрасывается искл
                return 0;
            }
        }
        return 1;
    };

}