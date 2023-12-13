#pragma once
#include "Clases.hpp"

namespace Juego {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for FrmJuego
	/// </summary>
	public ref class FrmJuego : public System::Windows::Forms::Form
	{
		Graphics^ lienzo;
		Graphics^ gameover;
		Tiempo contador;
		Escenario^ nivel1;
		Jugador^ jugador;
		Dino^ dino;
		BufferedGraphicsContext^ espacioBuffer;
		Int16 c;
	private: System::Windows::Forms::Timer^ timer2;
	private: System::Windows::Forms::Timer^ timer3;
		   BufferedGraphics^ buffer;
	public:
		FrmJuego(void)
		{
			InitializeComponent();
			lienzo = pnlJuego->CreateGraphics();

			jugador = gcnew Jugador(gcnew Bitmap("fighter.png"), 6, 9);
			dino = gcnew Dino(gcnew Bitmap("dino.png"), 6, 9);
			nivel1 = gcnew Escenario(gcnew Bitmap("2.jpg"));
			c = 0;
			espacioBuffer = BufferedGraphicsManager::Current;
			buffer = espacioBuffer->Allocate(lienzo, this->ClientRectangle);
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FrmJuego()
		{
			if (components)
			{
				delete components;
			}
			delete lienzo;
		}
	private: System::Windows::Forms::Panel^ pnlJuego;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;
	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pnlJuego = (gcnew System::Windows::Forms::Panel());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer3 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// pnlJuego
			// 
			this->pnlJuego->Location = System::Drawing::Point(0, 1);
			this->pnlJuego->Margin = System::Windows::Forms::Padding(2);
			this->pnlJuego->Name = L"pnlJuego";
			this->pnlJuego->Size = System::Drawing::Size(844, 537);
			this->pnlJuego->TabIndex = 0;
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &FrmJuego::timer1_Tick);
			// 
			// timer2
			// 
			this->timer2->Tick += gcnew System::EventHandler(this, &FrmJuego::timer2_Tick);
			// 
			// timer3
			// 
			this->timer3->Enabled = true;
			this->timer3->Interval = 1000;
			this->timer3->Tick += gcnew System::EventHandler(this, &FrmJuego::timer3_Tick);
			// 
			// FrmJuego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(845, 538);
			this->Controls->Add(this->pnlJuego);
			this->Margin = System::Windows::Forms::Padding(2);
			this->MaximizeBox = false;
			this->Name = L"FrmJuego";
			this->Text = L"FrmJuego";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &FrmJuego::FrmJuego_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &FrmJuego::FrmJuego_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		nivel1->graficar(buffer->Graphics);

		jugador->graficar(buffer->Graphics);
		jugador->gif();
		jugador->mostrarLineaVida(buffer->Graphics);

		
			dino->graficar(buffer->Graphics);

			dino->moverAutonomo();
		

		


		jugador->mostrarcolision(dino->getRectangle());

		if (jugador->mostrarcolision(dino->getRectangle()) <= 0) {

			timer1->Enabled = false;
		}



		buffer->Render(lienzo);
	}

	private: System::Void FrmJuego_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		jugador->animar();
		switch (e->KeyCode)
		{
		case Keys::Right:nivel1->mover(0); break;
		case Keys::Left:nivel1->mover(1); break;
		case Keys::S:timer2->Enabled = true; break;
		default:break;
		}
	}
	private: System::Void FrmJuego_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		jugador->parar();
		timer2->Enabled = false;
		nivel1->caida();
		//dino->caida();
	}

	private: System::Void timer2_Tick(System::Object^ sender, System::EventArgs^ e) {
		jugador->salto();
		//dino->vertical();
		nivel1->vertical();
		
	}
	private: System::Void timer3_Tick(System::Object^ sender, System::EventArgs^ e) {
		contador.Cuenta(buffer->Graphics);
		if (contador.Verifica(buffer->Graphics) == true) {
			Console::WriteLine("Fin del Juego");
		}
	}
};
}