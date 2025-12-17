// DriverValidator.h
#pragma once
#include "BaseValidator.hpp"
#include "Driver.hpp"
#include "DriversList.hpp"

namespace InfSystBusStation {

    public ref class DriverValidator sealed : public BaseValidator {
    public:
        // Обязательные методы
        virtual bool Validate(System::Object^ item) override;
        virtual bool ValidateForAddition(System::Object^ item, System::Object^ container) override;

        // Специфичные методы
        virtual bool ValidateFIO(System::String^ fio, [System::Runtime::InteropServices::Out] System::String^% errorMessage) override;
        virtual bool ValidateSalary(int salary, [System::Runtime::InteropServices::Out] System::String^% errorMessage) override;
        virtual bool ValidateGender(System::String^ gender, [System::Runtime::InteropServices::Out] System::String^% errorMessage) override;
        virtual bool ValidateLicense(System::String^ license, [System::Runtime::InteropServices::Out] System::String^% errorMessage) override;
        virtual bool ValidatePassport(System::String^ series, System::String^ number, [System::Runtime::InteropServices::Out] System::String^% errorMessage) override;
        virtual bool ValidateDriver(Driver^ driver, [System::Runtime::InteropServices::Out] System::String^% errorMessage) override;

        // Статические методы
        static bool ValidateFIOStatic(System::String^ fio, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
        static bool ValidateSalaryStatic(int salary, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
        static bool ValidateGenderStatic(System::String^ gender, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
        static bool ValidateLicenseStatic(System::String^ license, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
        static bool ValidatePassportStatic(System::String^ series, System::String^ number, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
        static bool ValidateDriverStatic(Driver^ driver, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
        static bool ValidateForAdditionStatic(Driver^ driver, DriversList^ driversList, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
    };
}