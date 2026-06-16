 // Lab10_29.cpp
// Лабораторная работа №10 - Вариант 29
// Сформировать одномерную структуру размера n из случайных целых чисел.
// Если k и m меньше размера, и все элементы от k до m простые,
// то создать новый массив из простых чисел.

#include "pch.h"  // Для предкомпилированных заголовков
#include <Windows.h>
#include <vector>
#include <random>
#include <string>
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;

// ====================================================================
// ГЛАВНЫЙ КЛАСС ФОРМЫ
// ====================================================================
public ref class Lab10Form : public Form
{
private:
    // --- Элементы управления ---
    GroupBox^ gbInput;
    GroupBox^ gbOutput;
    
    Label^ lblSize;
    Label^ lblMin;
    Label^ lblMax;
    Label^ lblK;
    Label^ lblM;
    
    TextBox^ txtSize;
    TextBox^ txtMin;
    TextBox^ txtMax;
    TextBox^ txtK;
    TextBox^ txtM;
    
    ListBox^ lstOriginal;
    ListBox^ lstResult;
    
    Label^ lblStatus;
    
    Button^ btnSolve;
    Button^ btnClear;
    Button^ btnExit;

public:
    Lab10Form()
    {
        // Инициализация формы
        this->Text = L"ЛР №10 - Вариант 29";
        this->Size = Drawing::Size(920, 720);
        this->StartPosition = FormStartPosition::CenterScreen;
        this->BackColor = Color::FromArgb(240, 240, 240);
        this->Font = gcnew Drawing::Font("Segoe UI", 9);

        CreateControls();
    }

private:
    // ====================================================================
    // СОЗДАНИЕ ВСЕХ ЭЛЕМЕНТОВ УПРАВЛЕНИЯ
    // ====================================================================
    void CreateControls()
    {
        // ---- ГРУППА ВВОДА ----
        gbInput = gcnew GroupBox();
        gbInput->Text = L"Входные параметры";
        gbInput->Location = Point(10, 10);
        gbInput->Size = Drawing::Size(880, 200);
        gbInput->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        this->Controls->Add(gbInput);

        int y = 30;
        int x1 = 20, x2 = 140, x3 = 310, x4 = 400;

        // Размер
        lblSize = gcnew Label();
        lblSize->Text = L"Размер:";
        lblSize->Location = Point(x1, y);
        lblSize->Size = Drawing::Size(100, 25);
        gbInput->Controls->Add(lblSize);

        txtSize = gcnew TextBox();
        txtSize->Location = Point(x2, y);
        txtSize->Size = Drawing::Size(120, 25);
        txtSize->Font = gcnew Drawing::Font("Segoe UI", 10);
        gbInput->Controls->Add(txtSize);

        Label^ hintSize = gcnew Label();
        hintSize->Text = L"(1-1000)";
        hintSize->Location = Point(x3, y);
        hintSize->Size = Drawing::Size(100, 25);
        hintSize->ForeColor = Color::Gray;
        hintSize->Font = gcnew Drawing::Font("Segoe UI", 8, FontStyle::Italic);
        gbInput->Controls->Add(hintSize);

        // Минимум
        y += 35;
        lblMin = gcnew Label();
        lblMin->Text = L"Минимум:";
        lblMin->Location = Point(x1, y);
        lblMin->Size = Drawing::Size(100, 25);
        gbInput->Controls->Add(lblMin);

        txtMin = gcnew TextBox();
        txtMin->Location = Point(x2, y);
        txtMin->Size = Drawing::Size(120, 25);
        txtMin->Font = gcnew Drawing::Font("Segoe UI", 10);
        gbInput->Controls->Add(txtMin);

        Label^ hintMin = gcnew Label();
        hintMin->Text = L"(-1000...1000)";
        hintMin->Location = Point(x3, y);
        hintMin->Size = Drawing::Size(120, 25);
        hintMin->ForeColor = Color::Gray;
        hintMin->Font = gcnew Drawing::Font("Segoe UI", 8, FontStyle::Italic);
        gbInput->Controls->Add(hintMin);

        // Максимум
        y += 35;
        lblMax = gcnew Label();
        lblMax->Text = L"Максимум:";
        lblMax->Location = Point(x1, y);
        lblMax->Size = Drawing::Size(100, 25);
        gbInput->Controls->Add(lblMax);

        txtMax = gcnew TextBox();
        txtMax->Location = Point(x2, y);
        txtMax->Size = Drawing::Size(120, 25);
        txtMax->Font = gcnew Drawing::Font("Segoe UI", 10);
        gbInput->Controls->Add(txtMax);

        Label^ hintMax = gcnew Label();
        hintMax->Text = L"(-1000...1000)";
        hintMax->Location = Point(x3, y);
        hintMax->Size = Drawing::Size(120, 25);
        hintMax->ForeColor = Color::Gray;
        hintMax->Font = gcnew Drawing::Font("Segoe UI", 8, FontStyle::Italic);
        gbInput->Controls->Add(hintMax);

        // k
        y += 35;
        lblK = gcnew Label();
        lblK->Text = L"k (начало):";
        lblK->Location = Point(x1, y);
        lblK->Size = Drawing::Size(100, 25);
        gbInput->Controls->Add(lblK);

        txtK = gcnew TextBox();
        txtK->Location = Point(x2, y);
        txtK->Size = Drawing::Size(120, 25);
        txtK->Font = gcnew Drawing::Font("Segoe UI", 10);
        gbInput->Controls->Add(txtK);

        Label^ hintK = gcnew Label();
        hintK->Text = L"(индекс >= 0)";
        hintK->Location = Point(x3, y);
        hintK->Size = Drawing::Size(120, 25);
        hintK->ForeColor = Color::Gray;
        hintK->Font = gcnew Drawing::Font("Segoe UI", 8, FontStyle::Italic);
        gbInput->Controls->Add(hintK);

        // m
        y += 35;
        lblM = gcnew Label();
        lblM->Text = L"m (конец):";
        lblM->Location = Point(x1, y);
        lblM->Size = Drawing::Size(100, 25);
        gbInput->Controls->Add(lblM);

        txtM = gcnew TextBox();
        txtM->Location = Point(x2, y);
        txtM->Size = Drawing::Size(120, 25);
        txtM->Font = gcnew Drawing::Font("Segoe UI", 10);
        gbInput->Controls->Add(txtM);

        Label^ hintM = gcnew Label();
        hintM->Text = L"(индекс >= k)";
        hintM->Location = Point(x3, y);
        hintM->Size = Drawing::Size(120, 25);
        hintM->ForeColor = Color::Gray;
        hintM->Font = gcnew Drawing::Font("Segoe UI", 8, FontStyle::Italic);
        gbInput->Controls->Add(hintM);

        // ---- ГРУППА ВЫВОДА ----
        gbOutput = gcnew GroupBox();
        gbOutput->Text = L"Результаты";
        gbOutput->Location = Point(10, 220);
        gbOutput->Size = Drawing::Size(880, 370);
        gbOutput->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        this->Controls->Add(gbOutput);

        // Левый список - исходный массив
        Label^ lblOrig = gcnew Label();
        lblOrig->Text = L"Исходный массив:";
        lblOrig->Location = Point(20, 30);
        lblOrig->Size = Drawing::Size(150, 25);
        lblOrig->Font = gcnew Drawing::Font("Segoe UI", 9);
        gbOutput->Controls->Add(lblOrig);

        lstOriginal = gcnew ListBox();
        lstOriginal->Location = Point(20, 60);
        lstOriginal->Size = Drawing::Size(400, 280);
        lstOriginal->Font = gcnew Drawing::Font("Consolas", 10);
        lstOriginal->BackColor = Color::White;
        lstOriginal->SelectionMode = SelectionMode::None;
        gbOutput->Controls->Add(lstOriginal);

        // Правый список - простые числа
        Label^ lblResult = gcnew Label();
        lblResult->Text = L"Простые числа:";
        lblResult->Location = Point(460, 30);
        lblResult->Size = Drawing::Size(150, 25);
        lblResult->Font = gcnew Drawing::Font("Segoe UI", 9);
        gbOutput->Controls->Add(lblResult);

        lstResult = gcnew ListBox();
        lstResult->Location = Point(460, 60);
        lstResult->Size = Drawing::Size(400, 280);
        lstResult->Font = gcnew Drawing::Font("Consolas", 10);
        lstResult->BackColor = Color::White;
        lstResult->SelectionMode = SelectionMode::None;
        gbOutput->Controls->Add(lstResult);

        // ---- СТАТУС ----
        lblStatus = gcnew Label();
        lblStatus->Text = L"Введите параметры и нажмите 'Решение'";
        lblStatus->Location = Point(10, 600);
        lblStatus->Size = Drawing::Size(880, 35);
        lblStatus->BackColor = Color::FromArgb(240, 240, 240);
        lblStatus->TextAlign = ContentAlignment::MiddleCenter;
        lblStatus->Font = gcnew Drawing::Font("Segoe UI", 9);
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
        btnSolve->Click += gcnew EventHandler(this, &Lab10Form::OnSolve);
        this->Controls->Add(btnSolve);

        btnClear = gcnew Button();
        btnClear->Text = L"Очистить";
        btnClear->Location = Point(430, 645);
        btnClear->Size = Drawing::Size(130, 35);
        btnClear->BackColor = Color::FromArgb(243, 156, 18);
        btnClear->ForeColor = Color::White;
        btnClear->FlatStyle = FlatStyle::Flat;
        btnClear->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        btnClear->Click += gcnew EventHandler(this, &Lab10Form::OnClear);
        this->Controls->Add(btnClear);

        btnExit = gcnew Button();
        btnExit->Text = L"Выход";
        btnExit->Location = Point(580, 645);
        btnExit->Size = Drawing::Size(130, 35);
        btnExit->BackColor = Color::FromArgb(220, 53, 69);
        btnExit->ForeColor = Color::White;
        btnExit->FlatStyle = FlatStyle::Flat;
        btnExit->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        btnExit->Click += gcnew EventHandler(this, &Lab10Form::OnExit);
        this->Controls->Add(btnExit);
    }

    // ====================================================================
    // ЛОГИЧЕСКИЕ ФУНКЦИИ
    // ====================================================================
    
    // Проверка, является ли число простым
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

    // Проверка, все ли элементы в диапазоне [k, m] простые
    bool AllInRangeArePrime(const std::vector<int>& arr, int k, int m)
    {
        if (k < 0 || m >= (int)arr.size() || k > m) return false;
        for (int i = k; i <= m; ++i)
        {
            if (!IsPrime(arr[i])) return false;
        }
        return true;
    }

    // Генерация случайного массива
    void GenerateArray(int size, int minVal, int maxVal, std::vector<int>& arr)
    {
        arr.clear();
        arr.reserve(size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(minVal, maxVal);
        for (int i = 0; i < size; ++i)
        {
            arr.push_back(dist(gen));
        }
    }

    // Отображение массива в ListBox
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

    // Обновление статусной строки
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

    // ====================================================================
    // ОБРАБОТЧИКИ СОБЫТИЙ
    // ====================================================================

    // Кнопка "Решение"
    void OnSolve(Object^ sender, EventArgs^ e)
    {
        int size, minVal, maxVal, k, m;

        // Валидация размера
        if (!Int32::TryParse(txtSize->Text, size) || size < 1 || size > 1000)
        {
            MessageBox::Show(L"Размер должен быть от 1 до 1000!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            txtSize->Focus();
            return;
        }

        // Валидация минимума
        if (!Int32::TryParse(txtMin->Text, minVal))
        {
            MessageBox::Show(L"Введите корректное минимальное значение!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            txtMin->Focus();
            return;
        }

        // Валидация максимума
        if (!Int32::TryParse(txtMax->Text, maxVal))
        {
            MessageBox::Show(L"Введите корректное максимальное значение!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            txtMax->Focus();
            return;
        }

        // Проверка диапазона
        if (minVal >= maxVal)
        {
            MessageBox::Show(L"Минимальное значение должно быть меньше максимального!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            txtMin->Focus();
            return;
        }

        // Валидация k
        if (!Int32::TryParse(txtK->Text, k) || k < 0)
        {
            MessageBox::Show(L"k должно быть >= 0!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            txtK->Focus();
            return;
        }

        // Валидация m
        if (!Int32::TryParse(txtM->Text, m) || m < 0)
        {
            MessageBox::Show(L"m должно быть >= 0!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            txtM->Focus();
            return;
        }

        // Проверка k <= m
        if (k > m)
        {
            MessageBox::Show(L"k должно быть <= m!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            txtK->Focus();
            return;
        }

        // Генерация массива
        std::vector<int> original;
        GenerateArray(size, minVal, maxVal, original);
        DisplayArray(original, lstOriginal);

        // Проверка условия
        if (k < (int)original.size() && m < (int)original.size())
        {
            if (AllInRangeArePrime(original, k, m))
            {
                // Создание массива простых чисел
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
                lstResult->Items->Add(L"❌ Условие не выполнено:");
                lstResult->Items->Add(L"Не все элементы в диапазоне [k, m] простые");
                UpdateStatus(L"❌ Условие не выполнено", true);
            }
        }
        else
        {
            lstResult->Items->Clear();
            lstResult->Items->Add(L"❌ Ошибка:");
            lstResult->Items->Add(String::Format(L"Индексы k={0} или m={1} выходят за границы массива (размер={2})", k, m, original.size()));
            UpdateStatus(L"❌ Ошибка: индексы вне границ", true);
        }
    }

    // Кнопка "Очистить"
    void OnClear(Object^ sender, EventArgs^ e)
    {
        txtSize->Text = L"";
        txtMin->Text = L"";
        txtMax->Text = L"";
        txtK->Text = L"";
        txtM->Text = L"";
        lstOriginal->Items->Clear();
        lstResult->Items->Clear();
        lblStatus->Text = L"Введите параметры и нажмите 'Решение'";
        lblStatus->BackColor = Color::FromArgb(240, 240, 240);
        lblStatus->ForeColor = Color::Black;
        txtSize->Focus();
    }

    // Кнопка "Выход"
    void OnExit(Object^ sender, EventArgs^ e)
    {
        Application::Exit();
    }
};

// ====================================================================
// ТОЧКА ВХОДА
// ====================================================================
[STAThreadAttribute]
int main()
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew Lab10Form());
    return 0;
}