// TripList.hpp
#pragma once

#include "Trip.hpp"
#include "BusList.hpp"
#include "DriversList.hpp"

namespace InfSystBusStation {

    public ref class TripList {
    private:
        System::Collections::Generic::List<Trip^>^ trips;
        System::Collections::Generic::List<Trip^>^ searchResults;

        // Âñïîìîãàòåëüíûå äàííûå (àíàëîãè÷íî map â Timing)
        System::Collections::Generic::Dictionary<String^, String^>^ stringData;
        System::Collections::Generic::Dictionary<String^, int>^ intData;
        System::Collections::Generic::Dictionary<String^, double>^ doubleData;

    public:
        TripList();
        ~TripList();

    public:
        // === ÌÅÒÎÄÛ ÄËß ĞÀÁÎÒÛ Ñ ĞÅÇÓËÜÒÀÒÀÌÈ ÏÎÈÑÊÀ ===
        void SetSearchResults(System::Collections::Generic::List<Trip^>^ results);
        System::Collections::Generic::List<Trip^>^ GetSearchResults();
        void ClearSearchResults();
        bool HasSearchResults();

        property System::Collections::Generic::List<Trip^>^ SearchResults {
            System::Collections::Generic::List<Trip^>^ get() { return searchResults; }
            void set(System::Collections::Generic::List<Trip^>^ value) { searchResults = value; }
        }

        // === ÎÑÍÎÂÍÛÅ ÌÅÒÎÄÛ ÓÏĞÀÂËÅÍÈß ===
        void AddTrip(Trip^ trip);
        bool RemoveTrip(String^ route);
        Trip^ FindTripByRoute(String^ route);
        Trip^ ChooseTrip();

        // === ÌÅÒÎÄÛ ÄËß ÔÎĞÌ ===
        bool ShowAddTripForm(Form^ owner, BusList^ busList, DriversList^ driverList);
        bool ShowDeleteTripForm(Form^ owner);
        void ShowTripListForm(Form^ owner, BusList^ busList, DriversList^ driverList);

        // === ÔÈËÜÒĞÀÖÈß È ÏÎÈÑÊ ===
        System::Collections::Generic::List<Trip^>^ GetActiveTrips();
        System::Collections::Generic::List<Trip^>^ GetCompletedTrips();
        System::Collections::Generic::List<Trip^>^ GetPlannedTrips();
        System::Collections::Generic::List<Trip^>^ GetTripsByDate(DateTime date);
        System::Collections::Generic::List<Trip^>^ GetTripsByBus(String^ busCode);
        System::Collections::Generic::List<Trip^>^ GetTripsByDriver(String^ driverName);

        // === ÎÒÎÁĞÀÆÅÍÈÅ ===
        void DisplayAllTrips();
        void DisplayActiveTrips();
        void DisplayCompletedTrips();
        void DisplayPlannedTrips();

        // === ÂÑÏÎÌÎÃÀÒÅËÜÍÛÅ ÄÀÍÍÛÅ ===
        void AddStringData(String^ key, String^ value);
        void AddIntData(String^ key, int value);
        void AddDoubleData(String^ key, double value);
        String^ GetStringData(String^ key);
        int GetIntData(String^ key);
        double GetDoubleData(String^ key);

        // === ÂÍÓÒĞÅÍÍÈÅ ÌÅÒÎÄÛ ÄËß ÔÎĞÌ ===
        bool InternalAddTrip(String^ startPoint, String^ finishPoint, int price,
            Bus^ bus, Driver^ driver, DateTime date, String^ time);
        bool InternalRemoveTrip(String^ route);
        System::Collections::Generic::List<String^>^ GetAllTripRoutes();
        Trip^ GetTripByRoute(String^ route);

        // === ÑÂÎÉÑÒÂÀ ===
        property System::Collections::Generic::List<Trip^>^ AllTrips {
            System::Collections::Generic::List<Trip^>^ get() { return trips; }
        }

        property int Count {
            int get() { return trips->Count; }
        }

        property int ActiveCount {
            int get() {
                int count = 0;
                for each (Trip ^ trip in trips) {
                    if (trip->IsPlanned() || trip->IsInProgress()) {
                        count++;
                    }
                }
                return count;
            }
        }

        property int PlannedCount {
            int get() {
                int count = 0;
                for each (Trip ^ trip in trips) {
                    if (trip->IsPlanned()) {
                        count++;
                    }
                }
                return count;
            }
        }

        property int CompletedCount {
            int get() {
                int count = 0;
                for each (Trip ^ trip in trips) {
                    if (trip->IsCompleted()) {
                        count++;
                    }
                }
                return count;
            }
        }
    };
}