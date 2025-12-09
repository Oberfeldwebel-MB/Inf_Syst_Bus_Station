#include "ISystemObject.hpp"
#include "SystemContainer.hpp"
#include "Bus.hpp"
#include "People.hpp"
#include "Driver.hpp"
#include "Passenger.hpp"
#include "Admin.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>

int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "################################################################\n\n";

    // ============================================================================
    // ДЕМОНСТРАЦИЯ 1: STL КОНТЕЙНЕРЫ (5 штук)
    // ============================================================================
    {
        std::cout << "===============================================\n";
        std::cout << "ДЕМОНСТРАЦИЯ 1: ИСПОЛЬЗОВАНИЕ 5 STL КОНТЕЙНЕРОВ\n";
        std::cout << "===============================================\n\n";

        SystemContainer<Bus> busPark;

        std::cout << "Создан SystemContainer<Bus>, который внутри содержит:\n";
        std::cout << "1. std::vector - для хранения всех автобусов\n";
        std::cout << "2. std::list   - для эффективных операций со списком\n";
        std::cout << "3. std::array  - для хранения топ-5 автобусов\n";
        std::cout << "4. std::map    - для поиска автобусов по коду (O(log n))\n";
        std::cout << "5. std::span   - (опционально) для работы с подмножествами\n\n";

        busPark.add(std::make_shared<Bus>("Mercedes", "Sprinter", 20, "BUS001",
            "Отличное", "2023-05-01", 2020));
        busPark.add(std::make_shared<Bus>("Ikarus", "280", 40, "BUS002",
            "Хорошее", "2022-03-15", 1990));
        busPark.add(std::make_shared<Bus>("PAZ", "3205", 25, "BUS003",
            "Удовлетворительное", "2024-01-10", 2005));

        std::cout << "Добавлено " << busPark.size() << " автобусов в SystemContainer\n";
        busPark.printInfo();
        std::cout << "\n";
    }

    // ============================================================================
    // ДЕМОНСТРАЦИЯ 2: STL АЛГОРИТМЫ 
    // ============================================================================
    {
        std::cout << "=============================================\n";
        std::cout << "ДЕМОНСТРАЦИЯ 2: ИСПОЛЬЗОВАНИЕ STL АЛГОРИТМОВ\n";
        std::cout << "=============================================\n\n";

        SystemContainer<Bus> container;

        container.add(std::make_shared<Bus>("Volvo", "B7R", 45, "V001",
            "Отличное", "2023-01-01", 2018));
        container.add(std::make_shared<Bus>("Scania", "Interlink", 55, "S002",
            "Хорошее", "2023-02-01", 2019));
        container.add(std::make_shared<Bus>("MAN", "Lion's Coach", 50, "M003",
            "Удовлетворительное", "2023-03-01", 2017));

        std::cout << "Создан тестовый контейнер с 3 автобусами\n\n";

        // 1. std::sort
        std::cout << "1. std::sort() - сортировка автобусов по имени:\n";
        std::cout << "   До сортировки: ";
        container.forEach([](const auto& bus) { std::cout << bus->getName() << " "; });
        std::cout << "\n";

        container.sortByName();

        std::cout << "   После сортировки: ";
        container.forEach([](const auto& bus) { std::cout << bus->getName() << " "; });
        std::cout << "\n\n";

        // 2. std::min_element и std::max_element
        std::cout << "2. std::min_element() и std::max_element():\n";
        auto minBus = container.getMinValue();
        auto maxBus = container.getMaxValue();
        std::cout << "   Автобус с минимальным значением: "
            << (minBus ? minBus->getName() : "нет") << "\n";
        std::cout << "   Автобус с максимальным значением: "
            << (maxBus ? maxBus->getName() : "нет") << "\n\n";

        // 3. std::find_if
        std::cout << "3. std::find_if() - поиск автобуса по тексту:\n";
        auto foundBus = container.findByText("Scania");
        std::cout << "   Поиск 'Scania': "
            << (foundBus ? "найден " + foundBus->getName() : "не найден") << "\n\n";

        // 4. std::copy_if
        std::cout << "4. std::copy_if() - копирование по условию:\n";
        auto allBuses = container.copyIfType("Bus");
        std::cout << "   Всего автобусов в контейнере: " << allBuses.size() << "\n\n";

        // 5. std::any_of
        std::cout << "5. std::any_of() - проверка условия:\n";
        bool hasVolvo = container.containsText("Volvo");
        std::cout << "   Есть ли автобус Volvo: " << (hasVolvo ? "да" : "нет") << "\n\n";

        // 6. std::transform
        std::cout << "6. std::transform() - преобразование данных:\n";
        auto ids = container.getAllIds();
        std::cout << "   ID всех автобусов: ";
        for (const auto& id : ids) std::cout << id << " ";
        std::cout << "\n\n";

        // 7. std::remove_if
        std::cout << "7. std::remove_if() - удаление по условию:\n";
        size_t removed = container.removeIfMarkedForDeletion();
        std::cout << "   Удалено автобусов, помеченных для списания: " << removed << "\n\n";
    }

    // ============================================================================
    // ДЕМОНСТРАЦИЯ 3: ШАБЛОННАЯ ФУНКЦИЯ С ОГРАНИЧЕНИЯМИ
    // ============================================================================
    std::cout << "Пример: Расчет средней загрузки автобусов\n";

    std::vector<int> capacities = { 50, 40, 30, 25 };  // Вместимость
    std::vector<int> occupied = { 45, 35, 20, 15 };    // Занято мест

    try {
        double avgLoad = calculateAverageLoad(capacities, occupied);

        std::cout << "   Вместимость автобусов: ";
        for (auto cap : capacities) std::cout << cap << " ";
        std::cout << "\n   Занято мест: ";
        for (auto occ : occupied) std::cout << occ << " ";
        std::cout << "\n   Средняя загрузка: " << avgLoad << "%\n";

    }
    catch (const std::exception& e) {
        std::cout << "   Ошибка: " << e.what() << "\n";
    }

    {
        std::cout << "============================================\n";
        std::cout << "ШАБЛОННЫЙ КЛАСС\n";
        std::cout << "============================================\n\n";

        std::cout << "SystemContainer<T> - шаблонный класс с:\n";
        std::cout << "1. Ограничением на T: должен наследовать от ISystemObject\n";
        std::cout << "2. Нешаблонными методами: add(), remove(), findById()\n";
        std::cout << "3. Шаблонным методом: forEach<Func>()\n\n";

        SystemContainer<Bus> busContainer;
        SystemContainer<Driver> driverContainer;

        std::cout << "Созданы два экземпляра шаблонного класса:\n";
        std::cout << "1. SystemContainer<Bus> - для автобусов\n";
        std::cout << "2. SystemContainer<Driver> - для водителей\n\n";

        busContainer.add(std::make_shared<Bus>("Mercedes", "Tourismo", 55, "BT001",
            "Отличное", "2023-06-01", 2021));

        std::cout << "Демонстрация шаблонного метода forEach<Func>():\n";
        busContainer.forEach([](const auto& bus) {
            std::cout << "   Обработка автобуса: " << bus->getName()
                << " (ID: " << bus->getId() << ")\n";
            });
        std::cout << "\n";
    }

    // ============================================================================
    // ДЕМОНСТРАЦИЯ 5: ПОЛИМОРФНОЕ ХРАНЕНИЕ
    // ============================================================================
    {
        

        std::vector<std::unique_ptr<ISystemObject>> polymorphicContainer;

        polymorphicContainer.push_back(
            std::make_unique<Bus>("Mercedes", "Sprinter", 20, "POLY001",
                "Хорошее", "2023-01-01", 2020));

        polymorphicContainer.push_back(
            std::make_unique<Driver>("Иванов", "Иван", "Иванович", 50000,
                "D", "2023-12-01", "Москва-СПб"));

        polymorphicContainer.push_back(
            std::make_unique<Passenger>("Петров", "Петр", "Петрович",
                "4500", "123456", "petrov@mail.ru"));

        std::cout << "Создан полиморфный контейнер с " << polymorphicContainer.size()
            << " объектами разных типов:\n\n";

        for (const auto& obj : polymorphicContainer) {
            std::cout << "Тип: " << std::setw(15) << std::left << obj->getType()
                << " | Имя: " << std::setw(25) << std::left << obj->getName()
                << " | ID: " << obj->getId()
                << " | Значение: " << obj->getSortValue() << "\n";
        }

        std::cout << "\nПолиморфные вызовы методов:\n";
        for (const auto& obj : polymorphicContainer) {
            std::cout << "\n=== " << obj->getType() << " ===\n";
            obj->displayInfo();
        }
        std::cout << "\n";
    }
    return 0;
}