// BusValidator.h
#pragma once
#include "Bus.hpp"
#include "BusList.hpp"
#include <regex>

namespace InfSystBusStation {
    public ref class BusValidator {
    public:
        value struct ValidationResult {
            bool isValid;
            String^ errorMessage;

            ValidationResult(bool valid, String^ msg) : isValid(valid), errorMessage(msg) {}
            static ValidationResult Success() { return ValidationResult(true, ""); }
            static ValidationResult Error(String^ msg) { return ValidationResult(false, msg); }
            operator bool() { return isValid; }
        };

        // Валидация всего автобуса
        static ValidationResult ValidateBus(Bus^ bus);

        // Валидация отдельных полей
        static ValidationResult ValidateBrand(String^ brand);
        static ValidationResult ValidateModel(String^ model);
        static ValidationResult ValidateCode(String^ code);
        static ValidationResult ValidatePlaceCount(int places);
        static ValidationResult ValidateTechCondition(String^ condition);
        static ValidationResult ValidateMaintenanceDate(String^ date);

        // Проверка перед добавлением
        static ValidationResult ValidateForAddition(Bus^ bus, BusList^ busList);
    };
}