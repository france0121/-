 // Lab11_29.cpp
// Лабораторная работа №11 - Вариант 29
// Ввести одномерную структуру целых чисел и два целых числа k и m.
// Если все элементы от k до m простые, то создать новый массив из простых чисел.

#include "pch.h"
#include <Windows.h>
#include <vector>
#include <string>
#include <sstream>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;

public ref class Lab11Form : public Form
{
private:
    GroupBox^ gbInput;
    GroupBox^ gbOutput;
    
    Label^ lblArray;
    Label^ lblK;
    Label^ lblM;
    
    TextBox^ txtArray;
    TextBox^ txtK;
    TextBox^ txtM;
    
    ListBox^ lstOriginal;
    ListBox^ lstResult;
    
    Label^ lblStatus;
    
    Button^ btnSolve;
    Button^ btnClear;
    Button^ btnExit;

public:
    Lab11Form()
    {
        this->Text = L"ЛР №11 - Вариант 29";
        this->Size = Drawing::Size(920, 720);
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
        gbInput->Text = L"Входные данные";
        gbInput->Location = Point(10, 10);
        gbInput->Size = Drawing::Size(880, 150);
        gbInput->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        this->Controls->Add(gbInput);

        int y = 30;
        int x1 = 20, x2 = 160;

        // Массив
        lblArray = gcnew Label();
        lblArray->Text = L"Массив (числа через пробел):";
        lblArray->Location = Point(x1, y);
        lblArray->Size = Drawing::Size(200, 25);
        gbInput->Controls->Add(lblArray);

        txtArray = gcnew TextBox();
        txtArray->Location = Point(x2, y);
        txtArray->Size = Drawing::Size(680, 25);
        txtArray->Font = gcnew Drawing::Font("Segoe UI", 10);
        txtArray->Text = L"2 3 5 7 11 13 17 19 23";
        gbInput->Controls->Add(txtArray);

        // k
        y += 45;
        lblK = gcnew Label();
        lblK->Text = L"k (индекс):";
        lblK->Location = Point(x1, y);
        lblK->Size = Drawing::Size(100, 25);
        gbInput->Controls->Add(lblK);

        txtK = gcnew TextBox();
        txtK->Location = Point(x2, y);
        txtK->Size = Drawing::Size(100, 25);
        txtK->Font = gcnew Drawing::Font("Segoe UI", 10);
        txtK->Text = L"0";
        gbInput->Controls->Add(txtK);

        // m
        lblM = gcnew Label();
        lblM->Text = L"m (индекс):";
        lblM->Location = Point(x2 + 140, y);
        lblM->Size = Drawing::Size(100, 25);
        gbInput->Controls->Add(lblM);

        txtM = gcnew TextBox();
        txtM->Location = Point(x2 + 240, y);
        txtM->Size = Drawing::Size(100, 25);
        txtM->Font = gcnew Drawing::Font("Segoe UI", 10);
        txtM->Text = L"3";
        gbInput->Controls->Add(txtM);

        Label^ hint = gcnew Label();
        hint->Text = L"(индексы должны быть >= 0 и k <= m)";
        hint->Location = Point(x2 + 360, y);
        hint->Size = Drawing::Size(300, 25);
        hint->ForeColor = Color::Gray;
        hint->Font = gcnew Drawing::Font("Segoe UI", 8, FontStyle::Italic);
        gbInput->Controls->Add(hint);

        // ---- ГРУППА ВЫВОДА ----
        gbOutput = gcnew GroupBox();
        gbOutput->Text = L"Результаты";
        gbOutput->Location = Point(10, 170);
        gbOutput->Size = Drawing::Size(880, 420);
        gbOutput->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        this->Controls->Add(gbOutput);

        // Левый список
        Label^ lblOrig = gcnew Label();
        lblOrig->Text = L"Исходный массив:";
        lblOrig->Location = Point(20, 30);
        lblOrig->Size = Drawing::Size(150, 25);
        lblOrig->Font = gcnew Drawing::Font("Segoe UI", 9);
        gbOutput->Controls->Add(lblOrig);

        lstOriginal = gcnew ListBox();
        lstOriginal->Location = Point(20, 60);
        lstOriginal->Size = Drawing::Size(400, 330);
        lstOriginal->Font = gcnew Drawing::Font("Consolas", 10);
        lstOriginal->BackColor = Color::White;
        lstOriginal->SelectionMode = SelectionMode::None;
        gbOutput->Controls->Add(lstOriginal);

        // Правый список
        Label^ lblResult = gcnew Label();
        lblResult->Text = L"Простые числа:";
        lblResult->Location = Point(460, 30);
        lblResult->Size = Drawing::Size(150, 25);
        lblResult->Font = gcnew Drawing::Font("Segoe UI", 9);
        gbOutput->Controls->Add(lblResult);

        lstResult = gcnew ListBox();
        lstResult->Location = Point(460, 60);
        lstResult->Size = Drawing::Size(400, 330);
        lstResult->Font = gcnew Drawing::Font("Consolas", 10);
        lstResult->BackColor = Color::White;
        lstResult->SelectionMode = SelectionMode::None;
        gbOutput->Controls->Add(lstResult);

        // ---- СТАТУС ----
        lblStatus = gcnew Label();
        lblStatus->Text = L"Введите данные и нажмите 'Решение'";
        lblStatus->Location = Point(10, 600);
        lblStatus->Size = Drawing::Size(880, 35);
        lblStatus->BackColor = Color::FromArgb(240, 240, 240);
        lblStatus->TextAlign = ContentAlignment::MiddleCenter;
        this->Controls->Add(lblStatus);

        // ---- КНОПКИ ----
        btnSolve = gcnew Button();
        btnSolve->Text = L"Решение";
        btnSolve->Location = Point(280, 645);
        btnSolve->Size = Drawing::Size(130, 35);
        btnSolve->BackColor = Color::FromArgb(0, 123, 255);
        btnSolve->ForeColor = Color::White;
        btnSolve->FlatStyle = FlatStyle::Flat;
        btnSolve->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        btnSolve->Click += gcnew EventHandler(this, &Lab11Form::OnSolve);
        this->Controls->Add(btnSolve);

        btnClear = gcnew Button();
        btnClear->Text = L"Очистить";
        btnClear->Location = Point(430, 645);
        btnClear->Size = Drawing::Size(130, 35);
        btnClear->BackColor = Color::FromArgb(243, 156, 18);
        btnClear->ForeColor = Color::White;
        btnClear->FlatStyle = FlatStyle::Flat;
        btnClear->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        btnClear->Click += gcnew EventHandler(this, &Lab11Form::OnClear);
        this->Controls->Add(btnClear);

        btnExit = gcnew Button();
        btnExit->Text = L"Выход";
        btnExit->Location = Point(580, 645);
        btnExit->Size = Drawing::Size(130, 35);
        btnExit->BackColor = Color::FromArgb(220, 53, 69);
        btnExit->ForeColor = Color::White;
        btnExit->FlatStyle = FlatStyle::Flat;
        btnExit->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        btnExit->Click += gcnew EventHandler(this, &Lab11Form::OnExit);
        this->Controls->Add(btnExit);
    }

    // ---- Логические функции ----
    bool IsPrime(int n)
    {
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6)
        {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    bool AllInRangeArePrime(const std::vector<int>& arr, int k, int m)
    {
        if (k < 0 || m >= (int)arr.size() || k > m) return false;
        for (int i = k; i <= m; ++i)
        {
            if (!IsPrime(arr[i])) return false;
        }
        return true;
    }

    void ParseInput(String^ text, std::vector<int>& arr)
    {
        arr.clear();
        array<String^>^ parts = text->Split(gcnew array<wchar_t>{L' ', L',', L';'}, StringSplitOptions::RemoveEmptyEntries);
        for each (String^ part in parts)
        {
            int val;
            if (Int32::TryParse(part, val))
            {
                arr.push_back(val);
            }
        }
    }

    void DisplayArray(const std::vector<int>& arr, ListBox^ list)
    {
        list->Items->Clear();
        if (arr.empty())
        {
            list->Items->Add(L"Пусто");
            return;
        }
        for (size_t i = 0; i < arr.size(); ++i)
        {
            list->Items->Add(String::Format(L"[{0,3}] = {1,6}", i, arr[i]));
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
        std::vector<int> original;
        ParseInput(txtArray->Text, original);

        int k, m;
        if (!Int32::TryParse(txtK->Text, k) || k < 0)
        {
            MessageBox::Show(L"k должно быть >= 0!", L"Ошибка");
            txtK->Focus();
            return;
        }
        if (!Int32::TryParse(txtM->Text, m) || m < 0)
        {
            MessageBox::Show(L"m должно быть >= 0!", L"Ошибка");
            txtM->Focus();
            return;
        }
        if (k > m)
        {
            MessageBox::Show(L"k должно быть <= m!", L"Ошибка");
            txtK->Focus();
            return;
        }

        DisplayArray(original, lstOriginal);

        if (original.empty())
        {
            lstResult->Items->Clear();
            lstResult->Items->Add(L"❌ Массив пуст");
            UpdateStatus(L"Ошибка: массив пуст", true);
            return;
        }

        if (k < (int)original.size() && m < (int)original.size())
        {
            if (AllInRangeArePrime(original, k, m))
            {
                std::vector<int> primes;
                for (int x : original)
                {
                    if (IsPrime(x)) primes.push_back(x);
                }
                DisplayArray(primes, lstResult);
                UpdateStatus(String::Format(L"✅ Условие выполнено! Найдено {0} простых чисел.", primes.size()));
            }
            else
            {
                lstResult->Items->Clear();
                lstResult->Items->Add(L"❌ Условие не выполнено");
                lstResult->Items->Add(L"Не все элементы в диапазоне [k, m] простые");
                UpdateStatus(L"❌ Условие не выполнено", true);
            }
        }
        else
        {
            lstResult->Items->Clear();
            lstResult->Items->Add(L"❌ Ошибка:");
            lstResult->Items->Add(String::Format(L"Индексы k={0} или m={1} выходят за границы (размер={2})", k, m, original.size()));
            UpdateStatus(L"❌ Ошибка: индексы вне границ", true);
        }
    }

    void OnClear(Object^ sender, EventArgs^ e)
    {
        txtArray->Text = L"";
        txtK->Text = L"";
        txtM->Text = L"";
        lstOriginal->Items->Clear();
        lstResult->Items->Clear();
        lblStatus->Text = L"Введите данные и нажмите 'Решение'";
        lblStatus->BackColor = Color::FromArgb(240, 240, 240);
        lblStatus->ForeColor = Color::Black;
        txtArray->Focus();
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
    Application::Run(gcnew Lab11Form());
    return 0;
}