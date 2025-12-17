// TripValidator.cpp
#include "TripValidator.hpp"
#include "TripList.hpp"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Text::RegularExpressions;
// Добавляем это пространство имен для атрибута [Out]
using namespace System::Runtime::InteropServices;

// Обязательные методы
bool TripValidator::Validate(Object^ item) {
    Trip^ trip = dynamic_cast<Trip^>(item);
    if (trip == nullptr) {
        _lastErrorMessage = "Неверный тип объекта! Ожидался Trip.";
        return false;
    }

    String^ error;
    bool isValid = ValidateTrip(trip, error);
    if (!isValid) {
        _lastErrorMessage = error;
    }
    return isValid;
}

bool TripValidator::ValidateForAddition(Object^ item, Object^ container) {
    Trip^ trip = dynamic_cast<Trip^>(item);
    TripList^ tripList = dynamic_cast<TripList^>(container);

    if (trip == nullptr) {
        _lastErrorMessage = "Неверный тип объекта! Ожидался Trip.";
        return false;
    }
    if (tripList == nullptr) {
        _lastErrorMessage = "Неверный тип контейнера! Ожидался TripList.";
        return false;
    }

    // Сначала валидируем поездку
    String^ error;
    if (!ValidateTrip(trip, error)) {
        _lastErrorMessage = error;
        return false;
    }

    // Проверка на дублирование
    if (!CheckDuplicateTrip(tripList, trip->GetStartPoint(),
        trip->GetFinishPoint(), trip->GetTripDate(), error)) {
        _lastErrorMessage = error;
        return false;
    }

    // Проверка доступности автобуса
    if (!CheckBusAvailability(trip->GetBus(), tripList,
        trip->GetTripDate(), error)) {
        _lastErrorMessage = error;
        return false;
    }

    // Проверка доступности водителя
    if (!CheckDriverAvailability(trip->GetDriver(), tripList,
        trip->GetTripDate(), error)) {
        _lastErrorMessage = error;
        return false;
    }

    _lastErrorMessage = "";
    return true;
}

// Специфичные методы
bool TripValidator::ValidateStartPoint(String^ startPoint, [Out] String^% errorMessage) {
    if (String::IsNullOrWhiteSpace(startPoint)) {
        errorMessage = "Пункт отправления не может быть пустым!";
        return false;
    }

    if (startPoint->Length < 2) {
        errorMessage = "Пункт отправления слишком короткий (минимум 2 символа)!";
        return false;
    }

    if (startPoint->Length > 100) {
        errorMessage = "Пункт отправления слишком длинный (максимум 100 символов)!";
        return false;
    }

    // Проверка на специальные символы
    return ValidateRegex(startPoint, "^[а-яА-ЯёЁa-zA-Z\\s\\-.,]+$",
        "Пункт отправления содержит недопустимые символы!", errorMessage);
}

bool TripValidator::ValidateFinishPoint(String^ finishPoint, [Out] String^% errorMessage) {
    if (String::IsNullOrWhiteSpace(finishPoint)) {
        errorMessage = "Пункт назначения не может быть пустым!";
        return false;
    }

    if (finishPoint->Length < 2) {
        errorMessage = "Пункт назначения слишком короткий (минимум 2 символа)!";
        return false;
    }

    if (finishPoint->Length > 100) {
        errorMessage = "Пункт назначения слишком длинный (максимум 100 символов)!";
        return false;
    }

    // Проверка на специальные символы
    return ValidateRegex(finishPoint, "^[а-яА-ЯёЁa-zA-Z\\s\\-.,]+$",
        "Пункт назначения содержит недопустимые символы!", errorMessage);
}

bool TripValidator::ValidatePrice(int price, [Out] String^% errorMessage) {
    return ValidateInt(price, "Цена билета", 1, 100000, errorMessage);
}

bool TripValidator::ValidateDateTime(DateTime dateTime, String^ time, [Out] String^% errorMessage) {
    // Проверка времени (если указано)
    if (!String::IsNullOrEmpty(time)) {
        if (!ValidateRegex(time, "^([01]?[0-9]|2[0-3]):[0-5][0-9]$",
            "Неверный формат времени! Используйте ЧЧ:ММ (например: 10:30)", errorMessage)) {
            return false;
        }
    }

    errorMessage = "";
    return true;
}

