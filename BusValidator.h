#pragma once
#include "Bus.hpp"

namespace InfSystBusStation {

    public ref class BusValidator {
    public:
        value struct ValidationResult {
            bool isValid;
            String^ errorMessage;

            ValidationResult(bool valid, String^ msg)
                : isValid(valid), errorMessage(msg) {
            }

            static ValidationResult Success() {
                return ValidationResult(true, "");
            }

            static ValidationResult Error(String^ msg) {
                return ValidationResult(false, msg);
            }

            operator bool() { return isValid; }
        };

        // Валидация отдельных полей
        static ValidationResult ValidateBrand(String^ brand);
        static ValidationResult ValidateModel(String^ model);
        static ValidationResult ValidatePlaceCount(int placeCount);
        static ValidationResult ValidateCode(String^ code);
        static ValidationResult ValidateTechCondition(String^ condition);
        static ValidationResult ValidateMaintenanceDate(String^ date);

        // Полная валидация автобуса
        static ValidationResult ValidateBus(Bus^ bus);
    };
}