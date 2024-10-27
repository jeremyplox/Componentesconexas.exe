#pragma once
#include "Pasos.h"
#include "FullScreenForm.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <Windows.h>
#include <string>
#include <array>
#include <map>
#include <numeric>
using namespace std;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Drawing::Drawing2D;

vector<vector<int>> matriz;
vector<vector<int>> matrizDiagonal;
vector<vector<int>> matrizCaminos;
vector<vector<int>> matrizReordenada;
vector<int> conteoUnos;
vector<char> letrasFilas;
vector<char> letrasFilasOriginales;  // Letras originales para las filas
vector<char> letrasFilasReordenadas;
bool entradaManual = false; // Flag para saber si la entrada es manual
int currentRow = 0;  // Fila actual
int currentCol = 0;  // Columna actual
// Funciones para las matrices
vector<vector<int>> generarMatriz(int n) {
    vector<vector<int>> matriz(n, vector<int>(n));
    letrasFilasOriginales.resize(n);  // Redimensionar el vector de letras originales

    srand(time(0));

    for (int i = 0; i < n; ++i) {
        letrasFilasOriginales[i] = 'A' + i;  // Asignar letras A, B, C, etc. a las filas
        for (int j = 0; j < n; ++j) {
            matriz[i][j] = rand() % 2;
        }
    }

    letrasFilasReordenadas = letrasFilasOriginales; // Iniciar letras reordenadas igual que las originales
    return matriz;
}

vector<vector<int>> ingresarMatrizManual(int n) {
    vector<vector<int>> matriz(n, vector<int>(n));
    cout << "Ingrese los valores de la matriz " << n << "x" << n << " (solo 0 o 1):\n";

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int valor;
            do {
                cout << "Elemento [" << i << "][" << j << "]: ";
                cin >> valor;
                if (valor != 0 && valor != 1) {
                    cout << "Error: solo se permiten 0 o 1. Intente de nuevo.\n";
                }
            } while (valor != 0 && valor != 1);
            matriz[i][j] = valor;
        }
    }

    return matriz;
}

void asegurarDiagonal(vector<vector<int>>& matriz) {
    int n = matriz.size();
    for (int i = 0; i < n; ++i) {
        matriz[i][i] = 1;
    }
}

void calcularMatrizDeCaminos(vector<vector<int>>& matriz) {
    asegurarDiagonal(matrizDiagonal);
    int n = matriz.size();
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                matriz[i][j] = matriz[i][j] || (matriz[i][k] && matriz[k][j]);
            }
        }
    }
}
void calcularCierreTransitivo(vector<vector<int>>& matriz) {
    int n = matriz.size();
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                matriz[i][j] = matriz[i][j] || (matriz[i][k] && matriz[k][j]);
            }
        }
    }
}
vector<int> contarUnosPorFila(const vector<vector<int>>& matriz) {
    int n = matriz.size();
    vector<int> conteo(n);
    for (int i = 0; i < n; ++i) {
        conteo[i] = count(matriz[i].begin(), matriz[i].end(), 1);
    }
    return conteo;
}

vector<vector<int>> reordenarMatriz(const vector<vector<int>>& matriz, const vector<int>& conteo) {
    int n = matriz.size();
    vector<int> orden(n);
    for (int i = 0; i < n; ++i) {
        orden[i] = i;
    }

    // Ordenar las filas en función del número de '1's, y también ordenar las letras de las filas (solo aquí)
    sort(orden.begin(), orden.end(), [&](int a, int b) {
        return conteo[a] > conteo[b];
        });

    vector<vector<int>> nuevaMatriz(n, vector<int>(n));
    vector<char> nuevasLetras(n);  // Vector temporal para las nuevas letras reordenadas

    for (int i = 0; i < n; ++i) {
        nuevasLetras[i] = letrasFilasOriginales[orden[i]];  // Reordenar las letras solo en esta fase final
        for (int j = 0; j < n; ++j) {
            nuevaMatriz[i][j] = matriz[orden[i]][orden[j]];
        }
    }

    letrasFilasReordenadas = nuevasLetras;  // Actualizar las letras solo en la matriz reordenada
    return nuevaMatriz;
}

