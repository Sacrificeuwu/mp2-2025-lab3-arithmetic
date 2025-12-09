#include <iostream>
#include <vector>
#include <map>
#include <stack.h>
#include <string>
class TArifmeticExpression {
	std::string infix;
	std::string postfix;
	std::vector<char> lexems;
	std::map <char, int> priority;
	std::map <char, double> operands;
public:
	TArifmeticExpression() {
		// Инициализация приоритетов
		priority['('] = 0;
		priority[')'] = 0;
		priority['+'] = 1;
		priority['-'] = 1;
		priority['*'] = 2;
		priority['/'] = 2;
		priority['^'] = 3;
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

		for (int i = 0; i < expression.length(); ++i) {
			char cur = expression[i];
			if (isspace(cur)) {
				continue;
			}
			if (!((cur >= 'a' && cur <= 'z') ||
				cur == '+' || cur == '-' || cur == '*' ||
				cur == '/' || cur == '^' || cur == '(' || cur == ')')) {
				errorPosition = i;
				errorMessage = "!" ;
				return false;
			}

			if (cur == '(') {
				bracketBalance++;
				if (!expectingOperand) {
					errorPosition = i;
					errorMessage = "Operator expected before '('";
					return false;
				}
				expectingOperand = true;
			}
			else if (cur == ')') {
				bracketBalance--;
				if (expectingOperand && expression[i - 1] != ')') {
					errorPosition = i;
					errorMessage = "Empty parentheses or missing operand before ')'";
					return false;
				}
				if (bracketBalance < 0) {
					errorPosition = i;
					errorMessage = "Extra closing parenthesis";
					return false;
				}
				expectingOperand = false; 
			}

			else if (cur >= 'a' && cur <= 'z') {
				if (!expectingOperand) {
					errorPosition = i;
					errorMessage = std::string("Operator was expected before ") + cur ;
					return false;
				}
				expectingOperand = false; 
			}
			else if (cur == '+' || cur == '-' || cur == '*' || cur == '/' || cur == '^') {
				if (expectingOperand) { 
					errorPosition = i;
					errorMessage = std::string("An operand was expected before ") + cur ;
					return false;
				}
				expectingOperand = true; 
			}
		}
		if (expectingOperand) {
			errorPosition = expression.length() - 1;
			errorMessage = "The expression ends with the operator";
			return false;
		}

		if (bracketBalance > 0) {
			errorPosition = expression.length() - 1;
			errorMessage = "Missing closing parentheses";
			return false;
		}

		return true;
	}

	void setExpression(const std::string& expression) {
		int errorPosition;
		std::string errorMessage;

		if (!checkValid(expression, errorPosition, errorMessage)) {
			std::string error = "Error in expression at position " + std::to_string(errorPosition +1) + ": " + errorMessage;
			throw error;
		}

		infix = expression;
		postfix = "";
		lexems.clear();
		operands.clear(); 
	}
	bool hasInfix() {
		if (infix.empty()) return true;
		else return false;
	}
	void toLexems() {
		lexems.clear();
		for (int i = 0; i < infix.length(); ++i) {
			char cur = infix[i];
			if (isspace(cur)) {
				continue;
			}
			else if ((cur >= 'a' && cur <= 'z') ||
				cur == '+' || cur == '-' || cur == '*' ||
				cur == '/' || cur == '^' || cur == '(' || cur == ')') {
				lexems.push_back(cur);
			}
			else {
				throw std::string("Invalid simbvol");
			}
		}
	}
	
	void toPostfix() {
		toLexems();
		std::string variables = "";
		TStack<char> stack;
		bool openingBracket = false;
		for (int i = 0; i < size(lexems); ++i) {
			if (lexems[i] >= 'a' && lexems[i] <= 'z') {
				variables += lexems[i];
			}
			else {
				size_t stack_prior;
				if (!stack.isEmpty()) stack_prior = priority[stack.seeLast()];
				else stack_prior = 0;
				size_t cur_prior = priority[lexems[i]];
				if (lexems[i] == '(') {
					stack.push(lexems[i]);
					openingBracket = true;
				}
				else if (lexems[i] == ')') {
					if (openingBracket) {
						while (stack.seeLast() != '(' && !stack.isEmpty()) {
							variables += stack.pop();
						}
						if (!stack.isEmpty() && stack.seeLast() == '(') {
							stack.pop();
						}
						openingBracket = false;
					}
				}
				else if (cur_prior >= stack_prior) {
					stack.push(lexems[i]);
				}
				else if (cur_prior < stack_prior) {
					while (!stack.isEmpty() && priority[stack.seeLast()] >= cur_prior) {
						variables += stack.pop();
					}
					//variables += stack.pop();
					stack.push(lexems[i]);
				}

			}
		}
		while (!stack.isEmpty()) {
			variables += stack.pop();
		}
		postfix = variables;
	}

	double calculate() {
		if (postfix.empty()) {
			throw std::string("call toPostfix()");
		}
		TStack<double> stack;
		for (int i = 0; i < postfix.length(); i++) {
			char curEl = postfix[i];
			if (curEl >= 'a' && curEl <= 'z') {
				stack.push(operands[curEl]);
			}
			else {
				double a = stack.pop();
				double b = stack.pop();
				switch (curEl) {
				case '+': stack.push(a + b); break;
				case '-': stack.push(b - a); break;
				case '*': stack.push(a * b); break;
				case '/': stack.push(b / a); break;
				}

			}
		}
		return stack.pop();
	}

	void setValue(const char& name, double value) {
		if (name >= 'a' && name <= 'z') {
			operands[name] = value;	
		}
		else { throw std::string("Variable name must be a letter"); }
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

};