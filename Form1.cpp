#include "Form1.h"

using namespace System;
using namespace System::Windows::Forms;

void main()

{
	Application::EnableVisualStyles();

	Application::SetCompatibleTextRenderingDefault(false);

	Application::Run(gcnew CompuTrabajo::MyForm()); //PRFormulario es el nombre del proyecto
	matriz.clear();
}