namespace CompuTrabajo {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::MyForm_KeyPress);
            
        }

    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }
        
    private: System::Windows::Forms::Panel^ panelOriginal;
    private: System::Windows::Forms::Panel^ panelDiagonal;
    private: System::Windows::Forms::Panel^ panelCaminos;
    private: System::Windows::Forms::Panel^ panelReordenado;
    private: System::Windows::Forms::Panel^ panelConteoUnos;
    private: System::Windows::Forms::Panel^ panelRecorridoFinal;
    private: System::Windows::Forms::Button^ buttonGenerar;
    private: System::Windows::Forms::Button^ buttonProcesar;
    private: System::Windows::Forms::Button^ buttonLimpiar;
    private: System::Windows::Forms::NumericUpDown^ numericUpDownSize;
    private: System::Windows::Forms::CheckBox^ checkBoxManual;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::Label^ label8;
    private: System::Windows::Forms::Label^ label9;
    private: System::Windows::Forms::Label^ label3;
    private: System::Windows::Forms::Panel^ panelConvexas;
    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::Button^ button0;

    private: System::Windows::Forms::Label^ label5;
    private: System::Windows::Forms::Button^ button2;
    private: System::Windows::Forms::Label^ label6;
    private: System::Windows::Forms::Label^ label7;
    private: System::Windows::Forms::Panel^ PanelOrdenFilas;
    private: System::Windows::Forms::Label^ label4;
    private: System::Windows::Forms::Label^ label10;
    private: System::Windows::Forms::Label^ label11;
    private: System::Windows::Forms::Label^ label12;
    private: System::Windows::Forms::Button^ Salir;

    private: System::Windows::Forms::Button^ btnInfoOriginal;
    private: System::Windows::Forms::Button^ btnInfoDiagonal;
    private: System::Windows::Forms::Button^ btnInfoCaminos;
    private: System::Windows::Forms::Button^ btnInfoReordenado;
    private: System::Windows::Forms::Button^ btnInfoConteoUnos;
    private: System::Windows::Forms::Button^ btnInfoConvexas;
    private: System::Windows::Forms::Button^ btnInfoAgrupacion;
    private: System::Windows::Forms::Button^ button3;







    private:
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->btnInfoOriginal = (gcnew System::Windows::Forms::Button());
            this->btnInfoDiagonal = (gcnew System::Windows::Forms::Button());
            this->btnInfoCaminos = (gcnew System::Windows::Forms::Button());
            this->btnInfoReordenado = (gcnew System::Windows::Forms::Button());
            this->btnInfoConteoUnos = (gcnew System::Windows::Forms::Button());
            this->btnInfoConvexas = (gcnew System::Windows::Forms::Button());
            this->panelOriginal = (gcnew System::Windows::Forms::Panel());
            this->panelDiagonal = (gcnew System::Windows::Forms::Panel());
            this->panelCaminos = (gcnew System::Windows::Forms::Panel());
            this->panelReordenado = (gcnew System::Windows::Forms::Panel());
            this->panelConteoUnos = (gcnew System::Windows::Forms::Panel());
            this->panelRecorridoFinal = (gcnew System::Windows::Forms::Panel());
            this->buttonGenerar = (gcnew System::Windows::Forms::Button());
            this->buttonProcesar = (gcnew System::Windows::Forms::Button());
            this->buttonLimpiar = (gcnew System::Windows::Forms::Button());
            this->numericUpDownSize = (gcnew System::Windows::Forms::NumericUpDown());
            this->checkBoxManual = (gcnew System::Windows::Forms::CheckBox());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label8 = (gcnew System::Windows::Forms::Label());
            this->label9 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->panelConvexas = (gcnew System::Windows::Forms::Panel());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->button0 = (gcnew System::Windows::Forms::Button());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->PanelOrdenFilas = (gcnew System::Windows::Forms::Panel());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->label10 = (gcnew System::Windows::Forms::Label());
            this->label11 = (gcnew System::Windows::Forms::Label());
            this->label12 = (gcnew System::Windows::Forms::Label());
            this->Salir = (gcnew System::Windows::Forms::Button());
            this->btnInfoAgrupacion = (gcnew System::Windows::Forms::Button());
            this->button3 = (gcnew System::Windows::Forms::Button());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownSize))->BeginInit();
            this->SuspendLayout();
            // 
            // btnInfoOriginal
            // 
            this->btnInfoOriginal->Location = System::Drawing::Point(918, -2);
            this->btnInfoOriginal->Name = L"btnInfoOriginal";
            this->btnInfoOriginal->Size = System::Drawing::Size(30, 30);
            this->btnInfoOriginal->TabIndex = 0;
            this->btnInfoOriginal->Text = L"\?";
            this->btnInfoOriginal->Click += gcnew System::EventHandler(this, &MyForm::btnInfoOriginal_Click);
            // 
            // btnInfoDiagonal
            // 
            this->btnInfoDiagonal->Location = System::Drawing::Point(1367, -1);
            this->btnInfoDiagonal->Name = L"btnInfoDiagonal";
            this->btnInfoDiagonal->Size = System::Drawing::Size(30, 30);
            this->btnInfoDiagonal->TabIndex = 1;
            this->btnInfoDiagonal->Text = L"\?";
            this->btnInfoDiagonal->Click += gcnew System::EventHandler(this, &MyForm::btnInfoDiagonal_Click);
            // 
            // btnInfoCaminos
            // 
            this->btnInfoCaminos->Location = System::Drawing::Point(1809, 0);
            this->btnInfoCaminos->Name = L"btnInfoCaminos";
            this->btnInfoCaminos->Size = System::Drawing::Size(30, 30);
            this->btnInfoCaminos->TabIndex = 2;
            this->btnInfoCaminos->Text = L"\?";
            this->btnInfoCaminos->Click += gcnew System::EventHandler(this, &MyForm::btnInfoCaminos_Click);
            // 
            // btnInfoReordenado
            // 
            this->btnInfoReordenado->Location = System::Drawing::Point(446, 527);
            this->btnInfoReordenado->Name = L"btnInfoReordenado";
            this->btnInfoReordenado->Size = System::Drawing::Size(30, 30);
            this->btnInfoReordenado->TabIndex = 3;
            this->btnInfoReordenado->Text = L"\?";
            this->btnInfoReordenado->Click += gcnew System::EventHandler(this, &MyForm::btnInfoReordenado_Click);
            // 
            // btnInfoConteoUnos
            // 
            this->btnInfoConteoUnos->Location = System::Drawing::Point(1893, 0);
            this->btnInfoConteoUnos->Name = L"btnInfoConteoUnos";
            this->btnInfoConteoUnos->Size = System::Drawing::Size(30, 30);
            this->btnInfoConteoUnos->TabIndex = 4;
            this->btnInfoConteoUnos->Text = L"\?";
            this->btnInfoConteoUnos->Click += gcnew System::EventHandler(this, &MyForm::btnInfoConteoUnos_Click);
            // 
            // btnInfoConvexas
            // 
            this->btnInfoConvexas->Location = System::Drawing::Point(1375, 531);
            this->btnInfoConvexas->Name = L"btnInfoConvexas";
            this->btnInfoConvexas->Size = System::Drawing::Size(30, 30);
            this->btnInfoConvexas->TabIndex = 5;
            this->btnInfoConvexas->Text = L"\?";
            this->btnInfoConvexas->Click += gcnew System::EventHandler(this, &MyForm::btnInfoConvexas_Click);
            // 
            // panelOriginal
            // 
            this->panelOriginal->BackColor = System::Drawing::Color::GhostWhite;
            this->panelOriginal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->panelOriginal->Location = System::Drawing::Point(491, 29);
            this->panelOriginal->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->panelOriginal->Name = L"panelOriginal";
            this->panelOriginal->Size = System::Drawing::Size(457, 496);
            this->panelOriginal->TabIndex = 0;
            this->panelOriginal->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panelOriginal_Paint);
            // 
            // panelDiagonal
            // 
            this->panelDiagonal->BackColor = System::Drawing::SystemColors::ControlLightLight;
            this->panelDiagonal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->panelDiagonal->Location = System::Drawing::Point(954, 29);
            this->panelDiagonal->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->panelDiagonal->Name = L"panelDiagonal";
            this->panelDiagonal->Size = System::Drawing::Size(443, 496);
            this->panelDiagonal->TabIndex = 1;
            this->panelDiagonal->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panelDiagonal_Paint);
            // 
            // panelCaminos
            // 
            this->panelCaminos->BackColor = System::Drawing::SystemColors::ControlLightLight;
            this->panelCaminos->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->panelCaminos->Location = System::Drawing::Point(1403, 29);
            this->panelCaminos->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->panelCaminos->Name = L"panelCaminos";
            this->panelCaminos->Size = System::Drawing::Size(443, 497);
            this->panelCaminos->TabIndex = 2;
            this->panelCaminos->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panelCaminos_Paint);
            // 
            // panelReordenado
            // 
            this->panelReordenado->BackColor = System::Drawing::SystemColors::InactiveBorder;
            this->panelReordenado->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->panelReordenado->Location = System::Drawing::Point(491, 562);
            this->panelReordenado->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->panelReordenado->Name = L"panelReordenado";
            this->panelReordenado->Size = System::Drawing::Size(457, 493);
            this->panelReordenado->TabIndex = 3;
            this->panelReordenado->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panelReordenado_Paint);
            // 
            // panelConteoUnos
            // 
            this->panelConteoUnos->BackColor = System::Drawing::SystemColors::ControlLightLight;
            this->panelConteoUnos->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->panelConteoUnos->Location = System::Drawing::Point(1862, 30);
            this->panelConteoUnos->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->panelConteoUnos->Name = L"panelConteoUnos";
            this->panelConteoUnos->Size = System::Drawing::Size(50, 496);
            this->panelConteoUnos->TabIndex = 4;
            this->panelConteoUnos->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panelConteoUnos_Paint);
            // 
            // panelRecorridoFinal
            // 
            this->panelRecorridoFinal->BackColor = System::Drawing::SystemColors::InactiveBorder;
            this->panelRecorridoFinal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->panelRecorridoFinal->Location = System::Drawing::Point(12, 29);
            this->panelRecorridoFinal->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->panelRecorridoFinal->Name = L"panelRecorridoFinal";
            this->panelRecorridoFinal->Size = System::Drawing::Size(473, 496);
            this->panelRecorridoFinal->TabIndex = 5;
            this->panelRecorridoFinal->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panelRecorridoFinal_Paint);
            // 
            // buttonGenerar
            // 
            this->buttonGenerar->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->buttonGenerar->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->buttonGenerar->Location = System::Drawing::Point(1564, 727);
            this->buttonGenerar->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->buttonGenerar->Name = L"buttonGenerar";
            this->buttonGenerar->Size = System::Drawing::Size(171, 52);
            this->buttonGenerar->TabIndex = 6;
            this->buttonGenerar->Text = L"Generar";
            this->buttonGenerar->UseVisualStyleBackColor = true;
            this->buttonGenerar->Click += gcnew System::EventHandler(this, &MyForm::buttonGenerar_Click);
            // 
            // buttonProcesar
            // 
            this->buttonProcesar->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->buttonProcesar->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->buttonProcesar->Location = System::Drawing::Point(1741, 727);
            this->buttonProcesar->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->buttonProcesar->Name = L"buttonProcesar";
            this->buttonProcesar->Size = System::Drawing::Size(171, 52);
            this->buttonProcesar->TabIndex = 7;
            this->buttonProcesar->Text = L"Procesar";
            this->buttonProcesar->UseVisualStyleBackColor = true;
            this->buttonProcesar->Click += gcnew System::EventHandler(this, &MyForm::buttonProcesar_Click);
            // 
            // buttonLimpiar
            // 
            this->buttonLimpiar->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->buttonLimpiar->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->buttonLimpiar->Location = System::Drawing::Point(1741, 808);
            this->buttonLimpiar->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->buttonLimpiar->Name = L"buttonLimpiar";
            this->buttonLimpiar->Size = System::Drawing::Size(171, 59);
            this->buttonLimpiar->TabIndex = 10;
            this->buttonLimpiar->Text = L"Limpiar";
            this->buttonLimpiar->UseVisualStyleBackColor = true;
            this->buttonLimpiar->Click += gcnew System::EventHandler(this, &MyForm::buttonLimpiar_Click);
            // 
            // numericUpDownSize
            // 
            this->numericUpDownSize->Location = System::Drawing::Point(1741, 696);
            this->numericUpDownSize->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->numericUpDownSize->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 17, 0, 0, 0 });
            this->numericUpDownSize->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 7, 0, 0, 0 });
            this->numericUpDownSize->Name = L"numericUpDownSize";
            this->numericUpDownSize->Size = System::Drawing::Size(171, 22);
            this->numericUpDownSize->TabIndex = 8;
            this->numericUpDownSize->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 8, 0, 0, 0 });
            this->numericUpDownSize->ValueChanged += gcnew System::EventHandler(this, &MyForm::numericUpDownSize_ValueChanged);
            // 
            // checkBoxManual
            // 
            this->checkBoxManual->Location = System::Drawing::Point(1564, 783);
            this->checkBoxManual->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->checkBoxManual->Name = L"checkBoxManual";
            this->checkBoxManual->Size = System::Drawing::Size(163, 25);
            this->checkBoxManual->TabIndex = 9;
            this->checkBoxManual->Text = L"Entrada Manual";
            this->checkBoxManual->UseVisualStyleBackColor = true;
            this->checkBoxManual->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxManual_CheckedChanged);
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
                static_cast<System::Int32>(static_cast<System::Byte>(192)));
            this->label1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->label1->Font = (gcnew System::Drawing::Font(L"Old English Text MT", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label1->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->label1->Location = System::Drawing::Point(1550, 596);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(369, 98);
            this->label1->TabIndex = 10;
            this->label1->Text = L"Componentes conexas\r\n        de un grafo";
            this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label2->ForeColor = System::Drawing::Color::Silver;
            this->label2->Location = System::Drawing::Point(605, 0);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(228, 27);
            this->label2->TabIndex = 11;
            this->label2->Text = L"Matriz de Adyacencia";
            // 
            // label8
            // 
            this->label8->AutoSize = true;
            this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label8->ForeColor = System::Drawing::Color::Silver;
            this->label8->Location = System::Drawing::Point(72, 0);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(318, 27);
            this->label8->TabIndex = 17;
            this->label8->Text = L"Grafo de Matriz de adyacencia";
            this->label8->Click += gcnew System::EventHandler(this, &MyForm::label8_Click);
            // 
            // label9
            // 
            this->label9->AutoSize = true;
            this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label9->ForeColor = System::Drawing::Color::Silver;
            this->label9->Location = System::Drawing::Point(1086, 0);
            this->label9->Name = L"label9";
            this->label9->Size = System::Drawing::Size(169, 27);
            this->label9->TabIndex = 18;
            this->label9->Text = L"Diagonal de 1´s";
            this->label9->Click += gcnew System::EventHandler(this, &MyForm::label9_Click);
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(1550, 698);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(185, 17);
            this->label3->TabIndex = 19;
            this->label3->Text = L"Ingresar cantidad de nodos ";
            this->label3->Click += gcnew System::EventHandler(this, &MyForm::label3_Click);
            // 
            // panelConvexas
            // 
            this->panelConvexas->BackColor = System::Drawing::SystemColors::InactiveBorder;
            this->panelConvexas->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->panelConvexas->Location = System::Drawing::Point(954, 562);
            this->panelConvexas->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->panelConvexas->Name = L"panelConvexas";
            this->panelConvexas->Size = System::Drawing::Size(457, 493);
            this->panelConvexas->TabIndex = 4;
            this->panelConvexas->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panelConvexas_Paint);
            // 
            // button1
            // 
            this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->button1->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->button1->Location = System::Drawing::Point(1591, 808);
            this->button1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(52, 47);
            this->button1->TabIndex = 20;
            this->button1->Text = L"1";
            this->button1->UseVisualStyleBackColor = true;
            this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
            // 
            // button0
            // 
            this->button0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->button0->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->button0->Location = System::Drawing::Point(1649, 808);
            this->button0->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->button0->Name = L"button0";
            this->button0->Size = System::Drawing::Size(52, 47);
            this->button0->TabIndex = 21;
            this->button0->Text = L"0";
            this->button0->UseVisualStyleBackColor = true;
            this->button0->Click += gcnew System::EventHandler(this, &MyForm::button0_Click);
            // 
            // label5
            // 
            this->label5->AutoSize = true;
            this->label5->BackColor = System::Drawing::Color::Yellow;
            this->label5->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label5->ForeColor = System::Drawing::Color::Red;
            this->label5->Location = System::Drawing::Point(1417, 860);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(2, 21);
            this->label5->TabIndex = 23;
            this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            // 
            // button2
            // 
            this->button2->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->button2->Location = System::Drawing::Point(1565, 530);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(170, 31);
            this->button2->TabIndex = 24;
            this->button2->Text = L"Pasos";
            this->button2->UseVisualStyleBackColor = true;
            this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
            // 
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label6->ForeColor = System::Drawing::Color::Silver;
            this->label6->Location = System::Drawing::Point(1512, 0);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(201, 27);
            this->label6->TabIndex = 25;
            this->label6->Text = L"Matriz de Caminos";
            this->label6->Click += gcnew System::EventHandler(this, &MyForm::label6_Click);
            // 
            // label7
            // 
            this->label7->AutoSize = true;
            this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label7->ForeColor = System::Drawing::Color::Silver;
            this->label7->Location = System::Drawing::Point(1849, 0);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(41, 27);
            this->label7->TabIndex = 26;
            this->label7->Text = L"1´s";
            this->label7->Click += gcnew System::EventHandler(this, &MyForm::label7_Click);
            // 
            // PanelOrdenFilas
            // 
            this->PanelOrdenFilas->BackColor = System::Drawing::Color::White;
            this->PanelOrdenFilas->Location = System::Drawing::Point(12, 563);
            this->PanelOrdenFilas->Name = L"PanelOrdenFilas";
            this->PanelOrdenFilas->Size = System::Drawing::Size(473, 492);
            this->PanelOrdenFilas->TabIndex = 27;
            this->PanelOrdenFilas->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::PanelOrdenFilas_Paint);
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label4->ForeColor = System::Drawing::Color::Silver;
            this->label4->Location = System::Drawing::Point(1005, 532);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(333, 27);
            this->label4->TabIndex = 28;
            this->label4->Text = L"Grafo de componentes Conexas";
            // 
            // label10
            // 
            this->label10->AutoSize = true;
            this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label10->ForeColor = System::Drawing::Color::Silver;
            this->label10->Location = System::Drawing::Point(571, 530);
            this->label10->Name = L"label10";
            this->label10->Size = System::Drawing::Size(312, 27);
            this->label10->TabIndex = 29;
            this->label10->Text = L"Ordenar columnas segun filas";
            // 
            // label11
            // 
            this->label11->AutoSize = true;
            this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label11->ForeColor = System::Drawing::Color::Silver;
            this->label11->Location = System::Drawing::Point(72, 527);
            this->label11->Name = L"label11";
            this->label11->Size = System::Drawing::Size(217, 27);
            this->label11->TabIndex = 30;
            this->label11->Text = L"Ordenar filas por 1´s";
            // 
            // label12
            // 
            this->label12->AutoSize = true;
            this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label12->ForeColor = System::Drawing::Color::Silver;
            this->label12->Location = System::Drawing::Point(1379, 834);
            this->label12->Name = L"label12";
            this->label12->Size = System::Drawing::Size(0, 27);
            this->label12->TabIndex = 31;
            // 
            // Salir
            // 
            this->Salir->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->Salir->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->Salir->Location = System::Drawing::Point(1809, 880);
            this->Salir->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->Salir->Name = L"Salir";
            this->Salir->Size = System::Drawing::Size(103, 59);
            this->Salir->TabIndex = 32;
            this->Salir->Text = L"Salir";
            this->Salir->UseVisualStyleBackColor = true;
            this->Salir->Click += gcnew System::EventHandler(this, &MyForm::Salir_Click);
            // 
            // btnInfoAgrupacion
            // 
            this->btnInfoAgrupacion->Location = System::Drawing::Point(914, 530);
            this->btnInfoAgrupacion->Name = L"btnInfoAgrupacion";
            this->btnInfoAgrupacion->Size = System::Drawing::Size(32, 30);
            this->btnInfoAgrupacion->TabIndex = 0;
            this->btnInfoAgrupacion->Text = L"\?";
            this->btnInfoAgrupacion->Click += gcnew System::EventHandler(this, &MyForm::btnInfoAgrupacion_Click);
            // 
            // button3
            // 
            this->button3->Location = System::Drawing::Point(1538, 783);
            this->button3->Name = L"button3";
            this->button3->Size = System::Drawing::Size(20, 25);
            this->button3->TabIndex = 33;
            this->button3->Text = L"\?";
            this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
                static_cast<System::Int32>(static_cast<System::Byte>(64)));
            this->ClientSize = System::Drawing::Size(1924, 1055);
            this->Controls->Add(this->button3);
            this->Controls->Add(this->btnInfoAgrupacion);
            this->Controls->Add(this->btnInfoReordenado);
            this->Controls->Add(this->btnInfoCaminos);
            this->Controls->Add(this->btnInfoOriginal);
            this->Controls->Add(this->btnInfoDiagonal);
            this->Controls->Add(this->btnInfoConteoUnos);
            this->Controls->Add(this->btnInfoConvexas);
            this->Controls->Add(this->Salir);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->label12);
            this->Controls->Add(this->label11);
            this->Controls->Add(this->label10);
            this->Controls->Add(this->label4);
            this->Controls->Add(this->PanelOrdenFilas);
            this->Controls->Add(this->panelOriginal);
            this->Controls->Add(this->label7);
            this->Controls->Add(this->label6);
            this->Controls->Add(this->button2);
            this->Controls->Add(this->label5);
            this->Controls->Add(this->button0);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->panelConvexas);
            this->Controls->Add(this->panelConteoUnos);
            this->Controls->Add(this->panelCaminos);
            this->Controls->Add(this->panelRecorridoFinal);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->label9);
            this->Controls->Add(this->label8);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->checkBoxManual);
            this->Controls->Add(this->numericUpDownSize);
            this->Controls->Add(this->buttonProcesar);
            this->Controls->Add(this->buttonGenerar);
            this->Controls->Add(this->buttonLimpiar);
            this->Controls->Add(this->panelReordenado);
            this->Controls->Add(this->panelDiagonal);
            this->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
            this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->Name = L"MyForm";
            this->Text = L"Trabajo Computacional";
            this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownSize))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

        // Métodos para efectos "hover" en los botones
    private: System::Void buttonGenerar_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
        this->buttonGenerar->BackColor = Color::DodgerBlue;
    }
    private: System::Void buttonGenerar_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
        this->buttonGenerar->BackColor = Color::DeepSkyBlue;
    }

    private: System::Void buttonProcesar_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
        this->buttonProcesar->BackColor = Color::Green;
    }
    private: System::Void buttonProcesar_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
        this->buttonProcesar->BackColor = Color::LimeGreen;
    }

    private: System::Void buttonLimpiar_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
        this->buttonLimpiar->BackColor = Color::DarkGray;
    }
    private: System::Void buttonLimpiar_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
        this->buttonLimpiar->BackColor = Color::LightGray;
    }

    private: System::Void buttonGenerar_Click(System::Object^ sender, System::EventArgs^ e) {
        int size = Decimal::ToInt32(numericUpDownSize->Value); // Obtener el tamaño de la matriz
        entradaManual = checkBoxManual->Checked; // Verificar si es entrada manual

        // Inicializar la matriz con el tamaño seleccionado
        matriz.clear(); // Limpiar la matriz anterior

        matriz = vector<vector<int>>(size, vector<int>(size, 0));

        // Asegúrate de resetear las variables relacionadas con la matriz
        letrasFilasOriginales.resize(size);  // Ajustar el tamaño de las letras de las filas
        letrasFilasReordenadas.resize(size); // Ajustar el tamaño de las letras reordenadas

        if (entradaManual) {
            currentRow = 0;
            currentCol = 0;
            button1->Enabled = true;
            button0->Enabled = true;
        }
        else {
            matriz = generarMatriz(size);
            button1->Enabled = false;
            button0->Enabled = false;
        }

        panelOriginal->Invalidate();
        panelRecorridoFinal->Invalidate();

        // Control de botones
        buttonProcesar->Enabled = true;  // Habilitar el botón "Procesar"
        button2->Enabled = false;        // Deshabilitar el botón "Pasos" hasta que se procese

        // Desactivar los botones de información
        btnInfoOriginal->Enabled = false;
        btnInfoDiagonal->Enabled = false;
        btnInfoCaminos->Enabled = false;
        btnInfoReordenado->Enabled = false;
        btnInfoConteoUnos->Enabled = false;
        btnInfoConvexas->Enabled = false;
        btnInfoAgrupacion->Enabled = false;
    }

    private: System::Void buttonProcesar_Click(System::Object^ sender, System::EventArgs^ e) {
        matrizDiagonal = matriz;
        asegurarDiagonal(matrizDiagonal);
        panelDiagonal->Invalidate();

        matrizCaminos = matrizDiagonal;
        calcularMatrizDeCaminos(matrizCaminos);
        panelCaminos->Invalidate();

        conteoUnos = contarUnosPorFila(matrizCaminos);
        matrizReordenada = reordenarMatriz(matrizCaminos, conteoUnos);
        panelReordenado->Invalidate();
        panelConteoUnos->Invalidate();
        panelRecorridoFinal->Invalidate();
        PanelOrdenFilas->Invalidate();

        vector<int> componentes = identificarComponentesConexasPorCuadrados(matrizReordenada);

        map<int, vector<char>> gruposComponentes;
        for (int i = 0; i < componentes.size(); ++i) {
            gruposComponentes[componentes[i]].push_back(letrasFilasReordenadas[i]);
        }

        String^ componentesTexto = "Grupos de componentes conexas:\n";
        int grupo = 1;
        for (const auto& par : gruposComponentes) {
            componentesTexto += "V" + grupo + " = {";
            for (int i = 0; i < par.second.size(); ++i) {
                componentesTexto += gcnew String(par.second[i], 1);
                if (i != par.second.size() - 1) {
                    componentesTexto += ",";
                }
            }
            componentesTexto += "}\n";
            grupo++;
        }

        label5->Text = componentesTexto;

        panelConvexas->Invalidate();

        button2->Enabled = true;  // Habilitar el botón "Pasos"

        // Habilitar todos los botones de información
        btnInfoOriginal->Enabled = true;
        btnInfoDiagonal->Enabled = true;
        btnInfoCaminos->Enabled = true;
        btnInfoReordenado->Enabled = true;
        btnInfoConteoUnos->Enabled = true;
        btnInfoConvexas->Enabled = true;
        btnInfoAgrupacion->Enabled = true;
    }

    private: System::Void buttonLimpiar_Click(System::Object^ sender, System::EventArgs^ e) {
        matriz.clear();
        matrizDiagonal.clear();
        matrizCaminos.clear();
        matrizReordenada.clear();
        conteoUnos.clear();
        label5->Text = "";

        panelOriginal->Invalidate();
        panelDiagonal->Invalidate();
        panelCaminos->Invalidate();
        panelReordenado->Invalidate();
        panelConteoUnos->Invalidate();
        panelRecorridoFinal->Invalidate();
        panelConvexas->Invalidate();
        PanelOrdenFilas->Invalidate();

        // Control de botones
        buttonProcesar->Enabled = false;  // Deshabilitar "Procesar"
        button2->Enabled = false;         // Deshabilitar "Pasos"

        // Deshabilitar todos los botones de información
        btnInfoOriginal->Enabled = false;
        btnInfoDiagonal->Enabled = false;
        btnInfoCaminos->Enabled = false;
        btnInfoReordenado->Enabled = false;
        btnInfoConteoUnos->Enabled = false;
        btnInfoConvexas->Enabled = false;
        btnInfoAgrupacion->Enabled = false;
    }

           void dibujarMatriz(Graphics^ graphics, const vector<vector<int>>& matriz, const vector<char>& letrasFilas, int filaActual, int colActual) {
               int cellSize = 20; // Tamaño de las celdas
               int n = matriz.size(); // Tamaño de la matriz

               System::Drawing::Font^ font = gcnew System::Drawing::Font(L"Arial", 10);

               // Dibujar etiquetas de las columnas (A, B, C, ...)
               for (int j = 0; j < n; ++j) {
                   String^ letraColumna = gcnew String(letrasFilas[j], 1);
                   graphics->DrawString(letraColumna, font, Brushes::Black, j * cellSize + cellSize, 0);
               }

               // Dibujar la matriz con etiquetas de filas y columnas
               for (int i = 0; i < n; ++i) {
                   // Etiqueta de las filas
                   String^ letraFila = gcnew String(letrasFilas[i], 1);
                   graphics->DrawString(letraFila, font, Brushes::Black, 0, i * cellSize + cellSize);

                   // Dibujar el contenido de la matriz (0 o 1)
                   for (int j = 0; j < n; ++j) {
                       System::Drawing::Rectangle cellRect(j * cellSize + cellSize, i * cellSize + cellSize, cellSize, cellSize);

                       // Verificar si es la celda actual (filaActual, colActual)
                       if (i == filaActual && j == colActual) {
                           // Dibujar borde más grueso o con color diferente para la celda actual
                           graphics->DrawRectangle(gcnew Pen(Color::Blue, 2), cellRect);
                       }
                       else {
                           // Dibujar borde normal
                           graphics->DrawRectangle(Pens::Black, cellRect);
                       }

                       // Dibujar el valor (0 o 1)
                       String^ texto = matriz[i][j].ToString();
                       graphics->DrawString(texto, font, Brushes::Black, j * cellSize + cellSize, i * cellSize + cellSize);
                   }
               }
           }


           void dibujarDiagonalConRojo(Graphics^ graphics, const vector<vector<int>>& matriz, const vector<char>& letrasFilas) {
               int cellSize = 20; // Tamaño de las celdas
               int n = matriz.size(); // Tamaño de la matriz

               // Crear fuente aquí
               System::Drawing::Font^ font = gcnew System::Drawing::Font(L"Arial", 10);

               // Dibujar etiquetas de las columnas (A, B, C, ...)
               for (int j = 0; j < n; ++j) {
                   String^ letraColumna = gcnew String(letrasFilas[j], 1);
                   graphics->DrawString(letraColumna, font, Brushes::Black, j * cellSize + cellSize, 0);
               }

               // Dibujar la matriz con etiquetas de filas y columnas
               for (int i = 0; i < n; ++i) {
                   // Etiqueta de las filas
                   String^ letraFila = gcnew String(letrasFilas[i], 1);
                   graphics->DrawString(letraFila, font, Brushes::Black, 0, i * cellSize + cellSize);

                   // Dibujar el contenido de la matriz (0 o 1)
                   for (int j = 0; j < n; ++j) {
                       System::Drawing::Rectangle cellRect(j * cellSize + cellSize, i * cellSize + cellSize, cellSize, cellSize);
                       graphics->DrawRectangle(Pens::Black, cellRect);

                       String^ texto = matriz[i][j].ToString();
                       graphics->DrawString(texto, font, Brushes::Black, j * cellSize + cellSize, i * cellSize + cellSize);
                   }

                   // Dibujar la línea roja en la diagonal
                   int diagonalX1 = i * cellSize + cellSize;
                   int diagonalY1 = i * cellSize + cellSize;
                   int diagonalX2 = (i + 1) * cellSize + cellSize;
                   int diagonalY2 = (i + 1) * cellSize + cellSize;
                   graphics->DrawLine(Pens::Red, diagonalX1, diagonalY1, diagonalX2, diagonalY2);
               }
           }

    private: System::Void panelDiagonal_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
        dibujarDiagonalConRojo(e->Graphics, matrizDiagonal, letrasFilasOriginales);
    }

    private: System::Void panelCaminos_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
        dibujarDiagonalConRojo(e->Graphics, matrizCaminos, letrasFilasOriginales); // Dibujar la diagonal con la línea roja
    }

    private: System::Void panelReordenado_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
        dibujarMatrizConCuadradosDiagonales(e->Graphics, matrizReordenada, letrasFilasReordenadas);
    }


    private: System::Void panelRecorridoFinal_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
        Graphics^ graphics = e->Graphics;
        int radius = 20;
        int centerX = 180; // Reducir este valor para mover el grafo más a la izquierda
        int centerY = 200;
        float bigRadius = 150.0f;

        size_t n = matriz.size();
        cli::array<System::Drawing::Point>^ nodePositions = gcnew cli::array<System::Drawing::Point>(n);

        for (size_t i = 0; i < n; ++i) {
            double angle = 2 * Math::PI * static_cast<double>(i) / static_cast<double>(n);
            int x = centerX + static_cast<int>(bigRadius * cos(angle));
            int y = centerY + static_cast<int>(bigRadius * sin(angle));
            nodePositions[i] = System::Drawing::Point(x, y);

            graphics->DrawEllipse(Pens::Black, x - radius / 2, y - radius / 2, radius, radius);

            String^ letra = gcnew String((char)('A' + static_cast<int>(i)), 1);
            System::Drawing::SizeF textSize = graphics->MeasureString(letra, System::Drawing::SystemFonts::DefaultFont);
            float textX = x - textSize.Width / 2;
            float textY = y - textSize.Height / 2;
            graphics->DrawString(letra, System::Drawing::SystemFonts::DefaultFont, Brushes::Black, textX, textY);
        }

        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (matriz[i][j] == 1) { // Solo dibuja conexiones si matriz[i][j] == 1
                    System::Drawing::Point p1 = nodePositions[i];
                    System::Drawing::Point p2 = nodePositions[j];

                    Pen^ pen = gcnew Pen(Color::Black, 2);
                    AdjustableArrowCap^ arrow = gcnew AdjustableArrowCap(5.0f, 5.0f);
                    pen->CustomEndCap = arrow;

                    if (i == j) { // Dibujar un bucle si i == j (nodo conectado consigo mismo)
                        int loopRadius = 15;
                        int loopX = p1.X - loopRadius / 2;
                        int loopY = p1.Y - loopRadius / 2;

                        System::Drawing::Rectangle loopRect(loopX, loopY - loopRadius, loopRadius * 2, loopRadius * 2);
                        graphics->DrawArc(pen, loopRect, 200, 270);
                    }
                    else { // Dibujar una línea normal si i != j
                        double angle = atan2(p2.Y - p1.Y, p2.X - p1.X);
                        int offsetX = static_cast<int>(radius / 2 * cos(angle));
                        int offsetY = static_cast<int>(radius / 2 * sin(angle));

                        graphics->DrawLine(pen,
                            static_cast<float>(p1.X + offsetX), static_cast<float>(p1.Y + offsetY),
                            static_cast<float>(p2.X - offsetX), static_cast<float>(p2.Y - offsetY));
                    }
                }
            }
        }
    }

    private: System::Void panelConteoUnos_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
        Graphics^ graphics = e->Graphics;
        int cellSize = 20; // Tamaño de la celda
        int n = conteoUnos.size(); // Cantidad de filas

        System::Drawing::Font^ font = gcnew System::Drawing::Font(L"Arial", 10);

        // Dibujar el conteo de unos junto con la letra correspondiente de cada fila (A, B, C...)
        for (int i = 0; i < n; ++i) {
            // Obtener la letra correspondiente en orden (A, B, C, D, ...)
            String^ letraFila = gcnew String((char)('A' + i), 1);

            // Dibujar la letra de la fila en el primer espacio
            graphics->DrawString(letraFila, font, Brushes::Black, 0, i * cellSize);

            // Dibujar el conteo de unos en el segundo espacio, alineado con la letra
            System::Drawing::Rectangle cellRect(cellSize, i * cellSize, cellSize, cellSize);
            graphics->DrawRectangle(Pens::Black, cellRect);
            String^ textoConteo = conteoUnos[i].ToString();
            graphics->DrawString(textoConteo, font, Brushes::Black, cellSize, i * cellSize);
        }
    }


           void dibujarConteoUnos(Graphics^ graphics, const vector<int>& conteo) {
               int cellSize = 20;
               System::Drawing::Font^ font = gcnew System::Drawing::Font(L"Arial", 10); // Crear fuente aquí también
               for (int i = 0; i < conteo.size(); ++i) {
                   String^ letraFila = gcnew String((char)('A' + i), 1);
                   graphics->DrawString(letraFila, font, Brushes::Black, -20, i * cellSize);

                   System::Drawing::Rectangle cellRect(0, i * cellSize, cellSize, cellSize);
                   graphics->DrawRectangle(Pens::Black, cellRect);
                   String^ texto = conteo[i].ToString();
                   graphics->DrawString(texto, font, Brushes::Black, 0, i * cellSize);
               }
           }
           // Función para identificar y dibujar los bloques cuadrados en la matriz reordenada
           void dibujarMatrizConCuadradosDiagonales(Graphics^ graphics, const vector<vector<int>>& matriz, const vector<char>& letrasFilas) {
               int cellSize = 20; // Tamaño de las celdas
               int n = matriz.size(); // Tamaño de la matriz

               System::Drawing::Font^ font = gcnew System::Drawing::Font(L"Arial", 10);

               // Dibujar etiquetas de las columnas (A, B, C, ...)
               for (int j = 0; j < n; ++j) {
                   String^ letraColumna = gcnew String(letrasFilas[j], 1);
                   graphics->DrawString(letraColumna, font, Brushes::Black, j * cellSize + cellSize, 0);
               }

               // Dibujar la matriz con etiquetas de filas y columnas
               for (int i = 0; i < n; ++i) {
                   // Etiqueta de las filas
                   String^ letraFila = gcnew String(letrasFilas[i], 1);
                   graphics->DrawString(letraFila, font, Brushes::Black, 0, i * cellSize + cellSize);

                   // Dibujar el contenido de la matriz (0 o 1)
                   for (int j = 0; j < n; ++j) {
                       System::Drawing::Rectangle cellRect(j * cellSize + cellSize, i * cellSize + cellSize, cellSize, cellSize);
                       graphics->DrawRectangle(Pens::Black, cellRect);

                       String^ texto = matriz[i][j].ToString();
                       graphics->DrawString(texto, font, Brushes::Black, j * cellSize + cellSize, i * cellSize + cellSize);
                   }
               }

               // Detectar componentes conexas como bloques a lo largo de la diagonal
               vector<vector<bool>> visitado(n, vector<bool>(n, false)); // Para rastrear qué celdas ya se han visitado

               for (int i = 0; i < n; ++i) {
                   for (int j = 0; j < n; ++j) {
                       // Solo considerar bloques que empiezan en la diagonal
                       if (i == j && matriz[i][j] == 1 && !visitado[i][j]) {
                           int maxTamaño = 1;

                           // Expandir el bloque cuadrado solo si está alineado con la diagonal
                           while (i + maxTamaño < n && j + maxTamaño < n) {
                               bool esCuadrado = true;

                               // Verificar si el bloque sigue siendo cuadrado a lo largo de la diagonal
                               for (int x = i; x <= i + maxTamaño; ++x) {
                                   for (int y = j; y <= j + maxTamaño; ++y) {
                                       if (matriz[x][y] != 1) {
                                           esCuadrado = false;
                                           break;
                                       }
                                   }
                                   if (!esCuadrado) break;
                               }

                               if (esCuadrado) {
                                   maxTamaño++; // Aumentar el tamaño si sigue siendo cuadrado
                               }
                               else {
                                   break;
                               }
                           }
                           maxTamaño--; // Ajustar el tamaño al último cuadrado válido

                           // Marcar todas las celdas en el bloque como visitadas
                           for (int x = i; x <= i + maxTamaño; ++x) {
                               for (int y = j; y <= j + maxTamaño; ++y) {
                                   visitado[x][y] = true;
                               }
                           }

                           // Dibujar el cuadrado alrededor del bloque de unos
                           System::Drawing::Rectangle groupRect(j * cellSize + cellSize, i * cellSize + cellSize, (maxTamaño + 1) * cellSize, (maxTamaño + 1) * cellSize);
                           graphics->DrawRectangle(gcnew Pen(Color::Red, 2), groupRect);
                       }
                   }
               }
           }

           vector<int> identificarComponentesConexasDiagonal(const vector<vector<int>>& matrizReordenada) {
               int n = matrizReordenada.size();
               vector<int> componentes(n, -1);  // Inicializar con -1, indicando sin asignar componente
               int componenteIndex = 0;

               vector<vector<bool>> visitado(n, vector<bool>(n, false));  // Para rastrear qué celdas ya se han visitado

               // Recorrer la diagonal y detectar bloques cuadrados de unos
               for (int i = 0; i < n; ++i) {
                   if (componentes[i] == -1 && matrizReordenada[i][i] == 1) {
                       int maxTamaño = 1;

                       // Expandir el bloque cuadrado solo si está alineado con la diagonal
                       while (i + maxTamaño < n && matrizReordenada[i + maxTamaño][i + maxTamaño] == 1) {
                           // Verificar si las filas y columnas son bloques completos de unos
                           bool esCuadrado = true;
                           for (int x = i; x <= i + maxTamaño; ++x) {
                               for (int y = i; y <= i + maxTamaño; ++y) {
                                   if (matrizReordenada[x][y] != 1) {
                                       esCuadrado = false;
                                       break;
                                   }
                               }
                               if (!esCuadrado) break;
                           }

                           if (esCuadrado) {
                               maxTamaño++;  // Expandir si sigue siendo un cuadrado
                           }
                           else {
                               break;
                           }
                       }

                       // Asignar componente a todo el bloque cuadrado
                       for (int x = i; x < i + maxTamaño; ++x) {
                           for (int y = i; y < i + maxTamaño; ++y) {
                               componentes[x] = componenteIndex;
                               componentes[y] = componenteIndex;
                               visitado[x][y] = true;
                           }
                       }

                       componenteIndex++;  // Pasar a la siguiente componente
                   }
               }

               return componentes;
           }
           void drawArrow(Graphics^ graphics, System::Drawing::Point from, System::Drawing::Point to, Pen^ pen, int radius) {
               // Calcular el ángulo entre los puntos 'from' y 'to'
               double angle = atan2(to.Y - from.Y, to.X - from.X);

               // Calcular el desplazamiento desde el centro del nodo hasta el borde del círculo
               int offsetX = static_cast<int>(radius / 2 * cos(angle));
               int offsetY = static_cast<int>(radius / 2 * sin(angle));

               // Ajustar los puntos 'from' y 'to' para que las flechas empiecen y terminen en el borde de los círculos
               System::Drawing::Point adjustedFrom(from.X + offsetX, from.Y + offsetY);
               System::Drawing::Point adjustedTo(to.X - offsetX, to.Y - offsetY);

               // Dibujar la línea entre los dos puntos ajustados
               graphics->DrawLine(pen, adjustedFrom, adjustedTo);

               // Dibujar la flecha al final de la línea
               AdjustableArrowCap^ arrowCap = gcnew AdjustableArrowCap(5, 5, true);  // Tamaño de la flecha
               pen->CustomEndCap = arrowCap;
               graphics->DrawLine(pen, adjustedFrom, adjustedTo);
           }

    private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
        // Generar una matriz aleatoria con tamaño por defecto (puedes cambiar el tamaño si lo deseas)
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None; // Sin bordes
        this->WindowState = System::Windows::Forms::FormWindowState::Maximized; // Pantalla completa
        int size = 16;  // Ejemplo con tamaño de 8x8
        matriz = generarMatriz(size);
        buttonProcesar->Enabled = false;
        button2->Enabled = false;
        // Mostrar en consola (opcional) la matriz generada antes de borrarla
        cout << "Matriz generada aleatoriamente:" << endl;
        for (int i = 0; i < matriz.size(); ++i) {
            for (int j = 0; j < matriz[i].size(); ++j) {
                cout << matriz[i][j] << " ";
            }
            cout << endl;
        }

        // Ahora borrar (limpiar) la matriz generada
        matriz.clear();

        // Asegúrate de que todos los paneles se invaliden (refrescar)
        panelOriginal->Invalidate();
        panelDiagonal->Invalidate();
        panelCaminos->Invalidate();
        panelReordenado->Invalidate();
        panelConteoUnos->Invalidate();
        panelRecorridoFinal->Invalidate();
        panelConvexas->Invalidate();
    }
    private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
    }private: System::Void panelOriginal_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
        dibujarMatriz(e->Graphics, matriz, letrasFilasOriginales, currentRow, currentCol);  // Pasar la celda actual
    }
    private: System::Void label9_Click(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void label8_Click(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void numericUpDownSize_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
        int value = (int)this->numericUpDownSize->Value;

        if (value < 8 || value > 16) {
            // Muestra el mensaje si el valor está fuera de los límites
            MessageBox::Show("El valor se sale de los límites permitidos (8-16)", "Advertencia", MessageBoxButtons::OK, MessageBoxIcon::Warning);

            // Restablece el valor a los límites permitidos
            this->numericUpDownSize->Value = (value < 8) ? 8 : 16;
        }
    }
    private: System::Void checkBoxManual_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
    }
           void dfs(int node, const vector<vector<int>>& matriz, vector<bool>& visitado, vector<int>& componente, int componentIndex) {
               visitado[node] = true;
               componente[node] = componentIndex;  // Asignar el componente actual al nodo

               for (int i = 0; i < matriz.size(); ++i) {
                   if (matriz[node][i] == 1 && !visitado[i]) {
                       dfs(i, matriz, visitado, componente, componentIndex);
                   }
               }
           }
           vector<int> identificarComponentesConexasPorCuadrados(const vector<vector<int>>& matrizReordenada) {
               int n = matrizReordenada.size();
               vector<int> componentes(n, -1);  // Inicializar con -1, indicando sin asignar componente
               int componenteIndex = 0;

               vector<vector<bool>> visitado(n, vector<bool>(n, false));  // Para rastrear qué celdas ya se han visitado

               // Recorrer la diagonal y detectar bloques cuadrados de unos
               for (int i = 0; i < n; ++i) {
                   if (componentes[i] == -1 && matrizReordenada[i][i] == 1) {
                       int maxTamaño = 1;

                       // Expandir el bloque cuadrado solo si está alineado con la diagonal
                       while (i + maxTamaño < n && matrizReordenada[i + maxTamaño][i + maxTamaño] == 1) {
                           // Verificar si las filas y columnas son bloques completos de unos
                           bool esCuadrado = true;
                           for (int x = i; x <= i + maxTamaño; ++x) {
                               for (int y = i; y <= i + maxTamaño; ++y) {
                                   if (matrizReordenada[x][y] != 1) {
                                       esCuadrado = false;
                                       break;
                                   }
                               }
                               if (!esCuadrado) break;
                           }

                           if (esCuadrado) {
                               maxTamaño++;  // Expandir si sigue siendo un cuadrado
                           }
                           else {
                               break;
                           }
                       }

                       // Asignar componente a todo el bloque cuadrado
                       for (int x = i; x < i + maxTamaño; ++x) {
                           for (int y = i; y < i + maxTamaño; ++y) {
                               componentes[x] = componenteIndex;
                               componentes[y] = componenteIndex;
                               visitado[x][y] = true;
                           }
                       }

                       componenteIndex++;  // Pasar a la siguiente componente
                   }
               }

               return componentes;
           }
           void dfsInverso(int node, const vector<vector<int>>& matriz, vector<bool>& visitado, vector<int>& componente, int componentIndex) {
               visitado[node] = true;
               componente[node] = componentIndex;

               // Explorar los vecinos inversos
               for (int i = 0; i < matriz.size(); ++i) {
                   if (matriz[i][node] == 1 && !visitado[i]) {
                       dfsInverso(i, matriz, visitado, componente, componentIndex);
                   }
               }
           }


           // Función para detectar componentes conexas en la matriz original
           vector<int> identificarComponentesConexas(const vector<vector<int>>& matriz) {
               int n = matriz.size();
               vector<bool> visitado(n, false);
               vector<int> componente(n, -1);  // Inicializar con -1, indicando sin asignar
               int componentIndex = 0;

               for (int i = 0; i < n; ++i) {
                   if (!visitado[i]) {
                       dfs(i, matriz, visitado, componente, componentIndex);
                       componentIndex++;  // Cambiar al siguiente componente después de terminar la DFS
                   }
               }

               return componente;
           }
           void dfs_matriz_ordenada(int node, const vector<vector<int>>& matrizReordenada, vector<bool>& visitado, vector<int>& componente, int componentIndex) {
               visitado[node] = true;
               componente[node] = componentIndex;

               for (int i = 0; i < matrizReordenada.size(); ++i) {
                   if (matrizReordenada[node][i] == 1 && !visitado[i]) {
                       dfs_matriz_ordenada(i, matrizReordenada, visitado, componente, componentIndex);
                   }
               }
           }


           void dibujarNodoConLetra(Graphics^ graphics, int x, int y, String^ letra, Pen^ pen, int radius) {
               // Dibujar el nodo como un círculo
               graphics->FillEllipse(gcnew SolidBrush(pen->Color), x - radius / 2, y - radius / 2, radius, radius);

               // Dibujar la letra centrada en el nodo
               System::Drawing::Font^ font = gcnew System::Drawing::Font(L"Arial", 10);
               System::Drawing::SizeF textSize = graphics->MeasureString(letra, font);
               graphics->DrawString(letra, font, Brushes::Black, x - textSize.Width / 2, y - textSize.Height / 2);
           }
           // Función para dibujar flechas fuera del círculo
           void ingresarValorManual(int valor) {
               int n = matriz.size();  // Tamaño de la matriz

               // Asignar el valor a la matriz en la posición actual
               matriz[currentRow][currentCol] = valor;

               // Avanzar el cursor
               currentCol++;
               if (currentCol >= n) {
                   currentCol = 0;  // Resetear la columna
                   currentRow++;    // Avanzar a la siguiente fila
               }

               // Si hemos llegado al final de la matriz, desactivar los botones para ingresar más valores
               if (currentRow >= n) {
                   button1->Enabled = false;
                   button0->Enabled = false;
               }

               // Actualizar el panel para que se dibuje la matriz actualizada
               panelOriginal->Invalidate();
           }
           void panelConvexas_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
               Graphics^ graphics = e->Graphics;

               // Ajustar el centro del grafo y el radio dinámicamente según el tamaño del panel
               int centerX = panelConvexas->Width / 2;
               int centerY = panelConvexas->Height / 2 - 38;  // Mover un poco hacia arriba
               float bigRadius = min(panelConvexas->Width, panelConvexas->Height) / 2.2f;  // 1/3 del tamaño más pequeño del panel

               int radius = 15;  // Reducir el tamaño de los nodos

               // Detectar las componentes conexas basadas en los bloques cuadrados en la diagonal
               vector<int> componente = identificarComponentesConexasPorCuadrados(matrizReordenada);

               // Colores para las diferentes componentes
               cli::array<Color>^ componentColors = { Color::Red, Color::Blue, Color::Green, Color::Orange, Color::Purple, Color::Yellow, Color::Cyan, Color::Magenta };

               size_t n = matrizReordenada.size();
               cli::array<System::Drawing::Point>^ nodePositions = gcnew cli::array<System::Drawing::Point>(n);

               // Posicionar los nodos en un círculo
               for (size_t i = 0; i < n; ++i) {
                   double angle = 2 * Math::PI * static_cast<double>(i) / static_cast<double>(n);
                   int x = centerX + static_cast<int>(bigRadius * cos(angle));
                   int y = centerY + static_cast<int>(bigRadius * sin(angle));
                   nodePositions[i] = System::Drawing::Point(x, y);
               }

               for (int node = 0; node < n; ++node) {
                   for (int i = 0; i < n; ++i) {
                       // Verificar las conexiones en la matriz de adyacencia original
                       int originalNode = letrasFilasReordenadas[node] - 'A';  // Convertir a índice original usando las letras reordenadas
                       int originalI = letrasFilasReordenadas[i] - 'A';        // Convertir a índice original usando las letras reordenadas

                       // Verificar si hay una conexión en la matriz original
                       if (matriz[originalNode][originalI] == 1 && componente[node] == componente[i]) {
                           Pen^ pen = gcnew Pen(componentColors[componente[node] % componentColors->Length], 2);

                           // Dibujar las conexiones usando las posiciones visuales reordenadas
                           drawArrow(graphics, nodePositions[node], nodePositions[i], pen, radius);

                           // Si hay una conexión bidireccional en la matriz original, dibujar la flecha inversa
                           if (matriz[originalI][originalNode] == 1) {
                               drawArrow(graphics, nodePositions[i], nodePositions[node], pen, radius);
                           }
                       }
                   }
               }

               // Finalmente, dibujar los nodos con las letras correspondientes a las filas reordenadas
               for (int node = 0; node < n; ++node) {
                   String^ letraNodo = gcnew String(letrasFilasReordenadas[node], 1);
                   if (node < componente.size()) {
                       Pen^ pen = gcnew Pen(componentColors[componente[node] % componentColors->Length], 2);
                       dibujarNodoConLetra(graphics, nodePositions[node].X, nodePositions[node].Y, letraNodo, pen, radius);
                   }
               }
           }


    private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
        ingresarValorManual(1);  // Ingresar un "1"
    }

    private: System::Void button0_Click(System::Object^ sender, System::EventArgs^ e) {
        ingresarValorManual(0);  // Ingresar un "0"
    }
    private: System::Void MyForm_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
        // Verificar si la entrada manual está habilitada
        if (entradaManual) {
            // Si el usuario presiona '1'
            if (e->KeyChar == '1') {
                ingresarValorManual(1);  // Ingresar un "1"
            }
            // Si el usuario presiona '0'
            else if (e->KeyChar == '0') {
                ingresarValorManual(0);  // Ingresar un "0"
            }
        }
    }
    private: System::Void label5_Click(System::Object^ sender, System::EventArgs^ e) {
    }

