#pragma once
#include <string>
#include <iostream>
#include "clx/ini.h"
#include "clx/base64.h"
#include "tkutil.h"
#include "tkadc.h"
#include "tkadcinfo.h"
#include "tkshotinfo.h"
#include "tkplot.h"
namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// SetupAnalyzeSP の概要
	/// </summary>
	public ref class SetupAnalyzeSP : public System::Windows::Forms::Form
	{
	private:
		clx::ini* Setting;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::TextBox^  textBox12;
		 TKSHOT* thisShot;
		int SaveSettings(void)
		{
			const char group[] = "AnalyzeSP";

			Setting->insert(group);
			(*Setting)[group]["VGain"] = TKUTIL::SystemStringToString(textBox1->Text).c_str();
			(*Setting)[group]["IR"] = TKUTIL::SystemStringToString(textBox2->Text).c_str();
			(*Setting)[group]["IGain"] = TKUTIL::SystemStringToString(textBox3->Text).c_str();
			(*Setting)[group]["IOffset"] = TKUTIL::SystemStringToString(textBox12->Text).c_str();

			(*Setting)[group]["VChannelIndex"] = std::to_string(comboBox1->SelectedIndex);
			(*Setting)[group]["IChannelIndex"] = std::to_string(comboBox2->SelectedIndex);

			return 0;
		}
		int LoadSettings(void)
		{
			const char group[] = "AnalyzeSP";

			std::vector<TKPLOT::PLOTINFO> plotInfo;

			plotInfo.clear();

			for (int data_index = 0; data_index < thisShot->GetADCNumber(); data_index++) {
				for (int trace_index = 0; trace_index < thisShot->GetTraceTotalNumber(thisShot->GetADCID(data_index));
					trace_index++) {
					TKPLOT::PLOTINFO plot_info;

					plot_info.model_name = thisShot->GetModelName(thisShot->GetADCID(data_index));
					plot_info.channel_number = thisShot->GetChannelNumber(thisShot->GetADCID(data_index), trace_index);
					plot_info.plot_file_name = "PlotRaw_" + plot_info.model_name
						+ "_CH" + std::to_string(plot_info.channel_number);
					plotInfo.push_back(plot_info);
				}
			}

			comboBox1->BeginUpdate();
			for (int i = 0; i < static_cast<int>(plotInfo.size()); i++) {
				comboBox1->Items->Add(gcnew System::String(
					((std::string)"CH" + std::to_string(plotInfo[i].channel_number)
						+ " - " + plotInfo[i].model_name).c_str()));
				comboBox2->Items->Add(gcnew System::String(
					((std::string)"CH" + std::to_string(plotInfo[i].channel_number)
						+ " - " + plotInfo[i].model_name).c_str()));
			}
			comboBox1->EndUpdate();
			
			textBox1->Text = gcnew System::String((*Setting)[group]["VGain"].c_str());
			textBox2->Text = gcnew System::String((*Setting)[group]["IR"].c_str());
			textBox3->Text = gcnew System::String((*Setting)[group]["IGain"].c_str());
			textBox12->Text = gcnew System::String((*Setting)[group]["IOffset"].c_str());

			if (static_cast<int>(plotInfo.size())) {

				if (std::stoi((*Setting)[group]["VChannelIndex"]) >= static_cast<signed int>(plotInfo.size()))
					comboBox1->SelectedIndex = 0;
				else
					comboBox1->SelectedIndex = std::stoi((*Setting)[group]["VChannelIndex"]);

				if (std::stoi((*Setting)[group]["IChannelIndex"]) >= static_cast<signed int>(plotInfo.size()))
					comboBox2->SelectedIndex = 0;
				else
					comboBox2->SelectedIndex = std::stoi((*Setting)[group]["IChannelIndex"]);

			} else {
				comboBox1->SelectedIndex = -1;
				comboBox2->SelectedIndex = -1;
			}

			return 0;
		}
	public:
		SetupAnalyzeSP(clx::ini* Setting_, TKSHOT* thisShot_)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
			Setting = Setting_;
			thisShot = thisShot_;
			this->LoadSettings();
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~SetupAnalyzeSP()
		{
			this->SaveSettings();
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;



	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::TextBox^  textBox9;
	private: System::Windows::Forms::ComboBox^  comboBox3;
	private: System::Windows::Forms::GroupBox^  groupBox6;
	private: System::Windows::Forms::GroupBox^  groupBox8;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::TextBox^  textBox11;
	private: System::Windows::Forms::RadioButton^  radioButton7;
	private: System::Windows::Forms::RadioButton^  radioButton8;
	private: System::Windows::Forms::RadioButton^  radioButton9;
	private: System::Windows::Forms::RadioButton^  radioButton10;
	private: System::Windows::Forms::GroupBox^  groupBox7;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::TextBox^  textBox10;
	private: System::Windows::Forms::RadioButton^  radioButton6;
	private: System::Windows::Forms::RadioButton^  radioButton5;
	private: System::Windows::Forms::RadioButton^  radioButton3;
	private: System::Windows::Forms::RadioButton^  radioButton4;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::GroupBox^  groupBox9;
	private: System::Windows::Forms::RadioButton^  radioButton13;
	private: System::Windows::Forms::RadioButton^  radioButton11;
	private: System::Windows::Forms::RadioButton^  radioButton12;
	protected:

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
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox8 = (gcnew System::Windows::Forms::GroupBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->radioButton7 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton8 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton9 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton10 = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->radioButton6 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton5 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->groupBox9 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton13 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton11 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton12 = (gcnew System::Windows::Forms::RadioButton());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->textBox12 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->groupBox8->SuspendLayout();
			this->groupBox7->SuspendLayout();
			this->groupBox9->SuspendLayout();
			this->SuspendLayout();
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(24, 64);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(152, 23);
			this->comboBox1->TabIndex = 0;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->textBox1);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->comboBox1);
			this->groupBox1->Location = System::Drawing::Point(16, 16);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(320, 104);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"バイアス電圧";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(200, 40);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(71, 15);
			this->label2->TabIndex = 3;
			this->label2->Text = L"測定ゲイン";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(200, 64);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 22);
			this->textBox1->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(24, 40);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(64, 15);
			this->label1->TabIndex = 1;
			this->label1->Text = L"チャンネル";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label17);
			this->groupBox2->Controls->Add(this->textBox12);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Controls->Add(this->textBox3);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->textBox2);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->comboBox2);
			this->groupBox2->Controls->Add(this->groupBox3);
			this->groupBox2->Location = System::Drawing::Point(16, 128);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(440, 184);
			this->groupBox2->TabIndex = 4;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"プローブ電流";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(320, 40);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(71, 15);
			this->label5->TabIndex = 5;
			this->label5->Text = L"測定ゲイン";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(320, 64);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 22);
			this->textBox3->TabIndex = 4;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(200, 40);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(67, 15);
			this->label3->TabIndex = 3;
			this->label3->Text = L"測定抵抗";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(200, 64);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 22);
			this->textBox2->TabIndex = 2;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(24, 40);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(64, 15);
			this->label4->TabIndex = 1;
			this->label4->Text = L"チャンネル";
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Location = System::Drawing::Point(24, 64);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(152, 23);
			this->comboBox2->TabIndex = 0;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->radioButton2);
			this->groupBox3->Controls->Add(this->radioButton1);
			this->groupBox3->Location = System::Drawing::Point(24, 96);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(144, 80);
			this->groupBox3->TabIndex = 9;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"極性";
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(16, 48);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(115, 19);
			this->radioButton2->TabIndex = 10;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"電子電流が正";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(16, 24);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(118, 19);
			this->radioButton1->TabIndex = 9;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"イオン電流が正";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->label11);
			this->groupBox4->Controls->Add(this->textBox7);
			this->groupBox4->Controls->Add(this->label10);
			this->groupBox4->Controls->Add(this->textBox6);
			this->groupBox4->Controls->Add(this->label9);
			this->groupBox4->Controls->Add(this->textBox5);
			this->groupBox4->Controls->Add(this->label8);
			this->groupBox4->Controls->Add(this->label7);
			this->groupBox4->Controls->Add(this->textBox4);
			this->groupBox4->Controls->Add(this->label6);
			this->groupBox4->Location = System::Drawing::Point(480, 16);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(480, 160);
			this->groupBox4->TabIndex = 5;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"ファンクション";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(24, 128);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(412, 15);
			this->label11->TabIndex = 9;
			this->label11->Text = L"(掃引終了時刻) = (掃引開始時刻) + 1 / (周波数) * (掃引波数)";
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(360, 64);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(100, 22);
			this->textBox7->TabIndex = 8;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(360, 40);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(67, 15);
			this->label10->TabIndex = 7;
			this->label10->Text = L"掃引波数";
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(248, 64);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(100, 22);
			this->textBox6->TabIndex = 6;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(248, 40);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(79, 15);
			this->label9->TabIndex = 5;
			this->label9->Text = L"ディレイ波数";
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(136, 64);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(100, 22);
			this->textBox5->TabIndex = 4;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(136, 40);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(84, 15);
			this->label8->TabIndex = 3;
			this->label8->Text = L"周波数 [Hz]";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(24, 104);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(376, 15);
			this->label7->TabIndex = 2;
			this->label7->Text = L"(掃引開始時刻) = (ディレイ) + 1 / (周波数) * (ディレイ波数)";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(24, 64);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(100, 22);
			this->textBox4->TabIndex = 1;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(24, 40);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(82, 15);
			this->label6->TabIndex = 0;
			this->label6->Text = L"ディレイ [ms]";
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->label14);
			this->groupBox5->Controls->Add(this->label12);
			this->groupBox5->Controls->Add(this->textBox8);
			this->groupBox5->Controls->Add(this->label13);
			this->groupBox5->Controls->Add(this->textBox9);
			this->groupBox5->Controls->Add(this->comboBox3);
			this->groupBox5->Location = System::Drawing::Point(176, 352);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(272, 160);
			this->groupBox5->TabIndex = 10;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"プローブチップ";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(24, 32);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(59, 15);
			this->label14->TabIndex = 11;
			this->label14->Text = L"プリセット";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(144, 96);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(69, 15);
			this->label12->TabIndex = 10;
			this->label12->Text = L"長さ [mm]";
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(144, 120);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(100, 22);
			this->textBox8->TabIndex = 9;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(24, 96);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(74, 15);
			this->label13->TabIndex = 8;
			this->label13->Text = L"半径 [mm]";
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(24, 120);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(100, 22);
			this->textBox9->TabIndex = 7;
			// 
			// comboBox3
			// 
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Location = System::Drawing::Point(24, 56);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(224, 23);
			this->comboBox3->TabIndex = 6;
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->groupBox8);
			this->groupBox6->Controls->Add(this->groupBox7);
			this->groupBox6->Location = System::Drawing::Point(480, 192);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(480, 264);
			this->groupBox6->TabIndex = 11;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"解析オプション";
			// 
			// groupBox8
			// 
			this->groupBox8->Controls->Add(this->label16);
			this->groupBox8->Controls->Add(this->textBox11);
			this->groupBox8->Controls->Add(this->radioButton7);
			this->groupBox8->Controls->Add(this->radioButton8);
			this->groupBox8->Controls->Add(this->radioButton9);
			this->groupBox8->Controls->Add(this->radioButton10);
			this->groupBox8->Location = System::Drawing::Point(168, 32);
			this->groupBox8->Name = L"groupBox8";
			this->groupBox8->Size = System::Drawing::Size(128, 192);
			this->groupBox8->TabIndex = 13;
			this->groupBox8->TabStop = false;
			this->groupBox8->Text = L"イオン捕集面積";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(16, 128);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(88, 15);
			this->label16->TabIndex = 12;
			this->label16->Text = L"面積 [mm^2]";
			// 
			// textBox11
			// 
			this->textBox11->Location = System::Drawing::Point(16, 152);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(100, 22);
			this->textBox11->TabIndex = 12;
			// 
			// radioButton7
			// 
			this->radioButton7->AutoSize = true;
			this->radioButton7->Location = System::Drawing::Point(16, 72);
			this->radioButton7->Name = L"radioButton7";
			this->radioButton7->Size = System::Drawing::Size(88, 19);
			this->radioButton7->TabIndex = 12;
			this->radioButton7->TabStop = true;
			this->radioButton7->Text = L"単純円筒";
			this->radioButton7->UseVisualStyleBackColor = true;
			// 
			// radioButton8
			// 
			this->radioButton8->AutoSize = true;
			this->radioButton8->Location = System::Drawing::Point(16, 96);
			this->radioButton8->Name = L"radioButton8";
			this->radioButton8->Size = System::Drawing::Size(88, 19);
			this->radioButton8->TabIndex = 11;
			this->radioButton8->TabStop = true;
			this->radioButton8->Text = L"手動入力";
			this->radioButton8->UseVisualStyleBackColor = true;
			// 
			// radioButton9
			// 
			this->radioButton9->AutoSize = true;
			this->radioButton9->Location = System::Drawing::Point(16, 48);
			this->radioButton9->Name = L"radioButton9";
			this->radioButton9->Size = System::Drawing::Size(44, 19);
			this->radioButton9->TabIndex = 10;
			this->radioButton9->TabStop = true;
			this->radioButton9->Text = L"4rl";
			this->radioButton9->UseVisualStyleBackColor = true;
			// 
			// radioButton10
			// 
			this->radioButton10->AutoSize = true;
			this->radioButton10->Location = System::Drawing::Point(16, 24);
			this->radioButton10->Name = L"radioButton10";
			this->radioButton10->Size = System::Drawing::Size(44, 19);
			this->radioButton10->TabIndex = 9;
			this->radioButton10->TabStop = true;
			this->radioButton10->Text = L"2rl";
			this->radioButton10->UseVisualStyleBackColor = true;
			// 
			// groupBox7
			// 
			this->groupBox7->Controls->Add(this->label15);
			this->groupBox7->Controls->Add(this->textBox10);
			this->groupBox7->Controls->Add(this->radioButton6);
			this->groupBox7->Controls->Add(this->radioButton5);
			this->groupBox7->Controls->Add(this->radioButton3);
			this->groupBox7->Controls->Add(this->radioButton4);
			this->groupBox7->Location = System::Drawing::Point(24, 32);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Size = System::Drawing::Size(128, 192);
			this->groupBox7->TabIndex = 11;
			this->groupBox7->TabStop = false;
			this->groupBox7->Text = L"電子捕集面積";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(16, 128);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(88, 15);
			this->label15->TabIndex = 12;
			this->label15->Text = L"面積 [mm^2]";
			// 
			// textBox10
			// 
			this->textBox10->Location = System::Drawing::Point(16, 152);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(100, 22);
			this->textBox10->TabIndex = 12;
			// 
			// radioButton6
			// 
			this->radioButton6->AutoSize = true;
			this->radioButton6->Location = System::Drawing::Point(16, 72);
			this->radioButton6->Name = L"radioButton6";
			this->radioButton6->Size = System::Drawing::Size(88, 19);
			this->radioButton6->TabIndex = 12;
			this->radioButton6->TabStop = true;
			this->radioButton6->Text = L"単純円筒";
			this->radioButton6->UseVisualStyleBackColor = true;
			// 
			// radioButton5
			// 
			this->radioButton5->AutoSize = true;
			this->radioButton5->Location = System::Drawing::Point(16, 96);
			this->radioButton5->Name = L"radioButton5";
			this->radioButton5->Size = System::Drawing::Size(88, 19);
			this->radioButton5->TabIndex = 11;
			this->radioButton5->TabStop = true;
			this->radioButton5->Text = L"手動入力";
			this->radioButton5->UseVisualStyleBackColor = true;
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(16, 48);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(44, 19);
			this->radioButton3->TabIndex = 10;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"4rl";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// radioButton4
			// 
			this->radioButton4->AutoSize = true;
			this->radioButton4->Location = System::Drawing::Point(16, 24);
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->Size = System::Drawing::Size(44, 19);
			this->radioButton4->TabIndex = 9;
			this->radioButton4->TabStop = true;
			this->radioButton4->Text = L"2rl";
			this->radioButton4->UseVisualStyleBackColor = true;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(680, 536);
			this->button3->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(100, 29);
			this->button3->TabIndex = 14;
			this->button3->Text = L"OK";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &SetupAnalyzeSP::button3_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(794, 536);
			this->button2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(100, 29);
			this->button2->TabIndex = 13;
			this->button2->Text = L"適用";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &SetupAnalyzeSP::button2_Click);
			// 
			// button1
			// 
			this->button1->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button1->Location = System::Drawing::Point(904, 536);
			this->button1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(100, 29);
			this->button1->TabIndex = 12;
			this->button1->Text = L"キャンセル";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &SetupAnalyzeSP::button1_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(16, 536);
			this->button4->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(100, 29);
			this->button4->TabIndex = 15;
			this->button4->Text = L"保存";
			this->button4->UseVisualStyleBackColor = true;
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(128, 536);
			this->button5->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(100, 29);
			this->button5->TabIndex = 16;
			this->button5->Text = L"読込";
			this->button5->UseVisualStyleBackColor = true;
			// 
			// groupBox9
			// 
			this->groupBox9->Controls->Add(this->radioButton13);
			this->groupBox9->Controls->Add(this->radioButton11);
			this->groupBox9->Controls->Add(this->radioButton12);
			this->groupBox9->Location = System::Drawing::Point(16, 344);
			this->groupBox9->Name = L"groupBox9";
			this->groupBox9->Size = System::Drawing::Size(144, 160);
			this->groupBox9->TabIndex = 11;
			this->groupBox9->TabStop = false;
			this->groupBox9->Text = L"ガス種";
			// 
			// radioButton13
			// 
			this->radioButton13->AutoSize = true;
			this->radioButton13->Location = System::Drawing::Point(16, 72);
			this->radioButton13->Name = L"radioButton13";
			this->radioButton13->Size = System::Drawing::Size(37, 19);
			this->radioButton13->TabIndex = 11;
			this->radioButton13->TabStop = true;
			this->radioButton13->Text = L"P";
			this->radioButton13->UseVisualStyleBackColor = true;
			// 
			// radioButton11
			// 
			this->radioButton11->AutoSize = true;
			this->radioButton11->Location = System::Drawing::Point(16, 24);
			this->radioButton11->Name = L"radioButton11";
			this->radioButton11->Size = System::Drawing::Size(42, 19);
			this->radioButton11->TabIndex = 10;
			this->radioButton11->TabStop = true;
			this->radioButton11->Text = L"Ar";
			this->radioButton11->UseVisualStyleBackColor = true;
			// 
			// radioButton12
			// 
			this->radioButton12->AutoSize = true;
			this->radioButton12->Location = System::Drawing::Point(16, 48);
			this->radioButton12->Name = L"radioButton12";
			this->radioButton12->Size = System::Drawing::Size(46, 19);
			this->radioButton12->TabIndex = 9;
			this->radioButton12->TabStop = true;
			this->radioButton12->Text = L"He";
			this->radioButton12->UseVisualStyleBackColor = true;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(200, 120);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(90, 15);
			this->label17->TabIndex = 7;
			this->label17->Text = L"オフセット電流";
			// 
			// textBox12
			// 
			this->textBox12->Location = System::Drawing::Point(200, 144);
			this->textBox12->Name = L"textBox12";
			this->textBox12->Size = System::Drawing::Size(100, 22);
			this->textBox12->TabIndex = 6;
			// 
			// SetupAnalyzeSP
			// 
			this->AcceptButton = this->button3;
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->button1;
			this->ClientSize = System::Drawing::Size(1016, 579);
			this->Controls->Add(this->groupBox9);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->groupBox6);
			this->Controls->Add(this->groupBox5);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Name = L"SetupAnalyzeSP";
			this->Text = L"SetupAnalyzeSP";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			this->groupBox6->ResumeLayout(false);
			this->groupBox8->ResumeLayout(false);
			this->groupBox8->PerformLayout();
			this->groupBox7->ResumeLayout(false);
			this->groupBox7->PerformLayout();
			this->groupBox9->ResumeLayout(false);
			this->groupBox9->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		System::Windows::Forms::Form::Close();
	}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	this->SaveSettings();
	System::Windows::Forms::Form::Close();
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	this->SaveSettings();
}
};
}
