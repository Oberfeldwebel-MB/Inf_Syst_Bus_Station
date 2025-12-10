#pragma once
#include <string>
#include <vector>
#include <functional>
#include <regex>
#include <memory>

// —труктура дл€ результата валидации
struct ValidationResult {
    bool isValid;
    std::string errorMessage;

    ValidationResult(bool valid = true, const std::string& msg = "")
        : isValid(valid), errorMessage(msg) {
    }

    operator bool() const { return isValid; }

    static ValidationResult Success() { return ValidationResult(true, ""); }
    static ValidationResult Error(const std::string& msg) {
        return ValidationResult(false, msg);
    }
};

// Ѕазовый класс дл€ всех валидаторов
template<typename T>
class BaseValidator {
public:
    virtual ValidationResult validate(const T& item) const = 0;
    virtual ValidationResult validateForAddition(const T& item,
        const std::vector<std::shared_ptr<T>>& existingItems) const = 0;
    virtual ~BaseValidator() = default;

protected:
    // ќбщие проверки, которые можно использовать в любом валидаторе
    static ValidationResult validateString(const std::string& str,
        const std::string& fieldName,
        size_t minLength = 1,
        size_t maxLength = 100) {
        if (str.empty()) {
            return ValidationResult::Error(fieldName + " не может быть пустым!");
        }
        if (str.length() < minLength) {
            return ValidationResult::Error(fieldName + " слишком короткий (минимум " +
                std::to_string(minLength) + " символов)!");
        }
        if (str.length() > maxLength) {
            return ValidationResult::Error(fieldName + " слишком длинный (максимум " +
                std::to_string(maxLength) + " символов)!");
        }
        return ValidationResult::Success();
    }

    static ValidationResult validateNumeric(int value,
        const std::string& fieldName,
        int minValue,
        int maxValue) {
        if (value < minValue) {
            return ValidationResult::Error(fieldName + " не может быть меньше " +
                std::to_string(minValue) + "!");
        }
        if (value > maxValue) {
            return ValidationResult::Error(fieldName + " не может быть больше " +
                std::to_string(maxValue) + "!");
        }
        return ValidationResult::Success();
    }

    static ValidationResult validateRegex(const std::string& str,
        const std::string& pattern,
        const std::string& errorMessage) {
        std::regex reg(pattern);
        if (!std::regex_match(str, reg)) {
            return ValidationResult::Error(errorMessage);
        }
        return ValidationResult::Success();
    }

    template<typename Container>
    static bool isUnique(const std::function<bool(const T&, const T&)>& comparator,
        const T& newItem,
        const Container& existingItems) {
        for (const auto& item : existingItems) {
            if (comparator(*item, newItem)) {
                return false;
            }
        }
        return true;
    }
};