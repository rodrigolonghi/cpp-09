#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

#define LINE_SIZE 42

class BitcoinExchange {
	private:
		std::vector<std::string>	db;

		void	displayLine(std::string inputLine, int count);
		bool	isValidInputDate(std::string iDate);

	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &src);
		BitcoinExchange &operator=(BitcoinExchange const &rhs);

		std::vector<std::string>	getDb() const;

		int	displayValues(std::string input);
};

std::ostream	&operator<<(std::ostream &o, BitcoinExchange const &b);

#endif
