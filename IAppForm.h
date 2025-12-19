#pragma once

namespace InfSystBusStation {


        using namespace System;
        using namespace System::Windows::Forms;

        /// <summary>
        /// Интерфейс для всех форм приложения
        /// </summary>
        public interface class IAppForm
        {
            /// <summary>
            /// Открыть новую форму и закрыть текущую
            /// </summary>
            /// <param name="nextForm">Новая форма для открытия</param>
            virtual void OpenAndClose(Form^ nextForm) = 0;

            /// <summary>
            /// Открыть форму как модальное окно
            /// </summary>
            /// <param name="dialogForm">Форма-диалог</param>
            /// <returns>Результат диалога</returns>
            virtual System::Windows::Forms::DialogResult OpenModal(Form^ dialogForm) = 0;

            /// <summary>
            /// Вернуться к предыдущей форме
            /// </summary>
            virtual void GoBack() = 0;
        };
}