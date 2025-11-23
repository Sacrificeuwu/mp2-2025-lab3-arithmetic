// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память


#include <iostream>

template<typename T>
class TStack {
private:
	int top;
	int sizeStack;
	T* data;
public:
	TStack(int initSize = 100) : top(-1), sizeStack(initSize){
		if (initSize <= 0) {
			throw std::string("Size must be positive");
		}
		data = new T[initSize];
	}
	~TStack() {
		delete[] data;
	}
	bool isEmpty() const {
		return top == -1;
	}

	void push(const T& value) {
		if (top >= sizeStack - 1) {
			throw std::string("stack is full");
		}
		data[++top] = value;
	}
	T pop() {
		if (isEmpty()) {
			throw std::string("Stack is empty");
		}
		return data[top--];
	}
	T& seeLast() {
		if (isEmpty()) {
			throw std::string("Stack is empty");
		}
		return data[top];
	}
	int size() const {
		return top + 1;
	}
	void clear() {
		top = -1;
	}

};
