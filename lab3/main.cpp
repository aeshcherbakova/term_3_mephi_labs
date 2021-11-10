#include "dialog.h"
#include <vector>

using namespace lab3;


int main() {
	TimeDiagram td;
	int choice;

	while (choice = dialog())
		if(!fptr[choice](td)) break;

	std::vector<TimeDiagram> vec;
	vec.push_back(td);
	vec.clear();

	std::cout << "That's all, bye! :)" << std::endl;
	return 0;
}