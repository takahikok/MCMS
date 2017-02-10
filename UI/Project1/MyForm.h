#include "SetupADCConnection.h"
#include "tkadc.h"
#include <iostream>
#include <string>
#include <sstream>
#include "clx/ini.h"
#include "clx/ftp.h"
#pragma once


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
	private: System::Windows::Forms::ToolStripButton^  toolStripButton5;

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
			this->menuStrip1->SuspendLayout();
			this->toolStrip1->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->toolStripContainer2->ContentPanel->SuspendLayout();
			this->toolStripContainer2->TopToolStripPanel->SuspendLayout();
			this->toolStripContainer2->SuspendLayout();
			this->toolStrip2->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->faToolStripMenuItem,
					this->toolStripMenuItem1, this->�n�[�h�E�F�AToolStripMenuItem, this->���悤�Ȃ�ToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(802, 31);
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
			this->toolStrip1->Location = System::Drawing::Point(3, 30);
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
			this->statusStrip1->Location = System::Drawing::Point(0, 410);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(802, 22);
			this->statusStrip1->TabIndex = 2;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Location = System::Drawing::Point(8, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(792, 344);
			this->tabControl1->TabIndex = 3;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->pictureBox1);
			this->tabPage1->Location = System::Drawing::Point(4, 25);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(784, 315);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"tabPage1";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(72, 40);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(244, 188);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// tabPage2
			// 
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(784, 315);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"tabPage2";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// toolStripContainer2
			// 
			// 
			// toolStripContainer2.ContentPanel
			// 
			this->toolStripContainer2->ContentPanel->Controls->Add(this->tabControl1);
			this->toolStripContainer2->ContentPanel->Size = System::Drawing::Size(800, 316);
			this->toolStripContainer2->Location = System::Drawing::Point(0, 32);
			this->toolStripContainer2->Name = L"toolStripContainer2";
			this->toolStripContainer2->Size = System::Drawing::Size(800, 376);
			this->toolStripContainer2->TabIndex = 6;
			this->toolStripContainer2->Text = L"toolStripContainer2";
			// 
			// toolStripContainer2.TopToolStripPanel
			// 
			this->toolStripContainer2->TopToolStripPanel->Controls->Add(this->toolStrip2);
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
			this->toolStrip2->Size = System::Drawing::Size(230, 30);
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
			this->toolStripButton5->Size = System::Drawing::Size(144, 27);
			this->toolStripButton5->Text = L"Connection Setup";
			this->toolStripButton5->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton5_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(802, 432);
			this->Controls->Add(this->toolStripContainer2);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
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
	if (!DL850->Close())
		MessageBox::Show("Disconnected!");
	else
		MessageBox::Show("Disconnection failed.");
}
private: System::Void �v����ڑ�ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	if (!DL850->Open(TM_CTL_VXI11, (*Setting)["DL850"]["IPAddress"].c_str()))
		MessageBox::Show("Connect!");
	else
		MessageBox::Show("Connection failed.");
}
private: System::Void ���ׂĕۑ�ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	MessageBox::Show("huge");
}
private: System::Void �v���J�nToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	DL850->Start();
	DL850->WaitADC();
//	DL850->BeginThread();
//	DL850->TermThread();
	DL850->Stop();
//	DL850->WaitADC();
/*	DL850->SaveShot("DL850001");
	clx::ftp session((*Setting)["DL850"]["IPAddress"].c_str(), 21);
	session.login((*Setting)["DL850"]["UserName"], (*Setting)["DL850"]["Password"]);
	session.cd("HD-0");
	session.retrieve("DL850001.WDF", "DL850001.WDF", clx::ftp::binary);
	session.finish();
*/	
}
private: System::Void �v����~ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
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
	clx::ftp session((*Setting)["DL850"]["IPAddress"].c_str(), 21);
	session.login((*Setting)["DL850"]["UserName"], (*Setting)["DL850"]["Password"]);
	session.cd("HD-0");
	session.retrieve("DTB00098.WDF", "DTB00098.WDF", clx::ftp::binary);
	session.finish();
}
private: System::Void toolStripButton3_Click(System::Object^  sender, System::EventArgs^  e) {
	�ۑ�ToolStripMenuItem_Click(sender, e);
}
};
}
