#include "Search.hpp"
#include "BusValidator.hpp"
#include "TripValidator.hpp"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Collections::Generic;

// ================= ПОИСК ДЛЯ УДАЛЕНИЯ =================

// Поиск автобуса по коду
Bus^ Search::FindBusByCode(BusList^ busList, String^ code) {
    if (busList == nullptr || String::IsNullOrEmpty(code)) {
        return nullptr;
    }

    // Используем статический метод с errorMessage
    String^ errorMessage;
    if (!BusValidator::ValidateCodeStatic(code, errorMessage)) {
        // Код невалидный, возвращаем nullptr
        return nullptr;
    }

    // Ищем автобус через BusList
    return busList->GetBusByFormattedCode(code);
}

// Поиск автобуса по отформатированному коду
Bus^ Search::FindBusByFormattedCode(BusList^ busList, String^ formattedCode) {
    if (busList == nullptr || String::IsNullOrEmpty(formattedCode)) {
        return nullptr;
    }

    // Убираем форматирование для поиска
    String^ code = formattedCode->Replace("/", "");
    return FindBusByCode(busList, code);
}

// Поиск водителя по ФИО
Driver^ Search::FindDriverByName(DriversList^ driversList, String^ fullName) {
    if (driversList == nullptr || String::IsNullOrEmpty(fullName)) {
        return nullptr;
    }

    // Ищем через DriversList
    return driversList->FindDriverByName(fullName);
}

// Поиск поездки по маршруту
Trip^ Search::FindTripByRoute(TripList^ tripList, String^ route) {
    if (tripList == nullptr || String::IsNullOrEmpty(route)) {
        return nullptr;
    }

    // Ищем через TripList
    return tripList->GetTripByRoute(route);
}

// ================= ОСНОВНОЙ МЕТОД ПОИСКА =================

List<Trip^>^ Search::SearchTrips(
    TripList^ tripList,
    String^ startPoint,
    String^ finishPoint,
    String^ date,  // Строка вместо DateTime
    int minPrice,
    int maxPrice,
    String^ driverName,
    String^ busCode) {

    try {
        // === 1. ПРОВЕРКА ВХОДНЫХ ДАННЫХ ===
        if (tripList == nullptr) {
            throw gcnew ArgumentNullException("tripList", "Список поездок не может быть null!");
        }

        // === 2. ПРОВЕРКА, ЕСТЬ ЛИ КРИТЕРИИ ===
        bool hasCriteria =
            (startPoint != nullptr && !String::IsNullOrEmpty(startPoint)) ||
            (finishPoint != nullptr && !String::IsNullOrEmpty(finishPoint)) ||
            (date != nullptr && !String::IsNullOrEmpty(date)) ||
            (minPrice > 0 || maxPrice > 0) ||
            (driverName != nullptr && !String::IsNullOrEmpty(driverName)) ||
            (busCode != nullptr && !String::IsNullOrEmpty(busCode));

        // Если нет критериев - возвращаем все активные поездки
        if (!hasCriteria) {
            return FindActiveTrips(tripList);
        }

        // === 3. ВАЛИДАЦИЯ КРИТЕРИЕВ ===
        // Проверяем цены
        if (minPrice < 0) {
            throw gcnew ArgumentException("Минимальная цена не может быть отрицательной!");
        }
        if (maxPrice < 0) {
            throw gcnew ArgumentException("Максимальная цена не может быть отрицательной!");
        }
        if (maxPrice > 0 && maxPrice < minPrice) {
            throw gcnew ArgumentException("Максимальная цена не может быть меньше минимальной!");
        }

        // Проверяем дату (если указана)
        if (!String::IsNullOrEmpty(date)) {
            try {
                // Пробуем распарсить дату для проверки формата
                DateTime parsedDate = DateTime::ParseExact(date, "dd/MM/yyyy HH:mm", nullptr);
                // Если не выбрасывает исключение - дата корректна
            }
            catch (FormatException^) {
                throw gcnew ArgumentException("Неверный формат даты! Используйте ДД/ММ/ГГГГ ЧЧ:ММ");
            }
            catch (Exception^ ex) {
                throw gcnew ArgumentException("Ошибка при обработке даты: " + ex->Message);
            }
        }

        // Проверяем точки маршрута (если есть TripValidator)
        String^ errorMessage;
        if (!String::IsNullOrEmpty(startPoint)) {
            // Если есть TripValidator::ValidateStartPointStatic, используем его
            // if (!TripValidator::ValidateStartPointStatic(startPoint, errorMessage)) {
            //     throw gcnew ArgumentException("Пункт отправления: " + errorMessage);
            // }
        }

        if (!String::IsNullOrEmpty(finishPoint)) {
            // if (!TripValidator::ValidateFinishPointStatic(finishPoint, errorMessage)) {
            //     throw gcnew ArgumentException("Пункт назначения: " + errorMessage);
            // }
        }

        // === 4. ВЫПОЛНЕНИЕ ПОИСКА ===
        List<Trip^>^ searchResults = nullptr;

        // Используем расширенный поиск
        searchResults = AdvancedTripSearch(
            tripList,
            startPoint,                    // from
            finishPoint,                   // to
            date,                          // date (строка)
            minPrice,                      // minPrice
            (maxPrice > 0) ? maxPrice : Int32::MaxValue, // maxPrice
            nullptr,                       // busModel (не используем)
            driverName,                    // driverName
            0                              // minAvailableSeats
        );

        // === 5. ДОПОЛНИТЕЛЬНАЯ ФИЛЬТРАЦИЯ ПО АВТОБУСУ ===
        if (busCode != nullptr && !String::IsNullOrEmpty(busCode) &&
            searchResults != nullptr && searchResults->Count > 0) {

            List<Trip^>^ filteredResults = gcnew List<Trip^>();
            for each (Trip ^ trip in searchResults) {
                if (trip->GetBus() != nullptr) {
                    // Сравниваем код без учета регистра
                    if (CompareStringsIgnoreCase(trip->GetBus()->GetCode(), busCode) ||
                        CompareStringsIgnoreCase(trip->GetBus()->GetFormattedCode(), busCode)) {
                        filteredResults->Add(trip);
                    }
                }
            }
            searchResults = filteredResults;
        }

        // === 6. ВОЗВРАТ РЕЗУЛЬТАТОВ ===
        return searchResults;
    }
    catch (Exception^ ex) {
        // Перебрасываем исключение для обработки в форме
        throw;
    }
}

