#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

#define LINE_SIZE 42

class BitcoinExchange {
	private:
		std::map<std::string, float>	db;

		void	displayLine(std::string inputLine, int count);
		bool	isValidInputDate(std::string iDate);

	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &src);
		BitcoinExchange &operator=(BitcoinExchange const &rhs);

		std::map<std::string, float>	getDb() const;

		int	displayValues(std::string input);
};

std::ostream	&operator<<(std::ostream &o, BitcoinExchange const &b);

#endif
