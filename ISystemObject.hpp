#pragma once
#include <string>
#include <memory>
#include <iostream>

//интерфейс для полиморфного хранения в STL контейнерах
class ISystemObject {
public:
    virtual ~ISystemObject() = default;

    // основные методы
    virtual std::string getId() const = 0;           // ID
    virtual std::string getName() const = 0;         // имя  
    virtual std::string getType() const = 0;         // Тип объекта
    virtual void displayInfo() const = 0;            // Показать информацию

    // === ДЛЯ STL АЛГОРИТМОВ ===

    // Для std::sort, std::min_element, std::max_element
    virtual double getSortValue() const = 0;         // Значение для сортировки

    // Для std::find_if, std::any_of, std::count_if
    virtual bool containsText(const std::string& text) const = 0;

    // Для std::remove_if 
    virtual bool isMarkedForRemoval() const { return false; }
};

// Вспомогательные функции для демонстрации STL алгоритмов

// 1. Для сортировки по имени
inline bool sortByName(const std::unique_ptr<ISystemObject>& a,
    const std::unique_ptr<ISystemObject>& b) {
    if (!a || !b) return false;
    return a->getName() < b->getName();
}

// 2. Для сортировки по значению
inline bool sortByValue(const std::unique_ptr<ISystemObject>& a,
    const std::unique_ptr<ISystemObject>& b) {
    if (!a || !b) return false;
    return a->getSortValue() < b->getSortValue();
}

// 3. Оператор вывода
inline std::ostream& operator<<(std::ostream& os, const ISystemObject& obj) {
    os << obj.getType() << " '" << obj.getName() << "' [ID: " << obj.getId() << "]";
    return os;
}

// 4. Функция для поиска по ID (возвращает лямбду для std::find_if)
inline auto findById(const std::string& id) {
    return [id](const std::unique_ptr<ISystemObject>& obj) {
        return obj && obj->getId() == id;
        };
}

// функция для приведения к нижнему регистру
inline std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}