private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
    Project15::Pasos^ pasos = gcnew Project15::Pasos(matriz);  // Pasar la matriz desde Form1
    pasos->Show();
}
private: System::Void label6_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label7_Click(System::Object^ sender, System::EventArgs^ e) {
}
       

private: System::Void PanelOrdenFilas_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
    Graphics^ graphics = e->Graphics;
    int cellSize = 20; // Tamaño de cada celda
    int n = matrizCaminos.size(); // Tamaño de la matriz

    System::Drawing::Font^ font = gcnew System::Drawing::Font(L"Arial", 10);

    // Crear una copia de conteoUnos para mantener los datos originales sin modificaciones
    vector<int> conteoUnosCopia(n, 0);
    for (int i = 0; i < n; ++i) {
        conteoUnosCopia[i] = count(matrizCaminos[i].begin(), matrizCaminos[i].end(), 1);
    }

    // Crear una copia de matrizCaminos para el reordenamiento temporal
    vector<vector<int>> matrizCaminosCopia = matrizCaminos;

    // Crear una copia de letrasFilasOriginales para el reordenamiento temporal
    vector<char> letrasFilasOrdenadas = letrasFilasOriginales;

    // Reordenar las filas según el conteo de unos en las copias, sin afectar los originales
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (conteoUnosCopia[i] < conteoUnosCopia[j]) {
                // Intercambiar conteoUnos en la copia
                std::swap(conteoUnosCopia[i], conteoUnosCopia[j]);

                // Intercambiar las filas en la copia de matrizCaminos
                std::swap(matrizCaminosCopia[i], matrizCaminosCopia[j]);

                // Intercambiar las letras en la copia de letrasFilas
                std::swap(letrasFilasOrdenadas[i], letrasFilasOrdenadas[j]);
            }
        }
    }

    // Dibujar las letras de las columnas (A, B, C, ...) en la parte superior usando la copia reordenada
    for (int j = 0; j < n; ++j) {
        String^ letraColumna = gcnew String(letrasFilasOriginales[j], 1);
        graphics->DrawString(letraColumna, font, Brushes::Black, j * cellSize + cellSize, 0);
    }

    // Dibujar cada fila de acuerdo con el nuevo orden basado en la copia reordenada
    for (int i = 0; i < n; ++i) {
        // Dibujar la letra de la fila reordenada
        String^ letraFila = gcnew String(letrasFilasOrdenadas[i], 1);
        graphics->DrawString(letraFila, font, Brushes::Black, 0, i * cellSize + cellSize);

        // Dibujar cada celda de la fila reordenada
        for (int j = 0; j < n; ++j) {
            System::Drawing::Rectangle cellRect(j * cellSize + cellSize, i * cellSize + cellSize, cellSize, cellSize);
            graphics->DrawRectangle(Pens::Black, cellRect);

            String^ texto = matrizCaminosCopia[i][j].ToString();
            graphics->DrawString(texto, font, Brushes::Black, j * cellSize + cellSize, i * cellSize + cellSize);
        }
    }
}


    //       cli::array<cli::array<int>^>^ convertirMatriz(const std::vector<std::vector<int>>& matrizOriginal) {
    //           cli::array<cli::array<int>^>^ matrizCLI = gcnew cli::array<cli::array<int>^>(matrizOriginal.size());
    //           for (size_t i = 0; i < matrizOriginal.size(); ++i) {
    //               matrizCLI[i] = gcnew cli::array<int>(matrizOriginal[i].size());
    //               for (size_t j = 0; j < matrizOriginal[i].size(); ++j) {
    //                   matrizCLI[i][j] = matrizOriginal[i][j];
    //               }
    //           }
    //           return matrizCLI;
    //       }

    //       cli::array<wchar_t>^ convertirLetras(const std::vector<char>& letrasOriginal) {
    //           cli::array<wchar_t>^ letrasCLI = gcnew cli::array<wchar_t>(letrasOriginal.size());
    //           for (size_t i = 0; i < letrasOriginal.size(); ++i) {
    //               letrasCLI[i] = letrasOriginal[i];
    //           }
    //           return letrasCLI;
    //       }
           private: System::Void buttonFullScreen_Click(System::Object^ sender, System::EventArgs^ e) {
               // Convertir matriz reordenada y letras reordenadas a cli::array para pasarlas al formulario en pantalla completa
             

               // Crear y mostrar el formulario en pantalla completa con la matriz y letras reordenadas
           
           }

    private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
    }
