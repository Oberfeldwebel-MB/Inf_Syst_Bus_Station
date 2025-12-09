#include "TimingForm.h"
#include <fstream> 
#include "StartForm.h"
#include "ChangeTripform.h"
#include "Resultform.h"
#include "ZaprosForm.h"


namespace InfSystBusStation {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::IO;
    using namespace System::Collections::Generic;
    using namespace System::Text::RegularExpressions;
    using namespace System::Globalization;


    void TimingForm::LoadDataFromFile() {
        try {
            // Очищаем DataGridView
            base_students_dataGridView->Rows->Clear();

            if (File::Exists(dataFilePath)) {
                StreamReader^ sr = gcnew StreamReader(dataFilePath, System::Text::Encoding::UTF8);

                // Пропускаем строку заголовков
                sr->ReadLine();

                // Читаем данные построчно
                String^ line;
                while ((line = sr->ReadLine()) != nullptr) {
                    array<String^>^ values = line->Split('\t');

                    // Проверяем, что количество значений соответствует ожидаемому
                    if (values->Length == 8) {
                        int rowIndex = base_students_dataGridView->Rows->Add();
                        DataGridViewRow^ row = base_students_dataGridView->Rows[rowIndex];

                        row->Cells["Num"]->Value = values[0];
                        row->Cells["FIO"]->Value = values[1];
                        row->Cells["Pol"]->Value = values[2];
                        row->Cells["Date"]->Value = values[3];
                        row->Cells["Faculty"]->Value = values[4];
                        row->Cells["Grupp"]->Value = values[5];
                        row->Cells["Rating"]->Value = values[6];
                        row->Cells["Soz_Act"]->Value = values[7];
                    }
                }
                sr->Close();
            }
            TimingForm::RenumberRows();
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при загрузке данных из файла: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    void TimingForm::SaveDataToFile(String^ fio, String^ pol, String^ date, String^ faculty, String^ grupp, Decimal rate, String^ soz_act) {
        try {
            // Читаем все строки из файла во временный список
            List<String^>^ lines = gcnew List<String^>();
            if (File::Exists(dataFilePath)) {
                StreamReader^ sr = gcnew StreamReader(dataFilePath, System::Text::Encoding::UTF8);
                sr->ReadLine(); // Пропускаем заголовок
                String^ line;
                while ((line = sr->ReadLine()) != nullptr) {
                    lines->Add(line);
                }
                sr->Close();
            }

            //        // Добавляем новую строку с данными
            String^ newLine = String::Format("{0}\t{1}\t{2}\t{3}\t{4}\t{5}\t{6}\t{7}",
                lines->Count + 1, // Автоматически генерируем номер строки
                fio, pol, date, faculty, grupp, rate, soz_act);
            lines->Add(newLine);

            // Записываем все строки обратно в файл
            StreamWriter^ sw = gcnew StreamWriter(dataFilePath, false, System::Text::Encoding::UTF8);
            sw->WriteLine("Num\tFIO\tPol\tDate\tFaculty\tGrupp\tRating\tSoz_Act"); // Записываем заголовок
            for (int i = 0; i < lines->Count; i++) {
                sw->WriteLine(lines[i]);
            }
            sw->Close();

            MessageBox::Show("Данные успешно сохранены в файл.", "Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);

            // Обновляем DataGridView (перезагружаем данные из файла)
            LoadDataFromFile();
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при сохранении данных в файл: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
    void TimingForm::SaveDataToFileAfterDeletion() {
        try {
            // Создаем временный список для хранения данных
            List<String^>^ lines = gcnew List<String^>();

            // Проходим по всем строкам в DataGridView и добавляем их во временный список
            for (int i = 0; i < base_students_dataGridView->Rows->Count; i++) {
                DataGridViewRow^ row = base_students_dataGridView->Rows[i];
                String^ newLine = String::Format("{0}\t{1}\t{2}\t{3}\t{4}\t{5}\t{6}\t{7}",
                    row->Cells["Num"]->Value,
                    row->Cells["FIO"]->Value,
                    row->Cells["Pol"]->Value,
                    row->Cells["Date"]->Value,
                    row->Cells["Faculty"]->Value,
                    row->Cells["Grupp"]->Value,
                    row->Cells["Rating"]->Value,
                    row->Cells["Soz_Act"]->Value);
                lines->Add(newLine);
            }

            // Записываем все строки обратно в файл
            StreamWriter^ sw = gcnew StreamWriter(dataFilePath, false, System::Text::Encoding::UTF8);
            sw->WriteLine("Num\tFIO\tPol\tDate\tFaculty\tGrupp\tRating\tSoz_Act"); // Записываем заголовок
            for (int i = 0; i < lines->Count; i++) {
                sw->WriteLine(lines[i]);
            }
            sw->Close();

            MessageBox::Show("Данные успешно сохранены в файл после удаления.", "Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при сохранении данных в файл после удаления: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    System::Void TimingForm::Back_Click(System::Object^ sender, System::EventArgs^ e) {
        dekanat^ dekanatForm = gcnew dekanat();
        dekanatForm->Show();
        this->Close();
    }

    System::Void TimingForm::SaveDataToFileAfterEditing() {
        try {
            StreamWriter^ sw = gcnew StreamWriter(dataFilePath, false, System::Text::Encoding::UTF8);
            sw->WriteLine("Num\tFIO\tPol\tDate\tFaculty\tGrupp\tRating\tSoz_Act"); // Заголовок

            for each (DataGridViewRow ^ row in base_students_dataGridView->Rows) {
                //if (!row->IsNewRow) {
                String^ line = String::Format("{0}\t{1}\t{2}\t{3}\t{4}\t{5}\t{6}\t{7}",
                    row->Cells["Num"]->Value,
                    row->Cells["FIO"]->Value,
                    row->Cells["Pol"]->Value,
                    row->Cells["date"]->Value,
                    row->Cells["Faculty"]->Value,
                    row->Cells["Grupp"]->Value,
                    row->Cells["Rating"]->Value,
                    row->Cells["soz_act"]->Value
                );
                sw->WriteLine(line);
                //}
            }
            sw->Close();
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при сохранении: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    System::Void TimingForm::ChangeTrip_Click(System::Object^ sender, System::EventArgs^ e) {
        change_str_form^ editForm = gcnew change_str_form();

        if (editForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            // Обновляем только отмеченные поля
            int rowIndex_to_ch = editForm->str_corr - 1;  // 

            if (rowIndex_to_ch >= 0 && rowIndex_to_ch < base_students_dataGridView->Rows->Count) {
                DataGridViewRow^ selected_row = base_students_dataGridView->Rows[rowIndex_to_ch];

                if (editForm->FIO_checkBox->Checked) selected_row->Cells["FIO"]->Value = editForm->NewFIO;
                if (editForm->pol_checkBox->Checked) selected_row->Cells["Pol"]->Value = editForm->NewPol;
                if (editForm->data_checkBox->Checked) selected_row->Cells["date"]->Value = editForm->NewDate;
                if (editForm->faculty_checkBox->Checked) selected_row->Cells["Faculty"]->Value = editForm->NewFaculty;
                if (editForm->grupp_checkBox->Checked) selected_row->Cells["Grupp"]->Value = editForm->NewGrupp;
                if (editForm->rate_checkBox->Checked) selected_row->Cells["Rating"]->Value = editForm->NewRating;
                if (editForm->soz_act_checkBox->Checked) selected_row->Cells["soz_act"]->Value = editForm->NewSozAct;


                SaveDataToFileAfterEditing();
            }
        }
    }

    List<DataGridViewRow^>^ TimingForm::SearchTrips(zapros_form^ searchForm) {
        List<DataGridViewRow^>^ results = gcnew List<DataGridViewRow^>();

        for each (DataGridViewRow ^ row in base_students_dataGridView->Rows) {

            bool match = true;

            // Проверяем каждое поле, если оно участвует в поиске
            if (searchForm->UseFIO) {
                String^ fio = row->Cells["FIO"]->Value != nullptr
                    ? row->Cells["FIO"]->Value->ToString()
                    : "";

                String^ searchFio = searchForm->SearchFIO != nullptr
                    ? searchForm->SearchFIO
                    : "";

                String^ cleanedFio = fio->Replace(".", "")->Replace(",", "")->Replace(" ", "");
                String^ cleanedSearch = searchFio->Replace(".", "")->Replace(",", "")->Replace(" ", "");

                // Вариант 1: Поиск по любому месту в ФИО (включая фамилию)
                match = cleanedFio->Contains(cleanedSearch);

                // Вариант 2: Умный поиск (инициалы или фамилия)
                if (!match) {
                    // Разбиваем ФИО на части (ЯМКлевакин -> ["Я", "М", "Клевакин"])
                    array<String^>^ parts = Regex::Split(cleanedFio, "([А-ЯA-Z])+");

                    // Проверяем каждую часть
                    for each (String ^ part in parts) {
                        if (part->Length > 0 && part->Contains(cleanedSearch)) {
                            match = true;
                            break;
                        }
                    }
                }
            }

            if (searchForm->UsePol == 1 && match == 1) {
                String^ pol = safe_cast<String^>(row->Cells["Pol"]->Value);
                if (pol == nullptr || pol != searchForm->SearchPol) {
                    match = false;
                }
            }


            if (searchForm->UseDate == 1 && match == 1) {
                DateTime searchDate;
                bool dateParseSuccess = DateTime::TryParseExact(searchForm->search_data->Text,
                    "dd.MM.yyyy",
                    CultureInfo::InvariantCulture,
                    DateTimeStyles::None,
                    searchDate);

                if (!dateParseSuccess)
                {
                    match = false;
                    System::Diagnostics::Debug::WriteLine("Ошибка парсинга введенной даты!");
                }
                else
                {
                    Object^ cellValue = row->Cells["date"]->Value;
                    if (cellValue != nullptr)
                    {
                        DateTime studentDate;
                        bool studentDateParseSuccess = DateTime::TryParseExact(cellValue->ToString(),
                            "dd.MM.yyyy",
                            CultureInfo::InvariantCulture,
                            DateTimeStyles::None,
                            studentDate);

                        // Отладочный вывод
                        System::Diagnostics::Debug::WriteLine("Попытка парсинга даты студента: " + cellValue->ToString() +
                            " Успех: " + studentDateParseSuccess +
                            " Результат: " + (studentDateParseSuccess ? studentDate.ToString("dd.MM.yyyy") : "N/A"));

                        if (!studentDateParseSuccess)
                        {
                            match = false;
                            System::Diagnostics::Debug::WriteLine("Ошибка парсинга даты студента!");
                        }
                        else
                        {
                            // Сравниваем даты
                            if (searchForm->date_bol_zad->Checked)
                                match = (studentDate > searchDate);
                            else if (searchForm->date_rav_zad->Checked)
                                match = (studentDate.Date == searchDate.Date); // Сравниваем только даты
                            else if (searchForm->date_men_zad->Checked)
                                match = (studentDate < searchDate);

                            System::Diagnostics::Debug::WriteLine("Сравнение: " + studentDate.ToString("dd.MM.yyyy") +
                                " vs " + searchDate.ToString("dd.MM.yyyy") +
                                " Результат: " + match);
                        }
                    }
                    else
                    {
                        match = false;
                        System::Diagnostics::Debug::WriteLine("Дата студента отсутствует!");
                    }
                }
            }

            if (searchForm->UseFaculty == 1 && match == 1) {
                String^ faculty = row->Cells["Faculty"]->Value != nullptr
                    ? row->Cells["Faculty"]->Value->ToString()
                    : "";

                String^ searchFaculty = searchForm->SearchFaculty != nullptr
                    ? searchForm->SearchFaculty
                    : "";

                match = faculty->Contains(searchFaculty);
            }

            if (searchForm->UseGrupp == 1 && match == 1) {
                String^ grupp = row->Cells["Grupp"]->Value != nullptr
                    ? row->Cells["Grupp"]->Value->ToString()
                    : "";

                String^ searchGrupp = searchForm->SearchGrupp != nullptr
                    ? searchForm->SearchGrupp
                    : "";

                match = grupp->Contains(searchGrupp);
            }

            if (searchForm->UseRating == 1 && match == 1) {
                Decimal rating = 0;

                if (row->Cells["Rating"]->Value != nullptr)
                {
                    String^ strValue = safe_cast<String^>(row->Cells["Rating"]->Value);
                    if (!String::IsNullOrWhiteSpace(strValue))
                    {
                        rating = Decimal::Parse(strValue);
                        if (searchForm->rate_bol_zad->Checked) match = (rating >= searchForm->SearchRating);
                        if (searchForm->rate_rav_zad->Checked) match = (rating == searchForm->SearchRating);
                        if (searchForm->rate_men_zad->Checked) match = (rating <= searchForm->SearchRating);
                    }
                }
            }

            if (searchForm->UseSozAct == 1 && match == 1) {
                Decimal sozact = 3;
                Decimal search_soz = 3;

                if (row->Cells["soz_act"]->Value != nullptr)
                {
                    String^ strValue_soz = safe_cast<String^>(row->Cells["soz_act"]->Value);

                    if (!String::IsNullOrWhiteSpace(strValue_soz))
                    {

                        sozact = Convert::ToDecimal(row->Cells["soz_act"]->Value);
                        search_soz = Decimal::Parse(searchForm->SearchSozAct);
                        if (searchForm->soz_bol_zad->Checked) match = (sozact >= search_soz);
                        if (searchForm->soz_rav_zad->Checked) match = (sozact == search_soz);
                        if (searchForm->soz_men_zad->Checked) match = (sozact <= search_soz);
                    }
                }
            }

            if (match == 1) {
                results->Add(row);
            }
        }
        return results;
    }

    System::Void TimingForm::Request_Click(System::Object^ sender, System::EventArgs^ e) {
        zapros_form^ searchForm = gcnew zapros_form();
        if (searchForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            // Ищем студентов
            List<DataGridViewRow^>^ foundStudents = SearchStudents(searchForm);


            // Открываем форму с результатами
            result_form^ resultsForm = gcnew result_form();
            this->Close();

            // Копируем найденные строки в resultsForm->results_base
            for each (DataGridViewRow ^ row in foundStudents) {
                int index = resultsForm->results_base->Rows->Add();
                DataGridViewRow^ newRow = resultsForm->results_base->Rows[index];

                // Копируем значения ячеек
                for (int i = 0; i < row->Cells->Count; i++) {
                    newRow->Cells[i]->Value = row->Cells[i]->Value;
                }
            }

            resultsForm->ShowDialog();
        }
    }

    
}