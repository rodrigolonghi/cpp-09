#include "./PmergeMe.hpp"

int main(int argc, char** argv) {
	int x = 0;

	if (argc == 1) {
		std::cout << "Error: Too few arguments!\n";
		return (1);
	} else {
		PmergeMe	pmm;
		x = pmm.sort(argv);
		return x;
	}
}
