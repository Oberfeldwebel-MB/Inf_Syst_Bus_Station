#include "DeleteTripForm.h"
#include "Search.hpp"  

using namespace InfSystBusStation;
using namespace System::Windows::Forms;

// Загрузка маршрутов поездок в ComboBox
void DeleteTripForm::LoadTripRoutes() {
    tripComboBox->Items->Clear();

    if (tripList == nullptr || tripList->Count == 0) {
        tripComboBox->Enabled = false;
        deleteButton->Enabled = false;
        infoLabel->Text = "Расписание пусто!";
        infoLabel->ForeColor = Drawing::Color::DarkRed;
        return;
    }

    // Получаем все маршруты поездок
    auto tripRoutes = tripList->GetAllTripRoutes();
    for each (String ^ route in tripRoutes) {
        tripComboBox->Items->Add(route);
    }

    if (tripComboBox->Items->Count > 0) {
        tripComboBox->SelectedIndex = 0;
    }
}

// Обновление информации о выбранной поездке
void DeleteTripForm::UpdateTripInfo(Trip^ trip) {
    if (trip == nullptr) {
        routeLabel->Text = "Маршрут: не указано";
        dateLabel->Text = "Дата: не указано";
        timeLabel->Text = "Время: не указано";
        priceLabel->Text = "Цена: не указано";
        busLabel->Text = "Автобус: не указано";
        driverLabel->Text = "Водитель: не указано";
        statusLabel->Text = "Статус: не указано";
        return;
    }

    // Заполняем информацию
    routeLabel->Text = "Маршрут: " + trip->GetRoute();
    dateLabel->Text = "Дата: " + trip->GetTripDate().ToString("dd.MM.yyyy");
    timeLabel->Text = "Время: " + trip->GetTripTime();
    priceLabel->Text = "Цена: " + trip->GetPrice().ToString("N0") + " руб.";

    // Автобус
    String^ busText = "Автобус: ";
    if (trip->GetBus() != nullptr) {
        busText += trip->GetBus()->GetBrand() + " [" + trip->GetBus()->GetFormattedCode() + "]";
    }
    else {
        busText += "не назначен";
    }
    busLabel->Text = busText;

    // Водитель
    String^ driverText = "Водитель: ";
    if (trip->GetDriver() != nullptr) {
        driverText += trip->GetDriver()->GetFullName();
    }
    else {
        driverText += "не назначен";
    }
    driverLabel->Text = driverText;

    // Статус с цветом предупреждения
    String^ status = trip->GetStatus();
    statusLabel->Text = "Статус: " + status;

    // Обновляем информационную метку
    infoLabel->Text = "Готово к удалению";
    infoLabel->ForeColor = Drawing::Color::DarkRed;
}

System::Void DeleteTripForm::tripComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
    if (tripComboBox->SelectedIndex >= 0) {
        String^ selectedRoute = safe_cast<String^>(tripComboBox->SelectedItem);

        // ИЗМЕНЕНО: Используем Search класс вместо прямого вызова
        Trip^ selectedTrip = Search::FindTripByRoute(tripList, selectedRoute);

        UpdateTripInfo(selectedTrip);
    }
}

System::Void DeleteTripForm::deleteButton_Click(System::Object^ sender, System::EventArgs^ e) {
    if (tripComboBox->SelectedIndex < 0) {
        MessageBox::Show("Выберите поездку для удаления!", "Ошибка",
            MessageBoxButtons::OK,
            MessageBoxIcon::Error);
        return;
    }

    String^ selectedRoute = safe_cast<String^>(tripComboBox->SelectedItem);

    // ИЗМЕНЕНО: Используем Search класс вместо прямого вызова
    Trip^ selectedTrip = Search::FindTripByRoute(tripList, selectedRoute);

    if (selectedTrip == nullptr) {
        MessageBox::Show("Выбранная поездка не найдена в системе!", "Ошибка",
            MessageBoxButtons::OK,
            MessageBoxIcon::Error);
        return;
    }

    try {
        // Удаляем поездку без подтверждения
        bool success = tripList->InternalRemoveTrip(selectedRoute);

        if (success) {
            // Показываем информацию об удаленной поездке
            String^ infoMessage = String::Format(
                "Поездка успешно удалена!\n\n"
                "Маршрут: {0}\n"
                "Дата: {1:dd.MM.yyyy}\n"
                "Время: {2}",
                selectedTrip->GetRoute(),
                selectedTrip->GetTripDate(),
                selectedTrip->GetTripTime());

            MessageBox::Show(infoMessage, "Успешное удаление",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information);

            // Обновляем список в ComboBox
            LoadTripRoutes();

            // Если еще есть поездки, выбираем первую
            if (tripComboBox->Items->Count > 0) {
                tripComboBox->SelectedIndex = 0;
            }
            else {
                // Если поездок не осталось, закрываем форму
                this->DialogResult = System::Windows::Forms::DialogResult::OK;
                this->Close();
            }
        }
        else {
            MessageBox::Show("Не удалось удалить поездку!", "Ошибка",
                MessageBoxButtons::OK,
                MessageBoxIcon::Error);
        }
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при удалении: " + ex->Message, "Ошибка",
            MessageBoxButtons::OK,
            MessageBoxIcon::Error);
    }
}

System::Void DeleteTripForm::cancelButton_Click(System::Object^ sender, System::EventArgs^ e) {
    this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
    this->Close();
}