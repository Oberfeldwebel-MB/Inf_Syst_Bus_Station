#pragma once

#include "TripList.hpp"
#include "BusList.hpp"
#include "DriversList.hpp"
#include "SearchForm.h"

namespace InfSystBusStation {

    ref class SearchForm;

    public ref class Search{
    public:
        // ================= ПОИСК ПОЕЗДОК =================

        // Основной метод поиска поездок (используется в SearchForm)
        static List<Trip^>^ SearchTrips(
            TripList^ tripList,
            String^ startPoint,
            String^ finishPoint,
            String^ date,  // Строка вместо DateTime
            int minPrice,
            int maxPrice,
            String^ driverName,
            String^ busCode);

        // ================= ПОИСК ДЛЯ УДАЛЕНИЯ =================

        // Поиск автобуса по коду (для DeleteBusForm)
        static Bus^ FindBusByCode(BusList^ busList, String^ code);

        // Поиск водителя по ФИО (для DeleteDriverForm)
        static Driver^ FindDriverByName(DriversList^ driversList, String^ fullName);

        // Поиск поездки по маршруту (для DeleteTripForm)
        static Trip^ FindTripByRoute(TripList^ tripList, String^ route);

        // Поиск автобуса по отформатированному коду (удобная обертка)
        static Bus^ FindBusByFormattedCode(BusList^ busList, String^ formattedCode);

    private:
        // ================= ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ =================

        // Основная логика поиска (вызывается из SearchTrips)
        static List<Trip^>^ AdvancedTripSearch(
            TripList^ tripList,
            String^ from,
            String^ to,
            String^ date,
            int minPrice,
            int maxPrice,
            String^ busModel,
            String^ driverName,
            int minAvailableSeats);

        // Поиск активных поездок (используется при отсутствии критериев)
        static List<Trip^>^ FindActiveTrips(TripList^ tripList);

        // Сравнение строк без учета регистра
        static bool CompareStringsIgnoreCase(String^ str1, String^ str2);

        // ================= ВНУТРЕННИЕ СТРУКТУРЫ =================

        ref class SearchData {
        public:
            bool searchByStartPoint;
            bool searchByFinishPoint;
            bool searchByDate;
            bool searchByPrice;
            bool searchByDriver;
            bool searchByBus;

            String^ startPoint;
            String^ finishPoint;
            DateTime^ date;
            int minPrice;
            int maxPrice;
            String^ driverName;
            String^ busCode;
        };
    };
}