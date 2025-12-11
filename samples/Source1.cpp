#include <iostream>
#include <arithmetic.h>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
bool isNumber(const std::string& s) {
	try {
		size_t pos;
		std::stod(s, &pos);
		return pos == s.length();
	}
	catch (...) {
		return false;
	}
}

int main() {

	std::cout << isNumber('12')
	return 0;
}