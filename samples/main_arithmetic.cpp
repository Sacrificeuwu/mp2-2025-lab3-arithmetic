// реализация пользовательского приложения
#include <iostream>
#include "arithmetic.h"
#include <cstdlib>
#include <sstream>
#include <string>
//a+b*c+(d*e+f)*g
int main() {
    TArifmeticExpression expression;
    while (true) {
    std::string input;
    int choice;
    std::cout << "1. Enter a new expression" << std::endl;
    std::cout << "2. Convert to postfix form" << std::endl;
    std::cout << "3. Enter variable values" << std::endl;
    std::cout << "4. Evaluate the expression" << std::endl;
    std::cout << "Select action: ";
    std::cin >> choice;
    system("cls");
        switch (choice) {
        case 1:
            std::cout << "Enter your expression: " << std::endl;
            std::cin.ignore(); 
            std::getline(std::cin, input);

            if (input.empty()) {
                std::cout << "Error: expression is empty" << std::endl;
                break;
            }

            try {
                expression.setExpression(input);
                std::cout << "Expression set successfully" << std::endl;
            }
            catch (const std::string& error) {
                std::cout << "Error" << error << std::endl;
            }
            break;
        case 2:
            if (expression.hasInfix()) {
                std::cout << "First enter the expression" << std::endl;
                break;
            }
            try {
                expression.toPostfix();
                std::cout << "Postfix form: " << expression.getPostfix() << std::endl;
            }
            catch (const std::string& error) {
                std::cout << "Error " << error << std::endl;
            }
            break;
        case 3:
            if (expression.hasInfix()) {  
                std::cout << "First enter the expression" << std::endl;
                break;
            }
            std::cout << "To exit, press 0" << std::endl;
            double valInp;
            char nameInp;
            while (true) {
                std::cout << "Enter a variable name (one letter) or 0 to exit:";
                std::string temp ;
                std::cin >> temp;
                if (temp == " ") {
                    std::cout << "Empty input." << std::endl;
                    continue;
                }

                if (temp == "0") {
                    break;
                }
                if (temp.length() != 1) {
                    std::cout << "Error. Try again" << std::endl;
                    temp = " ";
                    continue;
                }
                if (temp >= "a" && temp <= "z") nameInp = temp[0];
                else {
                    std::cout << "Error. Try again" << std::endl;
                    temp = " ";
                    continue;
                }

                std::cout << "Enter a value for the variable " << nameInp << ": ";
                std::cin >> valInp;
                std::cout << std::endl;

                try {
                    if (valInp != 0) {
                        expression.setValue(nameInp, valInp);
                        std::cout << "Variable value " << nameInp << " installed in " << valInp << std::endl;
                    }
                    else {
                        continue;
                    }
                }
                catch (const std::string& error) {
                    std::cout << "Error " << error << std::endl;
                }
            }
            break;
        case 4:
            if (expression.hasInfix()) {
                std::cout << "First enter the expression" << std::endl;
                break;
            }
            try {
                double result = expression.calculate();
                std::cout << "Result:" << result << std::endl;
            }
            catch (const std::string& error) {
                std::cout << "Error: " << error << std::endl;
            }
            break;
        default:
            std::cout << "Incorrect selection. Try again." << std::endl;
            break;
        

        }

    }
    return 0;
}