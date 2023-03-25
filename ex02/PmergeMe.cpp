#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {
	this->deq.erase(this->deq.begin());
	this->vec.erase(this->vec.begin());
}

PmergeMe::PmergeMe(PmergeMe const &src) {
	*this = src;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &rhs) {
	this->deq = rhs.getDeq();
	this->vec = rhs.getVec();
	return *this;
}

void	PmergeMe::insertionSortVector(int p, int q) {
	for (int i = p; i < q; i++) {
		int tempVal = this->vec[i + 1];
		int j = i + 1;
		while (j > p && this->vec[j - 1] > tempVal) {
			this->vec[j] = this->vec[j - 1];
			j--;
		}
		this->vec[j] = tempVal;
	}
}

void	PmergeMe::mergeVector(int p, int q, int r) {
	int	n1 = q - p + 1;
	int	n2 = r - q;
	int RIDX = 0;
	int LIDX = 0;
	std::vector<int>	LA;
	std::vector<int>	RA;

	for (int i = p; i < q + 1; i++)
		LA.push_back(this->vec[i]);
	for (int i = q + 1; i < r + 1; i++)
		RA.push_back(this->vec[i]);

	for (int i = p; i < r - p + 1; i++) {
		if (RIDX == n2) {
			this->vec[i] = LA[LIDX];
			LIDX++;
		} else if (LIDX == n1) {
			this->vec[i] = RA[RIDX];
			RIDX++;
		} else if (RA[RIDX] > LA[LIDX]) {
			this->vec[i] = LA[LIDX];
			LIDX++;
		} else {
			this->vec[i] = RA[RIDX];
			RIDX++;
		}
	}
}

void	PmergeMe::sortWithVector(int p, int r) {
	if (r - p > K) {
		int q = (p + r) / 2;
		sortWithVector(p, q);
		sortWithVector(q + 1, r);
		mergeVector(p, q, r);
	} else {
		insertionSortVector(p, r);
	}
}

void	PmergeMe::insertionSortDeque(int p, int q) {
	for (int i = p; i < q; i++) {
		int tempVal = this->deq[i + 1];
		int j = i + 1;
		while (j > p && this->deq[j - 1] > tempVal) {
			this->deq[j] = this->deq[j - 1];
			j--;
		}
		this->deq[j] = tempVal;
	}
}

void	PmergeMe::mergeDeque(int p, int q, int r) {
	int	n1 = q - p + 1;
	int	n2 = r - q;
	int RIDX = 0;
	int LIDX = 0;
	std::deque<int>	LA;
	std::deque<int>	RA;

	for (int i = p; i < q + 1; i++)
		LA.push_back(this->deq[i]);
	for (int i = q + 1; i < r + 1; i++)
		RA.push_back(this->deq[i]);

	for (int i = p; i < r - p + 1; i++) {
		if (RIDX == n2) {
			this->deq[i] = LA[LIDX];
			LIDX++;
		} else if (LIDX == n1) {
			this->deq[i] = RA[RIDX];
			RIDX++;
		} else if (RA[RIDX] > LA[LIDX]) {
			this->deq[i] = LA[LIDX];
			LIDX++;
		} else {
			this->deq[i] = RA[RIDX];
			RIDX++;
		}
	}
}

void	PmergeMe::sortWithDeque(int p, int r) {
	if (r - p > K) {
		int q = (p + r) / 2;
		sortWithDeque(p, q);
		sortWithDeque(q + 1, r);
		mergeDeque(p, q, r);
	} else {
		insertionSortDeque(p, r);
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
		value = std::stoi(temp);
		if (value < 0)
			return false;
		this->vec.push_back(std::stoi(temp));
		this->deq.push_back(std::stoi(temp));
	}
	return true;
}

int	PmergeMe::sort(char **input) {
	//TODO: adicionar contagem de tempo
	//TODO: adicionar print final
	if (!isValidInput(input)) {
		std::cout << "Error\n";
		return 1;
	}
	std::cout << "Before: ";
	for (size_t n = 0; n < this->vec.size(); n++)
		std::cout << this->vec[n] << " ";
	std::cout << "\n";
	sortWithVector(0, this->vec.size() - 1);
	sortWithDeque(0, this->deq.size() - 1);
	std::cout << "After:  ";
	for (size_t n = 0; n < this->deq.size(); n++)
		std::cout << this->deq[n] << " ";
	std::cout << "\n";
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
