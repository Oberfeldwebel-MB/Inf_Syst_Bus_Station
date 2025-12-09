#pragma once
#include <variant>
#include "ISystemObject.hpp"
#include <vector>
#include <list>
#include <array>
#include <map>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <type_traits>
#include <functional>


// Шаблонный класс контейнера для системных объектов
template<typename T>
class SystemContainer {
    // Статическая проверка наследования от ISystemObject
    static_assert(std::is_base_of<ISystemObject, T>::value,
        "T must inherit from ISystemObject");

private:
    // STL контейнеры

    // 1. std::vector - основной контейнер для хранения объектов
    std::vector<std::shared_ptr<T>> items;

    // 2. std::list - для частых вставок/удалений в середине
    std::list<std::shared_ptr<T>> itemList;

    // 3. std::array - фиксированный массив для топ-5 объектов
    static constexpr size_t TOP_N_COUNT = 5;
    std::array<std::shared_ptr<T>, TOP_N_COUNT> topObjects;

    // 4. std::map - для быстрого поиска по ID (O(log n))
    std::map<std::string, std::shared_ptr<T>> idMap;

public:

    // Конструктор по умолчанию
    SystemContainer() {
        topObjects.fill(nullptr);  // Инициализируем массив nullptr
    }

    // Конструктор из списка инициализации
    SystemContainer(std::initializer_list<std::shared_ptr<T>> initList) {
        topObjects.fill(nullptr);
        for (const auto& item : initList) {
            add(item);
        }
    }

    ~SystemContainer() = default;


    // === НЕШАБЛОННЫЕ МЕТОДЫ (базовые операции) ===

    // Добавление элемента в контейнер
    void add(std::shared_ptr<T> item) {
        if (!item) {
            throw std::invalid_argument("Cannot add null pointer to SystemContainer");
        }

        std::string id = item->getId();
        if (idMap.find(id) != idMap.end()) {
            throw std::runtime_error("Object with ID '" + id + "' already exists");
        }

        // Добавляем во все контейнеры
        items.push_back(item);
        itemList.push_back(item);
        idMap[id] = item;

        updateTopObjects();
    }

    // Удаление элемента по ID
    bool remove(const std::string& id) {
        auto it = idMap.find(id);
        if (it == idMap.end()) {
            return false;
        }

        auto item = it->second;

        // Удаляем из vector с помощью std::remove
        items.erase(std::remove(items.begin(), items.end(), item), items.end());

        // Удаляем из list
        itemList.remove(item);

        // Удаляем из map
        idMap.erase(it);

        updateTopObjects();
        return true;
    }

    // Поиск элемента по ID (O(log n))
    std::shared_ptr<T> findById(const std::string& id) const {
        auto it = idMap.find(id);
        return (it != idMap.end()) ? it->second : nullptr;
    }

    // Получение всех элементов (константная версия)
    const std::vector<std::shared_ptr<T>>& getAll() const {
        return items;
    }

    // Получение всех элементов (неконстантная версия)
    std::vector<std::shared_ptr<T>>& getAllMutable() {
        return items;
    }

    // Получение размера контейнера
    size_t size() const {
        return items.size();
    }

    // Проверка на пустоту
    bool empty() const {
        return items.empty();
    }

    // Очистка контейнера
    void clear() {
        items.clear();
        itemList.clear();
        idMap.clear();
        topObjects.fill(nullptr);
    }

    // === МЕТОДЫ С ИСПОЛЬЗОВАНИЕМ STL АЛГОРИТМОВ ===

    // 1. std::sort - сортировка по имени
    void sortByName() {
        std::sort(items.begin(), items.end(),
            [](const auto& a, const auto& b) {
                return a->getName() < b->getName();
            });
        updateTopObjects();
    }

    // 1. std::sort - сортировка по значению
    void sortByValue() {
        std::sort(items.begin(), items.end(),
            [](const auto& a, const auto& b) {
                return a->getSortValue() < b->getSortValue();
            });
        updateTopObjects();
    }

    // 2. std::min_element - поиск минимального значения
    std::shared_ptr<T> getMinValue() const {
        if (items.empty()) return nullptr;

        auto it = std::min_element(items.begin(), items.end(),
            [](const auto& a, const auto& b) {
                return a->getSortValue() < b->getSortValue();
            });
        return *it;
    }

    // 2. std::max_element - поиск максимального значения
    std::shared_ptr<T> getMaxValue() const {
        if (items.empty()) return nullptr;

        auto it = std::max_element(items.begin(), items.end(),
            [](const auto& a, const auto& b) {
                return a->getSortValue() < b->getSortValue();
            });
        return *it;
    }

