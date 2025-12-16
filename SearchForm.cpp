#include "SearchForm.h"
#include "Search.hpp"
#include "TripList.hpp"
#include "BusList.hpp"
#include "DriversList.hpp"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

// Загрузить список водителей в ComboBox
void SearchForm::LoadDriverComboBox() {
    driverComboBox->Items->Clear();
    if (driverList != nullptr) {
        for each (Driver ^ driver in driverList->AllDrivers) {
            driverComboBox->Items->Add(driver->GetFullName());
        }
    }
}

// Загрузить список автобусов в ComboBox
void SearchForm::LoadBusComboBox() {
    busComboBox->Items->Clear();
    if (busList != nullptr) {
        for each (Bus ^ bus in busList->AllBuses) {
            busComboBox->Items->Add(bus->GetBrand() + " " + bus->GetModel() +
                " (" + bus->GetFormattedCode() + ")");
        }
    }
}

// ================= ОБРАБОТЧИКИ ЧЕКБОКСОВ =================

System::Void SearchForm::checkStartBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    StartPointBox->Enabled = checkStartBox->Checked;
    if (!checkStartBox->Checked) {
        StartPointBox->Clear();
    }
}

System::Void SearchForm::checkFinishBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    FinishPointBox->Enabled = checkFinishBox->Checked;
    if (!checkFinishBox->Checked) {
        FinishPointBox->Clear();
    }
}

System::Void SearchForm::checkDateStartBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    DepDateBox->Enabled = checkDateStartBox->Checked;
    if (!checkDateStartBox->Checked) {
        DepDateBox->Clear();
    }
}

System::Void SearchForm::checkDateFinishBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    ArrDateBox->Enabled = checkDateFinishBox->Checked;
    if (!checkDateFinishBox->Checked) {
        ArrDateBox->Clear();
    }
}

System::Void SearchForm::checkPriceBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    PriceBox->Enabled = checkPriceBox->Checked;
    if (!checkPriceBox->Checked) {
        PriceBox->Clear();
    }
}

System::Void SearchForm::checkDriverBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    driverComboBox->Enabled = checkDriverBox->Checked;
    if (!checkDriverBox->Checked) {
        driverComboBox->SelectedIndex = -1;
    }
}

System::Void SearchForm::checkBusBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    busComboBox->Enabled = checkBusBox->Checked;
    if (!checkBusBox->Checked) {
        busComboBox->SelectedIndex = -1;
    }
}

// ================= ОСНОВНЫЕ МЕТОДЫ =================

