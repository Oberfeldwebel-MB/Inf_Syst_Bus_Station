#include "Search.hpp"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Collections::Generic;

// ================= ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ =================

bool Search::CompareStringsIgnoreCase(String^ str1, String^ str2) {
    return String::Compare(str1, str2, StringComparison::OrdinalIgnoreCase) == 0;
}

// ================= ПОИСК АВТОБУСОВ =================

Bus^ Search::FindBusByCode(BusList^ busList, String^ code) {
    if (busList == nullptr || String::IsNullOrEmpty(code)) {
        return nullptr;
    }

    // Используем BusValidator для проверки кода
    auto validationResult = BusValidator::ValidateCode(code);
    if (!validationResult.isValid) {
        return nullptr;
    }

    return busList->GetBusByFormattedCode(code);
}

List<Bus^>^ Search::FindBusesByBrand(BusList^ busList, String^ brand) {
    if (busList == nullptr) {
        return gcnew List<Bus^>();
    }

    auto validationResult = BusValidator::ValidateBrand(brand);
    if (!validationResult.isValid) {
        throw gcnew ArgumentException(validationResult.errorMessage);
    }

    List<Bus^>^ result = gcnew List<Bus^>();
    auto allBuses = busList->AllBuses;

    for each (Bus ^ bus in allBuses) {
        if (CompareStringsIgnoreCase(bus->GetBrand(), brand)) {
            result->Add(bus);
        }
    }

    return result;
}

List<Bus^>^ Search::FindBusesByModel(BusList^ busList, String^ model) {
    if (busList == nullptr) {
        return gcnew List<Bus^>();
    }

    auto validationResult = BusValidator::ValidateModel(model);
    if (!validationResult.isValid) {
        throw gcnew ArgumentException(validationResult.errorMessage);
    }

    List<Bus^>^ result = gcnew List<Bus^>();
    auto allBuses = busList->AllBuses;

    for each (Bus ^ bus in allBuses) {
        if (CompareStringsIgnoreCase(bus->GetModel(), model)) {
            result->Add(bus);
        }
    }

    return result;
}

List<Bus^>^ Search::FindAvailableBuses(BusList^ busList) {
    if (busList == nullptr) {
        return gcnew List<Bus^>();
    }

    List<Bus^>^ result = gcnew List<Bus^>();
    auto allBuses = busList->AllBuses;

    for each (Bus ^ bus in allBuses) {
        if (bus->CheckAvailability()) {
            result->Add(bus);
        }
    }

    return result;
}

List<Bus^>^ Search::FindBusesNeedingMaintenance(BusList^ busList) {
    if (busList == nullptr) {
        return gcnew List<Bus^>();
    }

    List<Bus^>^ result = gcnew List<Bus^>();
    auto allBuses = busList->AllBuses;

    for each (Bus ^ bus in allBuses) {
        if (bus->NeedsMaintenance()) {
            result->Add(bus);
        }
    }

    return result;
}

List<Bus^>^ Search::FindBusesByCondition(BusList^ busList, String^ condition) {
    if (busList == nullptr) {
        return gcnew List<Bus^>();
    }

    auto validationResult = BusValidator::ValidateTechCondition(condition);
    if (!validationResult.isValid) {
        throw gcnew ArgumentException(validationResult.errorMessage);
    }

    List<Bus^>^ result = gcnew List<Bus^>();
    auto allBuses = busList->AllBuses;

    for each (Bus ^ bus in allBuses) {
        if (bus->GetTechCondition() == condition) {
            result->Add(bus);
        }
    }

    return result;
}

List<Bus^>^ Search::FindBusesWithMinSeats(BusList^ busList, int minSeats) {
    if (busList == nullptr || minSeats <= 0) {
        return gcnew List<Bus^>();
    }

    List<Bus^>^ result = gcnew List<Bus^>();
    auto allBuses = busList->AllBuses;

    for each (Bus ^ bus in allBuses) {
        if (bus->GetSeatCount() >= minSeats) {
            result->Add(bus);
        }
    }

    return result;
}

// ================= ПОИСК ПОЕЗДОК =================