    // 3. std::find_if - поиск по тексту
    std::shared_ptr<T> findByText(const std::string& text) const {
        auto it = std::find_if(items.begin(), items.end(),
            [&text](const auto& item) {
                return item->containsText(text);
            });
        return (it != items.end()) ? *it : nullptr;
    }

    // 4. std::copy_if - копирование элементов по типу
    std::vector<std::shared_ptr<T>> copyIfType(const std::string& type) const {
        std::vector<std::shared_ptr<T>> result;

        std::copy_if(items.begin(), items.end(), std::back_inserter(result),
            [&type](const auto& item) {
                return item->getType() == type;
            });

        return result;
    }

    // 5. std::remove_if - удаление элементов, помеченных для удаления
    size_t removeIfMarkedForDeletion() {
        size_t oldSize = items.size();

        auto newEnd = std::remove_if(items.begin(), items.end(),
            [](const auto& item) {
                return item->isMarkedForRemoval();
            });

        items.erase(newEnd, items.end());
        synchronizeContainers();

        return oldSize - items.size();
    }

    // 6. std::any_of - проверка, содержит ли контейнер текст
    bool containsText(const std::string& text) const {
        return std::any_of(items.begin(), items.end(),
            [&text](const auto& item) {
                return item->containsText(text);
            });
    }

    // 7. std::transform - получение всех ID объектов
    std::vector<std::string> getAllIds() const {
        std::vector<std::string> ids;
        ids.reserve(items.size());

        std::transform(items.begin(), items.end(), std::back_inserter(ids),
            [](const auto& item) {
                return item->getId();
            });

        return ids;
    }

    // 8. std::for_each - применение функции ко всем элементам
    template<typename Func>
    void forEach(Func func) const {
        std::for_each(items.begin(), items.end(), func);
    }


    // === ИНФОРМАЦИОННЫЕ МЕТОДЫ ===

    // Вывод информации о контейнере
    void printInfo() const {
        std::cout << "=== SystemContainer Information ===\n";
        std::cout << "Total objects: " << size() << "\n";

        if (!empty()) {
            // Статистика по типам
            std::map<std::string, size_t> typeStats;
            for (const auto& item : items) {
                typeStats[item->getType()]++;
            }

            std::cout << "Object types:\n";
            for (const auto& [type, count] : typeStats) {
                std::cout << "  " << type << ": " << count << "\n";
            }

            // Топ-5 объектов
            std::cout << "\nTop " << TOP_N_COUNT << " objects by value:\n";
            for (size_t i = 0; i < TOP_N_COUNT; ++i) {
                if (topObjects[i]) {
                    std::cout << "  " << (i + 1) << ". " << topObjects[i]->getName()
                        << " (" << topObjects[i]->getType()
                        << ", value: " << topObjects[i]->getSortValue() << ")\n";
                }
            }

            // Минимум и максимум
            auto minItem = getMinValue();
            auto maxItem = getMaxValue();
            if (minItem && maxItem) {
                std::cout << "\nMin value: " << minItem->getName()
                    << " (" << minItem->getSortValue() << ")\n";
                std::cout << "Max value: " << maxItem->getName()
                    << " (" << maxItem->getSortValue() << ")\n";
            }
        }

        std::cout << "===================================\n";
    }

    // Вывод всех объектов
    void displayAll() const {
        std::cout << "=== All Objects in SystemContainer ===\n";
        forEach([](const auto& item) {
            std::cout << "  " << *item << "\n";
            });
        std::cout << "======================================\n";
    }

private:

    // Синхронизация всех контейнеров
    void synchronizeContainers() {
        // Очищаем list и map
        itemList.clear();
        idMap.clear();

        // Заполняем заново из vector
        for (const auto& item : items) {
            if (item) {
                itemList.push_back(item);
                idMap[item->getId()] = item;
            }
        }

        updateTopObjects();
    }
};

// Шаблонная функция 

// Функция для расчета средней загрузки транспорта
template<typename Container>
double calculateAverageLoad(const Container& capacities,
    const Container& occupied) {
    // Ограничение на типы: должны быть числовыми
    static_assert(std::is_arithmetic<typename Container::value_type>::value,
        "Container must contain arithmetic types");

    if (capacities.size() != occupied.size()) {
        throw std::invalid_argument("Containers must have the same size");
    }

    if (capacities.empty()) {
        return 0.0;
    }

    double totalLoad = 0.0;
    size_t validCount = 0;

    for (size_t i = 0; i < capacities.size(); ++i) {
        if (capacities[i] > 0) {
            double load = (static_cast<double>(occupied[i]) / capacities[i]) * 100.0;
            totalLoad += std::min(load, 100.0); // Ограничиваем 100%
            ++validCount;
        }
    }

    return validCount > 0 ? totalLoad / validCount : 0.0;
}

