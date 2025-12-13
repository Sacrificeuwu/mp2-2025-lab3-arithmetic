#include <iostream>
#include <vector>
#include <map>
#include <stack.h>
#include <sstream>
#include <string>
#include <limits>
class TArifmeticExpression {
	std::string infix;
	std::string postfix;
    std::vector<std::string> lexems; 
    std::map<char, int> priority;
    std::map<std::string, double> operands;
public:
	TArifmeticExpression() {
		priority['('] = 1;
		priority[')'] = 1;
		priority['+'] = 2;
		priority['-'] = 2;
		priority['*'] = 3;
		priority['/'] = 3;
		priority['^'] = 4;
	}
	TArifmeticExpression(const std::string& expression) {
		if (expression.empty()) {
			throw std::string("empty expression ");
		}
		infix = expression;
		priority['('] = 1;
		priority[')'] = 1;
		priority['+'] = 2;
		priority['-'] = 2;
		priority['*'] = 3;
		priority['/'] = 3;
		priority['^'] = 4;
	}
	bool checkValid(const std::string& expression, int& errorPosition, std::string& errorMessage) {
		int bracketBalance = 0;
		bool expectingOperand = true;
		bool lastWasOperator = false;

		for (size_t i = 0; i < expression.length(); ++i) {
			char cur = expression[i];

			if (std::isspace(static_cast<unsigned char>(cur))) {
				continue;
			}

			bool isValidChar = (cur >= 'a' && cur <= 'z') ||
				(cur >= 'A' && cur <= 'Z') ||
				(cur >= '0' && cur <= '9') ||
				cur == '.' ||
				cur == '+' || cur == '-' ||
				cur == '*' || cur == '/' ||
				cur == '^' || cur == '(' || cur == ')';

			if (!isValidChar) {
				errorPosition = static_cast<int>(i);
				errorMessage = "Invalid character: " + std::string(1, cur);
				return false;
			}

			if (cur == '(') {
				bracketBalance++;
				expectingOperand = true;
				lastWasOperator = false;
			}
			else if (cur == ')') {
				bracketBalance--;
				if (bracketBalance < 0) {
					errorPosition = static_cast<int>(i);
					errorMessage = "Extra closing parenthesis";
					return false;
				}
				expectingOperand = false;
				lastWasOperator = false;
			}
			else if ((cur >= 'a' && cur <= 'z') || (cur >= 'A' && cur <= 'Z')) {
				if (!expectingOperand) {
					errorPosition = static_cast<int>(i);
					errorMessage = "Operator expected before variable";
					return false;
				}
				expectingOperand = false;
				lastWasOperator = false;
			}
			else if (std::isdigit(static_cast<unsigned char>(cur))) {
				bool hasDecimal = false;
				size_t j = i;
				while (j < expression.length() &&
					(std::isdigit(static_cast<unsigned char>(expression[j])) || expression[j] == '.')) {
					if (expression[j] == '.') {
						if (hasDecimal) {
							errorPosition = static_cast<int>(j);
							errorMessage = "Multiple decimal points in number";
							return false;
						}
						hasDecimal = true;
					}
					j++;
				}

				if (j > i && expression[j - 1] == '.') {
					errorPosition = static_cast<int>(j - 1);
					errorMessage = "Number cannot end with decimal point";
					return false;
				}

				if (!expectingOperand) {
					errorPosition = static_cast<int>(i);
					errorMessage = "Operator expected before number";
					return false;
				}

				i = j - 1;
				expectingOperand = false;
				lastWasOperator = false;
			}
			else if (cur == '+' || cur == '-' || cur == '*' || cur == '/' || cur == '^') {
				if (expectingOperand && !(cur == '+' || cur == '-')) {
					errorPosition = static_cast<int>(i);
					errorMessage = "Operand expected before operator";
					return false;
				}
				if (!expectingOperand) {
					expectingOperand = true;
					lastWasOperator = true;
				}
			}
		}

		if (expectingOperand && lastWasOperator) {
			errorPosition = static_cast<int>(expression.length()) - 1;
			errorMessage = "Expression ends with operator";
			return false;
		}

		if (bracketBalance > 0) {
			errorPosition = static_cast<int>(expression.length()) - 1;
			errorMessage = "Missing closing parentheses";
			return false;
		}

		return true;
	}

	std::vector<char> simbToEnter() {
		if (postfix.empty()) {
			throw std::string("call toPostfix()");
		}
		std::vector<char> res;
		std::vector<std::string> tokens;
		std::stringstream ss(postfix);
		std::string token;

		while (ss >> token) {
			tokens.push_back(token);
		}
		for (int i = 0; i < size(tokens); i++) {
			std::string curToken = tokens[i];
			if (curToken >= "a" && curToken <= "z") {
				char sim = curToken[0];
				res.push_back(sim);
			}
		}
		return res;
	}



