/*Создать Container для типа char c виртуальными методами push, pop, isEmpty.
В качестве хранилища данных использовать динамический массив с возможностью его увеличения.
На основе Container реализовать классы Stack(стек) и Queue(очередь) с
соответствующей реализацией push и pop.Размер объекта класса задается при его создании.
*/


#include <iostream>
#include <locale.h>

using namespace std;

// Базовый абстрактный класс Container
class Container {
protected:
    char* data;    // Указатель на массив для хранения элементов
    int size;      // Максимальный размер контейнера
    int count;     // Текущее количество элементов в контейнере

    // Метод для увеличения размера массива при переполнении
    void resize() {
        int newSize = size * 2;                    // Увеличиваем размер в 2 раза
        char* newData = new char[newSize];         // Создаем новый массив
        for (int i = 0; i < count; ++i) {
            newData[i] = data[i];                  // Копируем старые данные
        }
        delete[] data;                             // Освобождаем старую память
        data = newData;                            // Обновляем указатель
        size = newSize;                            // Обновляем размер
    }

public:
    // Конструктор - создает контейнер заданного размера
    Container(int s) : size(s), count(0) {
        data = new char[size];                     // Выделяем память под массив
    }

    // Виртуальный деструктор для корректного удаления производных классов
    virtual ~Container() {
        delete[] data;                             // Освобождаем память
    }

    // Виртуальные методы 
    virtual bool push(char c) = 0;  // Добавление элемента
    virtual char pop() = 0;         // Извлечение элемента
    virtual bool isEmpty() const = 0; // Проверка на пустоту

    // Метод для получения текущего количества элементов
    int getCount() const {
        return count;
    }
};

// Класс Stack  - наследуется от Container
class Stack : public Container {
public:
    // Конструктор вызывает конструктор базового класса
    Stack(int s) : Container(s) {}

    // Добавление элемента в стек (LIFO - Last In First Out)
    bool push(char c) override {
        if (count == size) resize();    // Если массив полон, увеличиваем размер
        data[count++] = c;              // Добавляем элемент в конец
        return true;
    }

    // Извлечение элемента из стека (последний добавленный элемент)
    char pop() override {
        if (isEmpty()) return '\0';     // Если стек пуст, возвращаем нулевой символ
        return data[--count];           // Уменьшаем счетчик и возвращаем элемент
    }

    // Проверка, пуст ли стек
    bool isEmpty() const override {
        return count == 0;
    }
};

// Класс Queue  - наследуется от Container
class Queue : public Container {
private:
    int front, rear;  // Индексы начала и конца очереди

public:
    // Конструктор инициализирует базовый класс и свои поля
    Queue(int s) : Container(s), front(0), rear(0) {}

    // Добавление элемента в очередь (FIFO - First In First Out)
    bool push(char c) override {
        if (count == size) resize();           // Если массив полон, увеличиваем размер
        data[rear] = c;                        // Добавляем элемент в конец
        rear = (rear + 1) % size;              // Обновляем индекс конца (кольцевой буфер)
        count++;                               // Увеличиваем счетчик элементов
        return true;
    }

    // Извлечение элемента из очереди (первый добавленный элемент)
    char pop() override {
        if (isEmpty()) return '\0';            // Если очередь пуста, возвращаем нулевой символ
        char c = data[front];                  // Берем элемент из начала
        front = (front + 1) % size;            // Обновляем индекс начала (кольцевой буфер)
        count--;                               // Уменьшаем счетчик элементов
        return c;
    }

    // Проверка, пуста ли очередь
    bool isEmpty() const override {
        return count == 0;
    }
};

