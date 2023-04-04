#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {
	this->expressionElements.clear();
}

RPN::RPN(RPN const &src) {
	*this = src;
}

RPN &RPN::operator=(RPN const &rhs) {
	this->expressionElements = rhs.expressionElements;
	return *this;
}

std::list<char>	RPN::getExpressionElements() const {
	return this->expressionElements;
}

int	RPN::checkInput(std::string input) {
	for (size_t i = 0; i < input.size(); i++) {
		if (input[i] == 32)
			continue;
		if (std::isdigit(input[i]) || input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
			this->expressionElements.push_back(input[i]);
		} else {
			std::cout << "Error\n";
			return (0);
		}
	}
	return (1);
}

int	RPN::calculate(std::string input) {
	std::list<int>	elems;
	int				result = 0;

	if (!checkInput(input))
		return (1);

	for (std::list<char>::iterator it = this->expressionElements.begin(); it != this->expressionElements.end(); it++) {
		if (it == this->expressionElements.begin()) {
			elems.push_front(*it - 48);
			it++;
			if (!std::isdigit(*it)) { 
				std::cout << "Error\n";
				return (1);
			}
			elems.push_front(*it - 48);
			continue;
		}
		else {
			if (!std::isdigit(*it)) {
				result = elems.front();
				elems.pop_front();
				if (*it == '+')
					result = elems.front() + result;
				else if (*it == '-')
					result = elems.front() - result;
				else if (*it == '*')
					result = elems.front() * result;
				else if (*it == '/') {
					if (result == 0) {
						std::cout << "Error\n";
						return (1);
					}
					result = elems.front() / result;
				}
				elems.pop_front();
				elems.push_front(result);
			} else
				elems.push_front(*it - 48);
		}
	}
	if (elems.size() != 1) {
		std::cout << "Error\n";
		return (1);
	}
	std::cout << elems.front() << std::endl;
	return (0);
}

std::ostream	&operator<<(std::ostream &o, RPN const &b) {
	std::list<char>	elements = b.getExpressionElements();

	o << "RPN expression elements: ";
	for (std::list<char>::iterator it = elements.begin(); it != elements.end(); it++) {
		o << *it << " ";
	}
	o << std::endl;
	return o;
}
