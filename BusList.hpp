// BusList.hpp
#pragma once

#include "Bus.hpp"

namespace InfSystBusStation {
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Collections::Generic;

    public ref class BusList {
    private:
        List<Bus^>^ buses;
        Bus^ FindBusByCodeInternal(String^ code);

    public:
        BusList();
        ~BusList();

        // === лерндш дкъ бгюхлндеиярбхъ я тнплюлх ===
        bool InternalAddBus(String^ brand, String^ model, int placeCount,
            String^ code, String^ techCondition, String^ lastMaintenance);
        bool InternalRemoveBus(String^ code);
        List<String^>^ GetAllBusCodes();
        Bus^ GetBusByFormattedCode(String^ formattedCode);
        List<String^>^ GetAllBusFormattedCodes();
        String^ GetBusDetailedInfo(String^ formattedCode);
        bool RemoveBusByFormattedCode(String^ formattedCode);

        // === лерндш дкъ тнпл ===
        bool ShowAddBusForm(Form^ owner);
        bool ShowDeleteBusForm(Form^ owner);
        void ShowBusListForm(Form^ owner);

        // === онксвемхе дюммшу ===
        List<Bus^>^ GetAvailableBuses();
        List<Bus^>^ GetBusesByBrand(String^ brand);
        void DisplayAllBuses();

        // === днонкмхрекэмше лерндш ===
        List<Bus^>^ GetBusesReadyForTrip();
        bool UpdateBusCondition(String^ code, String^ newCondition);
        bool UpdateMaintenanceDate(String^ code, String^ newDate);
  

        // === опнбепйх ===
        bool HasAvailableBuses();
        String^ GetBusInfo(String^ code);

        // === ябниярбю ===
        property List<Bus^>^ AllBuses {
            List<Bus^>^ get() { return buses; }
        }

        property int Count {
            int get() { return (buses != nullptr) ? buses->Count : 0; }
        }

        property int AvailableCount {
            int get() {
                int count = 0;
                if (buses != nullptr) {
                    for each (Bus ^ bus in buses) {
                        if (bus->GetAvailability()) {
                            count++;
                        }
                    }
                }
                return count;
            }
        }
    };
}