int main() {
    setlocale(0, "Russian");

    int stackSize, queueSize;

    // Пользователь вводит размеры контейнеров
    cout << "=== СОЗДАНИЕ КОНТЕЙНЕРОВ ===" << endl;
    cout << "Введите размер стека: ";
    cin >> stackSize;
    cout << "Введите размер очереди: ";
    cin >> queueSize;

    // Создаём контейнеры с введёнными размерами
    Stack stack(stackSize);
    Queue queue(queueSize);

    // Указатели на базовый класс 
    Container* stackPtr = &stack;
    Container* queuePtr = &queue;

    cout << "\nКонтейнеры созданы успешно!" << endl;
    cout << "Стек размером: " << stackSize << endl;
    cout << "Очередь размером: " << queueSize << endl;

    int choice;
    char symbol;

    // Главный цикл программы
    do {
        cout << "\n=== ГЛАВНОЕ МЕНЮ ===" << endl;
        cout << "1. Работа со стеком" << endl;
        cout << "2. Работа с очередью" << endl;
        cout << "3. Показать состояние контейнеров" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            // Подменю для работы со стеком
            int stackChoice;
            cout << "\n--- РАБОТА СО СТЕКОМ ---" << endl;
            cout << "1. Добавить элемент" << endl;
            cout << "2. Извлечь элемент" << endl;
            cout << "3. Проверить на пустоту" << endl;
            cout << "Выберите операцию: ";
            cin >> stackChoice;

            switch (stackChoice) {
            case 1:
                // Добавление элемента в стек через указатель на базовый класс
                cout << "Введите символ для добавления в стек: ";
                cin >> symbol;
                if (stackPtr->push(symbol)) {  
                    cout << "Символ '" << symbol << "' успешно добавлен в стек" << endl;
                    cout << "Текущее количество элементов в стеке: " << stackPtr->getCount() << endl;
                }
                else {
                    cout << "Ошибка при добавлении в стек!" << endl;
                }
                break;
            case 2: {
                // Извлечение элемента из стека через указатель на базовый класс
                char result = stackPtr->pop();  
                if (result != '\0') {
                    cout << "Из стека извлечён символ: '" << result << "'" << endl;
                    cout << "Осталось элементов в стеке: " << stackPtr->getCount() << endl;
                }
                else {
                    cout << "Стек пуст!" << endl;
                }
                break;
            }
            case 3:
                // Проверка состояния стека через указатель на базовый класс
                if (stackPtr->isEmpty()) {  
                    cout << "Стек ПУСТ" << endl;
                }
                else {
                    cout << "Стек НЕ ПУСТ" << endl;
                    cout << "Количество элементов: " << stackPtr->getCount() << endl;
                }
                break;
            default:
                cout << "Неверный выбор!" << endl;
            }
            break;
        }

        case 2: {
            // Подменю для работы с очередью
            int queueChoice;
            cout << "\n--- РАБОТА С ОЧЕРЕДЬЮ ---" << endl;
            cout << "1. Добавить элемент" << endl;
            cout << "2. Извлечь элемент" << endl;
            cout << "3. Проверить на пустоту" << endl;
            cout << "Выберите операцию: ";
            cin >> queueChoice;

            switch (queueChoice) {
            case 1:
                // Добавление элемента в очередь через указатель на базовый класс
                cout << "Введите символ для добавления в очередь: ";
                cin >> symbol;
                if (queuePtr->push(symbol)) {  
                    cout << "Символ '" << symbol << "' успешно добавлен в очередь" << endl;
                    cout << "Текущее количество элементов в очереди: " << queuePtr->getCount() << endl;
                }
                else {
                    cout << "Ошибка при добавлении в очередь!" << endl;
                }
                break;
            case 2: {
                // Извлечение элемента из очереди через указатель на базовый класс
                char result = queuePtr->pop();  
                if (result != '\0') {
                    cout << "Из очереди извлечён символ: '" << result << "'" << endl;
                    cout << "Осталось элементов в очереди: " << queuePtr->getCount() << endl;
                }
                else {
                    cout << "Очередь пуста!" << endl;
                }
                break;
            }
            case 3:
                // Проверка состояния очереди через указатель на базовый класс
                if (queuePtr->isEmpty()) { 
                    cout << "Очередь ПУСТА" << endl;
                }
                else {
                    cout << "Очередь НЕ ПУСТА" << endl;
                    cout << "Количество элементов: " << queuePtr->getCount() << endl;
                }
                break;
            default:
                cout << "Неверный выбор!" << endl;
            }
            break;
        }

        case 3:
            // Отображение состояния всех контейнеров через указатели
            cout << "\n--- СОСТОЯНИЕ КОНТЕЙНЕРОВ ---" << endl;
            cout << "СТЕК:" << endl;
            cout << "  - Состояние: " << (stackPtr->isEmpty() ? "ПУСТ" : "ЗАПОЛНЕН") << endl;
            cout << "  - Элементов: " << stackPtr->getCount() << endl;
            cout << "ОЧЕРЕДЬ:" << endl;
            cout << "  - Состояние: " << (queuePtr->isEmpty() ? "ПУСТА" : "ЗАПОЛНЕНА") << endl;
            cout << "  - Элементов: " << queuePtr->getCount() << endl;
            break;

        case 0:
            // Выход из программы
            cout << "Выход из программы..." << endl;
            break;

        default:
            cout << "Неверный выбор! Попробуйте снова." << endl;
        }

    } while (choice != 0);  // Продолжаем цикл, пока пользователь не выберет выход

    cout << "Программа завершена" << endl;
    return 0;
}