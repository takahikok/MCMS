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


namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm の概要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private: 
		clx::ini* Setting;
		clx::ini* ShotSetting;

		TKADC* DL750;
		TKADC* DL850;
		TKSHOT* thisShot;
		int picture_box_total_number = 24;

	private: System::Windows::Forms::ToolStripMenuItem^  計測停止ToolStripMenuItem;
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
	private: System::Windows::Forms::ToolStripMenuItem^  グラフToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  グラフ描画ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  グラフ設定ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton6;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton7;
	private: System::Windows::Forms::PictureBox^  pictureBox17;
	private: System::Windows::Forms::PictureBox^  pictureBox18;
	private: System::Windows::Forms::PictureBox^  pictureBox19;
	private: System::Windows::Forms::PictureBox^  pictureBox20;
	private: System::Windows::Forms::PictureBox^  pictureBox21;
	private: System::Windows::Forms::PictureBox^  pictureBox22;
	private: System::Windows::Forms::PictureBox^  pictureBox23;
	private: System::Windows::Forms::PictureBox^  pictureBox24;
	private: System::Windows::Forms::PictureBox^  pictureBox9;
	private: System::Windows::Forms::PictureBox^  pictureBox10;
	private: System::Windows::Forms::PictureBox^  pictureBox11;
	private: System::Windows::Forms::PictureBox^  pictureBox12;
	private: System::Windows::Forms::PictureBox^  pictureBox13;
	private: System::Windows::Forms::PictureBox^  pictureBox14;
	private: System::Windows::Forms::PictureBox^  pictureBox15;
	private: System::Windows::Forms::PictureBox^  pictureBox16;
	private: System::Windows::Forms::PictureBox^  pictureBox5;
	private: System::Windows::Forms::PictureBox^  pictureBox6;
	private: System::Windows::Forms::PictureBox^  pictureBox7;
	private: System::Windows::Forms::PictureBox^  pictureBox8;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton5;


	private:
		array<System::Windows::Forms::PictureBox^>^ pBPlot = gcnew array<System::Windows::Forms::PictureBox^>(32);


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
			//配列化
			{
				int i = 0;
				pBPlot[i++] = (this->pictureBox1);
				pBPlot[i++] = (this->pictureBox2);
				pBPlot[i++] = (this->pictureBox3);
				pBPlot[i++] = (this->pictureBox4);
				pBPlot[i++] = (this->pictureBox5);
				pBPlot[i++] = (this->pictureBox6);
				pBPlot[i++] = (this->pictureBox7);
				pBPlot[i++] = (this->pictureBox8);
				pBPlot[i++] = (this->pictureBox9);
				pBPlot[i++] = (this->pictureBox10);
				pBPlot[i++] = (this->pictureBox11);
				pBPlot[i++] = (this->pictureBox12);
				pBPlot[i++] = (this->pictureBox13);
				pBPlot[i++] = (this->pictureBox14);
				pBPlot[i++] = (this->pictureBox15);
				pBPlot[i++] = (this->pictureBox16);
				pBPlot[i++] = (this->pictureBox17);
				pBPlot[i++] = (this->pictureBox18);
				pBPlot[i++] = (this->pictureBox19);
				pBPlot[i++] = (this->pictureBox20);
				pBPlot[i++] = (this->pictureBox21);
				pBPlot[i++] = (this->pictureBox22);
				pBPlot[i++] = (this->pictureBox23);
				pBPlot[i++] = (this->pictureBox24);
			}
			//
			//TODO: ここにコンストラクター コードを追加します
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
		/// 使用中のリソースをすべてクリーンアップします。
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
	private: System::Windows::Forms::ToolStripMenuItem^  開くToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  保存ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  名前を付けて保存ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  すべて保存ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  ハードウェアToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  計測器接続ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  計測器接続設定ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  計測開始ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  計測設定ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  終了ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  さようならToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  計測器切断;


	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->faToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->開くToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->保存ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->名前を付けて保存ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->すべて保存ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->終了ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->計測開始ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->計測停止ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->計測設定ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ハードウェアToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->計測器接続ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->計測器切断 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->計測器接続設定ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->グラフToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->グラフ描画ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->グラフ設定ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->さようならToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButton1 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton2 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton3 = (gcnew System::Windows::Forms::ToolStripButton());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->pictureBox17 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox18 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox19 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox20 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox21 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox22 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox23 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox24 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox9 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox10 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox11 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox12 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox13 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox14 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox15 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox16 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->toolStripContainer2 = (gcnew System::Windows::Forms::ToolStripContainer());
			this->toolStrip3 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButton6 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton7 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStrip2 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButton4 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton5 = (gcnew System::Windows::Forms::ToolStripButton());
			this->menuStrip1->SuspendLayout();
			this->toolStrip1->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox17))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox18))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox19))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox20))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox21))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox22))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox23))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox24))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox11))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox12))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox13))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox14))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox15))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox16))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->toolStripContainer2->ContentPanel->SuspendLayout();
			this->toolStripContainer2->TopToolStripPanel->SuspendLayout();
			this->toolStripContainer2->SuspendLayout();
			this->toolStrip3->SuspendLayout();
			this->toolStrip2->SuspendLayout();
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
					this->toolStripMenuItem1, this->ハードウェアToolStripMenuItem, this->グラフToolStripMenuItem, this->さようならToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(4, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(231, 26);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			this->menuStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &MyForm::menuStrip1_ItemClicked);
			// 
			// faToolStripMenuItem
			// 
			this->faToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->開くToolStripMenuItem,
					this->toolStripSeparator1, this->保存ToolStripMenuItem, this->名前を付けて保存ToolStripMenuItem, this->すべて保存ToolStripMenuItem, this->toolStripSeparator2,
					this->終了ToolStripMenuItem
			});
			this->faToolStripMenuItem->Name = L"faToolStripMenuItem";
			this->faToolStripMenuItem->Size = System::Drawing::Size(68, 22);
			this->faToolStripMenuItem->Text = L"ファイル";
			this->faToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::faToolStripMenuItem_Click);
			// 
			// 開くToolStripMenuItem
			// 
			this->開くToolStripMenuItem->Name = L"開くToolStripMenuItem";
			this->開くToolStripMenuItem->Size = System::Drawing::Size(172, 22);
			this->開くToolStripMenuItem->Text = L"開く";
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(169, 6);
			// 
			// 保存ToolStripMenuItem
			// 
			this->保存ToolStripMenuItem->Name = L"保存ToolStripMenuItem";
			this->保存ToolStripMenuItem->Size = System::Drawing::Size(172, 22);
			this->保存ToolStripMenuItem->Text = L"保存";
			this->保存ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::保存ToolStripMenuItem_Click);
			// 
			// 名前を付けて保存ToolStripMenuItem
			// 
			this->名前を付けて保存ToolStripMenuItem->Name = L"名前を付けて保存ToolStripMenuItem";
			this->名前を付けて保存ToolStripMenuItem->Size = System::Drawing::Size(172, 22);
			this->名前を付けて保存ToolStripMenuItem->Text = L"名前を付けて保存";
			// 
			// すべて保存ToolStripMenuItem
			// 
			this->すべて保存ToolStripMenuItem->Name = L"すべて保存ToolStripMenuItem";
			this->すべて保存ToolStripMenuItem->Size = System::Drawing::Size(172, 22);
			this->すべて保存ToolStripMenuItem->Text = L"すべて保存";
			this->すべて保存ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::すべて保存ToolStripMenuItem_Click);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(169, 6);
			// 
			// 終了ToolStripMenuItem
			// 
			this->終了ToolStripMenuItem->Name = L"終了ToolStripMenuItem";
			this->終了ToolStripMenuItem->Size = System::Drawing::Size(172, 22);
			this->終了ToolStripMenuItem->Text = L"終了";
			this->終了ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::終了ToolStripMenuItem_Click);
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->計測開始ToolStripMenuItem,
					this->計測停止ToolStripMenuItem, this->計測設定ToolStripMenuItem
			});
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->ShortcutKeyDisplayString = L"";
			this->toolStripMenuItem1->Size = System::Drawing::Size(44, 22);
			this->toolStripMenuItem1->Text = L"計測";
			this->toolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::toolStripMenuItem1_Click);
			// 
			// 計測開始ToolStripMenuItem
			// 
			this->計測開始ToolStripMenuItem->Name = L"計測開始ToolStripMenuItem";
			this->計測開始ToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->計測開始ToolStripMenuItem->Text = L"計測開始";
			this->計測開始ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::計測開始ToolStripMenuItem_Click);
			// 
			// 計測停止ToolStripMenuItem
			// 
			this->計測停止ToolStripMenuItem->Name = L"計測停止ToolStripMenuItem";
			this->計測停止ToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->計測停止ToolStripMenuItem->Text = L"計測停止";
			this->計測停止ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::計測停止ToolStripMenuItem_Click);
			// 
			// 計測設定ToolStripMenuItem
			// 
			this->計測設定ToolStripMenuItem->Name = L"計測設定ToolStripMenuItem";
			this->計測設定ToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->計測設定ToolStripMenuItem->Text = L"計測設定";
			// 
			// ハードウェアToolStripMenuItem
			// 
			this->ハードウェアToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->計測器接続ToolStripMenuItem,
					this->計測器切断, this->計測器接続設定ToolStripMenuItem
			});
			this->ハードウェアToolStripMenuItem->Name = L"ハードウェアToolStripMenuItem";
			this->ハードウェアToolStripMenuItem->Size = System::Drawing::Size(44, 22);
			this->ハードウェアToolStripMenuItem->Text = L"通信";
			// 
			// 計測器接続ToolStripMenuItem
			// 
			this->計測器接続ToolStripMenuItem->Name = L"計測器接続ToolStripMenuItem";
			this->計測器接続ToolStripMenuItem->Size = System::Drawing::Size(160, 22);
			this->計測器接続ToolStripMenuItem->Text = L"計測器接続";
			this->計測器接続ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::計測器接続ToolStripMenuItem_Click);
			// 
			// 計測器切断
			// 
			this->計測器切断->Name = L"計測器切断";
			this->計測器切断->Size = System::Drawing::Size(160, 22);
			this->計測器切断->Text = L"計測器切断";
			this->計測器切断->Click += gcnew System::EventHandler(this, &MyForm::toolStripMenuItem2_Click);
			// 
			// 計測器接続設定ToolStripMenuItem
			// 
			this->計測器接続設定ToolStripMenuItem->Name = L"計測器接続設定ToolStripMenuItem";
			this->計測器接続設定ToolStripMenuItem->Size = System::Drawing::Size(160, 22);
			this->計測器接続設定ToolStripMenuItem->Text = L"計測器接続設定";
			this->計測器接続設定ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::計測器接続設定ToolStripMenuItem_Click);
			// 
			// グラフToolStripMenuItem
			// 
			this->グラフToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->グラフ描画ToolStripMenuItem,
					this->グラフ設定ToolStripMenuItem
			});
			this->グラフToolStripMenuItem->Name = L"グラフToolStripMenuItem";
			this->グラフToolStripMenuItem->Size = System::Drawing::Size(56, 22);
			this->グラフToolStripMenuItem->Text = L"グラフ";
			// 
			// グラフ描画ToolStripMenuItem
			// 
			this->グラフ描画ToolStripMenuItem->Name = L"グラフ描画ToolStripMenuItem";
			this->グラフ描画ToolStripMenuItem->Size = System::Drawing::Size(136, 22);
			this->グラフ描画ToolStripMenuItem->Text = L"グラフ描画";
			this->グラフ描画ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::グラフ描画ToolStripMenuItem_Click);
			// 
			// グラフ設定ToolStripMenuItem
			// 
			this->グラフ設定ToolStripMenuItem->Name = L"グラフ設定ToolStripMenuItem";
			this->グラフ設定ToolStripMenuItem->Size = System::Drawing::Size(136, 22);
			this->グラフ設定ToolStripMenuItem->Text = L"グラフ設定";
			this->グラフ設定ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::グラフ設定ToolStripMenuItem_Click);
			// 
			// さようならToolStripMenuItem
			// 
			this->さようならToolStripMenuItem->Name = L"さようならToolStripMenuItem";
			this->さようならToolStripMenuItem->Size = System::Drawing::Size(41, 22);
			this->さようならToolStripMenuItem->Text = L"bye";
			this->さようならToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::さようならToolStripMenuItem_Click);
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
			this->toolStripButton1->Text = L"＞Start";
			this->toolStripButton1->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton1_Click);
			// 
			// toolStripButton2
			// 
			this->toolStripButton2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton2.Image")));
			this->toolStripButton2->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton2->Name = L"toolStripButton2";
			this->toolStripButton2->Size = System::Drawing::Size(51, 22);
			this->toolStripButton2->Text = L"□Stop";
			this->toolStripButton2->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton2_Click);
			// 
			// toolStripButton3
			// 
			this->toolStripButton3->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton3.Image")));
			this->toolStripButton3->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton3->Name = L"toolStripButton3";
			this->toolStripButton3->Size = System::Drawing::Size(53, 22);
			this->toolStripButton3->Text = L"↓Save";
			this->toolStripButton3->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton3_Click);
			// 
			// statusStrip1
			// 
			this->statusStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->statusStrip1->Location = System::Drawing::Point(0, 422);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Padding = System::Windows::Forms::Padding(1, 0, 10, 0);
			this->statusStrip1->Size = System::Drawing::Size(586, 22);
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
			this->tabControl1->Size = System::Drawing::Size(582, 323);
			this->tabControl1->TabIndex = 3;
			// 
			// tabPage1
			// 
			this->tabPage1->AutoScroll = true;
			this->tabPage1->Controls->Add(this->pictureBox17);
			this->tabPage1->Controls->Add(this->pictureBox18);
			this->tabPage1->Controls->Add(this->pictureBox19);
			this->tabPage1->Controls->Add(this->pictureBox20);
			this->tabPage1->Controls->Add(this->pictureBox21);
			this->tabPage1->Controls->Add(this->pictureBox22);
			this->tabPage1->Controls->Add(this->pictureBox23);
			this->tabPage1->Controls->Add(this->pictureBox24);
			this->tabPage1->Controls->Add(this->pictureBox9);
			this->tabPage1->Controls->Add(this->pictureBox10);
			this->tabPage1->Controls->Add(this->pictureBox11);
			this->tabPage1->Controls->Add(this->pictureBox12);
			this->tabPage1->Controls->Add(this->pictureBox13);
			this->tabPage1->Controls->Add(this->pictureBox14);
			this->tabPage1->Controls->Add(this->pictureBox15);
			this->tabPage1->Controls->Add(this->pictureBox16);
			this->tabPage1->Controls->Add(this->pictureBox5);
			this->tabPage1->Controls->Add(this->pictureBox6);
			this->tabPage1->Controls->Add(this->pictureBox7);
			this->tabPage1->Controls->Add(this->pictureBox8);
			this->tabPage1->Controls->Add(this->pictureBox4);
			this->tabPage1->Controls->Add(this->pictureBox3);
			this->tabPage1->Controls->Add(this->pictureBox2);
			this->tabPage1->Controls->Add(this->pictureBox1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Margin = System::Windows::Forms::Padding(2);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(2);
			this->tabPage1->Size = System::Drawing::Size(574, 297);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"tabPage1";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// pictureBox17
			// 
			this->pictureBox17->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox17.Image")));
			this->pictureBox17->Location = System::Drawing::Point(448, 152);
			this->pictureBox17->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox17->Name = L"pictureBox17";
			this->pictureBox17->Size = System::Drawing::Size(183, 150);
			this->pictureBox17->TabIndex = 24;
			this->pictureBox17->TabStop = false;
			// 
			// pictureBox18
			// 
			this->pictureBox18->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox18.Image")));
			this->pictureBox18->Location = System::Drawing::Point(384, 152);
			this->pictureBox18->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox18->Name = L"pictureBox18";
			this->pictureBox18->Size = System::Drawing::Size(183, 150);
			this->pictureBox18->TabIndex = 23;
			this->pictureBox18->TabStop = false;
			// 
			// pictureBox19
			// 
			this->pictureBox19->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox19.Image")));
			this->pictureBox19->Location = System::Drawing::Point(320, 152);
			this->pictureBox19->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox19->Name = L"pictureBox19";
			this->pictureBox19->Size = System::Drawing::Size(183, 150);
			this->pictureBox19->TabIndex = 22;
			this->pictureBox19->TabStop = false;
			// 
			// pictureBox20
			// 
			this->pictureBox20->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox20.Image")));
			this->pictureBox20->Location = System::Drawing::Point(256, 152);
			this->pictureBox20->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox20->Name = L"pictureBox20";
			this->pictureBox20->Size = System::Drawing::Size(183, 150);
			this->pictureBox20->TabIndex = 21;
			this->pictureBox20->TabStop = false;
			// 
			// pictureBox21
			// 
			this->pictureBox21->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox21.Image")));
			this->pictureBox21->Location = System::Drawing::Point(192, 152);
			this->pictureBox21->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox21->Name = L"pictureBox21";
			this->pictureBox21->Size = System::Drawing::Size(183, 150);
			this->pictureBox21->TabIndex = 20;
			this->pictureBox21->TabStop = false;
			// 
			// pictureBox22
			// 
			this->pictureBox22->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox22.Image")));
			this->pictureBox22->Location = System::Drawing::Point(128, 152);
			this->pictureBox22->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox22->Name = L"pictureBox22";
			this->pictureBox22->Size = System::Drawing::Size(183, 150);
			this->pictureBox22->TabIndex = 19;
			this->pictureBox22->TabStop = false;
			// 
			// pictureBox23
			// 
			this->pictureBox23->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox23.Image")));
			this->pictureBox23->Location = System::Drawing::Point(64, 152);
			this->pictureBox23->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox23->Name = L"pictureBox23";
			this->pictureBox23->Size = System::Drawing::Size(183, 150);
			this->pictureBox23->TabIndex = 18;
			this->pictureBox23->TabStop = false;
			// 
			// pictureBox24
			// 
			this->pictureBox24->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox24.Image")));
			this->pictureBox24->Location = System::Drawing::Point(0, 152);
			this->pictureBox24->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox24->Name = L"pictureBox24";
			this->pictureBox24->Size = System::Drawing::Size(183, 150);
			this->pictureBox24->TabIndex = 17;
			this->pictureBox24->TabStop = false;
			// 
			// pictureBox9
			// 
			this->pictureBox9->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox9.Image")));
			this->pictureBox9->Location = System::Drawing::Point(448, 73);
			this->pictureBox9->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox9->Name = L"pictureBox9";
			this->pictureBox9->Size = System::Drawing::Size(183, 150);
			this->pictureBox9->TabIndex = 16;
			this->pictureBox9->TabStop = false;
			// 
			// pictureBox10
			// 
			this->pictureBox10->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox10.Image")));
			this->pictureBox10->Location = System::Drawing::Point(384, 73);
			this->pictureBox10->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox10->Name = L"pictureBox10";
			this->pictureBox10->Size = System::Drawing::Size(183, 150);
			this->pictureBox10->TabIndex = 15;
			this->pictureBox10->TabStop = false;
			// 
			// pictureBox11
			// 
			this->pictureBox11->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox11.Image")));
			this->pictureBox11->Location = System::Drawing::Point(320, 73);
			this->pictureBox11->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox11->Name = L"pictureBox11";
			this->pictureBox11->Size = System::Drawing::Size(183, 150);
			this->pictureBox11->TabIndex = 14;
			this->pictureBox11->TabStop = false;
			// 
			// pictureBox12
			// 
			this->pictureBox12->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox12.Image")));
			this->pictureBox12->Location = System::Drawing::Point(256, 73);
			this->pictureBox12->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox12->Name = L"pictureBox12";
			this->pictureBox12->Size = System::Drawing::Size(183, 150);
			this->pictureBox12->TabIndex = 13;
			this->pictureBox12->TabStop = false;
			// 
			// pictureBox13
			// 
			this->pictureBox13->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox13.Image")));
			this->pictureBox13->Location = System::Drawing::Point(192, 73);
			this->pictureBox13->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox13->Name = L"pictureBox13";
			this->pictureBox13->Size = System::Drawing::Size(183, 150);
			this->pictureBox13->TabIndex = 12;
			this->pictureBox13->TabStop = false;
			// 
			// pictureBox14
			// 
			this->pictureBox14->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox14.Image")));
			this->pictureBox14->Location = System::Drawing::Point(128, 73);
			this->pictureBox14->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox14->Name = L"pictureBox14";
			this->pictureBox14->Size = System::Drawing::Size(183, 150);
			this->pictureBox14->TabIndex = 11;
			this->pictureBox14->TabStop = false;
			// 
			// pictureBox15
			// 
			this->pictureBox15->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox15.Image")));
			this->pictureBox15->Location = System::Drawing::Point(64, 73);
			this->pictureBox15->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox15->Name = L"pictureBox15";
			this->pictureBox15->Size = System::Drawing::Size(183, 150);
			this->pictureBox15->TabIndex = 10;
			this->pictureBox15->TabStop = false;
			// 
			// pictureBox16
			// 
			this->pictureBox16->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox16.Image")));
			this->pictureBox16->Location = System::Drawing::Point(0, 73);
			this->pictureBox16->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox16->Name = L"pictureBox16";
			this->pictureBox16->Size = System::Drawing::Size(183, 150);
			this->pictureBox16->TabIndex = 9;
			this->pictureBox16->TabStop = false;
			// 
			// pictureBox5
			// 
			this->pictureBox5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox5.Image")));
			this->pictureBox5->Location = System::Drawing::Point(448, 0);
			this->pictureBox5->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(183, 150);
			this->pictureBox5->TabIndex = 8;
			this->pictureBox5->TabStop = false;
			// 
			// pictureBox6
			// 
			this->pictureBox6->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox6.Image")));
			this->pictureBox6->Location = System::Drawing::Point(384, 0);
			this->pictureBox6->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(183, 150);
			this->pictureBox6->TabIndex = 7;
			this->pictureBox6->TabStop = false;
			// 
			// pictureBox7
			// 
			this->pictureBox7->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox7.Image")));
			this->pictureBox7->Location = System::Drawing::Point(320, 0);
			this->pictureBox7->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->Size = System::Drawing::Size(183, 150);
			this->pictureBox7->TabIndex = 6;
			this->pictureBox7->TabStop = false;
			// 
			// pictureBox8
			// 
			this->pictureBox8->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox8.Image")));
			this->pictureBox8->Location = System::Drawing::Point(256, 0);
			this->pictureBox8->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox8->Name = L"pictureBox8";
			this->pictureBox8->Size = System::Drawing::Size(183, 150);
			this->pictureBox8->TabIndex = 5;
			this->pictureBox8->TabStop = false;
			// 
			// pictureBox4
			// 
			this->pictureBox4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.Image")));
			this->pictureBox4->Location = System::Drawing::Point(192, 0);
			this->pictureBox4->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(183, 150);
			this->pictureBox4->TabIndex = 4;
			this->pictureBox4->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.Image")));
			this->pictureBox3->Location = System::Drawing::Point(128, 0);
			this->pictureBox3->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(183, 150);
			this->pictureBox3->TabIndex = 3;
			this->pictureBox3->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(64, 0);
			this->pictureBox2->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(183, 150);
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(183, 150);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// tabPage2
			// 
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Margin = System::Windows::Forms::Padding(2);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(2);
			this->tabPage2->Size = System::Drawing::Size(574, 297);
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
			this->toolStripContainer2->ContentPanel->Size = System::Drawing::Size(582, 322);
			this->toolStripContainer2->Location = System::Drawing::Point(0, 26);
			this->toolStripContainer2->Margin = System::Windows::Forms::Padding(2);
			this->toolStripContainer2->Name = L"toolStripContainer2";
			this->toolStripContainer2->Size = System::Drawing::Size(582, 397);
			this->toolStripContainer2->TabIndex = 6;
			this->toolStripContainer2->Text = L"toolStripContainer2";
			// 
			// toolStripContainer2.TopToolStripPanel
			// 
			this->toolStripContainer2->TopToolStripPanel->Controls->Add(this->toolStrip2);
			this->toolStripContainer2->TopToolStripPanel->Controls->Add(this->toolStrip3);
			this->toolStripContainer2->TopToolStripPanel->Controls->Add(this->toolStrip1);
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
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(586, 444);
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox17))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox18))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox19))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox20))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox21))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox22))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox23))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox24))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox11))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox12))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox13))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox14))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox15))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox16))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->toolStripContainer2->ContentPanel->ResumeLayout(false);
			this->toolStripContainer2->TopToolStripPanel->ResumeLayout(false);
			this->toolStripContainer2->TopToolStripPanel->PerformLayout();
			this->toolStripContainer2->ResumeLayout(false);
			this->toolStripContainer2->PerformLayout();
			this->toolStrip3->ResumeLayout(false);
			this->toolStrip3->PerformLayout();
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
private: System::Void 終了ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Close();
}
private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void 計測器接続設定ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	SetupADCConnection^ f = gcnew SetupADCConnection(Setting);
	f->Show();
}
private: System::Void さようならToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
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
private: System::Void 計測器接続ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	if (!Connection(0))
		MessageBox::Show("Connect!");
	else
		MessageBox::Show("Connection failed.");
}
private: System::Void すべて保存ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	MessageBox::Show("huge");
}
private: System::Void 計測開始ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
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
private: System::Void 計測停止ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	DL750->Stop();
	DL850->Stop();
}
private: System::Void menuStrip1_ItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e) {
}
private: System::Void toolStripButton1_Click(System::Object^  sender, System::EventArgs^  e) {
	計測開始ToolStripMenuItem_Click(sender, e);
}
private: System::Void toolStripButton5_Click(System::Object^  sender, System::EventArgs^  e) {
	計測器接続設定ToolStripMenuItem_Click(sender, e);
}
private: System::Void toolStripButton4_Click(System::Object^  sender, System::EventArgs^  e) {
	計測器接続ToolStripMenuItem_Click(sender, e);
}
private: System::Void toolStripButton2_Click(System::Object^  sender, System::EventArgs^  e) {
	計測停止ToolStripMenuItem_Click(sender, e);
}
private: System::Void 保存ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void toolStripButton3_Click(System::Object^  sender, System::EventArgs^  e) {
	保存ToolStripMenuItem_Click(sender, e);
}
private: System::Void グラフ設定ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	ShotSetting = new clx::ini((data_file_name + ".ini").c_str());
	ShotSetting->insert("This");
	(*ShotSetting)["This"]["FileName"] = data_file_name;
	ShotSetting->write((data_file_name + ".ini").c_str());
	SetupPlot^ f = gcnew SetupPlot(ShotSetting);
	f->Show(); 
}
private: System::Void グラフ描画ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	int total_plot;
	TKSHOT ThisShot;
