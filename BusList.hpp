// BusList.hpp
#pragma once
#include "Bus.hpp"
#include "AddBusForm.h"
#include "DeleteBusForm.h"
#include "BusListForm.h"

namespace InfSystBusStation {

    public ref class BusList {
    private:
        System::Collections::Generic::List<Bus^>^ buses;
        Bus^ FindBusByCodeInternal(String^ code);

    public:
        BusList();
        ~BusList();

        // === лерндш дкъ тнпл ===
        bool ShowAddBusForm(Form^ owner);
        bool ShowDeleteBusForm(Form^ owner);
        void ShowBusListForm(Form^ owner);

        // === лерндш дкъ бгюхлндеиярбхъ я тнплюлх ===
        bool InternalAddBus(String^ brand, String^ model, int placeCount,
            String^ code, String^ techCondition, String^ lastMaintenance);
        bool InternalRemoveBus(String^ code);
        System::Collections::Generic::List<String^>^ GetAllBusCodes();
        Bus^ GetBusByFormattedCode(String^ formattedCode);

        // === онксвемхе дюммшу ===
        System::Collections::Generic::List<Bus^>^ GetAvailableBuses();
        System::Collections::Generic::List<Bus^>^ GetBusesNeedingMaintenance();
        System::Collections::Generic::List<Bus^>^ GetBusesByBrand(String^ brand);
        void DisplayAllBuses();

        // === опнбепйх ===
        bool HasAvailableBuses();
        String^ GetBusInfo(String^ code);

        // === ябниярбю ===
        property System::Collections::Generic::List<Bus^>^ AllBuses {
            System::Collections::Generic::List<Bus^>^ get() { return buses; }
        }

        property int Count {
            int get() { return buses->Count; }
        }

        property int AvailableCount {
            int get() {
                int count = 0;
                for each (Bus ^ bus in buses) {
                    if (bus->GetAvailability() && !bus->IsInCriticalCondition()) {
                        count++;
                    }
                }
                return count;
            }
        }
    };
}