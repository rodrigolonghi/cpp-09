#include "BitcoinExchange.hpp"

int main(int argc, char** argv) {
	if (argc == 1) {
		std::cout << "Error: Too few arguments!\n";
		exit(1);
	} else if (argc > 2) {
		std::cout << "Error: Too many arguments!\n";
		exit(1);
	} else {
		BitcoinExchange	b;
		exit(b.displayValues(argv[1]));
	}
}
