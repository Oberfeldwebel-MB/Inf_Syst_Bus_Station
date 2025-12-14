// Search.cpp - ѕ–ќ—“јя ¬≈–—»я Ѕ≈« ЋяћЅƒ
#include "Search.hpp"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Collections::Generic;

bool Search::CompareStringsIgnoreCase(String^ str1, String^ str2) {
    return String::Compare(str1, str2, StringComparison::OrdinalIgnoreCase) == 0;
}

Bus^ Search::FindBusByCode(BusList^ busList, String^ code) {
    if (busList == nullptr || String::IsNullOrEmpty(code)) {
        return nullptr;
    }

    // »спользуем BusValidator дл€ проверки кода
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
        if (bus->GetPlaceCount() >= minSeats) {
            result->Add(bus);
        }
    }

    return result;
}

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

// ”прощенный FindAll без предиката (можно удалить, если не используетс€)
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