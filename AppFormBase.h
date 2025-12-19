#pragma once
#include "IAppForm.h"

namespace InfSystBusStation {
    namespace UI {

        using namespace System;
        using namespace System::Windows::Forms;
        using namespace System::Drawing;

        /// <summary>
        /// Базовая реализация интерфейса IAppForm
        /// </summary>
        public ref class AppFormBase abstract : public Form, public IAppForm
        {
        public:
            // Реализация событий IAppForm (автоматическая)
            virtual event EventHandler^ FormClosingRequested;
            virtual event EventHandler<String^>^ OpenFormRequested;

            // Конструктор
            AppFormBase()
            {
                ApplyDefaultStyle();
                this->FormClosing += gcnew FormClosingEventHandler(this, &AppFormBase::OnFormClosing);
            }

            // Реализация методов IAppForm
            virtual void Show() override { Form::Show(); OnFormShown(); }
            virtual System::Windows::Forms::DialogResult ShowDialog() override { return Form::ShowDialog(); }
            virtual void Hide() override { Form::Hide(); OnFormHidden(); }
            virtual void Close() override { Form::Close(); }
            virtual void RefreshData() { this->Refresh(); }

        protected:
            // Методы для вызова событий
            void RaiseFormClosingRequested()
            {
                // Вызываем событие (C++/CLI автоматом создает метод __raise)
                __raise FormClosingRequested(this, EventArgs::Empty);
            }

            void RaiseOpenFormRequested(String^ formName)
            {
                __raise OpenFormRequested(this, formName);
            }

            void ApplyDefaultStyle()
            {
                this->BackColor = System::Drawing::Color::SeaGreen;
                this->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 10.0f);
                this->StartPosition = FormStartPosition::CenterScreen;
                this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
                this->MaximizeBox = false;
            }

            virtual void OnFormShown() {}
            virtual void OnFormHidden() {}
            virtual void OnFormClosing(Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
            {
                if (!e->Cancel)
                {
                    RaiseFormClosingRequested();
                }
            }
        };

    }
}