private: System::Void Salir_Click(System::Object^ sender, System::EventArgs^ e) {
    this->Close();
}
       private: System::Void btnInfoOriginal_Click(System::Object^ sender, System::EventArgs^ e) {
           MessageBox::Show("Este panel muestra la matriz de adyacencia original del grafo.", "Información del Panel", MessageBoxButtons::OK, MessageBoxIcon::Information);
       }

private: System::Void btnInfoDiagonal_Click(System::Object^ sender, System::EventArgs^ e) {
    MessageBox::Show("Este panel muestra la matriz de adyacencia con la diagonal asegurada a 1s.", "Información del Panel", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

private: System::Void btnInfoCaminos_Click(System::Object^ sender, System::EventArgs^ e) {
    MessageBox::Show("Este panel muestra la matriz de caminos, que representa la conectividad entre nodos.", "Información del Panel", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

private: System::Void btnInfoReordenado_Click(System::Object^ sender, System::EventArgs^ e) {
    MessageBox::Show("Este panel muestra  la cantidad de 1s en cada fila de la matriz.", "Información del Panel", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

private: System::Void btnInfoConteoUnos_Click(System::Object^ sender, System::EventArgs^ e) {
    MessageBox::Show("Este panel muestra el conteo de 1s en cada fila de la matriz, ordenado de mayor a menor.", "Información del Panel", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

private: System::Void btnInfoConvexas_Click(System::Object^ sender, System::EventArgs^ e) {
    MessageBox::Show("Este panel muestra las componentes conexas en el grafo, agrupadas y coloreadas.", "Información del Panel", MessageBoxButtons::OK, MessageBoxIcon::Information);
}
       private: System::Void btnInfoAgrupacion_Click(System::Object^ sender, System::EventArgs^ e) {
           MessageBox::Show(L"Agrupando columnas basadas en el orden de las filas para identificar y organizar componentes conexas. Este proceso permite visualizar las relaciones dentro de la matriz de forma estructurada, destacando grupos de nodos conectados de acuerdo con su proximidad en la matriz.",
               L"Información de Agrupación", MessageBoxButtons::OK, MessageBoxIcon::Information);
       }
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
    MessageBox::Show(L"Marcar casilla en caso quiera ingresar los datos de forma manual, y seguido darle al boton generar, para que se desbloquen los botones 1 y 0 ","Informacion del Panel", MessageBoxButtons::OK, MessageBoxIcon::Information);
}
       

};
}