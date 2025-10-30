#pragma once

class Report {
private:
    int Income = 0;
    int Expenses = 0;
    int Profit = 0;

public:
    Report() = default;

    void Add_income(int new_income);
    void Add_expenses(int new_expenses);
};