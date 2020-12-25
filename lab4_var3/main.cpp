#include "dialog.h"

using namespace Tower_Defence;

int main() {
	Landscape land;
	// надо сделать сначала выбор уровня, отдельный конфиг, где будет лежать кол-во уровней и сколько игрок уже прошел

	int choice;

	while (true) {
		choice = dialog(land);
		if (!fptr[choice](land)) break;
	}

	return 0;
}


