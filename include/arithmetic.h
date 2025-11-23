#include <iostream>
#include <vector>
#include <map>
#include <stack.h>

class TArifmeticExpression {
	std::string infix;
	std::string postfix;
	std::vector<char> lexems;
	std::map <char, int> priority;
	std::map <char, double> operands;
public:
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
	void setExpression(const std::string& expression) {
		if (expression.empty()) {
			throw std::string("empty expression");
		}
		infix = expression;
		postfix = "";
		lexems.clear();
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
			const char& lexem = lexems[i];
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
					else {
						throw std::string("not found '('");
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
				else {
					throw std::string("Anknown simb");
				}
			}
		}
		while (!stack.isEmpty()) {
			variables += stack.pop();
		}
		std::cout << variables;
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