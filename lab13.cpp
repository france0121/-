// Lab13_29.cpp
// Лабораторная работа №13 - Вариант 29
// Проверить, начинается ли текст с заглавной буквы.

#include "pch.h"
#include <Windows.h>
#include <string>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

public ref class Lab13Form : public Form
{
private:
    GroupBox^ gbInput;
    GroupBox^ gbResult;
    
    TextBox^ txtText;
    Label^ lblResult;
    Label^ lblStatus;
    
    Button^ btnCheck;
    Button^ btnClear;
    Button^ btnExit;

public:
    Lab13Form()
    {
        this->Text = L"ЛР №13 - Вариант 29";
        this->Size = Drawing::Size(720, 520);
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
        gbInput->Text = L"Введите текст";
        gbInput->Location = Point(10, 10);
        gbInput->Size = Drawing::Size(680, 180);
        gbInput->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        this->Controls->Add(gbInput);

        txtText = gcnew TextBox();
        txtText->Location = Point(20, 30);
        txtText->Size = Drawing::Size(640, 130);
        txtText->Multiline = true;
        txtText->ScrollBars = ScrollBars::Vertical;
        txtText->Font = gcnew Drawing::Font("Segoe UI", 11);
        txtText->Text = L"Пример текста для проверки";
        gbInput->Controls->Add(txtText);

        // ---- ГРУППА РЕЗУЛЬТАТА ----
        gbResult = gcnew GroupBox();
        gbResult->Text = L"Результат проверки";
        gbResult->Location = Point(10, 200);
        gbResult->Size = Drawing::Size(680, 120);
        gbResult->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        this->Controls->Add(gbResult);

        lblResult = gcnew Label();
        lblResult->Text = L"Нажмите 'Проверить'";
        lblResult->Location = Point(20, 20);
        lblResult->Size = Drawing::Size(640, 80);
        lblResult->TextAlign = ContentAlignment::MiddleCenter;
        lblResult->Font = gcnew Drawing::Font("Segoe UI", 14, FontStyle::Bold);
        lblResult->BackColor = Color::White;
        lblResult->BorderStyle = BorderStyle::FixedSingle;
        gbResult->Controls->Add(lblResult);

        // ---- СТАТУС ----
        lblStatus = gcnew Label();
        lblStatus->Text = L"Введите текст и нажмите 'Проверить'";
        lblStatus->Location = Point(10, 330);
        lblStatus->Size = Drawing::Size(680, 35);
        lblStatus->BackColor = Color::FromArgb(240, 240, 240);
        lblStatus->TextAlign = ContentAlignment::MiddleCenter;
        this->Controls->Add(lblStatus);

        // ---- КНОПКИ ----
        btnCheck = gcnew Button();
        btnCheck->Text = L"Проверить";
        btnCheck->Location = Point(180, 380);
        btnCheck->Size = Drawing::Size(130, 35);
        btnCheck->BackColor = Color::FromArgb(0, 123, 255);
        btnCheck->ForeColor = Color::White;
        btnCheck->FlatStyle = FlatStyle::Flat;
        btnCheck->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        btnCheck->Click += gcnew EventHandler(this, &Lab13Form::OnCheck);
        this->Controls->Add(btnCheck);

        btnClear = gcnew Button();
        btnClear->Text = L"Очистить";
        btnClear->Location = Point(330, 380);
        btnClear->Size = Drawing::Size(130, 35);
        btnClear->BackColor = Color::FromArgb(243, 156, 18);
        btnClear->ForeColor = Color::White;
        btnClear->FlatStyle = FlatStyle::Flat;
        btnClear->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        btnClear->Click += gcnew EventHandler(this, &Lab13Form::OnClear);
        this->Controls->Add(btnClear);

        btnExit = gcnew Button();
        btnExit->Text = L"Выход";
        btnExit->Location = Point(480, 380);
        btnExit->Size = Drawing::Size(130, 35);
        btnExit->BackColor = Color::FromArgb(220, 53, 69);
        btnExit->ForeColor = Color::White;
        btnExit->FlatStyle = FlatStyle::Flat;
        btnExit->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        btnExit->Click += gcnew EventHandler(this, &Lab13Form::OnExit);
        this->Controls->Add(btnExit);
    }

    // ---- Логика ----
    bool StartsWithUppercase(String^ text)
    {
        if (String::IsNullOrWhiteSpace(text)) return false;
        return Char::IsUpper(text[0]);
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
    void OnCheck(Object^ sender, EventArgs^ e)
    {
        String^ text = txtText->Text;
        if (String::IsNullOrWhiteSpace(text))
        {
            MessageBox::Show(L"Введите текст!", L"Ошибка");
            lblResult->Text = L"❌ Текст не введен";
            lblResult->BackColor = Color::FromArgb(248, 215, 218);
            lblResult->ForeColor = Color::FromArgb(114, 28, 36);
            UpdateStatus(L"Ошибка: текст пуст", true);
            txtText->Focus();
            return;
        }

        bool result = StartsWithUppercase(text);
        if (result)
        {
            lblResult->Text = L"✅ Текст начинается с заглавной буквы!";
            lblResult->BackColor = Color::FromArgb(212, 237, 218);
            lblResult->ForeColor = Color::FromArgb(21, 87, 36);
            UpdateStatus(L"✅ Текст начинается с заглавной буквы");
        }
        else
        {
            wchar_t first = text[0];
            lblResult->Text = String::Format(L"❌ Текст начинается со строчной буквы ('{0}')", first);
            lblResult->BackColor = Color::FromArgb(248, 215, 218);
            lblResult->ForeColor = Color::FromArgb(114, 28, 36);
            UpdateStatus(L"❌ Текст начинается со строчной буквы", true);
        }
    }

    void OnClear(Object^ sender, EventArgs^ e)
    {
        txtText->Text = L"";
        lblResult->Text = L"Нажмите 'Проверить'";
        lblResult->BackColor = Color::White;
        lblResult->ForeColor = Color::Black;
        lblStatus->Text = L"Введите текст и нажмите 'Проверить'";
        lblStatus->BackColor = Color::FromArgb(240, 240, 240);
        lblStatus->ForeColor = Color::Black;
        txtText->Focus();
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
    Application::Run(gcnew Lab13Form());
    return 0;
}