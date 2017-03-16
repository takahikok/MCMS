#include "SetupADCConnection.h"
#include "SetupADCMeasurement.h"
#include "SetupPlot.h"
#include "tkadc.h"
#include <iostream>
#include <string>
#include <sstream>
#include "clx/ini.h"
#include "clx/ftp.h"
#include <iomanip>
#include <fstream>
#pragma once
#define SETTING_FILE_PATH "settings.ini"

//std::string data_file_name = "ECR00039";
#define data_file_name (std::string)"ECR00039"


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
	private: System::Windows::Forms::ToolStripMenuItem^  �v����~ToolStripMenuItem;
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::ColorDialog^  colorDialog1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
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

	private:
		int Connection(void)
		{
			int error_no;
			if (error_no = DL750->Open(TM_CTL_ETHER, ((*Setting)["DL750"]["IPAddress"] + ",anonymous,").c_str()))
				goto error;
			if (error_no = DL850->Open(TM_CTL_VXI11, (*Setting)["DL850"]["IPAddress"].c_str()))
				goto error;
//			Download750("D7T00000.WVF");
			return 0;
		error:
			return error_no;
		}
		int Download750(std::string filename)
		{
			clx::ftp session((std::string)((*Setting)["DL750"]["IPAddress"]), 21);
//			session.login((std::string)((*Setting)["DL750"]["UserName"].c_str()), (std::string)(clx::base64::decode((*Setting)["DL750"]["Password"].c_str())));
			session.login("ppl", "hs-3900");
			session.cd("HD-0");
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

		template<typename T> int ReadHDRLine(std::string buf, int trace_number, char* key_name, T* data)
		{
			switch (trace_number) {
			case 1:
				sscanf(buf.c_str(), "%s %f", key_name, &(data[0]));
				break;
			case 2:
				sscanf(buf.c_str(), "%s %f %f", key_name, &(data[0]), &(data[1]));
				break;
			case 3:
				sscanf(buf.c_str(), "%s %f %f %f", key_name, &(data[0]), &(data[1]), &(data[2]));
				break;
			case 4:
				sscanf(buf.c_str(), "%s %f %f %f %f", key_name, &(data[0]), &(data[1]), &(data[2]), &(data[3]));
				break;
			}
			return 0;
		}
		template<> int ReadHDRLine(std::string buf, int trace_number, char* key_name, int* data)
		{
			switch (trace_number) {
			case 1:
				sscanf(buf.c_str(), "%s %d", key_name, &(data[0]));
				break;
			case 2:
				sscanf(buf.c_str(), "%s %d %d", key_name, &(data[0]), &(data[1]));
				break;
			case 3:
				sscanf(buf.c_str(), "%s %d %d %d", key_name, &(data[0]), &(data[1]), &(data[2]));
				break;
			case 4:
				sscanf(buf.c_str(), "%s %d %d %d %d", key_name, &(data[0]), &(data[1]), &(data[2]), &(data[3]));
				break;
			}
			return 0;
		}

	public:
		MyForm(clx::ini* Setting_, TKADC* DL750_, TKADC* DL850_)
		{
			InitializeComponent();
			//
			//TODO: �����ɃR���X�g���N�^�[ �R�[�h��ǉ����܂�
			//
//			TKADC* DL850;
//			DL850 = new TKADC;
//			DL850->Close();
			Setting = Setting_;
			DL750 = DL750_;
			DL850 = DL850_;

			if((*Setting)["DL850"]["ConnectOnStartup"] == "Enable")
				if (Connection())
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
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
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
			this->menuStrip1->Padding = System::Windows::Forms::Padding(5, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(308, 31);
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
			this->faToolStripMenuItem->Size = System::Drawing::Size(82, 27);
			this->faToolStripMenuItem->Text = L"�t�@�C��";
			this->faToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::faToolStripMenuItem_Click);
			// 
			// �J��ToolStripMenuItem
			// 
			this->�J��ToolStripMenuItem->Name = L"�J��ToolStripMenuItem";
			this->�J��ToolStripMenuItem->Size = System::Drawing::Size(206, 28);
			this->�J��ToolStripMenuItem->Text = L"�J��";
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(203, 6);
			// 
			// �ۑ�ToolStripMenuItem
			// 
			this->�ۑ�ToolStripMenuItem->Name = L"�ۑ�ToolStripMenuItem";
			this->�ۑ�ToolStripMenuItem->Size = System::Drawing::Size(206, 28);
			this->�ۑ�ToolStripMenuItem->Text = L"�ۑ�";
			this->�ۑ�ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::�ۑ�ToolStripMenuItem_Click);
			// 
			// ���O��t���ĕۑ�ToolStripMenuItem
			// 
			this->���O��t���ĕۑ�ToolStripMenuItem->Name = L"���O��t���ĕۑ�ToolStripMenuItem";
			this->���O��t���ĕۑ�ToolStripMenuItem->Size = System::Drawing::Size(206, 28);
			this->���O��t���ĕۑ�ToolStripMenuItem->Text = L"���O��t���ĕۑ�";
			// 
			// ���ׂĕۑ�ToolStripMenuItem
			// 
			this->���ׂĕۑ�ToolStripMenuItem->Name = L"���ׂĕۑ�ToolStripMenuItem";
			this->���ׂĕۑ�ToolStripMenuItem->Size = System::Drawing::Size(206, 28);
			this->���ׂĕۑ�ToolStripMenuItem->Text = L"���ׂĕۑ�";
			this->���ׂĕۑ�ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::���ׂĕۑ�ToolStripMenuItem_Click);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(203, 6);
			// 
			// �I��ToolStripMenuItem
			// 
			this->�I��ToolStripMenuItem->Name = L"�I��ToolStripMenuItem";
			this->�I��ToolStripMenuItem->Size = System::Drawing::Size(206, 28);
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
			this->toolStripMenuItem1->Size = System::Drawing::Size(52, 27);
			this->toolStripMenuItem1->Text = L"�v��";
			this->toolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::toolStripMenuItem1_Click);
			// 
			// �v���J�nToolStripMenuItem
			// 
			this->�v���J�nToolStripMenuItem->Name = L"�v���J�nToolStripMenuItem";
			this->�v���J�nToolStripMenuItem->Size = System::Drawing::Size(146, 28);
			this->�v���J�nToolStripMenuItem->Text = L"�v���J�n";
			this->�v���J�nToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::�v���J�nToolStripMenuItem_Click);
			// 
			// �v����~ToolStripMenuItem
			// 
			this->�v����~ToolStripMenuItem->Name = L"�v����~ToolStripMenuItem";
			this->�v����~ToolStripMenuItem->Size = System::Drawing::Size(146, 28);
			this->�v����~ToolStripMenuItem->Text = L"�v����~";
			this->�v����~ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::�v����~ToolStripMenuItem_Click);
			// 
			// �v���ݒ�ToolStripMenuItem
			// 
			this->�v���ݒ�ToolStripMenuItem->Name = L"�v���ݒ�ToolStripMenuItem";
			this->�v���ݒ�ToolStripMenuItem->Size = System::Drawing::Size(146, 28);
			this->�v���ݒ�ToolStripMenuItem->Text = L"�v���ݒ�";
			// 
			// �n�[�h�E�F�AToolStripMenuItem
			// 
			this->�n�[�h�E�F�AToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->�v����ڑ�ToolStripMenuItem,
					this->�v����ؒf, this->�v����ڑ��ݒ�ToolStripMenuItem
			});
			this->�n�[�h�E�F�AToolStripMenuItem->Name = L"�n�[�h�E�F�AToolStripMenuItem";
			this->�n�[�h�E�F�AToolStripMenuItem->Size = System::Drawing::Size(52, 27);
			this->�n�[�h�E�F�AToolStripMenuItem->Text = L"�ʐM";
			// 
			// �v����ڑ�ToolStripMenuItem
			// 
			this->�v����ڑ�ToolStripMenuItem->Name = L"�v����ڑ�ToolStripMenuItem";
			this->�v����ڑ�ToolStripMenuItem->Size = System::Drawing::Size(191, 28);
			this->�v����ڑ�ToolStripMenuItem->Text = L"�v����ڑ�";
			this->�v����ڑ�ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::�v����ڑ�ToolStripMenuItem_Click);
			// 
			// �v����ؒf
			// 
			this->�v����ؒf->Name = L"�v����ؒf";
			this->�v����ؒf->Size = System::Drawing::Size(191, 28);
			this->�v����ؒf->Text = L"�v����ؒf";
			this->�v����ؒf->Click += gcnew System::EventHandler(this, &MyForm::toolStripMenuItem2_Click);
			// 
			// �v����ڑ��ݒ�ToolStripMenuItem
			// 
			this->�v����ڑ��ݒ�ToolStripMenuItem->Name = L"�v����ڑ��ݒ�ToolStripMenuItem";
			this->�v����ڑ��ݒ�ToolStripMenuItem->Size = System::Drawing::Size(191, 28);
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
			this->�O���tToolStripMenuItem->Size = System::Drawing::Size(67, 27);
			this->�O���tToolStripMenuItem->Text = L"�O���t";
			// 
			// �O���t�`��ToolStripMenuItem
			// 
			this->�O���t�`��ToolStripMenuItem->Name = L"�O���t�`��ToolStripMenuItem";
			this->�O���t�`��ToolStripMenuItem->Size = System::Drawing::Size(161, 28);
			this->�O���t�`��ToolStripMenuItem->Text = L"�O���t�`��";
			this->�O���t�`��ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::�O���t�`��ToolStripMenuItem_Click);
			// 
			// �O���t�ݒ�ToolStripMenuItem
			// 
			this->�O���t�ݒ�ToolStripMenuItem->Name = L"�O���t�ݒ�ToolStripMenuItem";
			this->�O���t�ݒ�ToolStripMenuItem->Size = System::Drawing::Size(161, 28);
			this->�O���t�ݒ�ToolStripMenuItem->Text = L"�O���t�ݒ�";
			this->�O���t�ݒ�ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::�O���t�ݒ�ToolStripMenuItem_Click);
			// 
			// ���悤�Ȃ�ToolStripMenuItem
			// 
			this->���悤�Ȃ�ToolStripMenuItem->Name = L"���悤�Ȃ�ToolStripMenuItem";
			this->���悤�Ȃ�ToolStripMenuItem->Size = System::Drawing::Size(48, 27);
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
			this->toolStrip1->Location = System::Drawing::Point(4, 0);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(206, 30);
			this->toolStrip1->TabIndex = 1;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// toolStripButton1
			// 
			this->toolStripButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton1.Image")));
			this->toolStripButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton1->Name = L"toolStripButton1";
			this->toolStripButton1->Size = System::Drawing::Size(66, 27);
			this->toolStripButton1->Text = L"��Start";
			this->toolStripButton1->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton1_Click);
			// 
			// toolStripButton2
			// 
			this->toolStripButton2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton2.Image")));
			this->toolStripButton2->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton2->Name = L"toolStripButton2";
			this->toolStripButton2->Size = System::Drawing::Size(63, 27);
			this->toolStripButton2->Text = L"��Stop";
			this->toolStripButton2->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton2_Click);
			// 
			// toolStripButton3
			// 
			this->toolStripButton3->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton3.Image")));
			this->toolStripButton3->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton3->Name = L"toolStripButton3";
			this->toolStripButton3->Size = System::Drawing::Size(65, 27);
			this->toolStripButton3->Text = L"��Save";
			this->toolStripButton3->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton3_Click);
			// 
			// statusStrip1
			// 
			this->statusStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->statusStrip1->Location = System::Drawing::Point(0, 533);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Padding = System::Windows::Forms::Padding(1, 0, 13, 0);
			this->statusStrip1->Size = System::Drawing::Size(782, 22);
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
			this->tabControl1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(776, 468);
			this->tabControl1->TabIndex = 3;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->pictureBox1);
			this->tabPage1->Location = System::Drawing::Point(4, 25);
			this->tabPage1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tabPage1->Size = System::Drawing::Size(768, 439);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"tabPage1";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(244, 188);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// tabPage2
			// 
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tabPage2->Size = System::Drawing::Size(768, 439);
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
			this->toolStripContainer2->ContentPanel->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->toolStripContainer2->ContentPanel->Size = System::Drawing::Size(776, 466);
			this->toolStripContainer2->Location = System::Drawing::Point(0, 32);
			this->toolStripContainer2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->toolStripContainer2->Name = L"toolStripContainer2";
			this->toolStripContainer2->Size = System::Drawing::Size(776, 496);
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
			this->toolStrip2->Location = System::Drawing::Point(370, 0);
			this->toolStrip2->Name = L"toolStrip2";
			this->toolStrip2->Size = System::Drawing::Size(237, 30);
			this->toolStrip2->TabIndex = 2;
			// 
			// toolStripButton4
			// 
			this->toolStripButton4->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton4.Image")));
			this->toolStripButton4->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton4->Name = L"toolStripButton4";
			this->toolStripButton4->Size = System::Drawing::Size(74, 27);
			this->toolStripButton4->Text = L"Connect";
			this->toolStripButton4->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton4_Click);
			// 
			// toolStripButton5
			// 
			this->toolStripButton5->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton5.Image")));
			this->toolStripButton5->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton5->Name = L"toolStripButton5";
			this->toolStripButton5->Size = System::Drawing::Size(151, 27);
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
			this->toolStrip3->Location = System::Drawing::Point(214, 0);
			this->toolStrip3->Name = L"toolStrip3";
			this->toolStrip3->Size = System::Drawing::Size(151, 30);
			this->toolStrip3->TabIndex = 3;
			// 
			// toolStripButton6
			// 
			this->toolStripButton6->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton6->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton6.Image")));
			this->toolStripButton6->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton6->Name = L"toolStripButton6";
			this->toolStripButton6->Size = System::Drawing::Size(42, 27);
			this->toolStripButton6->Text = L"Plot";
			this->toolStripButton6->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton6_Click);
			// 
			// toolStripButton7
			// 
			this->toolStripButton7->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton7->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton7.Image")));
			this->toolStripButton7->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton7->Name = L"toolStripButton7";
			this->toolStripButton7->Size = System::Drawing::Size(97, 27);
			this->toolStripButton7->Text = L"Plot setting";
			this->toolStripButton7->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton7_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(782, 555);
			this->Controls->Add(this->toolStripContainer2);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"MyForm";
			this->Text = L"DT-ALPHA MCMS";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
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
	if (!Connection())
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
//	std::system(((std::string)"wvfconv.exe " + data_file_name + " > " + data_file_name + ".CSV").c_str());
	std::ifstream ifs(data_file_name + ".HDR");
	std::string buf;
	float hresolution;
	float hoffset;
	for (int i = 1; std::getline(ifs, buf); i++) {
		int trace_number;
		char key_name[64];
		int idata[4];
		float fdata[4];

		switch (i) {
		//TraceNumber
		case 13:
			ReadHDRLine(buf, 1, key_name, idata);
			trace_number = idata[0];
			break;

		//HResolution
		case 26:
			ReadHDRLine(buf, trace_number, key_name, fdata);
			hresolution = fdata[0];
			break;

		//HOffset
		case 27:
			ReadHDRLine(buf, trace_number, key_name, fdata);
			hoffset = fdata[0];
			break;
#if 0
		//Date
		case 29:
			ReadHDRLine(buf, trace_number, key_name, fdata);
			hoffset = fdata[0];
			break;

		//Time
		case 30:
			ReadHDRLine(buf, trace_number, key_name, fdata);
			hresolution = fdata[0];
			break;
#endif
		}
	}