	void setExpression(const std::string& expression) {
		int errorPosition = 0;
		std::string errorMessage;

		if (expression.empty()) {
			throw std::string("Expression cannot be empty");
		}

		if (!checkValid(expression, errorPosition, errorMessage)) {
			std::string error = "Error in expression at position " +
				std::to_string(errorPosition + 1) + ": " + errorMessage;
			throw error;
		}

		infix = expression;
		postfix = "";
		lexems.clear();
	}


    void toLexems() {
        lexems.clear();
        for (size_t i = 0; i < infix.length(); ++i) {
            char cur = infix[i];
            if (std::isspace(cur)) {
                continue;
            }
            else if ((cur >= 'a' && cur <= 'z') || (cur >= 'A' && cur <= 'Z')) {
				std::string temp;
				temp = cur;  
				lexems.push_back(temp);
            }
            else if (std::isdigit(cur) || cur == '.') {
                std::string number;
                while (i < infix.length() &&
                    (std::isdigit(infix[i]) || infix[i] == '.')) {
                    number += infix[i];
                    i++;
                }
                i--;
                lexems.push_back(number);
            }
            else if (cur == '+' || cur == '-' || cur == '*' ||
                cur == '/' || cur == '^' || cur == '(' || cur == ')') {
				std::string temp;
				temp = cur;
				lexems.push_back(temp);
            }
            else {
				std::string temp;
				temp = cur;
                throw std::string("Invalid symbol: " + temp);
            }
        }
    }

	void toPostfix() {
		toLexems();
		std::string result = "";
		TStack<std::string> stack;

		for (size_t i = 0; i < lexems.size(); ++i) {
			const std::string& lexem = lexems[i];

			if (lexem == "(") {
				stack.push(lexem);
			}
			else if (lexem == ")") {
				while (!stack.isEmpty() && stack.seeLast() != "(") {
					result += stack.pop() + " ";
				}
				if (!stack.isEmpty() && stack.seeLast() == "(") {
					stack.pop();
				}
			}
			else if (lexem == "+" || lexem == "-" || lexem == "*" || lexem == "/" || lexem == "^") {
				int cur_prior = priority[lexem[0]];
				while (!stack.isEmpty() &&
					stack.seeLast() != "(" &&
					priority[stack.seeLast()[0]] >= cur_prior) {
					result += stack.pop() + " ";
				}
				stack.push(lexem);
			}
			else {
				result += lexem + " ";
			}
		}
		while (!stack.isEmpty()) {
			result += stack.pop() + " ";
		}
		if (!result.empty() && result.back() == ' ') {
			result.pop_back();
		}
		postfix = result;
	}
	double calculate() {
		if (postfix.empty()) {
			throw std::string("call toPostfix()");
		}
		TStack<double> stack;
		std::vector<std::string> tokens;
		std::stringstream ss(postfix);
		std::string token;

		while (ss >> token) {
			tokens.push_back(token);
		}
		for (int i = 0; i < size(tokens); i++) {
			std::string curToken = tokens[i];

			if (isNumber(curToken)) {
				stack.push(std::stod(curToken));
			}
			else if (curToken >= "a" && curToken <= "z" && curToken.length( ) == 1){
				stack.push(operands[curToken]);
			}
			else {
				char op = curToken[0];
				double a = stack.pop();
				double b = stack.pop();
				switch (op) {
				case '+': stack.push(b + a); break;
				case '-': stack.push(b - a); break;
				case '*': stack.push(b * a); break;
				case '/': {
					if (a == 0) {
						throw std::string("Div by zero");
					}
					else {
						stack.push(b / a);
						break;
					}
				}
				case '^': {
						stack.push(pow(b, a));
						break;
					}
				default: throw std::string("Unknown operator: " + token);
				}

			}
		}
		if (stack.size() != 1) {
			throw std::string("size!");
		}
		return stack.pop();
	}
	void clearAllExpr() {
		infix.clear();
		postfix.clear();
		lexems.clear();
		operands.clear();
	}
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


    void setValue(const std::string & name, double value) {
        if (name >= "a" && name <= "z")  {
            operands[name] = value;
        }
        else {
            throw std::string("Variable name must be a single letter");
        }
    }

	std::string getPostfix() {
		if (postfix.empty()) {
			throw std::string("call toPostfix()");
		}
		return postfix;
	}
	std::string getInfix() {
		return infix;
	}
	bool hasInfix() {
		if (infix.empty()) return true;
		else return false;
	}

};