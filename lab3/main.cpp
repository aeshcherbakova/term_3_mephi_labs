#include "dialog.h"
#include "Static/TimeDiagram_static.h"

using namespace lab3;

int main() {
	TimeDiagram td;
	int choice;

	while (choice = dialog())
		if (!fptr[choice](td)) break;

	std::cout << "That's all, bye! :)" << std::endl;
	return 0;
}