System::Void SearchForm::SearchButton_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        if (tripList == nullptr) {
            MessageBox::Show("Список поездок не загружен!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // Проверяем, есть ли выбранные критерии
        bool hasCriteria = checkStartBox->Checked || checkFinishBox->Checked ||
            checkDateStartBox->Checked || checkDateFinishBox->Checked ||
            checkPriceBox->Checked || checkDriverBox->Checked || checkBusBox->Checked;

        if (!hasCriteria) {
            // Если нет выбранных критериев - показываем все активные поездки
            searchResults = Search::FindActiveTrips(tripList);
        }
        else {
            // Используем методы из класса Search для каждого выбранного критерия

            List<Trip^>^ currentResults = nullptr;

            // 1. Поиск по пункту отправления
            if (checkStartBox->Checked && !String::IsNullOrEmpty(StartPointBox->Text)) {
                List<Trip^>^ startPointResults = Search::FindTripsByStartPoint(
                    tripList, StartPointBox->Text);

                if (currentResults == nullptr) {
                    currentResults = startPointResults;
                }
                else {
                    // Пересечение результатов
                    List<Trip^>^ intersection = gcnew List<Trip^>();
                    for each (Trip ^ trip in startPointResults) {
                        if (currentResults->Contains(trip)) {
                            intersection->Add(trip);
                        }
                    }
                    currentResults = intersection;
                }
            }

            // 2. Поиск по пункту назначения
            if (checkFinishBox->Checked && !String::IsNullOrEmpty(FinishPointBox->Text)) {
                List<Trip^>^ finishPointResults = Search::FindTripsByFinishPoint(
                    tripList, FinishPointBox->Text);

                if (currentResults == nullptr) {
                    currentResults = finishPointResults;
                }
                else {
                    List<Trip^>^ intersection = gcnew List<Trip^>();
                    for each (Trip ^ trip in finishPointResults) {
                        if (currentResults->Contains(trip)) {
                            intersection->Add(trip);
                        }
                    }
                    currentResults = intersection;
                }
            }

            // 3. Поиск по дате отправления
            if (checkDateStartBox->Checked && !String::IsNullOrEmpty(DepDateBox->Text)) {
                try {
                    DateTime date = DateTime::Parse(DepDateBox->Text);
                    List<Trip^>^ dateResults = Search::FindTripsByDate(tripList, date);

                    if (currentResults == nullptr) {
                        currentResults = dateResults;
                    }
                    else {
                        List<Trip^>^ intersection = gcnew List<Trip^>();
                        for each (Trip ^ trip in dateResults) {
                            if (currentResults->Contains(trip)) {
                                intersection->Add(trip);
                            }
                        }
                        currentResults = intersection;
                    }
                }
                catch (Exception^) {
                    MessageBox::Show("Некорректная дата отправления! Используйте формат ДД.ММ.ГГГГ ЧЧ:ММ",
                        "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }
            }

            // 4. Поиск по дате прибытия (упрощенно - добавляем 2 часа к дате отправления)
            if (checkDateFinishBox->Checked && !String::IsNullOrEmpty(ArrDateBox->Text)) {
                try {
                    DateTime date = DateTime::Parse(ArrDateBox->Text);
                    // Ищем поездки, которые прибывают в этот день
                    List<Trip^>^ allTrips = tripList->AllTrips;
                    List<Trip^>^ dateResults = gcnew List<Trip^>();

                    for each (Trip ^ trip in allTrips) {
                        DateTime arrivalDate = trip->GetTripDate().AddHours(2); // Упрощение
                        if (arrivalDate.Date == date.Date) {
                            dateResults->Add(trip);
                        }
                    }

                    if (currentResults == nullptr) {
                        currentResults = dateResults;
                    }
                    else {
                        List<Trip^>^ intersection = gcnew List<Trip^>();
                        for each (Trip ^ trip in dateResults) {
                            if (currentResults->Contains(trip)) {
                                intersection->Add(trip);
                            }
                        }
                        currentResults = intersection;
                    }
                }
                catch (Exception^) {
                    MessageBox::Show("Некорректная дата прибытия! Используйте формат ДД.ММ.ГГГГ ЧЧ:ММ",
                        "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }
            }

            // 5. Поиск по цене (диапазон ±100 от указанной)
            if (checkPriceBox->Checked && !String::IsNullOrEmpty(PriceBox->Text)) {
                try {
                    int price = Convert::ToInt32(PriceBox->Text);
                    if (price <= 0) {
                        throw gcnew ArgumentException("Цена должна быть положительной");
                    }

                    List<Trip^>^ priceResults = Search::FindTripsByPriceRange(
                        tripList, price - 100, price + 100);

                    if (currentResults == nullptr) {
                        currentResults = priceResults;
                    }
                    else {
                        List<Trip^>^ intersection = gcnew List<Trip^>();
                        for each (Trip ^ trip in priceResults) {
                            if (currentResults->Contains(trip)) {
                                intersection->Add(trip);
                            }
                        }
                        currentResults = intersection;
                    }
                }
                catch (Exception^ ex) {
                    MessageBox::Show("Некорректная цена: " + ex->Message,
                        "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }
            }

            // 6. Поиск по водителю
            if (checkDriverBox->Checked && driverComboBox->SelectedItem != nullptr) {
                String^ driverName = driverComboBox->SelectedItem->ToString();
                List<Trip^>^ driverResults = Search::FindTripsByDriver(tripList, driverName);

                if (currentResults == nullptr) {
                    currentResults = driverResults;
                }
                else {
                    List<Trip^>^ intersection = gcnew List<Trip^>();
                    for each (Trip ^ trip in driverResults) {
                        if (currentResults->Contains(trip)) {
                            intersection->Add(trip);
                        }
                    }
                    currentResults = intersection;
                }
            }

            // 7. Поиск по автобусу (по коду или модели)
            if (checkBusBox->Checked && busComboBox->SelectedItem != nullptr) {
                String^ busInfo = busComboBox->SelectedItem->ToString();
                // Извлекаем код автобуса из строки в формате "Марка Модель (Код)"
                int start = busInfo->LastIndexOf('(');
                int end = busInfo->LastIndexOf(')');

                if (start != -1 && end != -1 && end > start) {
                    String^ busCode = busInfo->Substring(start + 1, end - start - 1);
                    List<Trip^>^ busResults = Search::FindTripsByBus(tripList, busCode);

                    if (currentResults == nullptr) {
                        currentResults = busResults;
                    }
                    else {
                        List<Trip^>^ intersection = gcnew List<Trip^>();
                        for each (Trip ^ trip in busResults) {
                            if (currentResults->Contains(trip)) {
                                intersection->Add(trip);
                            }
                        }
                        currentResults = intersection;
                    }
                }
            }

            searchResults = currentResults;
        }

        // Проверяем результаты
        if (searchResults != nullptr && searchResults->Count > 0) {
            this->DialogResult = DialogResult::OK;
            this->Close();
        }
        else {
            MessageBox::Show("По указанным критериям ничего не найдено.\n"
                "Попробуйте изменить параметры поиска или сбросить критерии.",
                "Результат поиска", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при поиске: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void SearchForm::back_add_Click(System::Object^ sender, System::EventArgs^ e) {
    this->DialogResult = DialogResult::Cancel;
    this->Close();
}