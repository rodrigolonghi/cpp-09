#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <sys/time.h>
#include <iomanip>
#include <cstdlib>

class PmergeMe {
	private:
		std::vector<int>	vec;
		std::deque<int>		deq;

		bool	isValidInput(char **input);
		void	printResult(char **input, double timeVec, double timeDeq);
		double	timeNow();
		template <typename T>
		void	sortContainer(int x, int y, T& container);
		template <typename T>
		void	merge(int x, int y, int z, T& container);
		template <typename T>
		void	insertionSort(int x, int y, T& container);
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
