#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
	int				pos = 0;
	std::string		dataFile = "data.csv";
	std::ifstream	data(dataFile.c_str());
	std::string		line;

	while (std::getline(data, line)) {
		if (pos == 0 || line.size() == 0) {
			pos++;
			continue;
		}
		std::stringstream ss(line);
		std::string date;
		float value;

		std::getline(ss, date, ',');
		ss >> value;
		this->db[date] = value;
		pos++;
	}
	data.close();
}

BitcoinExchange::~BitcoinExchange() {
	this->db.clear();
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &src) {
	*this = src;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &rhs) {
	this->db = rhs.db;
	return *this;
}

std::map<std::string, float>	BitcoinExchange::getDb() const {
	return (this->db);
}

float	BitcoinExchange::getDbValue(const std::map<std::string, float>& dataBase, const std::string& iDate) {
	if (dataBase.find(iDate) != dataBase.end()) {
		return dataBase.at(iDate);
	}

	std::map<std::string, float>::const_iterator upperBound = dataBase.upper_bound(iDate);
	if (upperBound == dataBase.begin()) {
		return upperBound->second;
	}
	--upperBound;
	return upperBound->second;
}

bool	BitcoinExchange::isValidInputNumber(std::string line, float *iNbr) {
	std::string temp = line.substr(line.find("|") + 1);
	temp.erase(std::remove_if(temp.begin(), temp.end(), ::isspace), temp.end());
	char arr[temp.size() + 1];
	for (size_t j = 0; j < temp.size(); j++)
		arr[j] = temp[j];
	arr[temp.size()] = '\0';
	*iNbr = (float) std::strtod(arr, NULL);
	if (*iNbr < 0) {
		std::cout << "Error: not a positive number.\n";
		return false;
	}
	if (*iNbr > 1000) {
		std::cout << "Error: too large number.\n";
		return false;
	}
	return true;
}

bool	BitcoinExchange::isValidInputDate(std::string inputLine, std::string *iDate) {
	int	year;
	int	month;
	int	day;
	std::string	temp;

	temp = inputLine.substr(0, inputLine.find("|"));
	*iDate = temp;
	temp.erase(std::remove_if(temp.begin(), temp.end(), ::isspace), temp.end());

	if (temp.size() != 10)
		return false;

	sscanf(temp.c_str(), "%d-%d-%d", &year, &month, &day);
	if (year < 2009 || year > 2022 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;
	if (month == 2 && day > 29)
		return false;
	if (month == 2 && day == 29 && year != 2012 && year != 2016 && year != 2020)
		return false;
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31)
		return false;
	if (temp < "2009-01-02" || temp > "2022-03-29")
		return false;
	*iDate = temp;
	return true;
}

bool	BitcoinExchange::isValidLine(std::string line, int count) {
	if (count == 0 && line == "date | value")
		return false;
	if (line.size() == 0)
		return false;
	std::string::difference_type n = std::count(line.begin(), line.end(), '|');
	if (n == 0 || n > 1 || line.size() < 14) {
		std::cout << "Error: bad input => " << line << std::endl;
		return false;
	}
	return true;
}

void	BitcoinExchange::displayLine(std::string inputLine, int count) {
	float		iNbr;
	float		dbNbr;
	std::string	iDate;

	if (!isValidLine(inputLine, count))
		return ;

	if (!isValidInputDate(inputLine, &iDate)) {
		std::cout << "Error: not a valid date => " << iDate << std::endl;
		return ;
	}

	if (!isValidInputNumber(inputLine, &iNbr))
		return ;

	dbNbr = getDbValue(this->db, iDate);
	std::cout << iDate << " => " << iNbr << " = " << iNbr * dbNbr << std::endl;
}

int	BitcoinExchange::displayValues(char *input) {
	int				count = 0;
	std::string		line;
	std::ifstream	fin(input);

	if (!fin.is_open()) {
		std::cout << "Error: Failed to open file \"" << input << "\"\n";
		return (1);
	}

	while (std::getline(fin, line)) {
		displayLine(line, count);
		count++;
	}
	fin.close();
	return 0;
}

std::ostream	&operator<<(std::ostream &o, BitcoinExchange const &b) {
	std::map<std::string, float>	db = b.getDb();

	o << "BitcoinExchange with " << db.size() - 1 << " values.\n" << std::endl;
	return o;
}
