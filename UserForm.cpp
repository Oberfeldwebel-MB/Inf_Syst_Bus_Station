// UserForm.cpp
#include "pch.h"
#include "UserForm.h"
#include "StartForm.h"
#include "TimingForm.h"

namespace InfSystBusStation {

    // Îáğàáîò÷èê êíîïêè "Âûáğàòü áèëåò"
    System::Void UserForm::ChoseButton_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            // Ñîçäàåì è îòêğûâàåì ôîğìó ğàñïèñàíèÿ
            TimingForm^ timingForm = gcnew TimingForm();
            timingForm->Show();
        }
        catch (Exception^ ex) {
            MessageBox::Show("Îøèáêà: " + ex->Message);
        }
    }

    // Îáğàáîò÷èê êíîïêè "Ìîè áèëåòû"
    System::Void UserForm::TicketListButton_Click(System::Object^ sender, System::EventArgs^ e) {
        MessageBox::Show("Ôîğìà ñî ñïèñêîì áèëåòîâ");
        // TODO: Îòêğûòü ôîğìó TicketsListForm
        // TicketsListForm^ ticketsForm = gcnew TicketsListForm();
        // ticketsForm->Show();
    }

    // Îáğàáîò÷èê êíîïêè "Íàçàä"
    System::Void UserForm::BackButton_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            // Çàêğûâàåì òåêóùóş ôîğìó è ïîêàçûâàåì ñòàğòîâóş
            StartForm^ startForm = gcnew StartForm();
            startForm->Show();
            this->Close();
        }
        catch (Exception^ ex) {
            MessageBox::Show("Îøèáêà: " + ex->Message);
        }
    }
}