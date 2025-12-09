#pragma once
#include "AddTripForm.h"
#include "zapros_form.h"
#include "reference_form.h"
#include "delete_form.h"
#include <msclr\marshal_cppstd.h>

namespace InfSystBusStation {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Сводка для Student_base
	/// </summary>
	public ref class TimingForm : public System::Windows::Forms::Form
	{
	public:
		TimingForm(void) {
			InitializeComponent();
			LoadDataFromFile();

		}
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~TimingForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::MenuStrip^ base_menuStrip1;
	public: System::Windows::Forms::ToolStripMenuItem^ AddTrip;
	public: System::Windows::Forms::ToolStripMenuItem^ DeleteTrip;
	private:

	private:


	public: System::Windows::Forms::ToolStripMenuItem^ change_str;
	public: System::Windows::Forms::ToolStripMenuItem^ request;

	public: System::Windows::Forms::ToolStripMenuItem^ delete_file;
	private: System::Windows::Forms::ToolStripMenuItem^ reference;
	private: System::Windows::Forms::ToolStripMenuItem^ back;

	private: int studentCounter = 1;


	public: System::Windows::Forms::DataGridView^ base_students_dataGridView;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Num;
	public:
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ StartPoint;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ FinishPoint;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ BusData;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ DepDate;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ ArrDate;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Price;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ DriverDate;



	public:
		String^ dataFilePath = "database.txt"; // Путь к файлу
		void SaveDataToFile(String^ fio, String^ pol, String^ date, String^ faculty, String^ grupp, Decimal rate, String^ soz_act);
		void LoadDataFromFile();
		void SaveDataToFileAfterDeletion();
		void SaveDataToFileAfterEditing();
		System::Collections::Generic::List<System::Windows::Forms::DataGridViewRow^>^ SearchTrips(zapros_form^ searchForm);


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->base_menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->AddTrip = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->DeleteTrip = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->change_str = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->request = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->delete_file = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->reference = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->back = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->base_students_dataGridView = (gcnew System::Windows::Forms::DataGridView());
			this->Num = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->StartPoint = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->FinishPoint = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->BusData = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->DepDate = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ArrDate = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Price = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->DriverDate = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->base_menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->base_students_dataGridView))->BeginInit();
			this->SuspendLayout();
			// 
			// base_menuStrip1
			// 
			this->base_menuStrip1->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->base_menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->base_menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->AddTrip, this->DeleteTrip,
					this->change_str, this->request, this->delete_file, this->reference, this->back
			});
			this->base_menuStrip1->Location = System::Drawing::Point(0, 0);
			this->base_menuStrip1->Name = L"base_menuStrip1";
			this->base_menuStrip1->Size = System::Drawing::Size(1159, 28);
			this->base_menuStrip1->TabIndex = 0;
			// 
			// AddTrip
			// 
			this->AddTrip->Name = L"AddTrip";
			this->AddTrip->Size = System::Drawing::Size(149, 24);
			this->AddTrip->Text = L"Добавить поездку";
			this->AddTrip->Click += gcnew System::EventHandler(this, &TimingForm::AddTrip_Click);
			// 
			// DeleteTrip
			// 
			this->DeleteTrip->Name = L"DeleteTrip";
			this->DeleteTrip->Size = System::Drawing::Size(138, 24);
			this->DeleteTrip->Text = L"Удалить поездку";
			this->DeleteTrip->Click += gcnew System::EventHandler(this, &TimingForm::DeleteTrip_Click);
			// 
			// change_str
			// 
			this->change_str->Name = L"change_str";
			this->change_str->Size = System::Drawing::Size(184, 24);
			this->change_str->Text = L"Редактировать поездку";
			this->change_str->Click += gcnew System::EventHandler(this, &TimingForm::ChangeTrip_Click);
			// 
			// request
			// 
			this->request->Name = L"request";
			this->request->Size = System::Drawing::Size(66, 24);
			this->request->Text = L"Поиск";
			this->request->Click += gcnew System::EventHandler(this, &TimingForm::Request_Click);
			// 
			// delete_file
			// 
			this->delete_file->Name = L"delete_file";
			this->delete_file->Size = System::Drawing::Size(118, 24);
			this->delete_file->Text = L"Удалить файл";
			this->delete_file->Click += gcnew System::EventHandler(this, &TimingForm::DeleteFile_Click);
			// 
			// reference
			// 
			this->reference->Name = L"reference";
			this->reference->Size = System::Drawing::Size(81, 24);
			this->reference->Text = L"Справка";
			this->reference->Click += gcnew System::EventHandler(this, &TimingForm::Reference_Click);
			// 
			// back
			// 
			this->back->Name = L"back";
			this->back->Size = System::Drawing::Size(65, 24);
			this->back->Text = L"Назад";
			this->back->Click += gcnew System::EventHandler(this, &TimingForm::Back_Click);
			// 
			// base_students_dataGridView
			// 
			this->base_students_dataGridView->AllowUserToAddRows = false;
			this->base_students_dataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->base_students_dataGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(8) {
				this->Num,
					this->StartPoint, this->FinishPoint, this->BusData, this->DepDate, this->ArrDate, this->Price, this->DriverDate
			});
			this->base_students_dataGridView->Location = System::Drawing::Point(0, 31);
			this->base_students_dataGridView->Name = L"base_students_dataGridView";
			this->base_students_dataGridView->RowHeadersWidth = 51;
			this->base_students_dataGridView->RowTemplate->Height = 24;
			this->base_students_dataGridView->Size = System::Drawing::Size(1147, 466);
			this->base_students_dataGridView->TabIndex = 1;
			// 
			// Num
			// 
			this->Num->HeaderText = L"Номер маршрута";
			this->Num->MinimumWidth = 6;
			this->Num->Name = L"Num";
			this->Num->Width = 125;
			// 
			// StartPoint
			// 
			this->StartPoint->HeaderText = L"Начальный пункт";
			this->StartPoint->MinimumWidth = 6;
			this->StartPoint->Name = L"StartPoint";
			this->StartPoint->Width = 125;
			// 
			// FinishPoint
			// 
			this->FinishPoint->HeaderText = L"Конечный пункт";
			this->FinishPoint->MinimumWidth = 6;
			this->FinishPoint->Name = L"FinishPoint";
			this->FinishPoint->Width = 125;
			// 
			// BusData
			// 
			this->BusData->HeaderText = L"Данные об автобусе";
			this->BusData->MinimumWidth = 6;
			this->BusData->Name = L"BusData";
			this->BusData->Width = 125;
			// 
			// DepDate
			// 
			this->DepDate->HeaderText = L"Дата отправления";
			this->DepDate->MinimumWidth = 6;
			this->DepDate->Name = L"DepDate";
			this->DepDate->Width = 125;
			// 
			// ArrDate
			// 
			this->ArrDate->HeaderText = L"Дата прибытия";
			this->ArrDate->MinimumWidth = 6;
			this->ArrDate->Name = L"ArrDate";
			this->ArrDate->Width = 125;
			// 
			// Price
			// 
			this->Price->HeaderText = L"Цена";
			this->Price->MinimumWidth = 6;
			this->Price->Name = L"Price";
			this->Price->Width = 50;
			// 
			// DriverDate
			// 
			this->DriverDate->HeaderText = L"Данные о водителе";
			this->DriverDate->MinimumWidth = 6;
			this->DriverDate->Name = L"DriverDate";
			this->DriverDate->Width = 125;
			// 
			// TimingForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->ClientSize = System::Drawing::Size(1159, 483);
			this->Controls->Add(this->base_students_dataGridView);
			this->Controls->Add(this->base_menuStrip1);
			this->MainMenuStrip = this->base_menuStrip1;
			this->Name = L"TimingForm";
			this->Text = L"Расписание поездок";
			this->base_menuStrip1->ResumeLayout(false);
			this->base_menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->base_students_dataGridView))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
	private: System::Void AddTrip_Click(System::Object^ sender, System::EventArgs^ e) {
		add_form^ AddForm = gcnew add_form;
		if (AddForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			// Собираем данные из формы
			String^ fio = AddForm->FIO;
			String^ pol = AddForm->Pol;
			String^ date = AddForm->Data_Str;
			String^ faculty = AddForm->Faculty;
			String^ grupp = AddForm->Grupp;
			String^ soz_act = AddForm->SozAct;
			Decimal rate = AddForm->Rating;
			int rowIndex_to_ch;

			// Сохраняем данные в файл (метод SaveDataToFile)
			SaveDataToFile(fio, pol, date, faculty, grupp, rate, soz_act);
		}
	}
	private: System::Void DeleteTrip_Click(System::Object^ sender, System::EventArgs^ e) {
		delete_form^ DeleteForm = gcnew delete_form(base_students_dataGridView);
		if (DeleteForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			int rowIndexToDelete = DeleteForm->RowIndexToDelete;

			if (rowIndexToDelete >= 0) {
				// Удаляем строку из DataGridView
				base_students_dataGridView->Rows->RemoveAt(rowIndexToDelete);

				// Обновляем файл
				SaveDataToFileAfterDeletion();

				// Перенумеровываем строки
				RenumberRows();
			}
		}
	}
	private: System::Void TimingForm::RenumberRows() {
		for (int i = 0; i < base_students_dataGridView->Rows->Count; i++) {
			base_students_dataGridView->Rows[i]->Cells["Num"]->Value = i + 1;
		}
	}
	private: System::Void Back_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void DeleteFile_Click(System::Object^ sender, System::EventArgs^ e) {
		System::IO::File::Delete(dataFilePath);
		MessageBox::Show("Файл успешно удален.", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
		LoadDataFromFile();
	}
	private: System::Void ChangeTrip_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Request_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void Reference_Click(System::Object^ sender, System::EventArgs^ e) {
		reference_form^ sprav = gcnew reference_form();
		sprav->Show();
	}
	};
}