bool TripValidator::ValidateDepartureDate(DateTime departureDate, [Out] String^% errorMessage) {
    if (departureDate < DateTime::Now) {
        errorMessage = "Дата отправления должна быть в будущем!";
        return false;
    }

    // Нельзя планировать поездку более чем на год вперед
    DateTime maxDate = DateTime::Now.AddYears(1);
    if (departureDate > maxDate) {
        errorMessage = "Дата отправления не может быть более чем на год вперед!";
        return false;
    }

    errorMessage = "";
    return true;
}

bool TripValidator::ValidateTrip(Trip^ trip, [Out] String^% errorMessage) {
    if (trip == nullptr) {
        errorMessage = "Поездка не указана!";
        return false;
    }

    // Проверяем все поля
    String^ startError, ^ finishError, ^ priceError, ^ dateError, ^ timeError;

    bool isValid =
        ValidateStartPoint(trip->GetStartPoint(), startError) &&
        ValidateFinishPoint(trip->GetFinishPoint(), finishError) &&
        ValidatePrice(trip->GetPrice(), priceError) &&
        ValidateDepartureDate(trip->GetTripDate(), dateError) &&
        ValidateDateTime(trip->GetTripDate(), trip->GetTripTime(), timeError);

    if (!isValid) {
        // Возвращаем первую найденную ошибку
        if (!String::IsNullOrEmpty(startError)) errorMessage = startError;
        else if (!String::IsNullOrEmpty(finishError)) errorMessage = finishError;
        else if (!String::IsNullOrEmpty(priceError)) errorMessage = priceError;
        else if (!String::IsNullOrEmpty(dateError)) errorMessage = dateError;
        else if (!String::IsNullOrEmpty(timeError)) errorMessage = timeError;

        return false;
    }

    // Проверяем автобус и водителя
    if (trip->GetBus() == nullptr) {
        errorMessage = "Автобус должен быть выбран!";
        return false;
    }

    if (trip->GetDriver() == nullptr) {
        errorMessage = "Водитель должен быть выбран!";
        return false;
    }

    errorMessage = "";
    return true;
}

// Дополнительные методы
bool TripValidator::CheckDuplicateTrip(TripList^ tripList, String^ startPoint,
    String^ finishPoint, DateTime date, [Out] String^% errorMessage) {

    if (tripList == nullptr) {
        errorMessage = "";
        return true; // Невозможно проверить
    }

    // Проверяем все поездки на совпадение маршрута и даты
    for each (Trip ^ trip in tripList->AllTrips) {
        // Игнорируем завершенные и отмененные поездки
        if (trip->IsCompleted() || trip->IsCancelled()) {
            continue;
        }

        // Проверяем совпадение маршрута
        bool sameRoute = (trip->GetStartPoint() == startPoint &&
            trip->GetFinishPoint() == finishPoint);

        // Проверяем совпадение даты (день)
        bool sameDate = (trip->GetTripDate().Date == date.Date);

        if (sameRoute && sameDate) {
            errorMessage = String::Format(
                "Поездка по маршруту '{0} → {1}' на {2:dd.MM.yyyy} уже существует!",
                startPoint, finishPoint, date);
            return false;
        }
    }

    errorMessage = "";
    return true;
}

bool TripValidator::CheckBusAvailability(Bus^ bus, TripList^ tripList,
    DateTime date, [Out] String^% errorMessage) {

    if (bus == nullptr) {
        errorMessage = "Автобус не выбран!";
        return false;
    }

    // Проверяем, не занят ли автобус в эту дату
    if (tripList != nullptr) {
        for each (Trip ^ trip in tripList->AllTrips) {
            if (trip->GetBus() == bus &&
                trip->GetTripDate().Date == date.Date &&
                !trip->IsCompleted() && !trip->IsCancelled()) {

                errorMessage = String::Format(
                    "Автобус {0} уже занят на {1:dd.MM.yyyy} в поездке '{2} → {3}'",
                    bus->GetCode(), date,
                    trip->GetStartPoint(), trip->GetFinishPoint());
                return false;
            }
        }
    }

    errorMessage = "";
    return true;
}

