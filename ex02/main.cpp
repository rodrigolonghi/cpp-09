#include "PmergeMe.hpp"

int main(int argc, char** argv) {
	if (argc == 1) {
		std::cout << "Error: Too few arguments!\n";
		return (1);
	} else {
		PmergeMe	pmm;
		return (pmm.sort(argv));
	}
}
