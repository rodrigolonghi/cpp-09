#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <iostream>

#define K 5

class PmergeMe {
	private:
		std::vector<int>	vec;
		std::deque<int>		deq;

		bool	isValidInput(char **input);
		void	sortWithVector(int p, int r);
		void	mergeVector(int p, int q, int r);
		void	insertionSortVector(int p, int q);
		void	sortWithDeque(int p, int r);
		void	mergeDeque(int p, int q, int r);
		void	insertionSortDeque(int p, int q);
	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(PmergeMe const &src);
		PmergeMe &operator=(PmergeMe const &rhs);

		std::vector<int>	getVec() const;
		std::deque<int>		getDeq() const;

		int	sort(char **input);
};

std::ostream	&operator<<(std::ostream &o, PmergeMe const &b);

#endif
