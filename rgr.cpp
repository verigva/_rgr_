#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
using namespace std;

// Определяем класс "Заказ"
class Order {
private:
    std::string name;
    std::string date;
    std::string type;
public:
    Order(std::string name, std::string date, std::string type) : name(name), date(date), type(type) {}

    std::string getName() { return name; }
    std::string getDate() { return date; }
    std::string getType() { return type; }
};

// Определяем класс "Управление заказами"
class OrderManager {
private:
    std::vector<Order> orders;
public:
    void addOrder(Order order) {
        orders.push_back(order);
    }

    void removeOrder(int index) {
        if (index >= 0 && index < orders.size()) {
            orders.erase(orders.begin() + index);
        }
    }

    void printOrders() {
        for (int i = 0; i < orders.size(); i++) {
            std::cout << "Заказ " << i + 1 << ":" << std::endl;
            std::cout << "Имя: " << orders[i].getName() << std::endl;
            std::cout << "Дата: " << orders[i].getDate() << std::endl;
            std::cout << "Тип: " << orders[i].getType() << std::endl;
            std::cout << std::endl;
        }
    }

    void saveToFile(std::string filename) {
        std::ifstream inputFile(filename);
        std::vector<std::string> lines;
        std::string line;

        if (inputFile.is_open()) {
            while (getline(inputFile, line)) {
                lines.push_back(line);
            }
            inputFile.close();
        }
        // Определить номер последней строки
        int lastLineNumber = lines.size();

        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            for (int i = 0; i < orders.size(); i++) {
                file << lastLineNumber + i + 1 << " Заказ:  " << "Имя: " << orders[i].getName() << "," << "Дата: " << orders[i].getDate() << "," << "Тип: " << orders[i].getType() << std::endl;
            }
            file.close();
            std::cout << "Сохранено в файл: " << filename << std::endl;
        }
        else {
            std::cout << "Ошибка при открытии файла." << std::endl;
        }
    }

    void loadFromFile(std::string filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            orders.clear();
            std::string line;
            while (std::getline(file, line)) {
                std::string name, date, type;
                size_t pos1 = line.find(",");
                size_t pos2 = line.find(",", pos1 + 1);
                name = line.substr(0, pos1);
                date = line.substr(pos1 + 1, pos2 - pos1 - 1);
                type = line.substr(pos2 + 1);
                Order order(name, date, type);
                orders.push_back(order);
            }
            file.close();
            std::cout << "Загружено из файла: " << filename << std::endl;
        }
        else {
            std::cout << "Ошибка при открытии файла." << std::endl;
        }
    }

};

int main() {
    srand(time(NULL));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    OrderManager orderManager;

    int choice;
    std::string name, date, type, filename;

    do {
        std::cout << "Выберите действие:\n";
        std::cout << "1. Добавить заказ\n";
        std::cout << "2. Удалить заказ\n";
        std::cout << "3. Вывести все заказы\n";
        std::cout << "4. Сохранить в файл\n";
        std::cout << "5. Загрузить из файла\n";
        std::cout << "0. Выход\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Введите имя: ";
            std::cin >> name;
            std::cout << "Введите дату: ";
            std::cin >> date;
            std::cout << "Введите тип: ";
            std::cin >> type;
            orderManager.addOrder(Order(name, date, type));
            std::cout << "Заказ добавлен\n";
            break;
        case 2:
            int index;
            std::cout << "Введите индекс заказа: ";
            std::cin >> index;
            orderManager.removeOrder(index - 1);
            std::cout << "Заказ удален\n";
            break;
        case 3:
            orderManager.printOrders();
            break;
        case 4:
            std::
                cout << "Введите имя файла для сохранения: ";
            std::cin >> filename;
            orderManager.saveToFile(filename);
            break;
        case 5:
            std::cout << "Введите имя файла для загрузки: ";
            std::cin >> filename;
            orderManager.loadFromFile(filename);
            break;
        case 0:
            std::cout << "Выход\n";
            break;
        default:
            std::cout << "Неверный выбор\n";
            break;
        }
        std::cout << std::endl;
    } while (choice != 0);

    return 0;
}