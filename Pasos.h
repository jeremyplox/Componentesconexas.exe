#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <Windows.h>
#include <string>
#include <array>
#include <map>

using namespace std;
using namespace System::Drawing;
using namespace System::Windows::Forms;

std::vector<std::vector<std::vector<int>>> matricesPorPaso;
std::vector<std::vector<int>> matrizPasos;

namespace Project15 {

    public ref class Pasos : public System::Windows::Forms::Form
    {
    public:
        Pasos(const std::vector<std::vector<int>>& matriz)
        {
            InitializeComponent();
            cargarNuevaMatriz(matriz);
        }

    protected:
        ~Pasos()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        int pasoActual = 0;
        System::ComponentModel::Container^ components;
        System::Windows::Forms::Button^ btnAvanzar;
        System::Windows::Forms::Button^ btnRetroceder;
        System::Windows::Forms::Panel^ panelMatriz;
        System::Windows::Forms::Button^ btnCerrar;
        System::Windows::Forms::Label^ lblTeoriaPropagacion;
        System::Windows::Forms::Panel^ panelInfoScroll;
        System::Windows::Forms::Label^ lblInfoPropagacion;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->btnAvanzar = gcnew System::Windows::Forms::Button();
            this->btnRetroceder = gcnew System::Windows::Forms::Button();
            this->panelMatriz = gcnew System::Windows::Forms::Panel();
            this->btnCerrar = gcnew System::Windows::Forms::Button();
            this->lblInfoPropagacion = gcnew System::Windows::Forms::Label();
            this->lblTeoriaPropagacion = gcnew System::Windows::Forms::Label();
            this->panelInfoScroll = gcnew System::Windows::Forms::Panel();

            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(850, 650);
            this->BackColor = System::Drawing::Color::FromArgb(240, 240, 240);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->StartPosition = FormStartPosition::CenterScreen;
            this->Controls->Add(this->btnAvanzar);
            this->Controls->Add(this->btnRetroceder);
            this->Controls->Add(this->panelMatriz);
            this->Controls->Add(this->btnCerrar);
            this->Controls->Add(this->panelInfoScroll);
            this->Controls->Add(this->lblTeoriaPropagacion);
            this->Text = L"Pasos - Propagación de conexiones";
            this->Load += gcnew System::EventHandler(this, &Pasos::Pasos_Load);

            this->panelMatriz->Location = System::Drawing::Point(20, 20);
            this->panelMatriz->Size = System::Drawing::Size(500, 500);
            this->panelMatriz->BackColor = System::Drawing::Color::LightGray;
            this->panelMatriz->BorderStyle = BorderStyle::FixedSingle;
            this->panelMatriz->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Pasos::panelMatriz_Paint);

            this->panelInfoScroll->Location = System::Drawing::Point(530, 20);
            this->panelInfoScroll->Size = System::Drawing::Size(300, 200);
            this->panelInfoScroll->AutoScroll = true;
            this->panelInfoScroll->BorderStyle = BorderStyle::FixedSingle;
            this->panelInfoScroll->BackColor = System::Drawing::Color::White;

            this->lblInfoPropagacion->AutoSize = true;
            this->lblInfoPropagacion->Font = gcnew System::Drawing::Font(L"Arial", 9, FontStyle::Bold);
            this->lblInfoPropagacion->Text = L"Mostrando matriz de adyacencia con diagonal";
            this->panelInfoScroll->Controls->Add(this->lblInfoPropagacion);

            this->lblTeoriaPropagacion->Location = System::Drawing::Point(530, 250);
            this->lblTeoriaPropagacion->Size = System::Drawing::Size(300, 150);
            this->lblTeoriaPropagacion->Font = gcnew System::Drawing::Font(L"Arial", 8);
            this->lblTeoriaPropagacion->Text = L"Propagación de Conexiones Indirectas en una Matriz de Adyacencia:\n\n"
                L"1. Identificación: Si en una fila hay un ‘1’, localizamos la columna en que está.\n"
                L"2. Propagación: Luego, vamos a la fila de esa columna y copiamos todos los ‘1’ "
                L"encontrados en esa fila a la fila original donde hallamos el primer ‘1’ en la fila.\n"
                L"3. Repetición: Repetimos el proceso para los nuevos ‘1’ encontrados hasta que no haya cambios adicionales.";
            this->lblTeoriaPropagacion->BackColor = System::Drawing::Color::WhiteSmoke;
            this->lblTeoriaPropagacion->BorderStyle = BorderStyle::Fixed3D;