//	ShotSetting = new clx::ini(data_file_name + ".ini");

	delete this->pictureBox1->Image;
	std::ofstream of;
	of.open("plot.plt", std::ios::trunc);
	of << "set term png enhanced transparent truecolor font arial 11 size 640, 480" << std::endl;
	of << "set out \"graph1.png\"" << std::endl;
//	of << "plot using " << std::endl;
	of << "set datafile separator \',\'" << std::endl;
	of << "set multiplot " << std::endl;
	of << "set origin 0.0, 0.46" << std::endl;
	of << "set size 1.0, 0.5" << std::endl;
	of << "set lmargin 7.5" << std::endl;
	of << "set rmargin 2" << std::endl;
	of << "set tmargin 0" << std::endl;
	of << "set bmargin 0" << std::endl;
	of << "set label 2 left at graph 0.05,0.9 \"{/Arial (a)} {/Arial:Italic n}_{/Arial e}\"" << std::endl;
	of << "set yrange [*<0:0<*]" << std::endl;
	of << "plot \"" << data_file_name << ".CSV\""
		<< " every 10"
		<< " using (" << hoffset << " + (column(0)) * 10 * " << hresolution << "):7"
		<< " with line" 
		<< std::endl;
	of << "" << std::endl;
	of << "" << std::endl;
	of << "" << std::endl;
	of << "" << std::endl;
	of << "" << std::endl;
	std::system("gnuplot plot.plt");
	this->pictureBox1->Location = System::Drawing::Point(0, 0);
	this->pictureBox1->Size = System::Drawing::Size(640,480);
	this->pictureBox1->Image = dynamic_cast<Image^>(gcnew Bitmap("graph1.png"));
}
private: System::Void toolStripButton6_Click(System::Object^  sender, System::EventArgs^  e) {
	�O���t�`��ToolStripMenuItem_Click(sender, e);
}
private: System::Void toolStripButton7_Click(System::Object^  sender, System::EventArgs^  e) {
	�O���t�ݒ�ToolStripMenuItem_Click(sender, e);
}
};
}
