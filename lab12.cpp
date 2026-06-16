 // Lab12_29.cpp
// Лабораторная работа №12 - Вариант 29
// Сформировать матрицы A(m,n) и B(m,k). Создать R = A * max(B) по строкам.

#include "pch.h"
#include <Windows.h>
#include <vector>
#include <random>
#include <string>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

public ref class Lab12Form : public Form
{
private:
    GroupBox^ gbInput;
    GroupBox^ gbOutput;
    
    Label^ lblRowsA;
    Label^ lblColsA;
    Label^ lblRowsB;
    Label^ lblColsB;
    Label^ lblMin;
    Label^ lblMax;
    
    TextBox^ txtRowsA;
    TextBox^ txtColsA;
    TextBox^ txtRowsB;
    TextBox^ txtColsB;
    TextBox^ txtMin;
    TextBox^ txtMax;
    
    ListBox^ lstA;
    ListBox^ lstB;
    ListBox^ lstR;
    
    Label^ lblStatus;
    
    Button^ btnSolve;
    Button^ btnClear;
    Button^ btnExit;

public:
    Lab12Form()
    {
        this->Text = L"ЛР №12 - Вариант 29";
        this->Size = Drawing::Size(1020, 750);
        this->StartPosition = FormStartPosition::CenterScreen;
        this->BackColor = Color::FromArgb(240, 240, 240);
        this->Font = gcnew Drawing::Font("Segoe UI", 9);

        CreateControls();
    }

private:
    void CreateControls()
    {
        // ---- ГРУППА ВВОДА ----
        gbInput = gcnew GroupBox();
        gbInput->Text = L"Входные параметры";
        gbInput->Location = Point(10, 10);
        gbInput->Size = Drawing::Size(980, 150);
        gbInput->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        this->Controls->Add(gbInput);

        int y = 30;
        int x1 = 20, x2 = 120, x3 = 220;

        // Строка 0: A(m,n)
        lblRowsA = gcnew Label();
        lblRowsA->Text = L"Строки A:";
        lblRowsA->Location = Point(x1, y);
        lblRowsA->Size = Drawing::Size(80, 25);
        gbInput->Controls->Add(lblRowsA);

        txtRowsA = gcnew TextBox();
        txtRowsA->Location = Point(x2, y);
        txtRowsA->Size = Drawing::Size(80, 25);
        txtRowsA->Font = gcnew Drawing::Font("Segoe UI", 10);
        txtRowsA->Text = L"5";
        gbInput->Controls->Add(txtRowsA);

        lblColsA = gcnew Label();
        lblColsA->Text = L"Столбцы A:";
        lblColsA->Location = Point(x3 + 100, y);
        lblColsA->Size = Drawing::Size(80, 25);
        gbInput->Controls->Add(lblColsA);

        txtColsA = gcnew TextBox();
        txtColsA->Location = Point(x3 + 200, y);
        txtColsA->Size = Drawing::Size(80, 25);
        txtColsA->Font = gcnew Drawing::Font("Segoe UI", 10);
        txtColsA->Text = L"3";
        gbInput->Controls->Add(txtColsA);

        // Строка 1: B(m,k)
        y += 40;
        lblRowsB = gcnew Label();
        lblRowsB->Text = L"Строки B:";
        lblRowsB->Location = Point(x1, y);
        lblRowsB->Size = Drawing::Size(80, 25);
        gbInput->Controls->Add(lblRowsB);

        txtRowsB = gcnew TextBox();
        txtRowsB->Location = Point(x2, y);
        txtRowsB->Size = Drawing::Size(80, 25);
        txtRowsB->Font = gcnew Drawing::Font("Segoe UI", 10);
        txtRowsB->Text = L"5";
        gbInput->Controls->Add(txtRowsB);

        lblColsB = gcnew Label();
        lblColsB->Text = L"Столбцы B:";
        lblColsB->Location = Point(x3 + 100, y);
        lblColsB->Size = Drawing::Size(80, 25);
        gbInput->Controls->Add(lblColsB);

        txtColsB = gcnew TextBox();
        txtColsB->Location = Point(x3 + 200, y);
        txtColsB->Size = Drawing::Size(80, 25);
        txtColsB->Font = gcnew Drawing::Font("Segoe UI", 10);
        txtColsB->Text = L"4";
        gbInput->Controls->Add(txtColsB);

        // Строка 2: Диапазон
        y += 40;
        lblMin = gcnew Label();
        lblMin->Text = L"Минимум:";
        lblMin->Location = Point(x1, y);
        lblMin->Size = Drawing::Size(80, 25);
        gbInput->Controls->Add(lblMin);

        txtMin = gcnew TextBox();
        txtMin->Location = Point(x2, y);
        txtMin->Size = Drawing::Size(80, 25);
        txtMin->Font = gcnew Drawing::Font("Segoe UI", 10);
        txtMin->Text = L"-10";
        gbInput->Controls->Add(txtMin);

        lblMax = gcnew Label();
        lblMax->Text = L"Максимум:";
        lblMax->Location = Point(x3 + 100, y);
        lblMax->Size = Drawing::Size(80, 25);
        gbInput->Controls->Add(lblMax);

        txtMax = gcnew TextBox();
        txtMax->Location = Point(x3 + 200, y);
        txtMax->Size = Drawing::Size(80, 25);
        txtMax->Font = gcnew Drawing::Font("Segoe UI", 10);
        txtMax->Text = L"10";
        gbInput->Controls->Add(txtMax);

        Label^ hint = gcnew Label();
        hint->Text = L"(min должен быть < max)";
        hint->Location = Point(x3 + 300, y);
        hint->Size = Drawing::Size(200, 25);
        hint->ForeColor = Color::Gray;
        hint->Font = gcnew Drawing::Font("Segoe UI", 8, FontStyle::Italic);
        gbInput->Controls->Add(hint);

        // ---- ГРУППА ВЫВОДА ----
        gbOutput = gcnew GroupBox();
        gbOutput->Text = L"Результаты";
        gbOutput->Location = Point(10, 170);
        gbOutput->Size = Drawing::Size(980, 430);
        gbOutput->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        this->Controls->Add(gbOutput);

        int listWidth = 300, listHeight = 370;

        // Матрица A
        Label^ lblA = gcnew Label();
        lblA->Text = L"Матрица A:";
        lblA->Location = Point(20, 30);
        lblA->Size = Drawing::Size(120, 25);
        lblA->Font = gcnew Drawing::Font("Segoe UI", 9);
        gbOutput->Controls->Add(lblA);

        lstA = gcnew ListBox();
        lstA->Location = Point(20, 60);
        lstA->Size = Drawing::Size(listWidth, listHeight);
        lstA->Font = gcnew Drawing::Font("Consolas", 9);
        lstA->BackColor = Color::White;
        lstA->SelectionMode = SelectionMode::None;
        gbOutput->Controls->Add(lstA);

        // Матрица B
        Label^ lblB = gcnew Label();
        lblB->Text = L"Матрица B:";
        lblB->Location = Point(340, 30);
        lblB->Size = Drawing::Size(120, 25);
        lblB->Font = gcnew Drawing::Font("Segoe UI", 9);
        gbOutput->Controls->Add(lblB);

        lstB = gcnew ListBox();
        lstB->Location = Point(340, 60);
        lstB->Size = Drawing::Size(listWidth, listHeight);
        lstB->Font = gcnew Drawing::Font("Consolas", 9);
        lstB->BackColor = Color::White;
        lstB->SelectionMode = SelectionMode::None;
        gbOutput->Controls->Add(lstB);

        // Результат R
        Label^ lblR = gcnew Label();
        lblR->Text = L"Результат R = A × max(B):";
        lblR->Location = Point(660, 30);
        lblR->Size = Drawing::Size(200, 25);
        lblR->Font = gcnew Drawing::Font("Segoe UI", 9);
        gbOutput->Controls->Add(lblR);

        lstR = gcnew ListBox();
        lstR->Location = Point(660, 60);
        lstR->Size = Drawing::Size(listWidth, listHeight);
        lstR->Font = gcnew Drawing::Font("Consolas", 9);
        lstR->BackColor = Color::White;
        lstR->SelectionMode = SelectionMode::None;
        gbOutput->Controls->Add(lstR);

        // ---- СТАТУС ----
        lblStatus = gcnew Label();
        lblStatus->Text = L"Введите параметры и нажмите 'Решение'";
        lblStatus->Location = Point(10, 610);
        lblStatus->Size = Drawing::Size(980, 35);
        lblStatus->BackColor = Color::FromArgb(240, 240, 240);
        lblStatus->TextAlign = ContentAlignment::MiddleCenter;
        this->Controls->Add(lblStatus);

        // ---- КНОПКИ ----
        btnSolve = gcnew Button();
        btnSolve->Text = L"Решение";
        btnSolve->Location = Point(340, 660);
        btnSolve->Size = Drawing::Size(130, 35);
        btnSolve->BackColor = Color::FromArgb(0, 123, 255);
        btnSolve->ForeColor = Color::White;
        btnSolve->FlatStyle = FlatStyle::Flat;
        btnSolve->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        btnSolve->Click += gcnew EventHandler(this, &Lab12Form::OnSolve);
        this->Controls->Add(btnSolve);

        btnClear = gcnew Button();
        btnClear->Text = L"Очистить";
        btnClear->Location = Point(490, 660);
        btnClear->Size = Drawing::Size(130, 35);
        btnClear->BackColor = Color::FromArgb(243, 156, 18);
        btnClear->ForeColor = Color::White;
        btnClear->FlatStyle = FlatStyle::Flat;
        btnClear->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        btnClear->Click += gcnew EventHandler(this, &Lab12Form::OnClear);
        this->Controls->Add(btnClear);

        btnExit = gcnew Button();
        btnExit->Text = L"Выход";
        btnExit->Location = Point(640, 660);
        btnExit->Size = Drawing::Size(130, 35);
        btnExit->BackColor = Color::FromArgb(220, 53, 69);
        btnExit->ForeColor = Color::White;
        btnExit->FlatStyle = FlatStyle::Flat;
        btnExit->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        btnExit->Click += gcnew EventHandler(this, &Lab12Form::OnExit);
        this->Controls->Add(btnExit);
    }

    // ---- Логические функции ----
    void GenerateMatrix(int rows, int cols, double minVal, double maxVal,
                        std::vector<std::vector<double>>& mat)
    {
        mat.clear();
        mat.resize(rows, std::vector<double>(cols));
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(minVal, maxVal);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                mat[i][j] = dist(gen);
            }
        }
    }

    double MaxInRow(const std::vector<double>& row)
    {
        if (row.empty()) return 0;
        double mx = row[0];
        for (double val : row)
        {
            if (val > mx) mx = val;
        }
        return mx;
    }

    void DisplayMatrix(const std::vector<std::vector<double>>& mat, ListBox^ list)
    {
        list->Items->Clear();
        if (mat.empty())
        {
            list->Items->Add(L"Пусто");
            return;
        }
        for (size_t i = 0; i < mat.size(); ++i)
        {
            String^ line = L"";
            for (size_t j = 0; j < mat[i].size(); ++j)
            {
                line += String::Format(L"{0,8:F2}", mat[i][j]);
            }
            list->Items->Add(line);
        }
    }

    void UpdateStatus(String^ msg, bool isError = false)
    {
        lblStatus->Text = msg;
        if (isError)
        {
            lblStatus->BackColor = Color::FromArgb(248, 215, 218);
            lblStatus->ForeColor = Color::FromArgb(114, 28, 36);
        }
        else
        {
            lblStatus->BackColor = Color::FromArgb(212, 237, 218);
            lblStatus->ForeColor = Color::FromArgb(21, 87, 36);
        }
    }

    // ---- Обработчики ----
    void OnSolve(Object^ sender, EventArgs^ e)
    {
        int rowsA, colsA, rowsB, colsB;
        double minVal, maxVal;

        if (!Int32::TryParse(txtRowsA->Text, rowsA) || rowsA < 1)
        {
            MessageBox::Show(L"Строки A должны быть >= 1!", L"Ошибка");
            txtRowsA->Focus();
            return;
        }
        if (!Int32::TryParse(txtColsA->Text, colsA) || colsA < 1)
        {
            MessageBox::Show(L"Столбцы A должны быть >= 1!", L"Ошибка");
            txtColsA->Focus();
            return;
        }
        if (!Int32::TryParse(txtRowsB->Text, rowsB) || rowsB < 1)
        {
            MessageBox::Show(L"Строки B должны быть >= 1!", L"Ошибка");
            txtRowsB->Focus();
            return;
        }
        if (!Int32::TryParse(txtColsB->Text, colsB) || colsB < 1)
        {
            MessageBox::Show(L"Столбцы B должны быть >= 1!", L"Ошибка");
            txtColsB->Focus();
            return;
        }

        if (rowsA != rowsB)
        {
            MessageBox::Show(L"Количество строк A и B должно совпадать!", L"Ошибка");
            txtRowsA->Focus();
            return;
        }

        if (!Double::TryParse(txtMin->Text, minVal))
        {
            MessageBox::Show(L"Введите корректное минимальное значение!", L"Ошибка");
            txtMin->Focus();
            return;
        }
        if (!Double::TryParse(txtMax->Text, maxVal))
        {
            MessageBox::Show(L"Введите корректное максимальное значение!", L"Ошибка");
            txtMax->Focus();
            return;
        }
        if (minVal >= maxVal)
        {
            MessageBox::Show(L"min должен быть < max!", L"Ошибка");
            txtMin->Focus();
            return;
        }

        std::vector<std::vector<double>> A, B, R;
        GenerateMatrix(rowsA, colsA, minVal, maxVal, A);
        GenerateMatrix(rowsB, colsB, minVal, maxVal, B);

        DisplayMatrix(A, lstA);
        DisplayMatrix(B, lstB);

        R.resize(rowsA, std::vector<double>(colsA));

        for (int i = 0; i < rowsA; ++i)
        {
            double maxB = MaxInRow(B[i]);
            for (int j = 0; j < colsA; ++j)
            {
                R[i][j] = A[i][j] * maxB;
            }
        }

        DisplayMatrix(R, lstR);
        UpdateStatus(String::Format(L"✅ Готово! Размер R: {0}×{1}", rowsA, colsA));
    }

    void OnClear(Object^ sender, EventArgs^ e)
    {
        txtRowsA->Text = L"";
        txtColsA->Text = L"";
        txtRowsB->Text = L"";
        txtColsB->Text = L"";
        txtMin->Text = L"";
        txtMax->Text = L"";
        lstA->Items->Clear();
        lstB->Items->Clear();
        lstR->Items->Clear();
        lblStatus->Text = L"Введите параметры и нажмите 'Решение'";
        lblStatus->BackColor = Color::FromArgb(240, 240, 240);
        lblStatus->ForeColor = Color::Black;
        txtRowsA->Focus();
    }

    void OnExit(Object^ sender, EventArgs^ e)
    {
        Application::Exit();
    }
};

[STAThreadAttribute]
int main()
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew Lab12Form());
    return 0;
}