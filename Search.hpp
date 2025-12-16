#pragma once

#include "Bus.hpp"
#include "BusList.hpp"
#include "Trip.hpp"
#include "TripList.hpp"
#include "Driver.hpp"
#include "DriversList.hpp"
#include "BusValidator.hpp"

namespace InfSystBusStation {

    using namespace System;
    using namespace System::Collections::Generic;

    public ref class Search {

    public:
        // Комплексный поиск по всем возможным критериям
        static List<Trip^>^ ComplexTripSearch(
            TripList^ tripList,
            bool useStartPoint, String^ startPoint,
            bool useFinishPoint, String^ finishPoint,
            bool useDate, DateTime^ date,
            bool usePrice, int price,
            bool useDriver, String^ driverName,
            bool useBus, String^ busInfo,
            bool useStatus, String^ status);
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

        // === РАСШИРЕННЫЙ ПОИСК ПОЕЗДОК ===

        // Поиск поездок по диапазону цен
        static List<Trip^>^ FindTripsByPriceRange(TripList^ tripList, int minPrice, int maxPrice);

        // Поиск поездок с доступными местами
        static List<Trip^>^ FindTripsWithAvailableSeats(TripList^ tripList, int minSeats = 1);

        // Поиск поездок по пункту отправления
        static List<Trip^>^ FindTripsByStartPoint(TripList^ tripList, String^ startPoint);

        // Поиск поездок по пункту назначения
        static List<Trip^>^ FindTripsByFinishPoint(TripList^ tripList, String^ finishPoint);

        // Комбинированный поиск с большим количеством параметров
        static List<Trip^>^ AdvancedTripSearch(
            TripList^ tripList,
            String^ from = nullptr,
            String^ to = nullptr,
            DateTime^ date = nullptr,
            int minPrice = 0,
            int maxPrice = 0,
            String^ busModel = nullptr,
            String^ driverName = nullptr,
            int minAvailableSeats = 0
        );

        // === УНИВЕРСАЛЬНЫЙ ПОИСК ===

        // Универсальный поиск с предикатом
        generic<typename T>
        static List<T>^ FindAll(List<T>^ list, Predicate<T>^ predicate);

        // === СТАТИСТИКА ===

        // Получить количество поездок по статусу
        static Dictionary<String^, int>^ GetTripsStatistics(TripList^ tripList);

        // Получить список уникальных пунктов отправления
        static List<String^>^ GetUniqueStartPoints(TripList^ tripList);

        // Получить список уникальных пунктов назначения
        static List<String^>^ GetUniqueFinishPoints(TripList^ tripList);

        // Найти поездки сегодня
        static List<Trip^>^ FindTodayTrips(TripList^ tripList);

        // Найти поездки на завтра
        static List<Trip^>^ FindTomorrowTrips(TripList^ tripList);

        // Найти ближайшие поездки (на ближайшие N дней)
        static List<Trip^>^ FindUpcomingTrips(TripList^ tripList, int daysAhead = 7);

    private:
        // Вспомогательный метод для сравнения строк без учета регистра
        static bool CompareStringsIgnoreCase(String^ str1, String^ str2);
    };
}