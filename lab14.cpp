 // Lab14_29.cpp
// Лабораторная работа №14 - Вариант 29
// Дан текстовый файл. Создать новый файл и записать в него только строки,
// содержащие символ @, заменив @ на [at].

#include "pch.h"
#include <Windows.h>
#include <string>
#include <msclr\marshal_cppstd.h>
#include <fstream>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::IO;

public ref class Lab14Form : public Form
{
private:
    GroupBox^ gbFiles;
    GroupBox^ gbView;
    
    TextBox^ txtInput;
    TextBox^ txtOutput;
    
    ListBox^ lstInput;
    ListBox^ lstOutput;
    
    Label^ lblStatus;
    
    Button^ btnSelectInput;
    Button^ btnSelectOutput;
    Button^ btnProcess;
    Button^ btnClear;
    Button^ btnExit;
    
    String^ inputPath;
    String^ outputPath;

public:
    Lab14Form()
    {
        this->Text = L"ЛР №14 - Вариант 29";
        this->Size = Drawing::Size(950, 720);
        this->StartPosition = FormStartPosition::CenterScreen;
        this->BackColor = Color::FromArgb(240, 240, 240);
        this->Font = gcnew Drawing::Font("Segoe UI", 9);

        inputPath = L"";
        outputPath = L"";
        CreateControls();
    }

private:
    void CreateControls()
    {
        // ---- ГРУППА ВЫБОРА ФАЙЛОВ ----
        gbFiles = gcnew GroupBox();
        gbFiles->Text = L"Выбор файлов";
        gbFiles->Location = Point(10, 10);
        gbFiles->Size = Drawing::Size(910, 110);
        gbFiles->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        this->Controls->Add(gbFiles);

        int y = 30;
        int x1 = 20, x2 = 100;

        // Входной файл
        Label^ lblInput = gcnew Label();
        lblInput->Text = L"Входной:";
        lblInput->Location = Point(x1, y);
        lblInput->Size = Drawing::Size(60, 25);
        lblInput->Font = gcnew Drawing::Font("Segoe UI", 9);
        gbFiles->Controls->Add(lblInput);

        txtInput = gcnew TextBox();
        txtInput->Location = Point(x2, y);
        txtInput->Size = Drawing::Size(500, 25);
        txtInput->ReadOnly = true;
        txtInput->Font = gcnew Drawing::Font("Segoe UI", 9);
        gbFiles->Controls->Add(txtInput);

        btnSelectInput = gcnew Button();
        btnSelectInput->Text = L"Выбрать...";
        btnSelectInput->Location = Point(x2 + 510, y);
        btnSelectInput->Size = Drawing::Size(100, 25);
        btnSelectInput->BackColor = Color::FromArgb(108, 117, 125);
        btnSelectInput->ForeColor = Color::White;
        btnSelectInput->FlatStyle = FlatStyle::Flat;
        btnSelectInput->Font = gcnew Drawing::Font("Segoe UI", 9);
        btnSelectInput->Click += gcnew EventHandler(this, &Lab14Form::OnSelectInput);
        gbFiles->Controls->Add(btnSelectInput);

        // Выходной файл
        y += 40;
        Label^ lblOutput = gcnew Label();
        lblOutput->Text = L"Выходной:";
        lblOutput->Location = Point(x1, y);
        lblOutput->Size = Drawing::Size(60, 25);
        lblOutput->Font = gcnew Drawing::Font("Segoe UI", 9);
        gbFiles->Controls->Add(lblOutput);

        txtOutput = gcnew TextBox();
        txtOutput->Location = Point(x2, y);
        txtOutput->Size = Drawing::Size(500, 25);
        txtOutput->ReadOnly = true;
        txtOutput->Font = gcnew Drawing::Font("Segoe UI", 9);
        gbFiles->Controls->Add(txtOutput);

        btnSelectOutput = gcnew Button();
        btnSelectOutput->Text = L"Выбрать...";
        btnSelectOutput->Location = Point(x2 + 510, y);
        btnSelectOutput->Size = Drawing::Size(100, 25);
        btnSelectOutput->BackColor = Color::FromArgb(108, 117, 125);
        btnSelectOutput->ForeColor = Color::White;
        btnSelectOutput->FlatStyle = FlatStyle::Flat;
        btnSelectOutput->Font = gcnew Drawing::Font("Segoe UI", 9);
        btnSelectOutput->Click += gcnew EventHandler(this, &Lab14Form::OnSelectOutput);
        gbFiles->Controls->Add(btnSelectOutput);

        btnProcess = gcnew Button();
        btnProcess->Text = L"Обработка";
        btnProcess->Location = Point(x2 + 630, y - 20);
        btnProcess->Size = Drawing::Size(130, 60);
        btnProcess->BackColor = Color::FromArgb(0, 123, 255);
        btnProcess->ForeColor = Color::White;
        btnProcess->FlatStyle = FlatStyle::Flat;
        btnProcess->Font = gcnew Drawing::Font("Segoe UI", 12, FontStyle::Bold);
        btnProcess->Click += gcnew EventHandler(this, &Lab14Form::OnProcess);
        gbFiles->Controls->Add(btnProcess);

        // ---- ГРУППА ПРОСМОТРА ----
        gbView = gcnew GroupBox();
        gbView->Text = L"Содержимое файлов";
        gbView->Location = Point(10, 130);
        gbView->Size = Drawing::Size(910, 410);
        gbView->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        this->Controls->Add(gbView);

        // Левый список - входной файл
        Label^ lblInputContent = gcnew Label();
        lblInputContent->Text = L"Входной файл:";
        lblInputContent->Location = Point(20, 30);
        lblInputContent->Size = Drawing::Size(150, 25);
        lblInputContent->Font = gcnew Drawing::Font("Segoe UI", 9);
        gbView->Controls->Add(lblInputContent);

        lstInput = gcnew ListBox();
        lstInput->Location = Point(20, 60);
        lstInput->Size = Drawing::Size(410, 320);
        lstInput->Font = gcnew Drawing::Font("Consolas", 9);
        lstInput->BackColor = Color::White;
        lstInput->SelectionMode = SelectionMode::None;
        gbView->Controls->Add(lstInput);

        // Правый список - выходной файл
        Label^ lblOutputContent = gcnew Label();
        lblOutputContent->Text = L"Выходной файл (строки с @ → [at]):";
        lblOutputContent->Location = Point(470, 30);
        lblOutputContent->Size = Drawing::Size(250, 25);
        lblOutputContent->Font = gcnew Drawing::Font("Segoe UI", 9);
        gbView->Controls->Add(lblOutputContent);

        lstOutput = gcnew ListBox();
        lstOutput->Location = Point(470, 60);
        lstOutput->Size = Drawing::Size(420, 320);
        lstOutput->Font = gcnew Drawing::Font("Consolas", 9);
        lstOutput->BackColor = Color::White;
        lstOutput->SelectionMode = SelectionMode::None;
        gbView->Controls->Add(lstOutput);

        // ---- СТАТУС ----
        lblStatus = gcnew Label();
        lblStatus->Text = L"Выберите файлы и нажмите 'Обработка'";
        lblStatus->Location = Point(10, 550);
        lblStatus->Size = Drawing::Size(910, 35);
        lblStatus->BackColor = Color::FromArgb(240, 240, 240);
        lblStatus->TextAlign = ContentAlignment::MiddleCenter;
        this->Controls->Add(lblStatus);

        // ---- КНОПКИ ----
        btnClear = gcnew Button();
        btnClear->Text = L"Очистить";
        btnClear->Location = Point(340, 600);
        btnClear->Size = Drawing::Size(130, 35);
        btnClear->BackColor = Color::FromArgb(243, 156, 18);
        btnClear->ForeColor = Color::White;
        btnClear->FlatStyle = FlatStyle::Flat;
        btnClear->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        btnClear->Click += gcnew EventHandler(this, &Lab14Form::OnClear);
        this->Controls->Add(btnClear);

        btnExit = gcnew Button();
        btnExit->Text = L"Выход";
        btnExit->Location = Point(490, 600);
        btnExit->Size = Drawing::Size(130, 35);
        btnExit->BackColor = Color::FromArgb(220, 53, 69);
        btnExit->ForeColor = Color::White;
        btnExit->FlatStyle = FlatStyle::Flat;
        btnExit->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        btnExit->Click += gcnew EventHandler(this, &Lab14Form::OnExit);
        this->Controls->Add(btnExit);
    }

    // ---- Вспомогательные функции ----
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

    void LoadFileToList(String^ path, ListBox^ list)
    {
        list->Items->Clear();
        if (String::IsNullOrWhiteSpace(path) || !File::Exists(path))
        {
            list->Items->Add(L"Файл не найден");
            return;
        }
        try
        {
            array<String^>^ lines = File::ReadAllLines(path);
            for each (String^ line in lines)
            {
                list->Items->Add(line);
            }
        }
        catch (Exception^ ex)
        {
            list->Items->Add(L"Ошибка чтения: " + ex->Message);
        }
    }

    // ---- Обработчики ----
    void OnSelectInput(Object^ sender, EventArgs^ e)
    {
        OpenFileDialog^ dlg = gcnew OpenFileDialog();
        dlg->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
        dlg->Title = L"Выберите входной файл";
        if (dlg->ShowDialog() == DialogResult::OK)
        {
            inputPath = dlg->FileName;
            txtInput->Text = inputPath;
            LoadFileToList(inputPath, lstInput);
            UpdateStatus(L"Входной файл выбран: " + Path::GetFileName(inputPath));
        }
    }

    void OnSelectOutput(Object^ sender, EventArgs^ e)
    {
        SaveFileDialog^ dlg = gcnew SaveFileDialog();
        dlg->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
        dlg->Title = L"Выберите выходной файл";
        dlg->FileName = L"output.txt";
        if (dlg->ShowDialog() == DialogResult::OK)
        {
            outputPath = dlg->FileName;
            txtOutput->Text = outputPath;
            UpdateStatus(L"Выходной файл выбран: " + Path::GetFileName(outputPath));
        }
    }

    void OnProcess(Object^ sender, EventArgs^ e)
    {
        if (String::IsNullOrWhiteSpace(inputPath))
        {
            MessageBox::Show(L"Выберите входной файл!", L"Ошибка");
            return;
        }
        if (String::IsNullOrWhiteSpace(outputPath))
        {
            MessageBox::Show(L"Выберите выходной файл!", L"Ошибка");
            return;
        }
        if (!File::Exists(inputPath))
        {
            MessageBox::Show(L"Входной файл не существует!", L"Ошибка");
            return;
        }

        lstOutput->Items->Clear();

        try
        {
            array<String^>^ lines = File::ReadAllLines(inputPath);
            int count = 0;
            List<String^>^ resultLines = gcnew List<String^>();

            for each (String^ line in lines)
            {
                if (line->Contains(L"@"))
                {
                    String^ modified = line->Replace(L"@", L"[at]");
                    resultLines->Add(modified);
                    lstOutput->Items->Add(modified);
                    count++;
                }
            }

            File::WriteAllLines(outputPath, resultLines);
            UpdateStatus(String::Format(L"✅ Обработано {0} строк. Найдено {1} строк с @ → [at]",
                         lines->Length, count));
            
            if (count == 0)
            {
                MessageBox::Show(L"Строк с символом @ не найдено.", L"Информация");
            }
        }
        catch (Exception^ ex)
        {
            MessageBox::Show(L"Ошибка: " + ex->Message, L"Ошибка");
            UpdateStatus(L"❌ Ошибка при обработке", true);
        }
    }

    void OnClear(Object^ sender, EventArgs^ e)
    {
        inputPath = L"";
        outputPath = L"";
        txtInput->Text = L"";
        txtOutput->Text = L"";
        lstInput->Items->Clear();
        lstOutput->Items->Clear();
        UpdateStatus(L"Поля очищены. Выберите файлы.");
        lblStatus->BackColor = Color::FromArgb(240, 240, 240);
        lblStatus->ForeColor = Color::Black;
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
    Application::Run(gcnew Lab14Form());
    return 0;
}