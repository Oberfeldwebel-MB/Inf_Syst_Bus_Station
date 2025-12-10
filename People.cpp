// People.cpp
#include "People.hpp"

using namespace InfSystBusStation;

void People::PrintInfo() {
    Console::WriteLine("=== Информация о человеке ===");
    Console::WriteLine("ФИО: {0}", fullName);
    Console::WriteLine("Пол: {0}", gender);
    if (!String::IsNullOrEmpty(passportSeries) && !String::IsNullOrEmpty(passportNumber)) {
        Console::WriteLine("Паспорт: {0} {1}", passportSeries, passportNumber);
    }
    if (!String::IsNullOrEmpty(email)) {
        Console::WriteLine("Email: {0}", email);
    }
}

String^ People::GetFullInfo() {
    String^ info = fullName;

    if (!String::IsNullOrEmpty(passportSeries) && !String::IsNullOrEmpty(passportNumber)) {
        info += " (" + passportSeries + " " + passportNumber + ")";
    }

    return info;
}