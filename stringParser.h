#include <iostream>
#include "BST.h"
#include <regex>

struct stringParser
{
	// parses code that was in main to reduce complexity and improve tidiness
	void mainHelper(BST& tree);

	// helper functions for three functionalities of an AVL tree
	void insertHelper(std::string input, BST& tree);
	void searchHelper(std::string input, BST& tree);
	void removeHelper(std::string input, BST& tree, bool inorder);

};

// parses code that was in main to reduce complexity and improve tidiness
void stringParser::mainHelper(BST& tree) {

	std::string raw_input;
	std::getline(std::cin, raw_input);


	std::string conc_input = raw_input.substr(0, raw_input.find(" ")); // first word
	raw_input = raw_input.substr(raw_input.find(" ") + 1);

	// if first word in input is "insert"
	if (conc_input == "insert") {
		insertHelper(raw_input, tree);
	}

	// if first word in input is "search"
	else if (conc_input == "search") {
		searchHelper(raw_input, tree);
	}

	// if first word in input is "remove"
	else if (conc_input == "remove") {
		removeHelper(raw_input, tree, false);
	}

	// if first word in input is "removeInorder"
	else if (conc_input == "removeInorder") {
		removeHelper(raw_input, tree, true);

	}
	
	// if first word in input is "printInorder"
	else if (conc_input == "printInorder") {
		// prints InOrder traversal
		bool comma = false;
		tree.printInorder(tree.root, comma);
		std::cout << std::endl;
	}

	// if first word in input is "printPostorder"
	else if (conc_input == "printPostorder") {
		// prints PostOrder traversal
		bool comma = false;
		tree.printPostorder(tree.root, comma);
		std::cout << std::endl;
	}

	// if first word in input is "printPreorder"
	else if (conc_input == "printPreorder") {
		// prints PreOrder traversal
		bool comma = false;
		tree.printPreorder(tree.root, comma);
		std::cout << std::endl;
	}

	// if first word in input is "height"
	else if (conc_input == "height") {
		tree.inorderHeight(tree.root);
		std::cout << std::endl;
	}

	// if first word in input is "printLevelCount"
	else if (conc_input == "printLevelCount") {
		int max = 0;
		int level = 0;
		if (tree.root != nullptr) {
			std::cout << tree.printLevelCount(tree.root, max, level) << std::endl;
		}
		else {
			//std::cout << "Tree root is empty" << std::endl;
			std::cout << 0 << std::endl;
		}
	}

	// if conc_input is any other word, it will print "unsuccessful"
	else {
		std::cout << "unsuccessful" << std::endl;
	}
}


// helper function to insert students in the avl tree
void stringParser::insertHelper(std::string input, BST& tree) {

	std::string student_id = "00000000";
	bool inserted = false;

	if (input.find("\"") != std::string::npos) {
		// gets name and id by checking for quotation marks
		std::string student_name = input.substr(input.find("\"") + 1);
		student_name = student_name.substr(0, student_name.find("\""));

		bool contains_non_alpha = !std::regex_match(student_name, std::regex("^[A-Za-z ]+$"));


		input = input.substr(input.find("\"") + 1);

		auto iterator = input.find("\"");
		iterator +=2;

		// prevents out of bounds exception from being thrown
		if (input.find_first_of("0123456789")) {
			input = input.substr(iterator);
			student_id = input;
		}

		// checks if a number follows the name and then if the number contains only numbers
		if (!input.empty() && input.find_first_not_of("0123456789") == std::string::npos && !contains_non_alpha) {

			if (student_id.size() == 8) {
				bool inTree = false;
				std::string searched_name;
				tree.searchID(tree.root, student_id, inTree, searched_name);
				// only inserts if ID is unique
				if (!inTree) {
					tree.root = tree.insert(tree.root, student_name, student_id);
					inserted = true;
				}
			}
		}
			
	}
	// prints based on whether it was inserted or not
	if (inserted) {
		std::cout << "successful" << std::endl;
	}
	else {
		std::cout << "unsuccessful" << std::endl;
	}

}

// helper function to search for student nodes given their name or id
void stringParser::searchHelper(std::string input, BST& tree) {

	bool isFound = false;
	std::vector<std::string> id_container;

	// searches for name
	if (input.find("\"") != std::string::npos) {
		std::string student_name = input.substr(input.find("\"") + 1);
		student_name = student_name.substr(0, student_name.find("\""));

		// stores repeated names' ids in a vector container
		tree.searchName(tree.root, student_name, id_container);

		// prints ids separated by a newline
		if (!id_container.empty()) {
			for (std::string id : id_container) {
				std::cout << id << std::endl;
			}
		}
		// if container is empty, name was not found
		else {
			std::cout << "unsuccessful" << std::endl;
		}
	}
	// searches for id
	else {

		input = input.substr(0, input.find(" "));
		std::string returned_name = "";
		
		// checks if id matches the constraints
		if (!input.empty() && input.find_first_not_of("0123456789") == std::string::npos) {
			std::string to_search = input;

			if (input.size() == 8) {
				tree.searchID(tree.root, to_search, isFound, returned_name);
			}
		}

		if (!isFound) {
			std::cout << "unsuccessful" << std::endl;
		}
		else {
			std::cout << returned_name << std::endl;
		}
	}
}

// function to remove a certain input from the avl tree, takes a bool parameter
// to signify when to remove inorder or when to remove a specific name
void stringParser::removeHelper(std::string input, BST& tree, bool inorder) {
	// regular removal function
	if (!inorder) {
		if (!input.empty() && input.find_first_not_of("0123456789") == std::string::npos) {
			if (input.length() == 8) {
				tree.removeID(tree.root, input);
			}
		}
		else {
			std::cout << "unsuccessful" << std::endl;
		}
	}

	// inorder removal function
	if (inorder) {
		if (!input.empty() && input.find_first_not_of("0123456789") == std::string::npos) {
			tree.removeInorder(tree.root, stoi(input));
		}
		else {
			std::cout << "unsuccessful" << std::endl;
		}
	}
	
}