List<Trip^>^ Search::FindTripsByDate(TripList^ tripList, DateTime date) {
    if (tripList == nullptr) {
        return gcnew List<Trip^>();
    }

    List<Trip^>^ result = gcnew List<Trip^>();
    auto allTrips = tripList->AllTrips;

    for each (Trip ^ trip in allTrips) {
        if (trip->GetTripDate().Date == date.Date) {
            result->Add(trip);
        }
    }

    return result;
}

List<Trip^>^ Search::FindTripsByRoute(TripList^ tripList, String^ route) {
    if (tripList == nullptr || String::IsNullOrEmpty(route)) {
        return gcnew List<Trip^>();
    }

    List<Trip^>^ result = gcnew List<Trip^>();
    auto allTrips = tripList->AllTrips;
    String^ routeLower = route->ToLower();

    for each (Trip ^ trip in allTrips) {
        if (trip->GetRoute()->ToLower()->Contains(routeLower)) {
            result->Add(trip);
        }
    }

    return result;
}

List<Trip^>^ Search::FindTripsByBus(TripList^ tripList, String^ busCode) {
    if (tripList == nullptr || String::IsNullOrEmpty(busCode)) {
        return gcnew List<Trip^>();
    }

    List<Trip^>^ result = gcnew List<Trip^>();
    auto allTrips = tripList->AllTrips;

    for each (Trip ^ trip in allTrips) {
        if (trip->GetBus() != nullptr) {
            // Сравниваем код без учета регистра и формата
            if (trip->GetBus()->GetCode()->ToLower() == busCode->ToLower() ||
                trip->GetBus()->GetFormattedCode()->ToLower() == busCode->ToLower()) {
                result->Add(trip);
            }
        }
    }

    return result;
}

