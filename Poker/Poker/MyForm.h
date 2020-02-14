#pragma once

//TODO:
//animace pri zahozeni karet
//animace pri prihozeni karet na sutl
//dodelani grafiky karet a okoli
//grafika menu
//saving system

#include "Trainer.h"
#include "Player.h"
#include <chrono>
#include <thread>

namespace Poker {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;


	Ref mozek;
	bool isgameon;
	vector <unsigned> topology;
	Player player;
	bool task_complete;
	int akce;
	NN bot;
	bool startgame, preflopplayed, flop, turn, river , vyhodnoceni;
	int i;
	int karta_anim;

	/// <summary>
	/// Souhrn pro MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Sem pøidejte kód konstruktoru.
			//
			srand(time(NULL));

			task_complete = false;
			akce = 0;
			topology.clear();
			topology.push_back(9);
			for (int i = 0; i < 50; i++)
			{
				topology.push_back(30);
			}
			topology.push_back(10);
			topology.push_back(4);
			bot.InitializeComponent(topology, 0);
			startgame = true;
			i = 0;
			preflopplayed = false;
			flop = false;
			turn = false;
			river = false;
			karta_anim = 0;
			vyhodnoceni = false;

		}



	protected:
		/// <summary>
		/// Uvolnìte všechny používané prostøedky.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ MenuPanel;
	protected:

	protected:
	private: System::Windows::Forms::Button^ StartButton;
	private: System::Windows::Forms::Panel^ GamePanel;
	private: System::Windows::Forms::Button^ zpet;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ stul5;
	private: System::Windows::Forms::Label^ stul4;
	private: System::Windows::Forms::Label^ stul3;
	private: System::Windows::Forms::Label^ stul2;
	private: System::Windows::Forms::Label^ stul1;
	private: System::Windows::Forms::Panel^ actionPanel;
	private: System::Windows::Forms::Button^ allin;
	private: System::Windows::Forms::TrackBar^ castka;
	private: System::Windows::Forms::Button^ rise;
	private: System::Windows::Forms::Button^ fold;
	private: System::Windows::Forms::Button^ check;
	private: System::Windows::Forms::Timer^ NewGameTimer;

	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::PictureBox^ karta;
	private: System::Windows::Forms::Timer^ hrac_karta_animace;
	private: System::Windows::Forms::PictureBox^ prvnikarta;
	private: System::Windows::Forms::PictureBox^ druhakarta;
	private: System::Windows::Forms::PictureBox^ enemykarta;
	private: System::Windows::Forms::Timer^ enemy_karta_animce;
	private: System::Windows::Forms::ImageList^ imageList1;
	private: System::Windows::Forms::PictureBox^ enemy_druha_karta;
	private: System::Windows::Forms::PictureBox^ enemy_prvni_karta;
	private: System::Windows::Forms::Timer^ GameTimer;


	private: System::ComponentModel::IContainer^ components;



	private:
		/// <summary>
		/// Vyžaduje se promìnná návrháøe.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda vyžadovaná pro podporu Návrháøe - neupravovat
		/// obsah této metody v editoru kódu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->MenuPanel = (gcnew System::Windows::Forms::Panel());
			this->StartButton = (gcnew System::Windows::Forms::Button());
			this->GamePanel = (gcnew System::Windows::Forms::Panel());
			this->enemy_druha_karta = (gcnew System::Windows::Forms::PictureBox());
			this->enemy_prvni_karta = (gcnew System::Windows::Forms::PictureBox());
			this->druhakarta = (gcnew System::Windows::Forms::PictureBox());
			this->enemykarta = (gcnew System::Windows::Forms::PictureBox());
			this->prvnikarta = (gcnew System::Windows::Forms::PictureBox());
			this->karta = (gcnew System::Windows::Forms::PictureBox());
			this->actionPanel = (gcnew System::Windows::Forms::Panel());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->castka = (gcnew System::Windows::Forms::TrackBar());
			this->rise = (gcnew System::Windows::Forms::Button());
			this->fold = (gcnew System::Windows::Forms::Button());
			this->check = (gcnew System::Windows::Forms::Button());
			this->allin = (gcnew System::Windows::Forms::Button());
			this->stul5 = (gcnew System::Windows::Forms::Label());
			this->stul4 = (gcnew System::Windows::Forms::Label());
			this->stul3 = (gcnew System::Windows::Forms::Label());
			this->stul2 = (gcnew System::Windows::Forms::Label());
			this->stul1 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->zpet = (gcnew System::Windows::Forms::Button());
			this->NewGameTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->hrac_karta_animace = (gcnew System::Windows::Forms::Timer(this->components));
			this->enemy_karta_animce = (gcnew System::Windows::Forms::Timer(this->components));
			this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->GameTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->MenuPanel->SuspendLayout();
			this->GamePanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->enemy_druha_karta))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->enemy_prvni_karta))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->druhakarta))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->enemykarta))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->prvnikarta))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->karta))->BeginInit();
			this->actionPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->castka))->BeginInit();
			this->SuspendLayout();
			// 
			// MenuPanel
			// 
			this->MenuPanel->AutoSize = true;
			this->MenuPanel->Controls->Add(this->StartButton);
			this->MenuPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->MenuPanel->Location = System::Drawing::Point(0, 0);
			this->MenuPanel->Name = L"MenuPanel";
			this->MenuPanel->Size = System::Drawing::Size(984, 511);
			this->MenuPanel->TabIndex = 0;
			// 
			// StartButton
			// 
			this->StartButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->StartButton->Location = System::Drawing::Point(414, 182);
			this->StartButton->Name = L"StartButton";
			this->StartButton->Size = System::Drawing::Size(128, 56);
			this->StartButton->TabIndex = 0;
			this->StartButton->Text = L"Start Game";
			this->StartButton->UseVisualStyleBackColor = true;
			this->StartButton->Click += gcnew System::EventHandler(this, &MyForm::StartButton_Click);
			// 
			// GamePanel
			// 
			this->GamePanel->AutoSize = true;
			this->GamePanel->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->GamePanel->Controls->Add(this->enemy_druha_karta);
			this->GamePanel->Controls->Add(this->enemy_prvni_karta);
			this->GamePanel->Controls->Add(this->druhakarta);
			this->GamePanel->Controls->Add(this->enemykarta);
			this->GamePanel->Controls->Add(this->prvnikarta);
			this->GamePanel->Controls->Add(this->karta);
			this->GamePanel->Controls->Add(this->actionPanel);
			this->GamePanel->Controls->Add(this->stul5);
			this->GamePanel->Controls->Add(this->stul4);
			this->GamePanel->Controls->Add(this->stul3);
			this->GamePanel->Controls->Add(this->stul2);
			this->GamePanel->Controls->Add(this->stul1);
			this->GamePanel->Controls->Add(this->label4);
			this->GamePanel->Controls->Add(this->label3);
			this->GamePanel->Controls->Add(this->label2);
			this->GamePanel->Controls->Add(this->label1);
			this->GamePanel->Controls->Add(this->zpet);
			this->GamePanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->GamePanel->Location = System::Drawing::Point(0, 0);
			this->GamePanel->Name = L"GamePanel";
			this->GamePanel->Size = System::Drawing::Size(984, 511);
			this->GamePanel->TabIndex = 1;
			this->GamePanel->Visible = false;
			this->GamePanel->Enter += gcnew System::EventHandler(this, &MyForm::GamePanel_Enter);
			// 
			// enemy_druha_karta
			// 
			this->enemy_druha_karta->BackColor = System::Drawing::Color::Transparent;
			this->enemy_druha_karta->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->enemy_druha_karta->Location = System::Drawing::Point(471, 33);
			this->enemy_druha_karta->Name = L"enemy_druha_karta";
			this->enemy_druha_karta->Size = System::Drawing::Size(51, 84);
			this->enemy_druha_karta->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->enemy_druha_karta->TabIndex = 20;
			this->enemy_druha_karta->TabStop = false;
			// 
			// enemy_prvni_karta
			// 
			this->enemy_prvni_karta->BackColor = System::Drawing::Color::Transparent;
			this->enemy_prvni_karta->Location = System::Drawing::Point(414, 33);
			this->enemy_prvni_karta->Name = L"enemy_prvni_karta";
			this->enemy_prvni_karta->Size = System::Drawing::Size(51, 84);
			this->enemy_prvni_karta->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->enemy_prvni_karta->TabIndex = 21;
			this->enemy_prvni_karta->TabStop = false;
			// 
			// druhakarta
			// 
			this->druhakarta->BackColor = System::Drawing::Color::Transparent;
			this->druhakarta->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->druhakarta->Location = System::Drawing::Point(471, 336);
			this->druhakarta->Name = L"druhakarta";
			this->druhakarta->Size = System::Drawing::Size(51, 84);
			this->druhakarta->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->druhakarta->TabIndex = 13;
			this->druhakarta->TabStop = false;
			// 
			// enemykarta
			// 
			this->enemykarta->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"enemykarta.Image")));
			this->enemykarta->Location = System::Drawing::Point(442, 182);
			this->enemykarta->Name = L"enemykarta";
			this->enemykarta->Size = System::Drawing::Size(51, 84);
			this->enemykarta->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->enemykarta->TabIndex = 19;
			this->enemykarta->TabStop = false;
			// 
			// prvnikarta
			// 
			this->prvnikarta->BackColor = System::Drawing::Color::Transparent;
			this->prvnikarta->Location = System::Drawing::Point(414, 336);
			this->prvnikarta->Name = L"prvnikarta";
			this->prvnikarta->Size = System::Drawing::Size(51, 84);
			this->prvnikarta->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->prvnikarta->TabIndex = 18;
			this->prvnikarta->TabStop = false;
			// 
			// karta
			// 
			this->karta->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"karta.Image")));
			this->karta->Location = System::Drawing::Point(442, 182);
			this->karta->Name = L"karta";
			this->karta->Size = System::Drawing::Size(51, 84);
			this->karta->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->karta->TabIndex = 12;
			this->karta->TabStop = false;
			// 
			// actionPanel
			// 
			this->actionPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->actionPanel->Controls->Add(this->label10);
			this->actionPanel->Controls->Add(this->castka);
			this->actionPanel->Controls->Add(this->rise);
			this->actionPanel->Controls->Add(this->fold);
			this->actionPanel->Controls->Add(this->check);
			this->actionPanel->Controls->Add(this->allin);
			this->actionPanel->Location = System::Drawing::Point(442, 394);
			this->actionPanel->Name = L"actionPanel";
			this->actionPanel->Size = System::Drawing::Size(517, 105);
			this->actionPanel->TabIndex = 11;
			this->actionPanel->Visible = false;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(323, 76);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(41, 13);
			this->label10->TabIndex = 17;
			this->label10->Text = L"label10";
			// 
			// castka
			// 
			this->castka->Location = System::Drawing::Point(213, 75);
			this->castka->Name = L"castka";
			this->castka->Size = System::Drawing::Size(104, 45);
			this->castka->TabIndex = 16;
			this->castka->TickStyle = System::Windows::Forms::TickStyle::None;
			this->castka->Scroll += gcnew System::EventHandler(this, &MyForm::castka_Scroll);
			// 
			// rise
			// 
			this->rise->Location = System::Drawing::Point(379, 46);
			this->rise->Name = L"rise";
			this->rise->Size = System::Drawing::Size(75, 23);
			this->rise->TabIndex = 15;
			this->rise->Text = L"rise";
			this->rise->UseVisualStyleBackColor = true;
			this->rise->Click += gcnew System::EventHandler(this, &MyForm::rise_Click);
			// 
			// fold
			// 
			this->fold->Location = System::Drawing::Point(276, 46);
			this->fold->Name = L"fold";
			this->fold->Size = System::Drawing::Size(75, 23);
			this->fold->TabIndex = 14;
			this->fold->Text = L"fold";
			this->fold->UseVisualStyleBackColor = true;
			this->fold->Click += gcnew System::EventHandler(this, &MyForm::fold_Click);
			// 
			// check
			// 
			this->check->Location = System::Drawing::Point(170, 46);
			this->check->Name = L"check";
			this->check->Size = System::Drawing::Size(75, 23);
			this->check->TabIndex = 13;
			this->check->Text = L"check";
			this->check->UseVisualStyleBackColor = true;
			this->check->Click += gcnew System::EventHandler(this, &MyForm::check_Click);
			// 
			// allin
			// 
			this->allin->Location = System::Drawing::Point(16, 26);
			this->allin->Name = L"allin";
			this->allin->Size = System::Drawing::Size(125, 63);
			this->allin->TabIndex = 12;
			this->allin->Text = L"all in";
			this->allin->UseVisualStyleBackColor = true;
			this->allin->Click += gcnew System::EventHandler(this, &MyForm::allin_Click);
			// 
			// stul5
			// 
			this->stul5->AutoSize = true;
			this->stul5->Location = System::Drawing::Point(594, 181);
			this->stul5->Name = L"stul5";
			this->stul5->Size = System::Drawing::Size(35, 13);
			this->stul5->TabIndex = 9;
			this->stul5->Text = L"label9";
			// 
			// stul4
			// 
			this->stul4->AutoSize = true;
			this->stul4->Location = System::Drawing::Point(511, 182);
			this->stul4->Name = L"stul4";
			this->stul4->Size = System::Drawing::Size(35, 13);
			this->stul4->TabIndex = 8;
			this->stul4->Text = L"label8";
			// 
			// stul3
			// 
			this->stul3->AutoSize = true;
			this->stul3->Location = System::Drawing::Point(414, 182);
			this->stul3->Name = L"stul3";
			this->stul3->Size = System::Drawing::Size(35, 13);
			this->stul3->TabIndex = 7;
			this->stul3->Text = L"label7";
			// 
			// stul2
			// 
			this->stul2->AutoSize = true;
			this->stul2->Location = System::Drawing::Point(319, 182);
			this->stul2->Name = L"stul2";
			this->stul2->Size = System::Drawing::Size(35, 13);
			this->stul2->TabIndex = 6;
			this->stul2->Text = L"label6";
			// 
			// stul1
			// 
			this->stul1->AutoSize = true;
			this->stul1->Location = System::Drawing::Point(241, 182);
			this->stul1->Name = L"stul1";
			this->stul1->Size = System::Drawing::Size(35, 13);
			this->stul1->TabIndex = 5;
			this->stul1->Text = L"label5";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(785, 44);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(35, 13);
			this->label4->TabIndex = 4;
			this->label4->Text = L"label4";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(652, 43);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(35, 13);
			this->label3->TabIndex = 3;
			this->label3->Text = L"label3";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(258, 43);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"label2";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(124, 44);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"label1";
			// 
			// zpet
			// 
			this->zpet->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->zpet->Location = System::Drawing::Point(48, 412);
			this->zpet->Name = L"zpet";
			this->zpet->Size = System::Drawing::Size(154, 64);
			this->zpet->TabIndex = 0;
			this->zpet->Text = L"button1";
			this->zpet->UseVisualStyleBackColor = true;
			this->zpet->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// NewGameTimer
			// 
			this->NewGameTimer->Tick += gcnew System::EventHandler(this, &MyForm::GameTimer_Tick);
			// 
			// hrac_karta_animace
			// 
			this->hrac_karta_animace->Interval = 20;
			this->hrac_karta_animace->Tick += gcnew System::EventHandler(this, &MyForm::animce_Tick);
			// 
			// enemy_karta_animce
			// 
			this->enemy_karta_animce->Interval = 20;
			this->enemy_karta_animce->Tick += gcnew System::EventHandler(this, &MyForm::enemy_karta_animce_Tick);
			// 
			// imageList1
			// 
			this->imageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList1.ImageStream")));
			this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList1->Images->SetKeyName(0, L"money.png");
			this->imageList1->Images->SetKeyName(1, L"background balck wood.jpg");
			// 
			// GameTimer
			// 
			this->GameTimer->Interval = 500;
			this->GameTimer->Tick += gcnew System::EventHandler(this, &MyForm::GameTimer_Tick_1);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(984, 511);
			this->Controls->Add(this->GamePanel);
			this->Controls->Add(this->MenuPanel);
			this->MinimumSize = System::Drawing::Size(1000, 550);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Poker AI Game";
			this->MenuPanel->ResumeLayout(false);
			this->GamePanel->ResumeLayout(false);
			this->GamePanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->enemy_druha_karta))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->enemy_prvni_karta))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->druhakarta))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->enemykarta))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->prvnikarta))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->karta))->EndInit();
			this->actionPanel->ResumeLayout(false);
			this->actionPanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->castka))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: Void StartButton_Click(Object^ sender, EventArgs^ e) {

		MenuPanel->Visible = false;
		GamePanel->Visible = true;
		GamePanel->Focus();
		/*hrac_karta_animace->Start();
		enemy_karta_animce->Start();*/

	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		MenuPanel->Visible = true;
		GamePanel->Visible = false;
	}
	private: System::Void GamePanel_Enter(System::Object^ sender, System::EventArgs^ e) {

		mozek.rozdani();
		label1->Text = Convert::ToString(mozek.hraci[0].prvnikarta);
		label2->Text = Convert::ToString(mozek.hraci[0].druhakarta);
		isgameon = true;
		NewGameTimer->Start();
	}

	//animace pro rozdani karet hracovi a pote co ji dostane tak se karta otoci a ukaze
	//svoji vlastni hodnotu v podobe jiny textury na jinym piocture boxu
	void karta_deal_animation() {
		karta->Location = Point(karta->Location.X,karta->Location.Y + 10);
		if (karta->Location.Y >= 331)
		{
			hrac_karta_animace->Stop();
			karta->Location = Point(454, 181);
			if (karta_anim == 0)
			{
				label1->Text = Convert::ToString(mozek.hraci[0].prvnikarta);
				prvnikarta->Visible = true;
				prvnikarta->Image = imageList1->Images[1];
			}
			else
			{
				label2->Text = Convert::ToString(mozek.hraci[0].druhakarta);
				druhakarta->Visible = true;
				druhakarta->Image = imageList1->Images[0];
			}
			GamePanel->Refresh();
			karta->Visible = false;
			karta_anim++;
			rozdani_animace_handler();
			//karta->Location = Point(karta->Location.X, 0 - karta->Size.Height);
		}
	}

	//prehraje animaci pro rozdani karet protihracovi
	void enemy_karta_deal_animation() {
		enemykarta->Location = Point(enemykarta->Location.X, enemykarta->Location.Y - 10);
		if (enemykarta->Location.Y <= 14)
		{
			enemy_karta_animce->Stop();
			
			//nastavi karte protihrace texturu pozadi karty

			enemykarta->Location = Point(454, 181);
			enemykarta->Visible = false;
			if (karta_anim == 1)
			{
				enemy_prvni_karta->Visible = true;
				enemy_prvni_karta->Image = imageList1->Images[1];
			}
			else
			{
				enemy_druha_karta->Visible = true;
				enemy_druha_karta->Image = imageList1->Images[0];

			}
			karta_anim++;
			rozdani_animace_handler();
			//karta->Location = Point(karta->Location.X, 0 - karta->Size.Height);
		}
	}


	//resi problemy ohledne animaci pri rozdvani karet na stul
	//neni to nejidealnejsti zpusob ale c++ nenei moc prizpusobeno na forms programovani
	void rozdani_animace_handler() {
		if (hrac_karta_animace->Enabled == true || enemy_karta_animce->Enabled == true)
		{
			return;
		}

 		switch (karta_anim)
		{
		case 0:
		case 2:
			hrac_karta_animace->Start();
			break;
		case 1:
		case 3:
			enemy_karta_animce->Start();
			break;
		default:
			GameTimer->Start();
			break;
		}
	}

		//hlavni hra ktera bude pohanet poker
		void game() {

			   vector<double> input(9), results(4);


			   int tah = mozek.big;

			   if (task_complete == true)
			   {
				   tah = 0;
			   }
			   //----------PREFLOP-----------
			   if (startgame == true)
			   {
				   for (; i < 2; i++)
				   {
					   if (hrac_karta_animace->Enabled == true || enemy_karta_animce->Enabled == true)
						   return;

					   //task_complete = false;
					   if (tah == 0)
					   {
						   if (bot.risnultohlekolo == true && mozek.pot <= bot.vsazeno*2)
						   {
							   i += 2;
							   break;
						   }
						   akce_bota(input, results, mozek, player, bot, akce, i);
						   tah = abs(tah - 1);
					   }
					   else
					   {
						   if (player.risnultohlekolo == true && mozek.pot <= player.vsazeno * 2)
						   {
							   i += 2;
							   break;
						   }
						   akce_hrace();
						   if (task_complete == false)
						   {
							   //i++;
							   break;
						   }
						   else
						   {
							   tah = abs(tah - 1);
							   task_complete = false;
							   zmizeni_akce();
						   }
					   }
				   }
				   if (i >= 2)
				   {
					   if (mozek.tah == "allin")
					   {
						   vyhodnoceni = true;
					   }
					   cout << "Konec preflopu" << endl;
					   i = 0;
					   tah = mozek.big;
					   reset_raise(bot, player);
					   startgame = false;
					   preflopplayed = true;
				   }
			   }
			   //----------FLOPO-----------
			   if (akce == 0 && mozek.tah != "end" && preflopplayed == true)
			   {
				   if (flop == false)
				   {
					   task_complete = false;
					   mozek.cards_flop();
					   stul1->Text = Convert::ToString(mozek.stul[0]);
					   stul2->Text = Convert::ToString(mozek.stul[1]);
					   stul3->Text = Convert::ToString(mozek.stul[2]);
					   GamePanel->Refresh();
					   flop = true;
				   }
				   if (mozek.tah != "allin" || vyhodnoceni == false)
				   {
					   for (; i < 2; i++)
					   {
						   //task_complete = false;
						   if (tah == 0)
						   {
							   if (bot.risnultohlekolo == true && mozek.pot <= bot.vsazeno * 2)
							   {
								   i += 2;
								   break;
							   }
							   akce_bota(input, results, mozek, player, bot, akce+1, i);
							   tah = abs(tah - 1);
						   }
						   else
						   {
							   if (player.risnultohlekolo == true && mozek.pot <= player.vsazeno * 2)
							   {
								   i += 2;
								   break;
							   }
							   akce_hrace();
							   if (task_complete == false)
							   {
								   break;
							   }
							   else
							   {
								   tah = abs(tah - 1);
								   task_complete = false;
								   zmizeni_akce();
							   }
						   }

					   }
				   }
				   else
				   {
					   akce++;
				   }
				   if (i >= 2)
				   {
					   if (mozek.tah == "allin")
					   {
						   vyhodnoceni = true;
					   }
					   cout << "Konec flopu" << endl;
					   i = 0;
					   akce++;
					   tah = mozek.big;
					   reset_raise(bot, player);
				   }
			   }
			   //----------TURN-----------
			   if (akce == 1 && mozek.tah != "end")
			   {
				   if (turn == false)
				   {
					   task_complete = false;
					   mozek.cards_turn_river();
					   stul4->Text = Convert::ToString(mozek.stul[3]);
					   GamePanel->Refresh();
					   turn = true;
					   task_complete = false;
				   }
				   if (mozek.tah != "allin" || vyhodnoceni == false)
				   {
					   for (; i < 2; i++)
					   {
						   //task_complete = false;
						   if (tah == 0)
						   {
							   if (bot.risnultohlekolo == true && mozek.pot <= bot.vsazeno * 2)
							   {
								   i += 2;
								   break;
							   }
							   akce_bota(input, results, mozek, player, bot, akce+1, i);
							   tah = abs(tah - 1);
						   }
						   else
						   {
							   if (player.risnultohlekolo == true && mozek.pot <= player.vsazeno * 2)
							   {
								   i += 2;
								   break;
							   }
							   akce_hrace();
							   if (task_complete == false)
							   {
								   //i++;
								   break;
							   }
							   else
							   {
								   tah = abs(tah - 1);
								   task_complete = false;
								   zmizeni_akce();
							   }
						   }
					   }
				   }
				   else
				   {
					   akce++;
				   }
				   if (i >= 2)
				   {
					   if (mozek.tah == "allin")
					   {
						   vyhodnoceni = true;
					   }
					   cout << "Konec turnu" << endl;
					   i = 0;
					   akce++;
					   tah = mozek.big;
					   reset_raise(bot, player);
				   }
			   }
			   //----------RIVER-----------
			   if (akce == 2 && mozek.tah != "end")
			   {
				   if (river == false)
				   {
					   task_complete = false;
					   mozek.cards_turn_river();
					   stul5->Text = Convert::ToString(mozek.stul[4]);
					   GamePanel->Refresh();
					   river = true;
					   
				   }
				   if (mozek.tah != "allin" || vyhodnoceni == false)
				   {
					   for (; i < 2; i++)
					   {
						   //task_complete = false;
						   if (tah == 0)
						   {
							   if (bot.risnultohlekolo == true && mozek.pot <= bot.vsazeno * 2)
							   {
								   i += 2;
								   break;
							   }
							   akce_bota(input, results, mozek, player, bot, akce+1, i);
							   tah = abs(tah - 1);
						   }
						   else
						   {
							   if (player.risnultohlekolo == true && mozek.pot <= player.vsazeno * 2)
							   {
								   i += 2;
								   break;
							   }
							   akce_hrace();
							   if (task_complete == false)
							   {
								   //i++;
								   break;
							   }
							   else
							   {
								   tah = abs(tah - 1);
								   task_complete = false;
								   zmizeni_akce();
							   }
						   }
					   }
				   }
				   else
				   {
					   akce++;
					   river = true;
				   }
				   if (i >= 2)
				   {
					   if (mozek.tah == "allin")
					   {
						   vyhodnoceni = true;
					   }
					   cout << "Konec riveru" << endl;
					   i = 0;
					   akce++;
					   tah = mozek.big;
					   reset_raise(bot, player);
				   }
			   }



			   //-----------vyhodnceni---------
			   if (preflopplayed == true && (mozek.tah == "end"  || akce > 2))
			   {
				   vyhodnoceni = false;
				   label3->Text = Convert::ToString(mozek.hraci[1].prvnikarta);
				   label4->Text = Convert::ToString(mozek.hraci[1].druhakarta);
				   GamePanel->Refresh();

				   //zahraje se vyhodnoceni hry
				   rozdelenipenez();
			   }


		   }

		//presneji rozdeli penize mezi hrace a bota
		void rozdelenipenez() {
			if (mozek.tah != "end")
			{
				int vyherce = mozek.kombinace(5, 4);
				if (vyherce == 1)
				{
					mozek.vyhra(player,bot, vyherce, player.profit, bot.profit);
					cout << "Vyhral hrac" << mozek.pot << endl;
					//Trenuj(bot, topology);
				}
				else if (vyherce == 2)
				{
					mozek.prohra(bot, player, vyherce, bot.profit, player.profit);
					cout << "vyhral bot " << mozek.pot << endl;
					//Trenuj(player, topology);
				}
				else
				{
					mozek.vyhra(player, bot, vyherce, player.profit, bot.profit);
					cout << "remiza stul v hodnote: " << mozek.pot << endl;
				}

			}
			else if (bot.slozil == true)
			{
				mozek.vyhra(player, bot, 4, player.profit, bot.profit);
			}
			else if (player.slozil == true)
			{
				mozek.prohra(bot, player, 4, bot.profit, player.profit);
			}
			
			if (bot.mena == 0 || player.mena == 0)
			{
				//pokud enkdo prohraje tak se neco stane
				newgame(true);
			}
			else
				newgame(false);

	    }
		//necha vypnout sekci kde ma hrac tlacitka, aby mohl odehrat svuj tah, protoze
		//behem toho co hraje bot
		void zmizeni_akce() {
			actionPanel->Visible = false;
			actionPanel->Refresh();
			GamePanel->Refresh();
		}

		//tato funkce dela prikazy do gamemanageru(mozek), aby vedel co za operaci hrac pozaduje
		void akce_hrace() {
			
			if (bot.slozil == true || player.slozil == true)
			{
				i = 3;
				return;
			}
			actionPanel->Visible = true;
			check->Visible = true;
			allin->Visible = true;
			rise->Visible = true;
			fold->Visible = true;
			if (player.risnultohlekolo == true)
			{
				rise->Visible = false;
			}
			if (mozek.pot /2 > player.vsazeno)
			{
				check->Text = "Call";
			}
			else
			{
				check->Text = "Check";
			}
			if (bot.allin == true)
			{
				if (player.mena > bot.vsazeno)
				{
					rise->Visible = false;
				}
				else
				{
					check->Visible = false;
					rise->Visible = false;
				}
			}
			if (player.vsazeno *2 < mozek.pot)
			{
				castka->Minimum = player.vsazeno * 2 - mozek.pot + 1;
			}
			else
			{
				castka->Minimum = mozek.bigblind;
			}
			castka->Maximum = player.mena;
			castka->LargeChange = player.mena / 4;
			label10->Text = Convert::ToString(castka->Value);
			actionPanel->Refresh();
			GamePanel->Refresh();
			return;
		}

		//vyrestartovani hry  do puvodniho stavu
		//bool uplne_nova znamena jestli hra je uplne nova a nebo jenom je jinej stul, aby se neudelali nejaky malinky zmeny ktery by to pokazily
		void newgame(bool uplne_nova) {
			hrac_karta_animace->Stop();
			enemy_karta_animce->Stop();
			if (uplne_nova == true)
			{
				mozek.big = 0;
				player.mena = 1000;
				bot.mena = 1000;
			}
			else
			{
				mozek.big = abs(mozek.big - 1);
			}		
			mozek.tah = "hra";
			karta->Visible = false;
			enemykarta->Visible = false;
			karta->Location = Point(454, 181);
			enemykarta->Location = Point(454, 181);
			startgame = true;
			task_complete = false;
			player.allin = false;
			player.slozil = false;
			bot.allin = false;
			bot.slozil = false;
			preflopplayed = false;
			flop = false;
			turn = false;
			river = false;
			vyhodnoceni = false;
			akce = 0;
			karta_anim = 0;
			prvnikarta->Visible = false;
			druhakarta->Visible = false;
			enemy_druha_karta->Visible = false;
			enemy_prvni_karta->Visible = false;

			for (int i = 0; i < 2; i++)
			{
				mozek.hraci[i].prvnikarta = -1;
				mozek.hraci[i].druhakarta = -1;
			}
			player.vsazeno = 0;
			bot.vsazeno = 0;
			mozek.pot = 0;
			mozek.stul.clear();
			mozek.odehrane_karty.clear();
			mozek.ruka_vys.clear();
			mozek.rozdani();
			GamePanel->Refresh();
			if (mozek.big == 0)
			{
				i = 0;
				mozek.sazka_hrac(player, 10);
				mozek.sazka(bot, 5);
			}
			else
			{
				i = 0;
				mozek.sazka_hrac(player, 5);
				mozek.sazka(bot, 10);
			}
			reset_raise(bot, player);
			rozdani_animace_handler();

			game();
		}

	private: System::Void GameTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
		NewGameTimer->Stop();
		newgame(true);
	}
	private: System::Void castka_Scroll(System::Object^ sender, System::EventArgs^ e) {
	castka->Minimum = mozek.bigblind;
	castka->Maximum = player.mena;
	castka->LargeChange = player.mena / 4;
	if (castka->Value == player.mena)
	{
		label10->Text = "All in";
	}
	else
	{
		label10->Text = Convert::ToString(castka->Value);
	}
	castka->Refresh();
}
	private: System::Void allin_Click(System::Object^ sender, System::EventArgs^ e) {
	mozek.sazka_hrac(player, 0);
	task_complete = true;
	if (bot.allin == true)
		i = 2;
	else
		i--;

	zmizeni_akce();
	game();
}
	private: System::Void rise_Click(System::Object^ sender, System::EventArgs^ e) {
	mozek.sazka_hrac(player, castka->Value);
	cout << "rise" << endl;
	task_complete = true;
	i--;
	zmizeni_akce();
	game();
}
	private: System::Void fold_Click(System::Object^ sender, System::EventArgs^ e) {
	i = 2;
	mozek.tah = "end";
	player.slozil = true;
	cout << "zahodil" << endl;
	task_complete = true;
	zmizeni_akce();
	game();
}
	private: System::Void check_Click(System::Object^ sender, System::EventArgs^ e) {
	if (mozek.pot / 2 > player.vsazeno && player.allin == false)
	{
		int sazka = mozek.pot - 2 * player.vsazeno;
		if (sazka >= player.mena)
		{
			mozek.sazka_hrac(player, 0);
			cout << "dorovnal all inem" << endl;
			i = 2;
		}
		else
		{
			mozek.sazka_hrac(player, sazka);
			cout << "dorovnal" << endl;
			i += 2;
		}
	}
	else
	{
		cout << "chacknul" << endl;
	}
	task_complete = true;
	zmizeni_akce();
	game();
}
	private: System::Void animce_Tick(System::Object^ sender, System::EventArgs^ e) {
		karta->Visible = true;

		karta_deal_animation();
	}
	private: System::Void enemy_karta_animce_Tick(System::Object^ sender, System::EventArgs^ e) {
		enemykarta->Visible = true;
		enemy_karta_deal_animation();
	}

private: System::Void GameTimer_Tick_1(System::Object^ sender, System::EventArgs^ e) {
	GameTimer->Stop();
	game();
}
};
}
