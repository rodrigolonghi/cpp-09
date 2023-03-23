#include "RPN.hpp"

int main(int argc, char** argv) {
	if (argc == 1) {
		std::cout << "Error: Too few arguments!\n";
		return (1);
	} else if (argc > 2) {
		std::cout << "Error: Too many arguments!\n";
		return (1);
	} else {
		RPN	rpn;
		return (rpn.calculate(argv[1]));
	}
}
