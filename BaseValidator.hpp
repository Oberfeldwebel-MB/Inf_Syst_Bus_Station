// BaseValidator.h
#pragma once
#include "Bus.hpp"
#include "Driver.hpp"
#include "Trip.hpp"

namespace InfSystBusStation {

    public ref class BaseValidator abstract {
    protected:
        System::String^ _lastErrorMessage;

    public:
        BaseValidator() : _lastErrorMessage("") {}

        // === ќЅя«ј“≈Ћ№Ќџ≈ методы ===
        virtual bool Validate(System::Object^ item) abstract;
        virtual bool ValidateForAddition(System::Object^ item, System::Object^ container) abstract;

        // —войство дл€ получени€ последней ошибки
        property System::String^ LastErrorMessage {
            System::String^ get() { return _lastErrorMessage; }
        }

        // === ќЅў»≈ вспомогательные методы (реализаци€ по умолчанию) ===
        virtual bool ValidateString(System::String^ str, System::String^ fieldName,
            int minLength, int maxLength, [System::Runtime::InteropServices::Out] System::String^% errorMessage) {

            if (System::String::IsNullOrEmpty(str)) {
                errorMessage = fieldName + " не может быть пустым!";
                return false;
            }
            if (str->Length < minLength) {
                errorMessage = fieldName + " слишком короткий (минимум " + minLength + " символов)!";
                return false;
            }
            if (str->Length > maxLength) {
                errorMessage = fieldName + " слишком длинный (максимум " + maxLength + " символов)!";
                return false;
            }
            errorMessage = "";
            return true;
        }

        virtual bool ValidateInt(int value, System::String^ fieldName,
            int minValue, int maxValue, [System::Runtime::InteropServices::Out] System::String^% errorMessage) {

            if (value < minValue) {
                errorMessage = fieldName + " не может быть меньше " + minValue + "!";
                return false;
            }
            if (value > maxValue) {
                errorMessage = fieldName + " не может быть больше " + maxValue + "!";
                return false;
            }
            errorMessage = "";
            return true;
        }

        virtual bool ValidateRegex(System::String^ str, System::String^ pattern,
            System::String^ errorMessageTemplate, [System::Runtime::InteropServices::Out] System::String^% errorMessage) {

            System::Text::RegularExpressions::Regex^ regex = gcnew System::Text::RegularExpressions::Regex(pattern);
            if (!regex->IsMatch(str)) {
                errorMessage = errorMessageTemplate;
                return false;
            }
            errorMessage = "";
            return true;
        }



        // ƒл€ BusValidator
        virtual bool ValidateBrand(System::String^ brand, [System::Runtime::InteropServices::Out] System::String^% errorMessage) {
            errorMessage = "";
            return true;
        }
        virtual bool ValidateModel(System::String^ model, [System::Runtime::InteropServices::Out] System::String^% errorMessage) {
            errorMessage = "";
            return true;
        }
        virtual bool ValidateCode(System::String^ code, [System::Runtime::InteropServices::Out] System::String^% errorMessage) {
            errorMessage = "";
            return true;
        }
        virtual bool ValidatePlaceCount(int places, [System::Runtime::InteropServices::Out] System::String^% errorMessage) {
            errorMessage = "";
            return true;
        }
        virtual bool ValidateTechCondition(System::String^ condition, [System::Runtime::InteropServices::Out] System::String^% errorMessage) {
            errorMessage = "";
            return true;
        }
        virtual bool ValidateMaintenanceDate(System::String^ date, [System::Runtime::InteropServices::Out] System::String^% errorMessage) {
            errorMessage = "";
            return true;
        }
        virtual bool ValidateBus(Bus^ bus, [System::Runtime::InteropServices::Out] System::String^% errorMessage) {
            errorMessage = "";
            return true;
        }

        // ƒл€ DriverValidator
        virtual bool ValidateFIO(System::String^ fio, [System::Runtime::InteropServices::Out] System::String^% errorMessage) {
            errorMessage = "";
            return true;
        }
        virtual bool ValidateSalary(int salary, [System::Runtime::InteropServices::Out] System::String^% errorMessage) {
            errorMessage = "";
            return true;
        }
        virtual bool ValidateGender(System::String^ gender, [System::Runtime::InteropServices::Out] System::String^% errorMessage) {
            errorMessage = "";
            return true;
        }
        virtual bool ValidateLicense(System::String^ license, [System::Runtime::InteropServices::Out] System::String^% errorMessage) {
            errorMessage = "";
            return true;
        }
        virtual bool ValidatePassport(System::String^ series, System::String^ number, [System::Runtime::InteropServices::Out] System::String^% errorMessage) {
            errorMessage = "";
            return true;
        }
        virtual bool ValidateDriver(Driver^ driver, [System::Runtime::InteropServices::Out] System::String^% errorMessage) {
            errorMessage = "";
            return true;
        }

        // ƒл€ TripValidator
        virtual bool ValidateStartPoint(System::String^ startPoint, [System::Runtime::InteropServices::Out] System::String^% errorMessage) {
            errorMessage = "";
            return true;
        }
        virtual bool ValidateFinishPoint(System::String^ finishPoint, [System::Runtime::InteropServices::Out] System::String^% errorMessage) {
            errorMessage = "";
            return true;
        }
        virtual bool ValidatePrice(int price, [System::Runtime::InteropServices::Out] System::String^% errorMessage) {
            errorMessage = "";
            return true;
        }
        virtual bool ValidateDateTime(System::DateTime dateTime, System::String^ time, [System::Runtime::InteropServices::Out] System::String^% errorMessage) {
            errorMessage = "";
            return true;
        }
        virtual bool ValidateDepartureDate(System::DateTime departureDate, [System::Runtime::InteropServices::Out] System::String^% errorMessage) {
            errorMessage = "";
            return true;
        }
        virtual bool ValidateTrip(Trip^ trip, [System::Runtime::InteropServices::Out] System::String^% errorMessage) {
            errorMessage = "";
            return true;
        }

        virtual ~BaseValidator() {}
    };
}