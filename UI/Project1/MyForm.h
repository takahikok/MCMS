#include "SetupADCConnection.h"
#include "SetupADCMeasurement.h"
#include "SetupPlot.h"
#include "tkadc.h"
#include "tkadcinfo.h"
#include "tkshotinfo.h"
#include <iostream>
#include <string>
#include <sstream>
#include "clx/ini.h"
#include "clx/ftp.h"
#include <iomanip>
#include <fstream>
#include <vector>
#pragma once
#define SETTING_FILE_PATH "settings.ini"

//std::string data_file_name = "ECR00039";
#define data_file_name (std::string)"ECR00039"
#define data_file_name2 (std::string)"DTB00200"

#define MAX_PLOT_NUMBER 30


namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm �̊T�v
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private: 
		clx::ini* Setting;
		clx::ini* ShotSetting;

		TKADC* DL750;
		TKADC* DL850;
		TKSHOT* thisShot;
		int picture_box_total_number = MAX_PLOT_NUMBER;

	private: System::Windows::Forms::ToolStripMenuItem^  �v����~ToolStripMenuItem;
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::ColorDialog^  colorDialog1;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton1;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton2;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton3;
	private: System::Windows::Forms::ToolStripContainer^  toolStripContainer2;
	private: System::Windows::Forms::ToolStrip^  toolStrip2;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton4;
	private: System::Windows::Forms::ToolStrip^  toolStrip3;
	private: System::Windows::Forms::ToolStripMenuItem^  �O���tToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �O���t�`��ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �O���t�ݒ�ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton6;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton7;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton5;
	private: System::Windows::Forms::SplitContainer^  splitContainer1;



	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button2;
	private:
		array<System::Windows::Forms::PictureBox^>^ pBPlot = gcnew array<System::Windows::Forms::PictureBox^>(MAX_PLOT_NUMBER);
		array<System::Windows::Forms::PictureBox^>^ pBLine = gcnew array<System::Windows::Forms::PictureBox^>(MAX_PLOT_NUMBER);


	private:
		int Connection(bool on_startup)
		{
			int error_no;
			if (!(on_startup ^ (bool)((*Setting)["DL750"]["ConnectOnStartup"] == "Enable")))
				if ((bool)((*Setting)["DL750"]["Control"] == "Enable"))
					if (error_no = DL750->Open(TM_CTL_ETHER, ((*Setting)["DL750"]["IPAddress"] + ",anonymous,").c_str()))
						goto error;
			if (!(on_startup ^ (bool)((*Setting)["DL850"]["ConnectOnStartup"] == "Enable")))
				if ((bool)((*Setting)["DL850"]["Control"] == "Enable"))
					if (error_no = DL850->Open(TM_CTL_VXI11, (*Setting)["DL850"]["IPAddress"].c_str()))
						goto error;
			return 0;
		error:
			return error_no;
		}
//		Download750("D7T00000.WVF");
		int Download750(std::string filename)
		{
			clx::ftp session((std::string)((*Setting)["DL750"]["IPAddress"]), 21);
			session.login((std::string)((*Setting)["DL750"]["UserName"].c_str()), (std::string)(clx::base64::decode((*Setting)["DL750"]["Password"].c_str())));
//			session.login("ppl", "hs-3900");
//			session.cd("HD-0");
			session.cd((std::string)((*Setting)["DL750"]["StragePath"]));
			session.retrieve(filename, filename, clx::ftp::binary);
			session.finish();
			return 0;
		}
		int Download850(std::string filename)
		{
			clx::ftp session((std::string)((*Setting)["DL850"]["IPAddress"]), 21);
			session.login((std::string)((*Setting)["DL850"]["UserName"].c_str()), (std::string)(clx::base64::decode((*Setting)["DL850"]["Password"].c_str())));
			session.cd("HD-0");
			session.retrieve(filename, filename, clx::ftp::binary);
			session.finish();
			return 0;
		}
		std::string MakeLocalFileName(std::string prefix, int local_shot_number, int shot_number_length, std::string suffix)
		{
			std::ostringstream fname;
			fname << prefix << std::setfill('0') << std::setw(shot_number_length) << std::right << (local_shot_number) << suffix;
			return (std::string)fname.str();
		}

	public:
		MyForm(clx::ini* Setting_, TKSHOT* thisShot_, TKADC* DL750_, TKADC* DL850_)
		{
			InitializeComponent();
			for (int i = 0; i < MAX_PLOT_NUMBER; i++) {
				//Plot
				pBPlot[i] = (gcnew System::Windows::Forms::PictureBox());
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBPlot[i]))->BeginInit();
				this->splitContainer1->Panel1->Controls->Add(pBPlot[i]);
				pBPlot[i]->Location = System::Drawing::Point(184, 24);
				pBPlot[i]->Margin = System::Windows::Forms::Padding(2);
				pBPlot[i]->TabStop = false;
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBPlot[i]))->EndInit();

				//Line
				pBLine[i] = (gcnew System::Windows::Forms::PictureBox());
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBLine[i]))->BeginInit();
				this->splitContainer1->Panel1->Controls->Add(pBLine[i]);
				pBLine[i]->Location = System::Drawing::Point(184, 24);
				pBLine[i]->Margin = System::Windows::Forms::Padding(2);
				pBLine[i]->TabStop = false;
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBLine[i]))->EndInit();
				pBLine[i]->Size = System::Drawing::Size(1, 130);
				Bitmap^ bmpPicBox = gcnew Bitmap(pBLine[i]->Width, pBLine[i]->Height);
				pBLine[i]->Image = bmpPicBox;
				pBLine[i]->BringToFront();

				Graphics^ g = Graphics::FromImage(pBLine[i]->Image);
				Pen^ myPen = gcnew Pen(Color::Red);
				myPen->Width = 5;
				g->DrawLine(myPen, 0, 0, 0, pBLine[i]->Height);
			}

			//
			//TODO: �����ɃR���X�g���N�^�[ �R�[�h��ǉ����܂�
			//
//			TKADC* DL850;
//			DL850 = new TKADC;
//			DL850->Close();
			Setting = Setting_;
			DL750 = DL750_;
			DL850 = DL850_;
//			thisShot = thisShot_;

			if (Connection(1))
				MessageBox::Show("Connection failed.");

			DL750->SetLastLocalShotNumber(std::stoi((*Setting)["DL750"]["LastLocalShotNumber"]));
			DL750->SetLocalShotNumberMax(std::stoi((*Setting)["DL750"]["LocalShotNumberMax"]));
			DL850->SetLastLocalShotNumber(std::stoi((*Setting)["DL850"]["LastLocalShotNumber"]));
			DL850->SetLocalShotNumberMax(std::stoi((*Setting)["DL850"]["LocalShotNumberMax"]));

		}


	protected:
		/// <summary>
		/// �g�p���̃��\�[�X�����ׂăN���[���A�b�v���܂��B
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
			DL750->Close();
			DL850->Close();
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^  faToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �J��ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  �ۑ�ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ���O��t���ĕۑ�ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ���ׂĕۑ�ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  �n�[�h�E�F�AToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �v����ڑ�ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �v����ڑ��ݒ�ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �v���J�nToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �v���ݒ�ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �I��ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ���悤�Ȃ�ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �v����ؒf;


	private:
		/// <summary>
		/// �K�v�ȃf�U�C�i�[�ϐ��ł��B
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �f�U�C�i�[ �T�|�[�g�ɕK�v�ȃ��\�b�h�ł��B���̃��\�b�h�̓��e��
		/// �R�[�h �G�f�B�^�[�ŕύX���Ȃ��ł��������B
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->faToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�J��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->�ۑ�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->���O��t���ĕۑ�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->���ׂĕۑ�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->�I��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�v���J�nToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�v����~ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�v���ݒ�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�n�[�h�E�F�AToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�v����ڑ�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�v����ؒf = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�v����ڑ��ݒ�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�O���tToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�O���t�`��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�O���t�ݒ�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->���悤�Ȃ�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButton1 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton2 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton3 = (gcnew System::Windows::Forms::ToolStripButton());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->toolStripContainer2 = (gcnew System::Windows::Forms::ToolStripContainer());
			this->toolStrip2 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButton4 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton5 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStrip3 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButton6 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton7 = (gcnew System::Windows::Forms::ToolStripButton());
			this->menuStrip1->SuspendLayout();
			this->toolStrip1->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->toolStripContainer2->ContentPanel->SuspendLayout();
			this->toolStripContainer2->TopToolStripPanel->SuspendLayout();
			this->toolStripContainer2->SuspendLayout();
			this->toolStrip2->SuspendLayout();
			this->toolStrip3->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->menuStrip1->Dock = System::Windows::Forms::DockStyle::None;
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->faToolStripMenuItem,
					this->toolStripMenuItem1, this->�n�[�h�E�F�AToolStripMenuItem, this->�O���tToolStripMenuItem, this->���悤�Ȃ�ToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(4, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(259, 26);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			this->menuStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &MyForm::menuStrip1_ItemClicked);
			// 
			// faToolStripMenuItem
			// 
			this->faToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->�J��ToolStripMenuItem,
					this->toolStripSeparator1, this->�ۑ�ToolStripMenuItem, this->���O��t���ĕۑ�ToolStripMenuItem, this->���ׂĕۑ�ToolStripMenuItem, this->toolStripSeparator2,
					this->�I��ToolStripMenuItem
			});
			this->faToolStripMenuItem->Name = L"faToolStripMenuItem";
			this->faToolStripMenuItem->Size = System::Drawing::Size(68, 22);
			this->faToolStripMenuItem->Text = L"�t�@�C��";
			this->faToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::faToolStripMenuItem_Click);
			// 
			// �J��ToolStripMenuItem
			// 
			this->�J��ToolStripMenuItem->Name = L"�J��ToolStripMenuItem";
			this->�J��ToolStripMenuItem->Size = System::Drawing::Size(172, 22);
			this->�J��ToolStripMenuItem->Text = L"�J��";
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(169, 6);
			// 
			// �ۑ�ToolStripMenuItem
			// 
			this->�ۑ�ToolStripMenuItem->Name = L"�ۑ�ToolStripMenuItem";
			this->�ۑ�ToolStripMenuItem->Size = System::Drawing::Size(172, 22);
			this->�ۑ�ToolStripMenuItem->Text = L"�ۑ�";
			this->�ۑ�ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::�ۑ�ToolStripMenuItem_Click);
			// 
			// ���O��t���ĕۑ�ToolStripMenuItem
			// 
			this->���O��t���ĕۑ�ToolStripMenuItem->Name = L"���O��t���ĕۑ�ToolStripMenuItem";
			this->���O��t���ĕۑ�ToolStripMenuItem->Size = System::Drawing::Size(172, 22);
			this->���O��t���ĕۑ�ToolStripMenuItem->Text = L"���O��t���ĕۑ�";
			// 
			// ���ׂĕۑ�ToolStripMenuItem
			// 
			this->���ׂĕۑ�ToolStripMenuItem->Name = L"���ׂĕۑ�ToolStripMenuItem";
			this->���ׂĕۑ�ToolStripMenuItem->Size = System::Drawing::Size(172, 22);
			this->���ׂĕۑ�ToolStripMenuItem->Text = L"���ׂĕۑ�";
			this->���ׂĕۑ�ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::���ׂĕۑ�ToolStripMenuItem_Click);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(169, 6);
			// 
			// �I��ToolStripMenuItem
			// 
			this->�I��ToolStripMenuItem->Name = L"�I��ToolStripMenuItem";
			this->�I��ToolStripMenuItem->Size = System::Drawing::Size(172, 22);
			this->�I��ToolStripMenuItem->Text = L"�I��";
			this->�I��ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::�I��ToolStripMenuItem_Click);
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->�v���J�nToolStripMenuItem,
					this->�v����~ToolStripMenuItem, this->�v���ݒ�ToolStripMenuItem
			});
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->ShortcutKeyDisplayString = L"";
			this->toolStripMenuItem1->Size = System::Drawing::Size(44, 22);
			this->toolStripMenuItem1->Text = L"�v��";
			this->toolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::toolStripMenuItem1_Click);
			// 
			// �v���J�nToolStripMenuItem
			// 
			this->�v���J�nToolStripMenuItem->Name = L"�v���J�nToolStripMenuItem";
			this->�v���J�nToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->�v���J�nToolStripMenuItem->Text = L"�v���J�n";
			this->�v���J�nToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::�v���J�nToolStripMenuItem_Click);
			// 
			// �v����~ToolStripMenuItem
			// 
			this->�v����~ToolStripMenuItem->Name = L"�v����~ToolStripMenuItem";
			this->�v����~ToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->�v����~ToolStripMenuItem->Text = L"�v����~";
			this->�v����~ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::�v����~ToolStripMenuItem_Click);
			// 
			// �v���ݒ�ToolStripMenuItem
			// 
			this->�v���ݒ�ToolStripMenuItem->Name = L"�v���ݒ�ToolStripMenuItem";
			this->�v���ݒ�ToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->�v���ݒ�ToolStripMenuItem->Text = L"�v���ݒ�";
			// 
			// �n�[�h�E�F�AToolStripMenuItem
			// 
			this->�n�[�h�E�F�AToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->�v����ڑ�ToolStripMenuItem,
					this->�v����ؒf, this->�v����ڑ��ݒ�ToolStripMenuItem
			});
			this->�n�[�h�E�F�AToolStripMenuItem->Name = L"�n�[�h�E�F�AToolStripMenuItem";
			this->�n�[�h�E�F�AToolStripMenuItem->Size = System::Drawing::Size(44, 22);
			this->�n�[�h�E�F�AToolStripMenuItem->Text = L"�ʐM";
			// 
			// �v����ڑ�ToolStripMenuItem
			// 
			this->�v����ڑ�ToolStripMenuItem->Name = L"�v����ڑ�ToolStripMenuItem";
			this->�v����ڑ�ToolStripMenuItem->Size = System::Drawing::Size(160, 22);
			this->�v����ڑ�ToolStripMenuItem->Text = L"�v����ڑ�";
			this->�v����ڑ�ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::�v����ڑ�ToolStripMenuItem_Click);
			// 
			// �v����ؒf
			// 
			this->�v����ؒf->Name = L"�v����ؒf";
			this->�v����ؒf->Size = System::Drawing::Size(160, 22);
			this->�v����ؒf->Text = L"�v����ؒf";
			this->�v����ؒf->Click += gcnew System::EventHandler(this, &MyForm::toolStripMenuItem2_Click);
			// 
			// �v����ڑ��ݒ�ToolStripMenuItem
			// 
			this->�v����ڑ��ݒ�ToolStripMenuItem->Name = L"�v����ڑ��ݒ�ToolStripMenuItem";
			this->�v����ڑ��ݒ�ToolStripMenuItem->Size = System::Drawing::Size(160, 22);
			this->�v����ڑ��ݒ�ToolStripMenuItem->Text = L"�v����ڑ��ݒ�";
			this->�v����ڑ��ݒ�ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::�v����ڑ��ݒ�ToolStripMenuItem_Click);
			// 
			// �O���tToolStripMenuItem
			// 
			this->�O���tToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->�O���t�`��ToolStripMenuItem,
					this->�O���t�ݒ�ToolStripMenuItem
			});
			this->�O���tToolStripMenuItem->Name = L"�O���tToolStripMenuItem";
			this->�O���tToolStripMenuItem->Size = System::Drawing::Size(56, 22);
			this->�O���tToolStripMenuItem->Text = L"�O���t";
			// 
			// �O���t�`��ToolStripMenuItem
			// 
			this->�O���t�`��ToolStripMenuItem->Name = L"�O���t�`��ToolStripMenuItem";
			this->�O���t�`��ToolStripMenuItem->Size = System::Drawing::Size(136, 22);
			this->�O���t�`��ToolStripMenuItem->Text = L"�O���t�`��";
			this->�O���t�`��ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::�O���t�`��ToolStripMenuItem_Click);
			// 
			// �O���t�ݒ�ToolStripMenuItem
			// 
			this->�O���t�ݒ�ToolStripMenuItem->Name = L"�O���t�ݒ�ToolStripMenuItem";
			this->�O���t�ݒ�ToolStripMenuItem->Size = System::Drawing::Size(136, 22);
			this->�O���t�ݒ�ToolStripMenuItem->Text = L"�O���t�ݒ�";
			this->�O���t�ݒ�ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::�O���t�ݒ�ToolStripMenuItem_Click);
			// 
			// ���悤�Ȃ�ToolStripMenuItem
			// 
			this->���悤�Ȃ�ToolStripMenuItem->Name = L"���悤�Ȃ�ToolStripMenuItem";
			this->���悤�Ȃ�ToolStripMenuItem->Size = System::Drawing::Size(41, 22);
			this->���悤�Ȃ�ToolStripMenuItem->Text = L"bye";
			this->���悤�Ȃ�ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::���悤�Ȃ�ToolStripMenuItem_Click);
			// 
			// toolStrip1
			// 
			this->toolStrip1->Dock = System::Windows::Forms::DockStyle::None;
			this->toolStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->toolStripButton1,
					this->toolStripButton2, this->toolStripButton3
			});
			this->toolStrip1->Location = System::Drawing::Point(3, 50);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(170, 25);
			this->toolStrip1->TabIndex = 1;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// toolStripButton1
			// 
			this->toolStripButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton1.Image")));
			this->toolStripButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton1->Name = L"toolStripButton1";
			this->toolStripButton1->Size = System::Drawing::Size(54, 22);
			this->toolStripButton1->Text = L"��Start";
			this->toolStripButton1->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton1_Click);
			// 
			// toolStripButton2
			// 
			this->toolStripButton2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton2.Image")));
			this->toolStripButton2->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton2->Name = L"toolStripButton2";
			this->toolStripButton2->Size = System::Drawing::Size(51, 22);
			this->toolStripButton2->Text = L"��Stop";
			this->toolStripButton2->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton2_Click);
			// 
			// toolStripButton3
			// 
			this->toolStripButton3->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton3.Image")));
			this->toolStripButton3->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton3->Name = L"toolStripButton3";
			this->toolStripButton3->Size = System::Drawing::Size(53, 22);
			this->toolStripButton3->Text = L"��Save";
			this->toolStripButton3->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton3_Click);
			// 
			// statusStrip1
			// 
			this->statusStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->statusStrip1->Location = System::Drawing::Point(0, 448);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Padding = System::Windows::Forms::Padding(1, 0, 10, 0);
			this->statusStrip1->Size = System::Drawing::Size(737, 22);
			this->statusStrip1->TabIndex = 2;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// tabControl1
			// 
			this->tabControl1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Margin = System::Windows::Forms::Padding(2);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(733, 349);
			this->tabControl1->TabIndex = 3;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->splitContainer1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Margin = System::Windows::Forms::Padding(0);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Size = System::Drawing::Size(725, 323);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"tabPage1";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
			this->splitContainer1->IsSplitterFixed = true;
			this->splitContainer1->Location = System::Drawing::Point(0, 0);
			this->splitContainer1->Margin = System::Windows::Forms::Padding(0);
			this->splitContainer1->Name = L"splitContainer1";
			this->splitContainer1->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->AutoScroll = true;
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->BackColor = System::Drawing::Color::MediumAquamarine;
			this->splitContainer1->Panel2->Controls->Add(this->numericUpDown1);
			this->splitContainer1->Panel2->Controls->Add(this->button4);
			this->splitContainer1->Panel2->Controls->Add(this->button3);
			this->splitContainer1->Panel2->Controls->Add(this->button2);
			this->splitContainer1->Panel2->Controls->Add(this->button1);
			this->splitContainer1->Size = System::Drawing::Size(725, 323);
			this->splitContainer1->SplitterDistance = 223;
			this->splitContainer1->SplitterWidth = 1;
			this->splitContainer1->TabIndex = 27;
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(152, 48);
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(48, 19);
			this->numericUpDown1->TabIndex = 4;
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &MyForm::numericUpDown1_ValueChanged);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(232, 48);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(23, 23);
			this->button4->TabIndex = 3;
			this->button4->Text = L"��";
			this->button4->UseVisualStyleBackColor = true;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(208, 48);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(23, 23);
			this->button3->TabIndex = 2;
			this->button3->Text = L"<";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(120, 48);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(23, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"<";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(96, 48);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(23, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"��";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// tabPage2
			// 
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Margin = System::Windows::Forms::Padding(2);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(2);
			this->tabPage2->Size = System::Drawing::Size(725, 323);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"tabPage2";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// toolStripContainer2
			// 
			this->toolStripContainer2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			// 
			// toolStripContainer2.BottomToolStripPanel
			// 
			this->toolStripContainer2->BottomToolStripPanel->Enabled = false;
			// 
			// toolStripContainer2.ContentPanel
			// 
			this->toolStripContainer2->ContentPanel->Controls->Add(this->tabControl1);
			this->toolStripContainer2->ContentPanel->Margin = System::Windows::Forms::Padding(2);
			this->toolStripContainer2->ContentPanel->Size = System::Drawing::Size(733, 348);
			this->toolStripContainer2->Location = System::Drawing::Point(0, 26);
			this->toolStripContainer2->Margin = System::Windows::Forms::Padding(2);
			this->toolStripContainer2->Name = L"toolStripContainer2";
			this->toolStripContainer2->Size = System::Drawing::Size(733, 423);
			this->toolStripContainer2->TabIndex = 6;
			this->toolStripContainer2->Text = L"toolStripContainer2";
			// 
			// toolStripContainer2.TopToolStripPanel
			// 
			this->toolStripContainer2->TopToolStripPanel->Controls->Add(this->toolStrip2);
			this->toolStripContainer2->TopToolStripPanel->Controls->Add(this->toolStrip3);
			this->toolStripContainer2->TopToolStripPanel->Controls->Add(this->toolStrip1);
			// 
			// toolStrip2
			// 
			this->toolStrip2->Dock = System::Windows::Forms::DockStyle::None;
			this->toolStrip2->ImageScalingSize = System::Drawing::Size(20, 20);
			this->toolStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->toolStripButton4,
					this->toolStripButton5
			});
			this->toolStrip2->Location = System::Drawing::Point(3, 0);
			this->toolStrip2->Name = L"toolStrip2";
			this->toolStrip2->Size = System::Drawing::Size(191, 25);
			this->toolStrip2->TabIndex = 2;
			// 
			// toolStripButton4
			// 
			this->toolStripButton4->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton4.Image")));
			this->toolStripButton4->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton4->Name = L"toolStripButton4";
			this->toolStripButton4->Size = System::Drawing::Size(59, 22);
			this->toolStripButton4->Text = L"Connect";
			this->toolStripButton4->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton4_Click);
			// 
			// toolStripButton5
			// 
			this->toolStripButton5->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton5.Image")));
			this->toolStripButton5->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton5->Name = L"toolStripButton5";
			this->toolStripButton5->Size = System::Drawing::Size(120, 22);
			this->toolStripButton5->Text = L"Connection setting";
			this->toolStripButton5->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton5_Click);
			// 
			// toolStrip3
			// 
			this->toolStrip3->Dock = System::Windows::Forms::DockStyle::None;
			this->toolStrip3->ImageScalingSize = System::Drawing::Size(20, 20);
			this->toolStrip3->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->toolStripButton6,
					this->toolStripButton7
			});
			this->toolStrip3->Location = System::Drawing::Point(26, 25);
			this->toolStrip3->Name = L"toolStrip3";
			this->toolStrip3->Size = System::Drawing::Size(124, 25);
			this->toolStrip3->TabIndex = 3;
			// 
			// toolStripButton6
			// 
			this->toolStripButton6->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton6->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton6.Image")));
			this->toolStripButton6->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton6->Name = L"toolStripButton6";
			this->toolStripButton6->Size = System::Drawing::Size(34, 22);
			this->toolStripButton6->Text = L"Plot";
			this->toolStripButton6->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton6_Click);
			// 
			// toolStripButton7
			// 
			this->toolStripButton7->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton7->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton7.Image")));
			this->toolStripButton7->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton7->Name = L"toolStripButton7";
			this->toolStripButton7->Size = System::Drawing::Size(78, 22);
			this->toolStripButton7->Text = L"Plot setting";
			this->toolStripButton7->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton7_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(737, 470);
			this->Controls->Add(this->toolStripContainer2);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"MyForm";
			this->Text = L"DT-ALPHA MCMS";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->toolStripContainer2->ContentPanel->ResumeLayout(false);
			this->toolStripContainer2->TopToolStripPanel->ResumeLayout(false);
			this->toolStripContainer2->TopToolStripPanel->PerformLayout();
			this->toolStripContainer2->ResumeLayout(false);
			this->toolStripContainer2->PerformLayout();
			this->toolStrip2->ResumeLayout(false);
			this->toolStrip2->PerformLayout();
			this->toolStrip3->ResumeLayout(false);
			this->toolStrip3->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void faToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void toolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void �I��ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Close();
}
private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void �v����ڑ��ݒ�ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	SetupADCConnection^ f = gcnew SetupADCConnection(Setting);
	f->Show();
}
private: System::Void ���悤�Ȃ�ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Close();
}
private: System::Void toolStripMenuItem2_Click(System::Object^  sender, System::EventArgs^  e) {
	if (!DL750->Close())
		MessageBox::Show("Disconnected!");
	else
		MessageBox::Show("Disconnection failed.");
	if (!DL850->Close())
		MessageBox::Show("Disconnected!");
	else
		MessageBox::Show("Disconnection failed.");
}
private: System::Void �v����ڑ�ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	if (!Connection(0))
		MessageBox::Show("Connect!");
	else
		MessageBox::Show("Connection failed.");
}
private: System::Void ���ׂĕۑ�ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	MessageBox::Show("huge");
}
private: System::Void �v���J�nToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
//	DL750->SetLastLocalShotNumber(0);
//	DL750->SetLocalShotNumberMax(99999);
//	DL850->SetLastLocalShotNumber(0);
//	DL850->SetLocalShotNumberMax(99999);
	DL750->Start();
	DL850->Start();
	DL750->WaitADC();
	DL850->WaitADC();
	//	DL850->Stop();
	DL750->SaveShot(MakeLocalFileName("D7T", DL750->GetNextLocalShotNumber(), 5, ""));
	DL850->SaveShot(MakeLocalFileName("D8T", DL850->GetNextLocalShotNumber(), 5, ""));
	DL750->WaitADC();
	DL850->WaitADC();
	Download750(MakeLocalFileName("D7T", DL750->GetNextLocalShotNumber(), 5, ".WVF"));
	Download750(MakeLocalFileName("D7T", DL750->GetNextLocalShotNumber(), 5, ".HDR"));
	Download850(MakeLocalFileName("D8T", DL850->GetNextLocalShotNumber(), 5, ".WDF"));
	DL750->IncrementLocalShotNumber();
	DL850->IncrementLocalShotNumber();
	(*Setting)["DL750"]["LastLocalShotNumber"] = std::to_string(DL750->GetLastLocalShotNumber());
	(*Setting)["DL850"]["LastLocalShotNumber"] = std::to_string(DL850->GetLastLocalShotNumber());
	Setting->write(SETTING_FILE_PATH);
}
private: System::Void �v����~ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	DL750->Stop();
	DL850->Stop();
}
private: System::Void menuStrip1_ItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e) {
}
private: System::Void toolStripButton1_Click(System::Object^  sender, System::EventArgs^  e) {
	�v���J�nToolStripMenuItem_Click(sender, e);
}
private: System::Void toolStripButton5_Click(System::Object^  sender, System::EventArgs^  e) {
	�v����ڑ��ݒ�ToolStripMenuItem_Click(sender, e);
}
private: System::Void toolStripButton4_Click(System::Object^  sender, System::EventArgs^  e) {
	�v����ڑ�ToolStripMenuItem_Click(sender, e);
}
private: System::Void toolStripButton2_Click(System::Object^  sender, System::EventArgs^  e) {
	�v����~ToolStripMenuItem_Click(sender, e);
}
private: System::Void �ۑ�ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void toolStripButton3_Click(System::Object^  sender, System::EventArgs^  e) {
	�ۑ�ToolStripMenuItem_Click(sender, e);
}
private: System::Void �O���t�ݒ�ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	ShotSetting = new clx::ini((data_file_name + ".ini").c_str());
	ShotSetting->insert("This");
	(*ShotSetting)["This"]["FileName"] = data_file_name;
	ShotSetting->write((data_file_name + ".ini").c_str());
	SetupPlot^ f = gcnew SetupPlot(ShotSetting);
	f->Show(); 
}
private: System::Void �O���t�`��ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	int total_plot;
	TKSHOT ThisShot;
//	TKSHOT* thisshot = &ThisShot;
	TKPLOT TKPlot(&ThisShot);
#if 0
	ThisShot.AppendDataFile(TKADCINFO_ADC_ID_DL750, data_file_name);
	ThisShot.AppendDataFile(TKADCINFO_ADC_ID_DL850, data_file_name2);
#else
	//Conv
//	std::system(((std::string)"wvfconv.exe " + MakeLocalFileName("D7T", DL750->GetLastLocalShotNumber(), 5, "") + " > " + MakeLocalFileName("D7T", DL750->GetLastLocalShotNumber(), 5, "") + ".CSV").c_str());
//	std::system(((std::string)"WDFCon.exe " + MakeLocalFileName("D8T", DL850->GetLastLocalShotNumber(), 5, "") + ".WDF").c_str());
//	std::system(((std::string)"wvfconv.exe " + MakeLocalFileName("D8T", DL850->GetLastLocalShotNumber(), 5, "") + " > " + MakeLocalFileName("D8T", DL850->GetLastLocalShotNumber(), 5, "") + ".CSV").c_str());
	ThisShot.AppendDataFile(TKADCINFO_ADC_ID_DL750, MakeLocalFileName("D7T", DL750->GetLastLocalShotNumber(), 5, ""));
	ThisShot.AppendDataFile(TKADCINFO_ADC_ID_DL850, MakeLocalFileName("D8T", DL850->GetLastLocalShotNumber(), 5, ""));
#endif
//	std::system(((std::string)"wvfconv.exe " + data_file_name + " > " + data_file_name + ".CSV").c_str());
//	ShotSetting = new clx::ini(data_file_name + ".ini");
	for (int i = 0; i < picture_box_total_number; i++) {
		//Plot
		pBPlot[i]->Visible = false;
		delete pBPlot[i]->Image;

		//Line
		pBLine[i]->Visible = false;
	}
	std::vector<std::string> plot_file_name;
	total_plot = TKPlot.PlotRaw(plot_file_name);
	for (int i = 0; i < total_plot; i++) {
		//Plot
		pBPlot[i]->Location = System::Drawing::Point(i % 3 * 400, i / 3 * 200);
		pBPlot[i]->Size = System::Drawing::Size(400,200);
		pBPlot[i]->Image = dynamic_cast<Image^>(gcnew Bitmap(gcnew System::String((plot_file_name[i] + ".png").c_str())));
		pBPlot[i]->Visible = true;

		//Line
		pBLine[i]->Location = System::Drawing::Point((pBPlot[i]->Location).X + 80 + (int)(numericUpDown1->Value), (pBPlot[i]->Location).Y + 20);
		pBLine[i]->Visible = true;
	}
//	pBLine[24]->Location = System::Drawing::Point(184, 24);
}
private: System::Void toolStripButton6_Click(System::Object^  sender, System::EventArgs^  e) {
	�O���t�`��ToolStripMenuItem_Click(sender, e);
}
private: System::Void toolStripButton7_Click(System::Object^  sender, System::EventArgs^  e) {
	�O���t�ݒ�ToolStripMenuItem_Click(sender, e);
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
//	pBLine[24]->Location = System::Drawing::Point(20, 24);
}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
//	pBLine[24]->Location = System::Drawing::Point(40, 24);
}
private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	numericUpDown1->Maximum = 300;
	numericUpDown1->Minimum = 0;
	for (int i = 0; i < 24; i++) {
		pBLine[i]->Location = System::Drawing::Point(pBPlot[i]->Location.X + 80 + (int)(numericUpDown1->Value), pBPlot[i]->Location.Y + 20);
	}
}
};
}
