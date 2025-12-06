// реализация пользовательского приложения
#include <iostream>
#include "arithmetic.h"
#include <cstdlib>

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
            std::cout << "Введите свое выражение " << std::endl;
            std::cin >> input;
            if (input.empty()) {
                std::cout << "Ошибка: выражение пустое " << std::endl;
                break;
            }
            else expression.setExpression(input);
            std::cout << "Выражение успешно установлено" << std::endl;
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
                std::cout << "Cначала введите выражение" << std::endl;
                break;
            }
            std::cout << "Для выхода нажмите 0";
            double valInp;
            char nameInp;
            while (true) {
                std::cout << "Введите имя переменной (одна буква) или 0 для выхода: ";
                std::cin >> nameInp;
                if (nameInp == '0') {
                    break;
                }
                std::cout << "Введите значение для переменной " << nameInp << ": ";
                std::cin >> valInp;
                std::cout << std::endl;
                try {
                    expression.setValue(nameInp, valInp);
                    std::cout << "Установлено" << std::endl;
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

        }

    }
    return 0;
}