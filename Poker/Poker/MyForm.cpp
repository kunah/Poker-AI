#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")//hide console window

#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThreadAttribute]
void main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	//Poker::MyForm form;
	Application::Run(gcnew Poker::MyForm());
}

