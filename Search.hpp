// Search.hpp
#pragma once

#include "Bus.hpp"
#include "BusList.hpp"
#include "Trip.hpp"
#include "TripList.hpp"
#include "Driver.hpp"
#include "DriversList.hpp"
#include "BusValidator.h"

namespace InfSystBusStation {

    using namespace System;
    using namespace System::Collections::Generic;

    public ref class Search {
    public:
        // === ПОИСК АВТОБУСОВ ===

        // Поиск автобуса по коду (с использованием BusValidator)
        static Bus^ FindBusByCode(BusList^ busList, String^ code);

        // Поиск автобусов по марке (с валидацией через BusValidator)
        static List<Bus^>^ FindBusesByBrand(BusList^ busList, String^ brand);

        // Поиск автобусов по модели (с валидацией через BusValidator)
        static List<Bus^>^ FindBusesByModel(BusList^ busList, String^ model);

        // Поиск доступных автобусов
        static List<Bus^>^ FindAvailableBuses(BusList^ busList);

        // Поиск автобусов, требующих ТО
        static List<Bus^>^ FindBusesNeedingMaintenance(BusList^ busList);

        // Поиск автобусов по техническому состоянию (с валидацией через BusValidator)
        static List<Bus^>^ FindBusesByCondition(BusList^ busList, String^ condition);

        // Поиск автобусов с количеством мест больше указанного
        static List<Bus^>^ FindBusesWithMinSeats(BusList^ busList, int minSeats);

        // === ПОИСК ПОЕЗДОК ===

        // Поиск поездок по дате
        static List<Trip^>^ FindTripsByDate(TripList^ tripList, DateTime date);

        // Поиск поездок по маршруту
        static List<Trip^>^ FindTripsByRoute(TripList^ tripList, String^ route);

        // Поиск поездок по автобусу
        static List<Trip^>^ FindTripsByBus(TripList^ tripList, String^ busCode);

        // Поиск поездок по водителю
        static List<Trip^>^ FindTripsByDriver(TripList^ tripList, String^ driverName);

        // Поиск активных поездок
        static List<Trip^>^ FindActiveTrips(TripList^ tripList);

        // Поиск запланированных поездок
        static List<Trip^>^ FindPlannedTrips(TripList^ tripList);

        // Комбинированный поиск поездок
        static List<Trip^>^ FindTripsCombined(TripList^ tripList,
            String^ routeFilter, DateTime^ dateFilter, String^ statusFilter);

        // === УНИВЕРСАЛЬНЫЙ ПОИСК ===

        // Универсальный поиск с предикатом
        generic<typename T>
        static List<T>^ FindAll(List<T>^ list, Predicate<T>^ predicate);

    private:
        // Вспомогательный метод для сравнения строк без учета регистра
        static bool CompareStringsIgnoreCase(String^ str1, String^ str2);
    };
}