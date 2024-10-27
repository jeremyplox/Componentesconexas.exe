#include <vector>
#include "Form1.h"
#pragma once

namespace CompuTrabajo {
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;

    public ref class FullScreenForm : public Form {
    private:
        cli::array<cli::array<int>^>^ matrizConexaCLI;
        cli::array<wchar_t>^ letrasNodosCLI;

    public:
        FullScreenForm(cli::array<cli::array<int>^>^ matriz, cli::array<wchar_t>^ letras) {
            InitializeComponent();
            matrizConexaCLI = matriz;
            letrasNodosCLI = letras;
        }

    protected:
        ~FullScreenForm() {
            if (components) delete components;
        }

    private:
        System::ComponentModel::Container^ components;

        void InitializeComponent(void) {
            this->Text = L"Grafo de Componentes Conexas - Pantalla Completa";
            this->WindowState = FormWindowState::Maximized;
            this->BackColor = Color::White;
            this->Paint += gcnew PaintEventHandler(this, &FullScreenForm::FullScreenForm_Paint);
            this->KeyDown += gcnew KeyEventHandler(this, &FullScreenForm::FullScreenForm_KeyDown);
        }

        void FullScreenForm_Paint(Object^ sender, PaintEventArgs^ e) {
            Graphics^ graphics = e->Graphics;
            int centerX = this->ClientSize.Width / 2;
            int centerY = this->ClientSize.Height / 2;
            float bigRadius = min(this->ClientSize.Width, this->ClientSize.Height) / 3.0f;
            int radius = 20;

            // Posicionar nodos en un círculo
            cli::array<Point>^ nodePositions = gcnew cli::array<Point>(letrasNodosCLI->Length);
            for (int i = 0; i < letrasNodosCLI->Length; ++i) {
                double angle = 2 * Math::PI * i / letrasNodosCLI->Length;
                int x = centerX + static_cast<int>(bigRadius * cos(angle));
                int y = centerY + static_cast<int>(bigRadius * sin(angle));
                nodePositions[i] = Point(x, y);

                // Dibujar nodo y letra
                graphics->DrawEllipse(Pens::Black, x - radius / 2, y - radius / 2, radius, radius);
                graphics->DrawString(gcnew String(letrasNodosCLI[i], 1), SystemFonts::DefaultFont, Brushes::Black, x - 10, y - 10);
            }

            // Dibujar conexiones
            for (int i = 0; i < matrizConexaCLI->Length; ++i) {
                for (int j = 0; j < matrizConexaCLI[i]->Length; ++j) {
                    if (matrizConexaCLI[i][j] == 1) {
                        Pen^ pen = gcnew Pen(Color::Blue, 2);
                        AdjustableArrowCap^ arrow = gcnew AdjustableArrowCap(5.0f, 5.0f);
                        pen->CustomEndCap = arrow;
                        graphics->DrawLine(pen, nodePositions[i], nodePositions[j]);
                    }
                }
            }
        }

        void FullScreenForm_KeyDown(Object^ sender, KeyEventArgs^ e) {
            if (e->KeyCode == Keys::Escape) {
                this->Close();  // Cerrar al presionar ESC
            }
        }
    };
}
