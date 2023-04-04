#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {
}

PmergeMe::PmergeMe(PmergeMe const &src) {
	*this = src;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &rhs) {
	this->deq = rhs.getDeq();
	this->vec = rhs.getVec();
	return *this;
}

double	PmergeMe::timeNow() {
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec * 0.001));
}

void	PmergeMe::printResult(char **input, double timeVec, double timeDeq) {
	size_t	limit;

	this->vec.size() > 10 ? limit = 10 : limit = this->vec.size();
	std::cout << "Before: ";
	for (size_t i = 1; i < limit + 1; i++)
		std::cout << input[i] << " ";
	if (this->vec.size() > 10)
		std::cout << "[...]";
	std::cout << "\nAfter:  ";
	for (size_t i = 0; i < limit; i++)
		std::cout << this->deq[i] << " ";
	if (this->vec.size() > 10)
		std::cout << "[...]";
	std::cout << "\nTime to process a range of " << this->deq.size() << " elements with std::vector : " << timeVec << " us" << std::endl;
	std::cout << "Time to process a range of " << this->deq.size() << " elements with std::deque  : " << timeDeq << " us" << std::endl;
}

template <typename T>
void	PmergeMe::insertionSort(int x, int y, T& container) {
	for (int i = x; i < y; i++) {
		int temp = container[i + 1];
		int j = i + 1;
		while (j > x && container[j - 1] > temp) {
			container[j] = container[j - 1];
			j--;
		}
		container[j] = temp;
	}
}

template <typename T>
void	PmergeMe::merge(int x, int y, int z, T& container) {
	int	n1 = z - x + 1;
	int	n2 = y - z;
	int rPos = 0;
	int lpos = 0;

	T	leftSize(container.begin() + x, container.begin() + z + 1);
	T	rigthSize(container.begin() + z + 1, container.begin() + y + 1);

	for (int i = x; i < y - x + 1; i++) {
		if (rPos == n2) {
			container[i] = leftSize[lpos];
			lpos++;
		} else if (lpos == n1) {
			container[i] = rigthSize[rPos];
			rPos++;
		} else if (rigthSize[rPos] > leftSize[lpos]) {
			container[i] = leftSize[lpos];
			lpos++;
		} else {
			container[i] = rigthSize[rPos];
			rPos++;
		}
	}
}

template <typename T>
void	PmergeMe::sortContainer(int x, int y, T& container) {
	int	K = container.size() / 2;
	if (y - x > K) {
		int z = (x + y) / 2;
		sortContainer(x, z, container);
		sortContainer(z + 1, y, container);
		merge(x, y, z, container);
	} else {
		insertionSort(x, y, container);
	}
}

bool	PmergeMe::isValidInput(char **input) {
	int			value;
	std::string	temp;

	for (int i = 1; input[i]; i++) {
		for (int j = 0; input[i][j]; j++) {
			if (!std::isdigit(input[i][j]))
				return false;
		}
		temp = input[i];
		if (temp.size() > 10)
			return false;
		char arr[temp.size() + 1];
		for (size_t j = 0; j < temp.size(); j++)
			arr[j] = temp[j];
		arr[temp.size()] = '\0';
		double aux = std::strtod(arr, NULL);
		if (aux > 2147483647)
			return false;
		value = (int) aux;
		if (value < 0)
			return false;
		this->vec.push_back(value);
		this->deq.push_back(value);
	}
	// for (std::vector<int>::iterator it = this->vec.begin(); it != this->vec.end() - 1; it++) {
	// 	for (std::vector<int>::iterator it2 = it + 1; it2 != this->vec.end(); it2++) {
	// 		if (*it == *it2)
	// 			return false;
	// 	}
	// }
	return true;
}

int	PmergeMe::sort(char **input) {
	double	timeVec;
	double	timeDeq;

	if (!isValidInput(input)) {
		std::cout << "Error\n";
		return 1;
	}

	timeVec = timeNow();
	sortContainer(0, this->vec.size() - 1, this->vec);
	timeVec = timeNow() - timeVec;
	timeDeq = timeNow();
	sortContainer(0, this->deq.size() - 1, this->deq);
	timeDeq = timeNow() - timeDeq;

	printResult(input, timeVec, timeDeq);
	return 0;
}

std::vector<int>	PmergeMe::getVec() const {
	return this->vec;
}

std::deque<int>		PmergeMe::getDeq() const {
	return this->deq;
}

std::ostream	&operator<<(std::ostream &o, PmergeMe const &pmm) {
	std::vector<int>	vec = pmm.getVec();

	o << "PmergeMe whit " << vec.size() << "numbers\n";
	return o;
}
