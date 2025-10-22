#include <iostream>
#include <string>

using namespace std;

struct EventSystem {
    void (*handlers[100])(const string&);
    int count = 0;
};

void registerHandler(EventSystem& system, void(*handler)(const string&)) {
    if (system.count < 100) {
        system.handlers[system.count] = handler;
        system.count++;
    }
}

void triggerEvent(const EventSystem& system, const string& message) {
    for (int i = 0; i < system.count; i++) {
        system.handlers[i](message);
    }
}

void onUserLogin(const string& message) {
    cout << "\nПользователь вошел в систему. Сообщение: " << message << endl;
}

void onUserLogout(const string& message) {
    cout << "\nПользователь вышел из системы. Сообщение: " << message << endl;
}

void onError(const string& message) {
    cout << "\nПроизошла ошибка! Сообщение: " << message << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    EventSystem system;
    EventSystem loginSystem;
    EventSystem logoutSystem;
    EventSystem errorSystem;

    registerHandler(loginSystem, onUserLogin);
    registerHandler(logoutSystem, onUserLogout);
    registerHandler(errorSystem, onError);

    cout << "=== Событие входа ===" << endl;
    triggerEvent(loginSystem, "Привет!");

    cout << "\n=== Событие выхода ===" << endl;
    triggerEvent(logoutSystem, "Как дела?");

    cout << "\n=== Событие ошибки ===" << endl;
    triggerEvent(errorSystem, "Как настроение?");

    return 0;
}