List<Trip^>^ Search::FindTripsByDriver(TripList^ tripList, String^ driverName) {
    if (tripList == nullptr || String::IsNullOrEmpty(driverName)) {
        return gcnew List<Trip^>();
    }

    List<Trip^>^ result = gcnew List<Trip^>();
    auto allTrips = tripList->AllTrips;
    String^ driverNameLower = driverName->ToLower();

    for each (Trip ^ trip in allTrips) {
        if (trip->GetDriver() != nullptr) {
            String^ fullName = trip->GetDriver()->GetFullName()->ToLower();
            if (fullName->Contains(driverNameLower)) {
                result->Add(trip);
            }
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

List<Trip^>^ Search::FindPlannedTrips(TripList^ tripList) {
    if (tripList == nullptr) {
        return gcnew List<Trip^>();
    }

    List<Trip^>^ result = gcnew List<Trip^>();
    auto allTrips = tripList->AllTrips;

    for each (Trip ^ trip in allTrips) {
        if (trip->IsPlanned()) {
            result->Add(trip);
        }
    }

    return result;
}

List<Trip^>^ Search::FindTripsCombined(TripList^ tripList,
    String^ routeFilter, DateTime^ dateFilter, String^ statusFilter) {

    if (tripList == nullptr) {
        return gcnew List<Trip^>();
    }

    List<Trip^>^ result = gcnew List<Trip^>();
    auto allTrips = tripList->AllTrips;

    for each (Trip ^ trip in allTrips) {
        bool matches = true;

        // Фильтр по маршруту
        if (!String::IsNullOrEmpty(routeFilter)) {
            if (!trip->GetRoute()->ToLower()->Contains(routeFilter->ToLower())) {
                matches = false;
            }
        }

        // Фильтр по дате
        if (dateFilter != nullptr) {
            if (trip->GetTripDate().Date != dateFilter->Date) {
                matches = false;
            }
        }

        // Фильтр по статусу
        if (!String::IsNullOrEmpty(statusFilter)) {
            if (trip->GetStatus() != statusFilter) {
                matches = false;
            }
        }

        if (matches) {
            result->Add(trip);
        }
    }

    return result;
}

// ================= РАСШИРЕННЫЙ ПОИСК ПОЕЗДОК =================

List<Trip^>^ Search::FindTripsByPriceRange(TripList^ tripList, int minPrice, int maxPrice) {
    if (tripList == nullptr || minPrice < 0 || maxPrice < minPrice) {
        return gcnew List<Trip^>();
    }

    if (maxPrice == 0) maxPrice = Int32::MaxValue;

    List<Trip^>^ result = gcnew List<Trip^>();
    auto allTrips = tripList->AllTrips;

    for each (Trip ^ trip in allTrips) {
        int price = trip->GetPrice();
        if (price >= minPrice && price <= maxPrice) {
            result->Add(trip);
        }
    }

    return result;
}

List<Trip^>^ Search::FindTripsWithAvailableSeats(TripList^ tripList, int minSeats) {
    if (tripList == nullptr || minSeats < 0) {
        return gcnew List<Trip^>();
    }

    List<Trip^>^ result = gcnew List<Trip^>();
    auto allTrips = tripList->AllTrips;

    for each (Trip ^ trip in allTrips) {
        if (trip->GetAvailableSeatsCount() >= minSeats) {
            result->Add(trip);
        }
    }

    return result;
}

List<Trip^>^ Search::FindTripsByStartPoint(TripList^ tripList, String^ startPoint) {
    if (tripList == nullptr || String::IsNullOrEmpty(startPoint)) {
        return gcnew List<Trip^>();
    }

    List<Trip^>^ result = gcnew List<Trip^>();
    auto allTrips = tripList->AllTrips;
    String^ startPointLower = startPoint->ToLower();

    for each (Trip ^ trip in allTrips) {
        if (trip->GetStartPoint()->ToLower()->Contains(startPointLower)) {
            result->Add(trip);
        }
    }

    return result;
}

List<Trip^>^ Search::FindTripsByFinishPoint(TripList^ tripList, String^ finishPoint) {
    if (tripList == nullptr || String::IsNullOrEmpty(finishPoint)) {
        return gcnew List<Trip^>();
    }

    List<Trip^>^ result = gcnew List<Trip^>();
    auto allTrips = tripList->AllTrips;
    String^ finishPointLower = finishPoint->ToLower();

    for each (Trip ^ trip in allTrips) {
        if (trip->GetFinishPoint()->ToLower()->Contains(finishPointLower)) {
            result->Add(trip);
        }
    }

    return result;
}

List<Trip^>^ Search::AdvancedTripSearch(
    TripList^ tripList,
    String^ from,
    String^ to,
    DateTime^ date,
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

        // Фильтр по дате
        if (date != nullptr) {
            if (trip->GetTripDate().Date != date->Date) {
                matches = false;
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

// ================= УНИВЕРСАЛЬНЫЙ ПОИСК =================

generic<typename T>
List<T>^ Search::FindAll(List<T>^ list, Predicate<T>^ predicate) {
    if (list == nullptr || predicate == nullptr) {
        return gcnew List<T>();
    }

    List<T>^ result = gcnew List<T>();

    for each (T item in list) {
        if (predicate(item)) {
            result->Add(item);
        }
    }

    return result;
}

// ================= СТАТИСТИКА =================

Dictionary<String^, int>^ Search::GetTripsStatistics(TripList^ tripList) {
    Dictionary<String^, int>^ stats = gcnew Dictionary<String^, int>();

    if (tripList == nullptr) {
        return stats;
    }

    auto allTrips = tripList->AllTrips;

    for each (Trip ^ trip in allTrips) {
        String^ status = trip->GetStatus();

        if (stats->ContainsKey(status)) {
            stats[status]++;
        }
        else {
            stats->Add(status, 1);
        }
    }

    return stats;
}

List<String^>^ Search::GetUniqueStartPoints(TripList^ tripList) {
    List<String^>^ result = gcnew List<String^>();

    if (tripList == nullptr) {
        return result;
    }

    auto allTrips = tripList->AllTrips;

    for each (Trip ^ trip in allTrips) {
        String^ startPoint = trip->GetStartPoint();

        if (!String::IsNullOrEmpty(startPoint) && !result->Contains(startPoint)) {
            result->Add(startPoint);
        }
    }

    result->Sort();
    return result;
}

List<String^>^ Search::GetUniqueFinishPoints(TripList^ tripList) {
    List<String^>^ result = gcnew List<String^>();

    if (tripList == nullptr) {
        return result;
    }

    auto allTrips = tripList->AllTrips;

    for each (Trip ^ trip in allTrips) {
        String^ finishPoint = trip->GetFinishPoint();

        if (!String::IsNullOrEmpty(finishPoint) && !result->Contains(finishPoint)) {
            result->Add(finishPoint);
        }
    }

    result->Sort();
    return result;
}

List<Trip^>^ Search::FindTodayTrips(TripList^ tripList) {
    if (tripList == nullptr) {
        return gcnew List<Trip^>();
    }

    return FindTripsByDate(tripList, DateTime::Today);
}

List<Trip^>^ Search::FindTomorrowTrips(TripList^ tripList) {
    if (tripList == nullptr) {
        return gcnew List<Trip^>();
    }

    DateTime tomorrow = DateTime::Today.AddDays(1);
    return FindTripsByDate(tripList, tomorrow);
}

List<Trip^>^ Search::FindUpcomingTrips(TripList^ tripList, int daysAhead) {
    if (tripList == nullptr || daysAhead <= 0) {
        return gcnew List<Trip^>();
    }

    List<Trip^>^ result = gcnew List<Trip^>();
    auto allTrips = tripList->AllTrips;

    DateTime today = DateTime::Today;
    DateTime endDate = today.AddDays(daysAhead);

    for each (Trip ^ trip in allTrips) {
        DateTime tripDate = trip->GetTripDate().Date;

        if (tripDate >= today && tripDate <= endDate && trip->IsPlanned()) {
            result->Add(trip);
        }
    }

    return result;

}


List<Trip^>^ Search::ComplexTripSearch(
    TripList^ tripList,
    bool useStartPoint, String^ startPoint,
    bool useFinishPoint, String^ finishPoint,
    bool useDate, DateTime^ date,
    bool usePrice, int price,
    bool useDriver, String^ driverName,
    bool useBus, String^ busInfo,
    bool useStatus, String^ status) {

    if (tripList == nullptr) {
        return gcnew List<Trip^>();
    }

    List<Trip^>^ result = gcnew List<Trip^>();
    auto allTrips = tripList->AllTrips;

    for each (Trip ^ trip in allTrips) {
        bool matches = true;

        // Фильтр по пункту отправления
        if (useStartPoint && !String::IsNullOrEmpty(startPoint)) {
            if (!trip->GetStartPoint()->ToLower()->Contains(startPoint->ToLower())) {
                matches = false;
            }
        }

        // Фильтр по пункту назначения
        if (useFinishPoint && !String::IsNullOrEmpty(finishPoint)) {
            if (!trip->GetFinishPoint()->ToLower()->Contains(finishPoint->ToLower())) {
                matches = false;
            }
        }

        // Фильтр по дате
        if (useDate && date != nullptr) {
            if (trip->GetTripDate().Date != date->Date) {
                matches = false;
            }
        }

        // Фильтр по цене (диапазон ±100)
        if (usePrice && price > 0) {
            int tripPrice = trip->GetPrice();
            if (tripPrice < (price - 100) || tripPrice >(price + 100)) {
                matches = false;
            }
        }

        // Фильтр по водителю
        if (useDriver && !String::IsNullOrEmpty(driverName) && trip->GetDriver() != nullptr) {
            if (!trip->GetDriver()->GetFullName()->ToLower()->Contains(driverName->ToLower())) {
                matches = false;
            }
        }

        // Фильтр по автобусу (упрощенно - ищем по модели)
        if (useBus && !String::IsNullOrEmpty(busInfo) && trip->GetBus() != nullptr) {
            String^ busModel = trip->GetBus()->GetModel()->ToLower();
            String^ busBrand = trip->GetBus()->GetBrand()->ToLower();
            String^ search = busInfo->ToLower();

            if (!busModel->Contains(search) && !busBrand->Contains(search)) {
                matches = false;
            }
        }

        // Фильтр по статусу
        if (useStatus && !String::IsNullOrEmpty(status)) {
            if (trip->GetStatus() != status) {
                matches = false;
            }
        }

        if (matches) {
            result->Add(trip);
        }
    }

    return result;
}


List<Trip^>^ Search::FindTripsByPriceRange(TripList^ tripList, int minPrice, int maxPrice) {
    if (tripList == nullptr || minPrice < 0 || maxPrice < 0 || maxPrice < minPrice) {
        return gcnew List<Trip^>();
    }

    List<Trip^>^ result = gcnew List<Trip^>();
    auto allTrips = tripList->AllTrips;

    for each (Trip ^ trip in allTrips) {
        int price = trip->GetPrice();
        if (price >= minPrice && price <= maxPrice) {
            result->Add(trip);
        }
    }

    return result;
}