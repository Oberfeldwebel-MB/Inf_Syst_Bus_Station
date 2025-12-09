#include "AddDriverForm.h"

namespace InfSystBusStatio {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    System::Void AddDriverForm::add_button_Click(System::Object^ sender, System::EventArgs^ e) {

        String^ fioText = FIO_add->Text->Replace("_", "")->Replace(" ", "");
        fioText = fioText->Trim();

        if (fioText->Length < 3) {
            MessageBox::Show("Некорректный формат ФИО. Пример: А,А,Рогатин", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        if (fioText[1] != ',' || fioText[3] != ',') {
            MessageBox::Show("Некорректный формат ФИО (проверьте инициалы). (А,А,Рогатин - пример)", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // Проверяем, что инициалы - буквы
        if (!Char::IsLetter(fioText[0]) || !Char::IsLetter(fioText[2])) {
            MessageBox::Show("Некорректный формат ФИО (проверьте инициалы). (А,А,Рогатин - пример)", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // Проверяем, что фамилия (все, что после 4-го символа) не пустая
        String^ lastName = fioText->Substring(4);
        if (String::IsNullOrWhiteSpace(lastName) || lastName->Length < 1) {
            MessageBox::Show("Укажите фамилию (А,А,Рогатин - пример)", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        if (String::IsNullOrWhiteSpace(pol_add->Text)) {
            MessageBox::Show("Поле Пол не может быть пустым.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        String^ dateText = data_add->Text;

        // Проверяем, что дата заполнена полностью
        if (!data_add->MaskCompleted) {
            MessageBox::Show("Пожалуйста, заполните дату полностью.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // Разделяем дату на день, месяц и год
        array<String^>^ dateParts = dateText->Split('.');

        if (dateParts->Length != 3) {
            MessageBox::Show("Некорректный формат даты. Используйте dd/MM/yyyy.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        int day = Convert::ToInt32(dateParts[0]);
        int month = Convert::ToInt32(dateParts[1]);
        int year = Convert::ToInt32(dateParts[2]);

        // Список с количеством дней в каждом месяце
        array<int>^ daysInMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        // Проверка на високосный год для февраля
        if (DateTime::IsLeapYear(year)) {
            daysInMonth[1] = 29; // Февраль - 29 дней
        }

        // Проверяем месяц
        if (month < 1 || month > 12) {
            MessageBox::Show("Месяц должен быть между 1 и 12.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // Проверяем день
        if (day < 1 || day > daysInMonth[month - 1]) {
            MessageBox::Show("День должен быть между 1 и " + daysInMonth[month - 1].ToString() + " для выбранного месяца.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }


        if (String::IsNullOrWhiteSpace(faculty_add->Text)) {
            MessageBox::Show("Поле Факультет не может быть пустым.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        if (String::IsNullOrWhiteSpace(grupp_add->Text)) {
            MessageBox::Show("Поле Группа не может быть пустым.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        if (String::IsNullOrWhiteSpace(add_soz_act->Text)) {
            MessageBox::Show("Поле Соц. активность не может быть пустым.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        String^ Fio = FIO_add->Text;
        String^ Pol = "";
        if (pol_add->CheckedItems->Count > 0) {
            Pol = pol_add->CheckedItems[0]->ToString();
        }
        String^ Data_str = data_add->Text;
        String^ Faculty = faculty_add->Text;
        String^ Grupp = grupp_add->Text;
        String^ Soz_act = add_soz_act->Text;
        Decimal Rating = 0;
        try {
            Rating = Convert::ToDecimal(ratingNumericUpDown->Value); // Если используете NumericUpDown
            if (Rating < 0 || Rating > 100) {
                MessageBox::Show("Рейтинг должен быть в диапазоне от 0 до 100.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }
        }
        catch (FormatException^) {
            MessageBox::Show("Неверный формат рейтинга. Введите число.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // Присваиваем значения свойствам
        this->FIO = Fio;
        this->Pol = Pol;
        this->Data_Str = Data_str;
        this->Faculty = Faculty;
        this->Grupp = Grupp;
        this->SozAct = Soz_act;
        this->Rating = Rating;

        this->DialogResult = System::Windows::Forms::DialogResult::OK;
        this->Close();
    }
}