// ================= ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ =================

List<Trip^>^ Search::AdvancedTripSearch(
    TripList^ tripList,
    String^ from,
    String^ to,
    String^ date,  // Строка вместо DateTime
    int minPrice,
    int maxPrice,
    String^ busModel,
    String^ driverName,
    int minAvailableSeats) {

    if (tripList == nullptr) {
        return gcnew List<Trip^>();
    }

    if (maxPrice == 0) maxPrice = Int32::MaxValue;

    List<Trip^>^ result = gcnew List<Trip^>();
    auto allTrips = tripList->AllTrips;

    for each (Trip ^ trip in allTrips) {
        bool matches = true;

        // Фильтр по пункту отправления
        if (!String::IsNullOrEmpty(from)) {
            if (!trip->GetStartPoint()->ToLower()->Contains(from->ToLower())) {
                matches = false;
            }
        }

        // Фильтр по пункту назначения
        if (!String::IsNullOrEmpty(to)) {
            if (!trip->GetFinishPoint()->ToLower()->Contains(to->ToLower())) {
                matches = false;
            }
        }

        // Фильтр по дате - СТРОГОЕ РАВЕНСТВО
        if (!String::IsNullOrEmpty(date)) {
            try {
                DateTime searchDate = DateTime::ParseExact(date, "dd/MM/yyyy HH:mm", nullptr);
                DateTime tripDate = trip->GetTripDate();

                // Сравниваем дату и время (строгое равенство)
                if (tripDate != searchDate) {
                    matches = false;
                }
            }
            catch (Exception^) {
                // Если не удалось распарсить - пропускаем фильтр по дате
            }
        }

        // Фильтр по цене
        int price = trip->GetPrice();
        if (price < minPrice || price > maxPrice) {
            matches = false;
        }

        // Фильтр по автобусу
        if (!String::IsNullOrEmpty(busModel) && trip->GetBus() != nullptr) {
            if (!trip->GetBus()->GetModel()->ToLower()->Contains(busModel->ToLower())) {
                matches = false;
            }
        }

        // Фильтр по водителю
        if (!String::IsNullOrEmpty(driverName) && trip->GetDriver() != nullptr) {
            if (!trip->GetDriver()->GetFullName()->ToLower()->Contains(driverName->ToLower())) {
                matches = false;
            }
        }

        // Фильтр по свободным местам
        if (trip->GetAvailableSeatsCount() < minAvailableSeats) {
            matches = false;
        }

        if (matches) {
            result->Add(trip);
        }
    }

    return result;
}

List<Trip^>^ Search::FindActiveTrips(TripList^ tripList) {
    if (tripList == nullptr) {
        return gcnew List<Trip^>();
    }

    List<Trip^>^ result = gcnew List<Trip^>();
    auto allTrips = tripList->AllTrips;

    for each (Trip ^ trip in allTrips) {
        if (trip->IsPlanned() || trip->IsInProgress()) {
            result->Add(trip);
        }
    }

    return result;
}

bool Search::CompareStringsIgnoreCase(String^ str1, String^ str2) {
    return String::Compare(str1, str2, StringComparison::OrdinalIgnoreCase) == 0;
}