bool TripValidator::CheckDriverAvailability(Driver^ driver, TripList^ tripList,
    DateTime date, [Out] String^% errorMessage) {

    if (driver == nullptr) {
        errorMessage = "Водитель не выбран!";
        return false;
    }

    // Проверяем, не занят ли водитель в эту дату
    if (tripList != nullptr) {
        for each (Trip ^ trip in tripList->AllTrips) {
            if (trip->GetDriver() == driver &&
                trip->GetTripDate().Date == date.Date &&
                !trip->IsCompleted() && !trip->IsCancelled()) {

                errorMessage = String::Format(
                    "Водитель {0} уже занят на {1:dd.MM.yyyy} в поездке '{2} → {3}'",
                    driver->GetFullName(), date,
                    trip->GetStartPoint(), trip->GetFinishPoint());
                return false;
            }
        }
    }

    errorMessage = "";
    return true;
}

// Статические методы
bool TripValidator::ValidateStartPointStatic(String^ startPoint, [Out] String^% errorMessage) {
    TripValidator^ validator = gcnew TripValidator();
    return validator->ValidateStartPoint(startPoint, errorMessage);
}

bool TripValidator::ValidateFinishPointStatic(String^ finishPoint, [Out] String^% errorMessage) {
    TripValidator^ validator = gcnew TripValidator();
    return validator->ValidateFinishPoint(finishPoint, errorMessage);
}

bool TripValidator::ValidatePriceStatic(int price, [Out] String^% errorMessage) {
    TripValidator^ validator = gcnew TripValidator();
    return validator->ValidatePrice(price, errorMessage);
}

bool TripValidator::ValidateDateTimeStatic(DateTime dateTime, String^ time, [Out] String^% errorMessage) {
    TripValidator^ validator = gcnew TripValidator();
    return validator->ValidateDateTime(dateTime, time, errorMessage);
}

bool TripValidator::ValidateDepartureDateStatic(DateTime departureDate, [Out] String^% errorMessage) {
    TripValidator^ validator = gcnew TripValidator();
    return validator->ValidateDepartureDate(departureDate, errorMessage);
}

bool TripValidator::ValidateTripStatic(Trip^ trip, [Out] String^% errorMessage) {
    TripValidator^ validator = gcnew TripValidator();
    return validator->ValidateTrip(trip, errorMessage);
}

bool TripValidator::ValidateNewTripStatic(String^ startPoint, String^ finishPoint,
    int price, Bus^ bus, Driver^ driver,
    DateTime departureDate, String^ time,
    TripList^ tripList, [Out] String^% errorMessage) {

    TripValidator^ validator = gcnew TripValidator();

    // Проверяем все данные
    if (!validator->ValidateStartPoint(startPoint, errorMessage)) return false;
    if (!validator->ValidateFinishPoint(finishPoint, errorMessage)) return false;
    if (!validator->ValidatePrice(price, errorMessage)) return false;
    if (!validator->ValidateDepartureDate(departureDate, errorMessage)) return false;
    if (!validator->ValidateDateTime(departureDate, time, errorMessage)) return false;

    // Проверяем автобус и водителя
    if (bus == nullptr) {
        errorMessage = "Автобус должен быть выбран!";
        return false;
    }
    if (driver == nullptr) {
        errorMessage = "Водитель должен быть выбран!";
        return false;
    }

    // Проверка на дублирование
    if (!validator->CheckDuplicateTrip(tripList, startPoint, finishPoint,
        departureDate, errorMessage)) return false;

    // Проверка доступности
    if (!validator->CheckBusAvailability(bus, tripList, departureDate, errorMessage)) return false;
    if (!validator->CheckDriverAvailability(driver, tripList, departureDate, errorMessage)) return false;

    errorMessage = "";
    return true;
}