            this->btnCerrar->Location = System::Drawing::Point(640, 500);
            this->btnCerrar->Size = System::Drawing::Size(80, 30);
            this->btnCerrar->Text = L"Cerrar";
            this->btnCerrar->Click += gcnew System::EventHandler(this, &Pasos::btnCerrar_Click);

            this->btnAvanzar->Location = System::Drawing::Point(380, 550);
            this->btnAvanzar->Size = System::Drawing::Size(100, 30);
            this->btnAvanzar->Text = L"Avanzar";
            this->btnAvanzar->BackColor = System::Drawing::Color::LightSteelBlue;
            this->btnAvanzar->Click += gcnew System::EventHandler(this, &Pasos::btnAvanzar_Click);

            this->btnRetroceder->Location = System::Drawing::Point(270, 550);
            this->btnRetroceder->Size = System::Drawing::Size(100, 30);
            this->btnRetroceder->Text = L"Retroceder";
            this->btnRetroceder->BackColor = System::Drawing::Color::LightSteelBlue;
            this->btnRetroceder->Click += gcnew System::EventHandler(this, &Pasos::btnRetroceder_Click);

            this->ResumeLayout(false);
        }
#pragma endregion

        void cargarNuevaMatriz(std::vector<std::vector<int>> matriz)
        {
            for (size_t i = 0; i < matriz.size(); ++i) {
                matriz[i][i] = 1;
            }

            matricesPorPaso.clear();
            pasoActual = 0;

            guardarMatrizOriginal(matriz);
            generarMatricesPorPaso(matriz);
        }

        void guardarMatrizOriginal(const std::vector<std::vector<int>>& matrizOriginal) {
            matricesPorPaso.push_back(matrizOriginal);
        }

        void generarMatricesPorPaso(const std::vector<std::vector<int>>& matrizOriginal) {
            size_t n = matrizOriginal.size();
            std::vector<std::vector<int>> matriz = matrizOriginal;

            for (size_t paso = 0; paso < n; ++paso) {
                std::vector<std::vector<int>> matrizPaso = matricesPorPaso.back(); // Copia del último paso

                // Propagación de conexiones en la fila correspondiente al paso actual
                for (size_t j = 0; j < n; ++j) {
                    if (matrizPaso[paso][j] == 1) {
                        for (size_t k = 0; k < n; ++k) {
                            if (matrizPaso[j][k] == 1 && matrizPaso[paso][k] == 0) {
                                matrizPaso[paso][k] = 1; // Se añade un 1 solo en la fila del paso actual
                            }
                        }
                    }
                }

                matricesPorPaso.push_back(matrizPaso); // Guardamos la matriz actualizada como un nuevo paso
            }
        }

        void mostrarMatrizActual() {
            if (pasoActual == 0) {
                this->lblInfoPropagacion->Text = L"Mostrando matriz de adyacencia con diagonal";
            }
            else {
                actualizarInformacionPropagacion();
            }
            this->panelMatriz->Invalidate();
        }

        void actualizarInformacionPropagacion() {
            std::wstring info = L"Propagación en paso " + std::to_wstring(pasoActual) + L":\n";
            std::vector<std::vector<int>> matrizActual = matricesPorPaso[pasoActual];
            std::vector<std::vector<int>> matrizAnterior = pasoActual > 0 ? matricesPorPaso[pasoActual - 1] : matrizActual;
            bool cambios = false;
            bool filaCambio = false;

            // Revisar únicamente la fila correspondiente al paso actual
            size_t i = pasoActual - 1;
            for (size_t j = 0; j < matrizActual[i].size(); ++j) {
                if (matrizActual[i][j] == 1 && matrizAnterior[i][j] == 0) {
                    for (size_t k = 0; k < matrizActual.size(); ++k) {
                        if (matrizAnterior[i][k] == 1 && matrizAnterior[k][j] == 1) {
                            wchar_t filaLetra = 'A' + i;
                            wchar_t fuenteLetraFila = 'A' + k;
                            wchar_t fuenteLetraColumna = 'A' + j;
                            info += L"Fila " + std::wstring(1, filaLetra) + L" obtiene '1' de Fila " +
                                std::wstring(1, fuenteLetraFila) + L" a través de Columna " +
                                std::wstring(1, fuenteLetraColumna) + L"\n";
                            filaCambio = true;
                            break;
                        }
                    }
                }
            }

            // Agregar mensaje de "no se realiza cambios" si no hubo cambios en la fila actual
            if (!filaCambio) {
                wchar_t letraFila = 'A' + i;
                info += L"En la fila " + std::wstring(1, letraFila) + L" no se realiza cambios\n";
            }

            this->lblInfoPropagacion->Text = gcnew System::String(info.c_str());
        }

        void panelMatriz_Paint(System::Object^ sender, PaintEventArgs^ e) {
            Graphics^ graphics = e->Graphics;
            std::vector<std::vector<int>> matrizActual = matricesPorPaso[pasoActual];
            int cellSize = 20;
            System::Drawing::Font^ font = gcnew System::Drawing::Font(L"Arial", 10);

            for (size_t j = 0; j < matrizActual[0].size(); ++j) {
                char letraColumna = 'A' + j;
                System::String^ letraColumnaString = gcnew System::String(letraColumna, 1);
                graphics->DrawString(letraColumnaString, font, Brushes::Black, j * cellSize + 40, 0);
            }

            for (size_t i = 0; i < matrizActual.size(); ++i) {
                char letraFila = 'A' + i;
                System::String^ letraFilaString = gcnew System::String(letraFila, 1);
                graphics->DrawString(letraFilaString, font, Brushes::Black, 10, i * cellSize + 25);

                for (size_t j = 0; j < matrizActual[i].size(); ++j) {
                    System::Drawing::Rectangle cellRect(j * cellSize + 40, i * cellSize + 20, cellSize, cellSize);

                    if (pasoActual > 0 && i == pasoActual - 1) {
                        graphics->FillRectangle(Brushes::LightBlue, cellRect);
                    }

                    if (pasoActual > 0 && matricesPorPaso[pasoActual][i][j] == 1 && matricesPorPaso[pasoActual - 1][i][j] == 0) {
                        graphics->DrawRectangle(Pens::Red, cellRect);
                    }

                    System::String^ texto = matrizActual[i][j].ToString();
                    graphics->DrawString(texto, font, Brushes::Black, j * cellSize + 40, i * cellSize + 20);
                }
            }

            if (pasoActual > 0 && pasoActual < matrizActual.size()) {
                Pen^ arrowPen = gcnew Pen(Color::Red, 2);
                int arrowStartX = 5;
                int arrowStartY = (pasoActual - 1) * cellSize + 30;
                int arrowEndX = 15;
                int arrowEndY = (pasoActual - 1) * cellSize + 30;
                graphics->DrawLine(arrowPen, arrowStartX, arrowStartY, arrowEndX, arrowEndY);
                graphics->DrawLine(arrowPen, arrowEndX, arrowEndY, arrowEndX - 5, arrowEndY - 5);
                graphics->DrawLine(arrowPen, arrowEndX, arrowEndY, arrowEndX - 5, arrowEndY + 5);
            }
        }

        System::Void btnAvanzar_Click(System::Object^ sender, System::EventArgs^ e) {
            if (pasoActual < matricesPorPaso.size() - 1) {
                pasoActual++;
                mostrarMatrizActual();
            }
        }

        System::Void btnRetroceder_Click(System::Object^ sender, System::EventArgs^ e) {
            if (pasoActual > 0) {
                pasoActual--;
                mostrarMatrizActual();
            }
        }

        System::Void Pasos_Load(System::Object^ sender, System::EventArgs^ e) {
            lblInfoPropagacion->Text = L"Mostrando matriz de adyacencia con diagonal";
            mostrarMatrizActual();
        }

        System::Void btnCerrar_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }
    };
}
