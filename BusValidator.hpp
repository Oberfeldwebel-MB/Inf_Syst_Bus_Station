// BusValidator.h
#pragma once
#include "BaseValidator.hpp"
#include "Bus.hpp"
#include "BusList.hpp"

namespace InfSystBusStation {

    public ref class BusValidator sealed : public BaseValidator {
    public:
        // Обязательные методы
        virtual bool Validate(System::Object^ item) override;
        virtual bool ValidateForAddition(System::Object^ item, System::Object^ container) override;

        // Специфичные методы (переопределяем)
        virtual bool ValidateBrand(System::String^ brand, [System::Runtime::InteropServices::Out] System::String^% errorMessage) override;
        virtual bool ValidateModel(System::String^ model, [System::Runtime::InteropServices::Out] System::String^% errorMessage) override;
        virtual bool ValidateCode(System::String^ code, [System::Runtime::InteropServices::Out] System::String^% errorMessage) override;
        virtual bool ValidatePlaceCount(int places, [System::Runtime::InteropServices::Out] System::String^% errorMessage) override;
        virtual bool ValidateTechCondition(System::String^ condition, [System::Runtime::InteropServices::Out] System::String^% errorMessage) override;
        virtual bool ValidateMaintenanceDate(System::String^ date, [System::Runtime::InteropServices::Out] System::String^% errorMessage) override;
        virtual bool ValidateBus(Bus^ bus, [System::Runtime::InteropServices::Out] System::String^% errorMessage) override;

        // Статические методы для обратной совместимости
        static bool ValidateBrandStatic(System::String^ brand, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
        static bool ValidateModelStatic(System::String^ model, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
        static bool ValidateCodeStatic(System::String^ code, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
        static bool ValidatePlaceCountStatic(int places, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
        static bool ValidateTechConditionStatic(System::String^ condition, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
        static bool ValidateMaintenanceDateStatic(System::String^ date, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
        static bool ValidateBusStatic(Bus^ bus, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
        static bool ValidateForAdditionStatic(Bus^ bus, BusList^ busList, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
    };
}