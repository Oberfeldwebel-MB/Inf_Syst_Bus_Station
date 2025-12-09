#pragma once

namespace InfSystBusStation {

        using namespace System;
        using namespace System::Collections::Generic;

        public interface class IValidatable
        {
            bool Validate();
            array<String^>^ GetValidationErrors();
            void ClearValidationErrors();
            bool HasValidationErrors();
        };

} 