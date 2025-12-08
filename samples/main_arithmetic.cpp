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
    std::cout << "1. Ввести новое выражение" << std::endl;
    std::cout << "2. Преобразовать в постфиксную форму" << std::endl;
    std::cout << "3. Ввести значения переменных" << std::endl;
    std::cout << "4. Вычислить выражение" << std::endl;
    std::cout << "Выберите действие: ";
    std::cin >> choice;
    system("cls");
        switch (choice) {
        case 1:
            std::cout << "Введите свое выражение: " << std::endl;
            std::cin.ignore(); 
            std::getline(std::cin, input);

            if (input.empty()) {
                std::cout << "Ошибка: выражение пустое" << std::endl;
                break;
            }

            try {
                expression.setExpression(input);
                std::cout << "Выражение успешно установлено" << std::endl;
            }
            catch (const std::string& error) {
                std::cout << "Ошибка: " << error << std::endl;
            }
            break;
        case 2:
            if (expression.hasInfix()) {
                std::cout << "Cначала введите выражение" << std::endl;
                break;
            }
            try {
                expression.toPostfix();
                std::cout << "Постфиксная форма: " << expression.getPostfix() << std::endl;
            }
            catch (const std::string& error) {
                std::cout << "Ошибка " << error << std::endl;
            }
            break;
        case 3:
            if (expression.hasInfix()) {  
                std::cout << "Сначала введите выражение" << std::endl;
                break;
            }
            std::cout << "Для выхода нажмите 0" << std::endl;
            double valInp;
            char nameInp;
            while (true) {
                std::cout << "Введите имя переменной (одна буква) или 0 для выхода: ";
                std::string temp ;
                std::cin >> temp;
                if (temp == " ") {
                    std::cout << "Пустой ввод." << std::endl;
                    continue;
                }

                if (temp == "0") {
                    break;
                }
                if (temp.length() != 1) {
                    std::cout << "Ошибка. Попробуйте снова" << std::endl;
                    temp = " ";
                    continue;
                }
                if (temp >= "a" && temp <= "z") nameInp = temp[0];
                else {
                    std::cout << "Ошибка. Попробуйте снова" << std::endl;
                    temp = " ";
                    continue;
                }

                std::cout << "Введите значение для переменной " << nameInp << ": ";
                std::cin >> valInp;
                std::cout << std::endl;

                try {
                    if (valInp != 0) {
                        expression.setValue(nameInp, valInp);
                        std::cout << "Значение переменной " << nameInp << " установлено в " << valInp << std::endl;
                    }
                    else {
                        continue;
                    }
                }
                catch (const std::string& error) {
                    std::cout << "Ошибка: " << error << std::endl;
                }
            }
            break;
        case 4:
            if (expression.hasInfix()) {
                std::cout << "Cначала введите выражение" << std::endl;
                break;
            }
            try {
                double result = expression.calculate();
                std::cout << "Результат: " << result << std::endl;
            }
            catch (const std::string& error) {
                std::cout << "Ошибка: " << error << std::endl;
            }
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
            break;
        

        }

    }
    return 0;
}