//	TKSHOT* thisshot = &ThisShot;
	TKPLOT TKPlot(&ThisShot);
#if 0
	ThisShot.AppendDataFile(TKADCINFO_ADC_ID_DL750, data_file_name);
	ThisShot.AppendDataFile(TKADCINFO_ADC_ID_DL850, data_file_name2);
#else
	//Conv
	std::system(((std::string)"wvfconv.exe " + MakeLocalFileName("D7T", DL750->GetLastLocalShotNumber(), 5, "") + " > " + MakeLocalFileName("D7T", DL750->GetLastLocalShotNumber(), 5, "") + ".CSV").c_str());
	std::system(((std::string)"WDFCon.exe " + MakeLocalFileName("D8T", DL850->GetLastLocalShotNumber(), 5, "") + ".WDF").c_str());
	std::system(((std::string)"wvfconv.exe " + MakeLocalFileName("D8T", DL850->GetLastLocalShotNumber(), 5, "") + " > " + MakeLocalFileName("D8T", DL850->GetLastLocalShotNumber(), 5, "") + ".CSV").c_str());
	ThisShot.AppendDataFile(TKADCINFO_ADC_ID_DL750, MakeLocalFileName("D7T", DL750->GetLastLocalShotNumber(), 5, ""));
	ThisShot.AppendDataFile(TKADCINFO_ADC_ID_DL850, MakeLocalFileName("D8T", DL850->GetLastLocalShotNumber(), 5, ""));
#endif
//	std::system(((std::string)"wvfconv.exe " + data_file_name + " > " + data_file_name + ".CSV").c_str());
//	ShotSetting = new clx::ini(data_file_name + ".ini");
	for (int i = 0; i < picture_box_total_number; i++) {
		pBPlot[i]->Visible = false;
		delete pBPlot[i]->Image;
	}
	std::vector<std::string> plot_file_name;
	total_plot = TKPlot.PlotRaw(plot_file_name);
	for (int i = 0; i < total_plot; i++) {
		pBPlot[i]->Location = System::Drawing::Point(i % 3 * 400, i / 3 * 200);
		pBPlot[i]->Size = System::Drawing::Size(400,200);
		pBPlot[i]->Image = dynamic_cast<Image^>(gcnew Bitmap(gcnew System::String((plot_file_name[i] + ".png").c_str())));
		pBPlot[i]->Visible = true;
	}
}
private: System::Void toolStripButton6_Click(System::Object^  sender, System::EventArgs^  e) {
	グラフ描画ToolStripMenuItem_Click(sender, e);
}
private: System::Void toolStripButton7_Click(System::Object^  sender, System::EventArgs^  e) {
	グラフ設定ToolStripMenuItem_Click(sender, e);
}
};
}
