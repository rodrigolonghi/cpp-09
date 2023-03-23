#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
	char			buff[LINE_SIZE];
	std::ifstream	data("data.csv");

	while (data) {
		data.getline(buff, LINE_SIZE);
		this->db.push_back(buff);
	}
}

BitcoinExchange::~BitcoinExchange() {
	this->db.clear();
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &src) {
	*this = src;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &rhs) {
	for (size_t i = 0; i < rhs.db.size(); i++) {
		this->db.push_back(rhs.db[i]);
	}
	return *this;
}

std::vector<std::string>	BitcoinExchange::getDb() const {
	return (this->db);
}

bool	BitcoinExchange::isValidInputDate(std::string iDate) {
	int			aux = 0;
	int			firstLim = -1;
	int			secondLim = -1;
	double		year;
	double		month;
	double		day;
	std::string	temp;

	if (iDate.size() != 10)
		return false;
	for (size_t i = 0; i < iDate.size(); i++) {
		if (iDate[i] == '-')
		{
			if (firstLim == -1)
				firstLim = i;
			else
				secondLim = i;
			aux++;
		}
		if (!std::isdigit(iDate[i]) && iDate[i] != '-')
			return false;
	}
	if (aux != 2)
		return false;

	temp = iDate.substr(0, firstLim);
	if (temp.size() != 4)
		return false;
	year = std::stod(temp);

	temp = iDate.substr(firstLim + 1, secondLim - firstLim - 1);
	if (temp.size() != 2)
		return false;
	month = std::stod(temp);

	temp = iDate.substr(secondLim + 1);
	if (temp.size() != 2)
		return false;
	day = std::stod(temp);

	if (year < 2009 || year > 2022 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;
	if (month == 2 && day > 29)
		return false;
	if (iDate < "2009-01-02" || iDate > "2022-03-29")
		return false;
	return true;
}

void	BitcoinExchange::displayLine(std::string inputLine, int count) {
	int			aux = 0;
	int			index = 0;
	float		iNbr;
	float		dbNbr;
	std::string	iDate;

	if (count == 0 && inputLine == "date | value")
		return ;
	for (size_t i = 0; i < inputLine.size(); i++) {
		if (inputLine[i] == '|')
			aux++;
	}
	if (inputLine.size() == 0)
		return ;
	if (aux == 0 || aux > 1 || inputLine.size() < 14) {
		std::cout << "Error: bad input => " << inputLine << std::endl;
		return ;
	}

	iDate = inputLine.substr(0, inputLine.find("|"));
	iDate.erase(std::remove_if(iDate.begin(), iDate.end(), ::isspace), iDate.end());
	if (!isValidInputDate(iDate)) {
		std::cout << "Error: not a valid date => " << iDate << std::endl;
		return ;
	}

	iNbr = std::stof(inputLine.substr(inputLine.find("|") + 1));
	if (iNbr < 0) {
		std::cout << "Error: not a positive number.\n";
		return ;
	}
	if (iNbr > 1000) {
		std::cout << "Error: too large number.\n";
		return ;
	}

	for (size_t i = 1; i < this->db.size(); i++) {
		std::string temp = this->db[i].substr(0, 10);
		if (temp == iDate) {
			index = i;
			break;
		}
		if (temp > iDate && i > 1) {
			index = i -1;
			break;
		}
	}
	if (index == 0) {
		std::cout << "Error: date not found in data base => " << iDate << std::endl;
		return ;
	}
	dbNbr = std::stof(db[index].substr(11));
	std::cout << iDate << " => " << iNbr << " = " << iNbr * dbNbr << std::endl;
}

int	BitcoinExchange::displayValues(std::string input) {
	int				count = 0;
	char			buff[LINE_SIZE];
	std::ifstream	fin(input);

	if (!fin.is_open()) {
		std::cout << "Error: Failed to open file \"" << input << "\"\n";
		return (1);
	}
	while (fin) {
		fin.getline(buff, LINE_SIZE);
		displayLine(buff, count);
		count++;
	}
	return 0;
}

std::ostream	&operator<<(std::ostream &o, BitcoinExchange const &b) {
	std::vector<std::string>	db = b.getDb();

	o << "BitcoinExchange with " << db.size() - 1 << " values.\n" << std::endl;
	return o;
}
