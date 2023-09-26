#include "stringParser.h"
#include <iomanip>
#include <string>

int main() {

	BST tree{};
	stringParser parser;

	int input_count = 0;
	std::string white_space;
	std::cin >> input_count;
	std::getline(std::cin, white_space);

	// takes input a defined number of times
	while (input_count--) { 
		parser.mainHelper(tree);
	}

	return 0;
}