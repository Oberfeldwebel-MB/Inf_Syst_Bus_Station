#include "AdminForm.h"
#include "TimingForm.h"
#include "BusListForm.h"
#include "DriversListForm.h"
#include "StartForm.h"  // Добавляем

namespace InfSystBusStation {


	System::Void AdminForm::buttonSchedule_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			TripList^ tripList = gcnew TripList();
			BusList^ busList = gcnew BusList();
			DriversList^ driverList = gcnew DriversList();

			TimingForm^ timingForm = gcnew TimingForm(tripList, busList, driverList);
			timingForm->ShowDialog();

			delete timingForm;
			delete tripList;
			delete busList;
			delete driverList;
		}
		catch (Exception^ ex) {
			MessageBox::Show("Ошибка при открытии формы расписания: " + ex->Message,
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	System::Void AdminForm::buttonDrivers_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			DriversList^ driverList = gcnew DriversList();
			DriversListForm^ driversForm = gcnew DriversListForm(driverList);
			driversForm->ShowDialog();
			delete driversForm;
			delete driverList;
		}
		catch (Exception^ ex) {
			MessageBox::Show("Ошибка при открытии формы водителей: " + ex->Message,
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	System::Void AdminForm::buttonBuses_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			BusList^ busList = gcnew BusList();
			BusListForm^ busesForm = gcnew BusListForm(busList);
			busesForm->ShowDialog();
			delete busesForm;
			delete busList;
		}
		catch (Exception^ ex) {
			MessageBox::Show("Ошибка при открытии формы автобусов: " + ex->Message,
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	System::Void AdminForm::buttonLogout_Click(System::Object^ sender, System::EventArgs^ e) {
		DialogResult result = MessageBox::Show(
			L"Вы уверены, что хотите выйти из системы администратора?",
			L"Подтверждение выхода",
			MessageBoxButtons::YesNo,
			MessageBoxIcon::Question);

		if (result == DialogResult::Yes) {
			this->Close();
		}
	}

	System::Void AdminForm::buttonBack_Click(System::Object^ sender, System::EventArgs^ e) {
		// Возвращаемся на стартовую форму
		DialogResult result = MessageBox::Show(
			L"Вернуться на главный экран?",
			L"Подтверждение",
			MessageBoxButtons::YesNo,
			MessageBoxIcon::Question);

		if (result == DialogResult::Yes) {
			// Закрываем AdminForm и показываем StartForm
			StartForm^ startForm = gcnew StartForm();
			startForm->Show();
			this->Close();
		}
	}
}