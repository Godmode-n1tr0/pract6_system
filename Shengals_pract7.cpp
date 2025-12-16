#include <iostream>
#include <vector>
#include <functional>

using EventHandler = std::function<void(const std::string&)>;

struct EventSystem {
    std::vector<EventHandler> handlers;
};

void registerHandler(EventSystem& system, const EventHandler& handler) {
    system.handlers.push_back(handler);
}

void triggerEvent(const EventSystem& system, const std::string& message) {
    for (const auto& handler : system.handlers) {
        handler(message);
    }
}

void onUserLogin(const std::string& message) {
    std::cout << "Пользователь вошел в систему. Сообщение: " << message << std::endl;
}

void onUserLogout(const std::string& message) {
    std::cout << "Пользователь вышел из системы. Сообщение: " << message << std::endl;
}

void onError(const std::string& message) {
    std::cout << "Произошла ошибка! Сообщение: " << message << std::endl;
}

int main() {
    EventSystem system;
    
    registerHandler(system, onUserLogin);
    registerHandler(system, onUserLogout);
    registerHandler(system, onError);
    
    std::cout << "=== Запуск события login ===" << std::endl;
    triggerEvent(system, "Сеанс начат в 10:30");
    
    std::cout << "\n=== Запуск события error ===" << std::endl;
    triggerEvent(system, "Неверный пароль");
    
    std::cout << "\n=== Запуск события logout ===" << std::endl;
    triggerEvent(system, "Сеанс завершен в 12:45");
    
    std::cout << "\n=== Добавление лямбда-обработчика ===" << std::endl;
    registerHandler(system, [](const std::string& msg) {
        std::cout << "Лямбда-обработчик: " << msg << std::endl;
    });
    
    triggerEvent(system, "Тестовое сообщение");
    
    return 0;
}