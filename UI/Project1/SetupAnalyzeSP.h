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
#include "tkphysics.h"
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <cmath>
#ifndef M_PI
#define M_PI       3.14159265358979323846   // pi
#endif

namespace Project1
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	static std::string group;

	/// <summary>
	/// SetupAnalyzeSP の概要
	/// </summary>
	public ref class SetupAnalyzeSP : public System::Windows::Forms::Form
	{
	private:
		clx::ini* Setting;


	private: System::Windows::Forms::TextBox^  textBox13;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::TextBox^  textBox14;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::RadioButton^  radioButton14;
	private: System::Windows::Forms::RadioButton^  radioButton15;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::RadioButton^  radioButton16;
	private: System::Windows::Forms::RadioButton^  radioButton17;
	private: System::Windows::Forms::GroupBox^  groupBox10;
	private: System::Windows::Forms::RadioButton^  radioButton18;
	private: System::Windows::Forms::RadioButton^  radioButton19;
	private: System::Windows::Forms::GroupBox^  groupBox11;
	private: System::Windows::Forms::RadioButton^  radioButton25;
	private: System::Windows::Forms::GroupBox^  groupBox12;
	private: System::Windows::Forms::RadioButton^  radioButton24;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown2;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::RadioButton^  radioButton23;
	private: System::Windows::Forms::RadioButton^  radioButton22;
	private: System::Windows::Forms::RadioButton^  radioButton21;
	private: System::Windows::Forms::RadioButton^  radioButton20;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::CheckBox^  checkBox1;

		 TKSHOT* thisShot;

	private:
		double calcSurfaceArea(TKChargedParticleType particle_type)
		{
			double r = std::stod((*Setting)[group]["ProbeTipRadius"]);
			double l = std::stod((*Setting)[group]["ProbeTipLength"]);

			switch (particle_type) {
			case TKChargedParticleType::electron:
				if ((*Setting)[group]["ElectronCurrentCollectionSurfaceArea"] == "2rl")
					return 2 * r * l;
				else if ((*Setting)[group]["ElectronCurrentCollectionSurfaceArea"] == "4rl")
					return 4 * r * l;
				else if ((*Setting)[group]["ElectronCurrentCollectionSurfaceArea"] == "Cylinder")
					return 4 * M_PI * r * l + M_PI * r * r;
				else
					return std::stod((*Setting)[group]["ElectronCurrentCollectionSurfaceAreaValue"]);
				break;
			case TKChargedParticleType::ion:
				if ((*Setting)[group]["IonCurrentCollectionSurfaceArea"] == "2rl")
					return 2 * r * l;
				else if ((*Setting)[group]["IonCurrentCollectionSurfaceArea"] == "4rl")
					return 4 * r * l;
				else if ((*Setting)[group]["IonCurrentCollectionSurfaceArea"] == "Cylinder")
					return 4 * M_PI * r * l + M_PI * r * r;
				else
					return std::stod((*Setting)[group]["IonCurrentCollectionSurfaceAreaValue"]);
				break;
			default:
				return 1.0;
			}
		}

		int SaveSettings(void)
		{

			Setting->insert(group);


			// save v, I line

			(*Setting)[group]["VMonitorGain"] = checkBox1->Checked ? "1/100" : "1";
			(*Setting)[group]["VGain"] = TKUTIL::SystemStringToString(textBox1->Text).c_str();
			(*Setting)[group]["IR"] = TKUTIL::SystemStringToString(textBox2->Text).c_str();
			(*Setting)[group]["IGain"] = TKUTIL::SystemStringToString(textBox3->Text).c_str();

			(*Setting)[group]["VChannelIndex"] = std::to_string(comboBox1->SelectedIndex);
			(*Setting)[group]["IChannelIndex"] = std::to_string(comboBox2->SelectedIndex);



			// save polarity

			(*Setting)[group]["ProbeCurrentPolarity"] = radioButton1->Checked ? "IonCurrent" : "ElectronCurrent";

			// save polarity2

			(*Setting)[group]["AnalyzeCurrentPolarity"] = radioButton19->Checked ? "IonCurrent" : "ElectronCurrent";



			// save gas type

			if (radioButton11->Checked)
				(*Setting)[group]["GasType"] = "Ar";
			else if (radioButton12->Checked)
				(*Setting)[group]["GasType"] = "He";
			else if (radioButton13->Checked)
				(*Setting)[group]["GasType"] = "Proton";



			// save probe size

			(*Setting)[group]["ProbeTip"] = radioButton16->Checked ? "Preset" : "Manual";
			(*Setting)[group]["ProbeTipIndex"] = std::to_string(comboBox3->SelectedIndex);
			(*Setting)[group]["ProbeTipRadius"] = std::to_string(std::stod(TKUTIL::SystemStringToString(textBox9->Text).c_str())*1e-3);
			(*Setting)[group]["ProbeTipLength"] = std::to_string(std::stod(TKUTIL::SystemStringToString(textBox8->Text).c_str())*1e-3);



			// save electron current collection  surface area measurement option

			if (radioButton4->Checked) {
				(*Setting)[group]["ElectronCurrentCollectionSurfaceArea"] = "2rl";
			} else if (radioButton3->Checked) {
				(*Setting)[group]["ElectronCurrentCollectionSurfaceArea"] = "4rl";
			} else if (radioButton6->Checked) {
				(*Setting)[group]["ElectronCurrentCollectionSurfaceArea"] = "Cylinder";
			} else {
				(*Setting)[group]["ElectronCurrentCollectionSurfaceArea"] = "Manual";
				(*Setting)[group]["ElectronCurrentCollectionSurfaceAreaValue"]
					= std::to_string(std::stod(TKUTIL::SystemStringToString(textBox10->Text).c_str())*1e6);
			}


			// save ion current collection  surface area measurement option

			if (radioButton10->Checked) {
				(*Setting)[group]["IonCurrentCollectionSurfaceArea"] = "2rl";
			} else if (radioButton9->Checked) {
				(*Setting)[group]["IonCurrentCollectionSurfaceArea"] = "4rl";
			} else if (radioButton7->Checked) {
				(*Setting)[group]["IonCurrentCollectionSurfaceArea"] = "Cylinder";
			} else {
				(*Setting)[group]["IonCurrentCollectionSurfaceArea"] = "Manual";
				(*Setting)[group]["IonCurrentCollectionSurfaceAreaValue"]
					= std::to_string(std::stod(TKUTIL::SystemStringToString(textBox11->Text).c_str())*1e6);
			}


			// save function

			(*Setting)[group]["TimeRegion"] = radioButton15->Checked ? "Auto" : "Manual";
			(*Setting)[group]["FunctionDelayTime"] = std::to_string(std::stod(TKUTIL::SystemStringToString(textBox4->Text).c_str()));
			(*Setting)[group]["FunctionFrequency"] = TKUTIL::SystemStringToString(textBox5->Text).c_str();
			(*Setting)[group]["FunctionDelayCycle"] = std::to_string(std::stod(TKUTIL::SystemStringToString(textBox6->Text).c_str()) / 2);
			(*Setting)[group]["FunctionSweepCycle"] = std::to_string(std::stod(TKUTIL::SystemStringToString(textBox7->Text).c_str()) / 2);
			(*Setting)[group]["TimeRegionStart"] = std::to_string(std::stod(TKUTIL::SystemStringToString(textBox14->Text).c_str())*1e3);
			(*Setting)[group]["TimeRegionStop"] = std::to_string(std::stod(TKUTIL::SystemStringToString(textBox13->Text).c_str())*1e3);


			// save pre data processing 

			if (radioButton20->Checked)
				(*Setting)[group]["PreDataProcessing"] = "Raw";
			else if (radioButton21->Checked)
				(*Setting)[group]["PreDataProcessing"] = "SMA";
			else if (radioButton22->Checked)
				(*Setting)[group]["PreDataProcessing"] = "SMA+KillHysteresis";
			else
				(*Setting)[group]["PreDataProcessing"] = "SMA+KillHysteresis+SMA";

			(*Setting)[group]["PreDataProcessingSMA1Sample"] = std::to_string(static_cast<int>(numericUpDown1->Value));
			(*Setting)[group]["PreDataProcessingSMA2Sample"] = std::to_string(static_cast<int>(numericUpDown2->Value));

			(*Setting)[group]["PreDataProcessingPhase"] = radioButton24->Checked ? "0" : "90";

			return 0;
		}

		int LoadSettings(void)
		{

			// get trace list of thisShot

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



			// update comboBox from trace list

			comboBox1->BeginUpdate();
			comboBox2->BeginUpdate();
			for (int i = 0; i < static_cast<int>(plotInfo.size()); i++) {
				comboBox1->Items->Add(gcnew System::String(
					((std::string)"CH" + std::to_string(plotInfo[i].channel_number)
						+ " - " + plotInfo[i].model_name).c_str()));
				comboBox2->Items->Add(gcnew System::String(
					((std::string)"CH" + std::to_string(plotInfo[i].channel_number)
						+ " - " + plotInfo[i].model_name).c_str()));
			}
			comboBox1->EndUpdate();
			comboBox2->BeginUpdate();



			// load V, I line

			checkBox1->Checked = ((*Setting)[group]["VMonitorGain"] == "1/100");
			textBox1->Text = gcnew System::String((*Setting)[group]["VGain"].c_str());
			textBox2->Text = gcnew System::String((*Setting)[group]["IR"].c_str());
			textBox3->Text = gcnew System::String((*Setting)[group]["IGain"].c_str());
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


			// load polarity1

			radioButton1->Checked = ((*Setting)[group]["ProbeCurrentPolarity"] == "IonCurrent");
			radioButton2->Checked = ((*Setting)[group]["ProbeCurrentPolarity"] == "ElectronCurrent");

			// load polarity2

			radioButton19->Checked = ((*Setting)[group]["AnalyzeCurrentPolarity"] == "IonCurrent");
			radioButton18->Checked = ((*Setting)[group]["AnalyzeCurrentPolarity"] == "ElectronCurrent");


			// load gas type

			radioButton11->Checked = ((*Setting)[group]["GasType"] == "Ar");
			radioButton12->Checked = ((*Setting)[group]["GasType"] == "He");
			radioButton13->Checked = ((*Setting)[group]["GasType"] == "Proton");


			// load probe size

			if ((*Setting)[group]["ProbeTip"] == "Preset") {
				radioButton16->Checked = true;
				radioButton17->Checked = false;
				comboBox3->Enabled = true;
				textBox9->Enabled = false;
				textBox8->Enabled = false;
			} else {
				radioButton16->Checked = false;
				radioButton17->Checked = true;
				comboBox3->Enabled = false;
				textBox9->Enabled = true;
				textBox8->Enabled = true;
			}
			comboBox3->SelectedIndex = std::stoi((*Setting)[group]["ProbeTipIndex"]);
			comboBox3->SelectedIndex = -1;

			textBox9->Text = gcnew System::String((std::to_string(std::stod(((*Setting)[group]["ProbeTipRadius"]).c_str())*1e3)).c_str());
			textBox8->Text = gcnew System::String((std::to_string(std::stod(((*Setting)[group]["ProbeTipLength"]).c_str())*1e3)).c_str());



			// load electron current collection  surface area measurement option

			radioButton4->Checked = ((*Setting)[group]["ElectronCurrentCollectionSurfaceArea"] == "2rl");
			radioButton3->Checked = ((*Setting)[group]["ElectronCurrentCollectionSurfaceArea"] == "4rl");
			radioButton6->Checked = ((*Setting)[group]["ElectronCurrentCollectionSurfaceArea"] == "Cylinder");
			radioButton5->Checked = ((*Setting)[group]["ElectronCurrentCollectionSurfaceArea"] == "Manual");
			textBox10->Enabled = radioButton5->Checked;
			textBox10->Text = gcnew System::String((std::to_string(std::stod(
				((*Setting)[group]["ElectronCurrentCollectionSurfaceAreaValue"]).c_str())*1e-6)).c_str());



			// load ion current collection  surface area measurement option

			radioButton10->Checked = ((*Setting)[group]["IonCurrentCollectionSurfaceArea"] == "2rl");
			radioButton9->Checked = ((*Setting)[group]["IonCurrentCollectionSurfaceArea"] == "4rl");
			radioButton7->Checked = ((*Setting)[group]["IonCurrentCollectionSurfaceArea"] == "Cylinder");
			radioButton8->Checked = ((*Setting)[group]["IonCurrentCollectionSurfaceArea"] == "Manual");
			textBox11->Enabled = radioButton8->Checked;
			textBox11->Text = gcnew System::String((std::to_string(std::stod(
				((*Setting)[group]["IonCurrentCollectionSurfaceAreaValue"]).c_str())*1e-6)).c_str());



			// load function

			if ((*Setting)[group]["TimeRegion"] == "Auto") {
				radioButton15->Checked = true;
				radioButton14->Checked = false;
				textBox4->Enabled = true;
				textBox5->Enabled = true;
				textBox6->Enabled = true;
				textBox7->Enabled = true;
				textBox14->Enabled = false;
				textBox13->Enabled = false;
			} else {
				radioButton15->Checked = false;
				radioButton14->Checked = true;
				textBox4->Enabled = false;
				textBox5->Enabled = false;
				textBox6->Enabled = false;
				textBox7->Enabled = false;
				textBox14->Enabled = true;
				textBox13->Enabled = true;
			}
			textBox4->Text = gcnew System::String((std::to_string(std::stod(
				((*Setting)[group]["FunctionDelayTime"]).c_str()))).c_str());
			textBox5->Text = gcnew System::String((std::to_string(std::stod(
				((*Setting)[group]["FunctionFrequency"]).c_str()))).c_str());
			textBox6->Text = gcnew System::String((std::to_string(std::stod(
				((*Setting)[group]["FunctionDelayCycle"]).c_str()) * 2)).c_str());
			textBox7->Text = gcnew System::String((std::to_string(std::stod(
				((*Setting)[group]["FunctionSweepCycle"]).c_str()) * 2)).c_str());
			textBox14->Text = gcnew System::String((std::to_string(std::stod(
				((*Setting)[group]["TimeRegionStart"]).c_str())*1e-3)).c_str());
			textBox13->Text = gcnew System::String((std::to_string(std::stod(
				((*Setting)[group]["TimeRegionStop"]).c_str())*1e-3)).c_str());



			// load pre data processing 

			radioButton20->Checked = ((*Setting)[group]["PreDataProcessing"] == "Raw");
			radioButton21->Checked = ((*Setting)[group]["PreDataProcessing"] == "SMA");
			radioButton22->Checked = ((*Setting)[group]["PreDataProcessing"] == "SMA+KillHysteresis");
			radioButton23->Checked = ((*Setting)[group]["PreDataProcessing"] == "SMA+KillHysteresis+SMA");
			numericUpDown1->Value = std::stoi((*Setting)[group]["PreDataProcessingSMA1Sample"]);
			numericUpDown2->Value = std::stoi((*Setting)[group]["PreDataProcessingSMA2Sample"]);
			radioButton24->Checked = ((*Setting)[group]["PreDataProcessingPhase"] == "0");
			radioButton25->Checked = ((*Setting)[group]["PreDataProcessingPhase"] == "90");


			return 0;
		}
	public:
		SetupAnalyzeSP(clx::ini* Setting_, TKSHOT* thisShot_, std::string group_)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
			Setting = Setting_;
			thisShot = thisShot_;
			group = group_;
			this->LoadSettings();
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~SetupAnalyzeSP()
		{
			this->SaveSettings();
			if (components) {
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

	private: System::Windows::Forms::Label^  label10;

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
			this->groupBox10 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton18 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton19 = (gcnew System::Windows::Forms::RadioButton());
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
			this->textBox13 = (gcnew System::Windows::Forms::TextBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->textBox14 = (gcnew System::Windows::Forms::TextBox());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->radioButton14 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton15 = (gcnew System::Windows::Forms::RadioButton());
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
			this->radioButton17 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton16 = (gcnew System::Windows::Forms::RadioButton());
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
			this->groupBox11 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton25 = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox12 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton24 = (gcnew System::Windows::Forms::RadioButton());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->radioButton23 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton22 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton21 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton20 = (gcnew System::Windows::Forms::RadioButton());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox10->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->groupBox8->SuspendLayout();
			this->groupBox7->SuspendLayout();
			this->groupBox9->SuspendLayout();
			this->groupBox11->SuspendLayout();
			this->groupBox12->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->SuspendLayout();
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(18, 51);
			this->comboBox1->Margin = System::Windows::Forms::Padding(2);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(115, 20);
			this->comboBox1->TabIndex = 0;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label21);
			this->groupBox1->Controls->Add(this->checkBox1);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->textBox1);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->comboBox1);
			this->groupBox1->Location = System::Drawing::Point(12, 13);
			this->groupBox1->Margin = System::Windows::Forms::Padding(2);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(2);
			this->groupBox1->Size = System::Drawing::Size(332, 83);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"バイアス電圧";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(240, 32);
			this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(57, 12);
			this->label2->TabIndex = 3;
			this->label2->Text = L"測定ゲイン";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(240, 51);
			this->textBox1->Margin = System::Windows::Forms::Padding(2);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(76, 19);
			this->textBox1->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(18, 32);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(41, 12);
			this->label1->TabIndex = 1;
			this->label1->Text = L"トレース";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->groupBox10);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Controls->Add(this->textBox3);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->textBox2);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->comboBox2);
			this->groupBox2->Controls->Add(this->groupBox3);
			this->groupBox2->Location = System::Drawing::Point(12, 102);
			this->groupBox2->Margin = System::Windows::Forms::Padding(2);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Padding = System::Windows::Forms::Padding(2);
			this->groupBox2->Size = System::Drawing::Size(330, 147);
			this->groupBox2->TabIndex = 4;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"プローブ電流";
			// 
			// groupBox10
			// 
			this->groupBox10->Controls->Add(this->radioButton18);
			this->groupBox10->Controls->Add(this->radioButton19);
			this->groupBox10->Location = System::Drawing::Point(154, 77);
			this->groupBox10->Margin = System::Windows::Forms::Padding(2);
			this->groupBox10->Name = L"groupBox10";
			this->groupBox10->Padding = System::Windows::Forms::Padding(2);
			this->groupBox10->Size = System::Drawing::Size(118, 64);
			this->groupBox10->TabIndex = 11;
			this->groupBox10->TabStop = false;
			this->groupBox10->Text = L"解析に用いる極性";
			// 
			// radioButton18
			// 
			this->radioButton18->AutoSize = true;
			this->radioButton18->Location = System::Drawing::Point(12, 38);
			this->radioButton18->Margin = System::Windows::Forms::Padding(2);
			this->radioButton18->Name = L"radioButton18";
			this->radioButton18->Size = System::Drawing::Size(71, 16);
			this->radioButton18->TabIndex = 10;
			this->radioButton18->TabStop = true;
			this->radioButton18->Text = L"電子電流";
			this->radioButton18->UseVisualStyleBackColor = true;
			// 
			// radioButton19
			// 
			this->radioButton19->AutoSize = true;
			this->radioButton19->Checked = true;
			this->radioButton19->Location = System::Drawing::Point(12, 19);
			this->radioButton19->Margin = System::Windows::Forms::Padding(2);
			this->radioButton19->Name = L"radioButton19";
			this->radioButton19->Size = System::Drawing::Size(74, 16);
			this->radioButton19->TabIndex = 9;
			this->radioButton19->TabStop = true;
			this->radioButton19->Text = L"イオン電流";
			this->radioButton19->UseVisualStyleBackColor = true;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(240, 32);
			this->label5->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(57, 12);
			this->label5->TabIndex = 5;
			this->label5->Text = L"測定ゲイン";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(240, 51);
			this->textBox3->Margin = System::Windows::Forms::Padding(2);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(76, 19);
			this->textBox3->TabIndex = 4;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(150, 32);
			this->label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(53, 12);
			this->label3->TabIndex = 3;
			this->label3->Text = L"測定抵抗";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(150, 51);
			this->textBox2->Margin = System::Windows::Forms::Padding(2);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(76, 19);
			this->textBox2->TabIndex = 2;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(18, 32);
			this->label4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(41, 12);
			this->label4->TabIndex = 1;
			this->label4->Text = L"トレース";
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Location = System::Drawing::Point(18, 51);
			this->comboBox2->Margin = System::Windows::Forms::Padding(2);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(115, 20);
			this->comboBox2->TabIndex = 0;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->radioButton2);
			this->groupBox3->Controls->Add(this->radioButton1);
			this->groupBox3->Location = System::Drawing::Point(18, 77);
			this->groupBox3->Margin = System::Windows::Forms::Padding(2);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Padding = System::Windows::Forms::Padding(2);
			this->groupBox3->Size = System::Drawing::Size(118, 64);
			this->groupBox3->TabIndex = 9;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"IV変換の極性";
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(12, 38);
			this->radioButton2->Margin = System::Windows::Forms::Padding(2);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(93, 16);
			this->radioButton2->TabIndex = 10;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"電子電流が正";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->Location = System::Drawing::Point(12, 19);
			this->radioButton1->Margin = System::Windows::Forms::Padding(2);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(96, 16);
			this->radioButton1->TabIndex = 9;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"イオン電流が正";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->textBox13);
			this->groupBox4->Controls->Add(this->label18);
			this->groupBox4->Controls->Add(this->textBox14);
			this->groupBox4->Controls->Add(this->label19);
			this->groupBox4->Controls->Add(this->radioButton14);
			this->groupBox4->Controls->Add(this->radioButton15);
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
			this->groupBox4->Location = System::Drawing::Point(360, 13);
			this->groupBox4->Margin = System::Windows::Forms::Padding(2);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Padding = System::Windows::Forms::Padding(2);
			this->groupBox4->Size = System::Drawing::Size(408, 235);
			this->groupBox4->TabIndex = 5;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"解析範囲";
			// 
			// textBox13
			// 
			this->textBox13->Location = System::Drawing::Point(116, 203);
			this->textBox13->Margin = System::Windows::Forms::Padding(2);
			this->textBox13->Name = L"textBox13";
			this->textBox13->Size = System::Drawing::Size(76, 19);
			this->textBox13->TabIndex = 16;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(116, 184);
			this->label18->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(80, 12);
			this->label18->TabIndex = 15;
			this->label18->Text = L"掃引終了 [ms]";
			// 
			// textBox14
			// 
			this->textBox14->Location = System::Drawing::Point(32, 203);
			this->textBox14->Margin = System::Windows::Forms::Padding(2);
			this->textBox14->Name = L"textBox14";
			this->textBox14->Size = System::Drawing::Size(76, 19);
			this->textBox14->TabIndex = 14;
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(32, 184);
			this->label19->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(80, 12);
			this->label19->TabIndex = 13;
			this->label19->Text = L"掃引開始 [ms]";
			// 
			// radioButton14
			// 
			this->radioButton14->AutoSize = true;
			this->radioButton14->Location = System::Drawing::Point(16, 160);
			this->radioButton14->Margin = System::Windows::Forms::Padding(2);
			this->radioButton14->Name = L"radioButton14";
			this->radioButton14->Size = System::Drawing::Size(71, 16);
			this->radioButton14->TabIndex = 12;
			this->radioButton14->Text = L"手動入力";
			this->radioButton14->UseVisualStyleBackColor = true;
			// 
			// radioButton15
			// 
			this->radioButton15->AutoSize = true;
			this->radioButton15->Checked = true;
			this->radioButton15->Location = System::Drawing::Point(16, 24);
			this->radioButton15->Margin = System::Windows::Forms::Padding(2);
			this->radioButton15->Name = L"radioButton15";
			this->radioButton15->Size = System::Drawing::Size(137, 16);
			this->radioButton15->TabIndex = 11;
			this->radioButton15->TabStop = true;
			this->radioButton15->Text = L"掃引関数から自動計算";
			this->radioButton15->UseVisualStyleBackColor = true;
			this->radioButton15->CheckedChanged += gcnew System::EventHandler(this, &SetupAnalyzeSP::radioButton15_CheckedChanged);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(32, 118);
			this->label11->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(359, 12);
			this->label11->TabIndex = 9;
			this->label11->Text = L"(掃引終了時刻) = (掃引開始時刻) + 1 / (周波数) * (掃引半周期) / 2";
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(284, 67);
			this->textBox7->Margin = System::Windows::Forms::Padding(2);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(76, 19);
			this->textBox7->TabIndex = 8;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(284, 48);
			this->label10->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(65, 12);
			this->label10->TabIndex = 7;
			this->label10->Text = L"掃引半周期";
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(200, 67);
			this->textBox6->Margin = System::Windows::Forms::Padding(2);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(76, 19);
			this->textBox6->TabIndex = 6;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(200, 48);
			this->label9->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(76, 12);
			this->label9->TabIndex = 5;
			this->label9->Text = L"ディレイ半周期";
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(116, 67);
			this->textBox5->Margin = System::Windows::Forms::Padding(2);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(76, 19);
			this->textBox5->TabIndex = 4;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(116, 48);
			this->label8->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(66, 12);
			this->label8->TabIndex = 3;
			this->label8->Text = L"周波数 [Hz]";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(32, 99);
			this->label7->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(333, 12);
			this->label7->TabIndex = 2;
			this->label7->Text = L"(掃引開始時刻) = (ディレイ) + 1 / (周波数) * (ディレイ半周期) / 2";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(32, 67);
			this->textBox4->Margin = System::Windows::Forms::Padding(2);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(76, 19);
			this->textBox4->TabIndex = 1;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(32, 48);
			this->label6->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(67, 12);
			this->label6->TabIndex = 0;
			this->label6->Text = L"ディレイ [ms]";
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->radioButton17);
			this->groupBox5->Controls->Add(this->radioButton16);
			this->groupBox5->Controls->Add(this->label14);
			this->groupBox5->Controls->Add(this->label12);
			this->groupBox5->Controls->Add(this->textBox8);
			this->groupBox5->Controls->Add(this->label13);
			this->groupBox5->Controls->Add(this->textBox9);
			this->groupBox5->Controls->Add(this->comboBox3);
			this->groupBox5->Location = System::Drawing::Point(80, 264);
			this->groupBox5->Margin = System::Windows::Forms::Padding(2);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Padding = System::Windows::Forms::Padding(2);
			this->groupBox5->Size = System::Drawing::Size(208, 184);
			this->groupBox5->TabIndex = 10;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"プローブチップ寸法";
			// 
			// radioButton17
			// 
			this->radioButton17->AutoSize = true;
			this->radioButton17->Location = System::Drawing::Point(16, 104);
			this->radioButton17->Name = L"radioButton17";
			this->radioButton17->Size = System::Drawing::Size(71, 16);
			this->radioButton17->TabIndex = 13;
			this->radioButton17->TabStop = true;
			this->radioButton17->Text = L"手動入力";
			this->radioButton17->UseVisualStyleBackColor = true;
			// 
			// radioButton16
			// 
			this->radioButton16->AutoSize = true;
			this->radioButton16->Location = System::Drawing::Point(16, 24);
			this->radioButton16->Name = L"radioButton16";
			this->radioButton16->Size = System::Drawing::Size(97, 16);
			this->radioButton16->TabIndex = 12;
			this->radioButton16->TabStop = true;
			this->radioButton16->Text = L"プリセットを使用";
			this->radioButton16->UseVisualStyleBackColor = true;
			this->radioButton16->CheckedChanged += gcnew System::EventHandler(this, &SetupAnalyzeSP::radioButton16_CheckedChanged);
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(32, 48);
			this->label14->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(46, 12);
			this->label14->TabIndex = 11;
			this->label14->Text = L"プリセット";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(122, 128);
			this->label12->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(55, 12);
			this->label12->TabIndex = 10;
			this->label12->Text = L"長さ [mm]";
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(122, 147);
			this->textBox8->Margin = System::Windows::Forms::Padding(2);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(76, 19);
			this->textBox8->TabIndex = 9;
			this->textBox8->TextChanged += gcnew System::EventHandler(this, &SetupAnalyzeSP::textBox8_TextChanged);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(32, 128);
			this->label13->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(59, 12);
			this->label13->TabIndex = 8;
			this->label13->Text = L"半径 [mm]";
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(32, 147);
			this->textBox9->Margin = System::Windows::Forms::Padding(2);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(76, 19);
			this->textBox9->TabIndex = 7;
			this->textBox9->TextChanged += gcnew System::EventHandler(this, &SetupAnalyzeSP::textBox9_TextChanged);
			// 
			// comboBox3
			// 
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Location = System::Drawing::Point(32, 67);
			this->comboBox3->Margin = System::Windows::Forms::Padding(2);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(169, 20);
			this->comboBox3->TabIndex = 6;
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->groupBox8);
			this->groupBox6->Controls->Add(this->groupBox7);
			this->groupBox6->Location = System::Drawing::Point(304, 264);
			this->groupBox6->Margin = System::Windows::Forms::Padding(2);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Padding = System::Windows::Forms::Padding(2);
			this->groupBox6->Size = System::Drawing::Size(240, 200);
			this->groupBox6->TabIndex = 11;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"荷電粒子捕集面積";
			// 
			// groupBox8
			// 
			this->groupBox8->Controls->Add(this->label16);
			this->groupBox8->Controls->Add(this->textBox11);
			this->groupBox8->Controls->Add(this->radioButton7);
			this->groupBox8->Controls->Add(this->radioButton8);
			this->groupBox8->Controls->Add(this->radioButton9);
			this->groupBox8->Controls->Add(this->radioButton10);
			this->groupBox8->Location = System::Drawing::Point(126, 26);
			this->groupBox8->Margin = System::Windows::Forms::Padding(2);
			this->groupBox8->Name = L"groupBox8";
			this->groupBox8->Padding = System::Windows::Forms::Padding(2);
			this->groupBox8->Size = System::Drawing::Size(96, 154);
			this->groupBox8->TabIndex = 13;
			this->groupBox8->TabStop = false;
			this->groupBox8->Text = L"イオン捕集面積";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(12, 102);
			this->label16->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(70, 12);
			this->label16->TabIndex = 12;
			this->label16->Text = L"面積 [mm^2]";
			// 
			// textBox11
			// 
			this->textBox11->Enabled = false;
			this->textBox11->Location = System::Drawing::Point(12, 122);
			this->textBox11->Margin = System::Windows::Forms::Padding(2);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(76, 19);
			this->textBox11->TabIndex = 12;
			// 
			// radioButton7
			// 
			this->radioButton7->AutoSize = true;
			this->radioButton7->Location = System::Drawing::Point(12, 58);
			this->radioButton7->Margin = System::Windows::Forms::Padding(2);
			this->radioButton7->Name = L"radioButton7";
			this->radioButton7->Size = System::Drawing::Size(47, 16);
			this->radioButton7->TabIndex = 12;
			this->radioButton7->TabStop = true;
			this->radioButton7->Text = L"円筒";
			this->radioButton7->UseVisualStyleBackColor = true;
			this->radioButton7->CheckedChanged += gcnew System::EventHandler(this, &SetupAnalyzeSP::radioButton7_CheckedChanged);
			// 
			// radioButton8
			// 
			this->radioButton8->AutoSize = true;
			this->radioButton8->Location = System::Drawing::Point(12, 77);
			this->radioButton8->Margin = System::Windows::Forms::Padding(2);
			this->radioButton8->Name = L"radioButton8";
			this->radioButton8->Size = System::Drawing::Size(71, 16);
			this->radioButton8->TabIndex = 11;
			this->radioButton8->TabStop = true;
			this->radioButton8->Text = L"手動入力";
			this->radioButton8->UseVisualStyleBackColor = true;
			this->radioButton8->CheckedChanged += gcnew System::EventHandler(this, &SetupAnalyzeSP::radioButton8_CheckedChanged);
			// 
			// radioButton9
			// 
			this->radioButton9->AutoSize = true;
			this->radioButton9->Location = System::Drawing::Point(12, 38);
			this->radioButton9->Margin = System::Windows::Forms::Padding(2);
			this->radioButton9->Name = L"radioButton9";
			this->radioButton9->Size = System::Drawing::Size(36, 16);
			this->radioButton9->TabIndex = 10;
			this->radioButton9->TabStop = true;
			this->radioButton9->Text = L"4rl";
			this->radioButton9->UseVisualStyleBackColor = true;
			this->radioButton9->CheckedChanged += gcnew System::EventHandler(this, &SetupAnalyzeSP::radioButton9_CheckedChanged);
			// 
			// radioButton10
			// 
			this->radioButton10->AutoSize = true;
			this->radioButton10->Checked = true;
			this->radioButton10->Location = System::Drawing::Point(12, 19);
			this->radioButton10->Margin = System::Windows::Forms::Padding(2);
			this->radioButton10->Name = L"radioButton10";
			this->radioButton10->Size = System::Drawing::Size(36, 16);
			this->radioButton10->TabIndex = 9;
			this->radioButton10->TabStop = true;
			this->radioButton10->Text = L"2rl";
			this->radioButton10->UseVisualStyleBackColor = true;
			this->radioButton10->CheckedChanged += gcnew System::EventHandler(this, &SetupAnalyzeSP::radioButton10_CheckedChanged);
			// 
			// groupBox7
			// 
			this->groupBox7->Controls->Add(this->label15);
			this->groupBox7->Controls->Add(this->textBox10);
			this->groupBox7->Controls->Add(this->radioButton6);
			this->groupBox7->Controls->Add(this->radioButton5);
			this->groupBox7->Controls->Add(this->radioButton3);
			this->groupBox7->Controls->Add(this->radioButton4);
			this->groupBox7->Location = System::Drawing::Point(18, 26);
			this->groupBox7->Margin = System::Windows::Forms::Padding(2);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Padding = System::Windows::Forms::Padding(2);
			this->groupBox7->Size = System::Drawing::Size(96, 154);
			this->groupBox7->TabIndex = 11;
			this->groupBox7->TabStop = false;
			this->groupBox7->Text = L"電子捕集面積";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(12, 102);
			this->label15->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(70, 12);
			this->label15->TabIndex = 12;
			this->label15->Text = L"面積 [mm^2]";
			// 
			// textBox10
			// 
			this->textBox10->Enabled = false;
			this->textBox10->Location = System::Drawing::Point(12, 122);
			this->textBox10->Margin = System::Windows::Forms::Padding(2);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(76, 19);
			this->textBox10->TabIndex = 12;
			this->textBox10->Text = L"C";
			// 
			// radioButton6
			// 
			this->radioButton6->AutoSize = true;
			this->radioButton6->Location = System::Drawing::Point(12, 58);
			this->radioButton6->Margin = System::Windows::Forms::Padding(2);
			this->radioButton6->Name = L"radioButton6";
			this->radioButton6->Size = System::Drawing::Size(47, 16);
			this->radioButton6->TabIndex = 12;
			this->radioButton6->TabStop = true;
			this->radioButton6->Text = L"円筒";
			this->radioButton6->UseVisualStyleBackColor = true;
			this->radioButton6->CheckedChanged += gcnew System::EventHandler(this, &SetupAnalyzeSP::radioButton6_CheckedChanged);
			// 
			// radioButton5
			// 
			this->radioButton5->AutoSize = true;
			this->radioButton5->Location = System::Drawing::Point(12, 77);
			this->radioButton5->Margin = System::Windows::Forms::Padding(2);
			this->radioButton5->Name = L"radioButton5";
			this->radioButton5->Size = System::Drawing::Size(71, 16);
			this->radioButton5->TabIndex = 11;
			this->radioButton5->TabStop = true;
			this->radioButton5->Text = L"手動入力";
			this->radioButton5->UseVisualStyleBackColor = true;
			this->radioButton5->CheckedChanged += gcnew System::EventHandler(this, &SetupAnalyzeSP::radioButton5_CheckedChanged);
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(12, 38);
			this->radioButton3->Margin = System::Windows::Forms::Padding(2);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(36, 16);
			this->radioButton3->TabIndex = 10;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"4rl";
			this->radioButton3->UseVisualStyleBackColor = true;
			this->radioButton3->CheckedChanged += gcnew System::EventHandler(this, &SetupAnalyzeSP::radioButton3_CheckedChanged);
			// 
			// radioButton4
			// 
			this->radioButton4->AutoSize = true;
			this->radioButton4->Checked = true;
			this->radioButton4->Location = System::Drawing::Point(12, 19);
			this->radioButton4->Margin = System::Windows::Forms::Padding(2);
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->Size = System::Drawing::Size(36, 16);
			this->radioButton4->TabIndex = 9;
			this->radioButton4->TabStop = true;
			this->radioButton4->Text = L"2rl";
			this->radioButton4->UseVisualStyleBackColor = true;
			this->radioButton4->CheckedChanged += gcnew System::EventHandler(this, &SetupAnalyzeSP::radioButton4_CheckedChanged);
			// 
			// button3
			// 
			this->button3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button3->Location = System::Drawing::Point(526, 477);
			this->button3->Margin = System::Windows::Forms::Padding(2);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 14;
			this->button3->Text = L"OK";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &SetupAnalyzeSP::button3_Click);
			// 
			// button2
			// 
			this->button2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button2->Location = System::Drawing::Point(612, 477);
			this->button2->Margin = System::Windows::Forms::Padding(2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 13;
			this->button2->Text = L"適用";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &SetupAnalyzeSP::button2_Click);
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button1->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button1->Location = System::Drawing::Point(694, 477);
			this->button1->Margin = System::Windows::Forms::Padding(2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 12;
			this->button1->Text = L"キャンセル";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &SetupAnalyzeSP::button1_Click);
			// 
			// button4
			// 
			this->button4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->button4->Location = System::Drawing::Point(12, 477);
			this->button4->Margin = System::Windows::Forms::Padding(2);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 15;
			this->button4->Text = L"保存";
			this->button4->UseVisualStyleBackColor = true;
			// 
			// button5
			// 
			this->button5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->button5->Location = System::Drawing::Point(96, 477);
			this->button5->Margin = System::Windows::Forms::Padding(2);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(75, 23);
			this->button5->TabIndex = 16;
			this->button5->Text = L"読込";
			this->button5->UseVisualStyleBackColor = true;
			// 
			// groupBox9
			// 
			this->groupBox9->Controls->Add(this->radioButton13);
			this->groupBox9->Controls->Add(this->radioButton11);
			this->groupBox9->Controls->Add(this->radioButton12);
			this->groupBox9->Location = System::Drawing::Point(16, 264);
			this->groupBox9->Margin = System::Windows::Forms::Padding(2);
			this->groupBox9->Name = L"groupBox9";
			this->groupBox9->Padding = System::Windows::Forms::Padding(2);
			this->groupBox9->Size = System::Drawing::Size(56, 88);
			this->groupBox9->TabIndex = 11;
			this->groupBox9->TabStop = false;
			this->groupBox9->Text = L"ガス種";
			// 
			// radioButton13
			// 
			this->radioButton13->AutoSize = true;
			this->radioButton13->Location = System::Drawing::Point(12, 58);
			this->radioButton13->Margin = System::Windows::Forms::Padding(2);
			this->radioButton13->Name = L"radioButton13";
			this->radioButton13->Size = System::Drawing::Size(30, 16);
			this->radioButton13->TabIndex = 11;
			this->radioButton13->TabStop = true;
			this->radioButton13->Text = L"P";
			this->radioButton13->UseVisualStyleBackColor = true;
			// 
			// radioButton11
			// 
			this->radioButton11->AutoSize = true;
			this->radioButton11->Location = System::Drawing::Point(12, 19);
			this->radioButton11->Margin = System::Windows::Forms::Padding(2);
			this->radioButton11->Name = L"radioButton11";
			this->radioButton11->Size = System::Drawing::Size(35, 16);
			this->radioButton11->TabIndex = 10;
			this->radioButton11->TabStop = true;
			this->radioButton11->Text = L"Ar";
			this->radioButton11->UseVisualStyleBackColor = true;
			// 
			// radioButton12
			// 
			this->radioButton12->AutoSize = true;
			this->radioButton12->Checked = true;
			this->radioButton12->Location = System::Drawing::Point(12, 38);
			this->radioButton12->Margin = System::Windows::Forms::Padding(2);
			this->radioButton12->Name = L"radioButton12";
			this->radioButton12->Size = System::Drawing::Size(37, 16);
			this->radioButton12->TabIndex = 9;
			this->radioButton12->TabStop = true;
			this->radioButton12->Text = L"He";
			this->radioButton12->UseVisualStyleBackColor = true;
			// 
			// groupBox11
			// 
			this->groupBox11->Controls->Add(this->groupBox12);
			this->groupBox11->Controls->Add(this->label20);
			this->groupBox11->Controls->Add(this->label17);
			this->groupBox11->Controls->Add(this->numericUpDown2);
			this->groupBox11->Controls->Add(this->numericUpDown1);
			this->groupBox11->Controls->Add(this->radioButton23);
			this->groupBox11->Controls->Add(this->radioButton22);
			this->groupBox11->Controls->Add(this->radioButton21);
			this->groupBox11->Controls->Add(this->radioButton20);
			this->groupBox11->Location = System::Drawing::Point(560, 264);
			this->groupBox11->Name = L"groupBox11";
			this->groupBox11->Size = System::Drawing::Size(208, 200);
			this->groupBox11->TabIndex = 17;
			this->groupBox11->TabStop = false;
			this->groupBox11->Text = L"解析前データ処理";
			// 
			// radioButton25
			// 
			this->radioButton25->AutoSize = true;
			this->radioButton25->Location = System::Drawing::Point(96, 16);
			this->radioButton25->Name = L"radioButton25";
			this->radioButton25->Size = System::Drawing::Size(83, 16);
			this->radioButton25->TabIndex = 1;
			this->radioButton25->TabStop = true;
			this->radioButton25->Text = L"90, 270 deg.";
			this->radioButton25->UseVisualStyleBackColor = true;
			// 
			// groupBox12
			// 
			this->groupBox12->Controls->Add(this->radioButton25);
			this->groupBox12->Controls->Add(this->radioButton24);
			this->groupBox12->Location = System::Drawing::Point(16, 144);
			this->groupBox12->Name = L"groupBox12";
			this->groupBox12->Size = System::Drawing::Size(184, 40);
			this->groupBox12->TabIndex = 10;
			this->groupBox12->TabStop = false;
			this->groupBox12->Text = L"掃引関数の初期位相 (KH)";
			// 
			// radioButton24
			// 
			this->radioButton24->AutoSize = true;
			this->radioButton24->Location = System::Drawing::Point(8, 16);
			this->radioButton24->Name = L"radioButton24";
			this->radioButton24->Size = System::Drawing::Size(77, 16);
			this->radioButton24->TabIndex = 0;
			this->radioButton24->TabStop = true;
			this->radioButton24->Text = L"0, 180 deg.";
			this->radioButton24->UseVisualStyleBackColor = true;
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(104, 96);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(73, 12);
			this->label20->TabIndex = 9;
			this->label20->Text = L"SMA2サンプル";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(16, 96);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(73, 12);
			this->label17->TabIndex = 8;
			this->label17->Text = L"SMA1サンプル";
			// 
			// numericUpDown2
			// 
			this->numericUpDown2->Location = System::Drawing::Point(104, 112);
			this->numericUpDown2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown2->Name = L"numericUpDown2";
			this->numericUpDown2->Size = System::Drawing::Size(72, 19);
			this->numericUpDown2->TabIndex = 5;
			this->numericUpDown2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(16, 112);
			this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(72, 19);
			this->numericUpDown1->TabIndex = 4;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// radioButton23
			// 
			this->radioButton23->AutoSize = true;
			this->radioButton23->Location = System::Drawing::Point(16, 72);
			this->radioButton23->Name = L"radioButton23";
			this->radioButton23->Size = System::Drawing::Size(138, 16);
			this->radioButton23->TabIndex = 3;
			this->radioButton23->TabStop = true;
			this->radioButton23->Text = L"SMA1 -> KH -> SMA2";
			this->radioButton23->UseVisualStyleBackColor = true;
			// 
			// radioButton22
			// 
			this->radioButton22->AutoSize = true;
			this->radioButton22->Location = System::Drawing::Point(16, 56);
			this->radioButton22->Name = L"radioButton22";
			this->radioButton22->Size = System::Drawing::Size(175, 16);
			this->radioButton22->TabIndex = 2;
			this->radioButton22->TabStop = true;
			this->radioButton22->Text = L"SMA1 -> Kill Hysteresis (KH)";
			this->radioButton22->UseVisualStyleBackColor = true;
			// 
			// radioButton21
			// 
			this->radioButton21->AutoSize = true;
			this->radioButton21->Location = System::Drawing::Point(16, 40);
			this->radioButton21->Name = L"radioButton21";
			this->radioButton21->Size = System::Drawing::Size(189, 16);
			this->radioButton21->TabIndex = 1;
			this->radioButton21->TabStop = true;
			this->radioButton21->Text = L"Simple Moving Average (SMA) 1";
			this->radioButton21->UseVisualStyleBackColor = true;
			// 
			// radioButton20
			// 
			this->radioButton20->AutoSize = true;
			this->radioButton20->Location = System::Drawing::Point(16, 24);
			this->radioButton20->Name = L"radioButton20";
			this->radioButton20->Size = System::Drawing::Size(45, 16);
			this->radioButton20->TabIndex = 0;
			this->radioButton20->TabStop = true;
			this->radioButton20->Text = L"Raw";
			this->radioButton20->UseVisualStyleBackColor = true;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(152, 48);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(62, 16);
			this->checkBox1->TabIndex = 4;
			this->checkBox1->Text = L"1 / 100";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(152, 32);
			this->label21->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(65, 12);
			this->label21->TabIndex = 5;
			this->label21->Text = L"モニター出力";
			// 
			// SetupAnalyzeSP
			// 
			this->AcceptButton = this->button3;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->button1;
			this->ClientSize = System::Drawing::Size(778, 511);
			this->Controls->Add(this->groupBox11);
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
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"SetupAnalyzeSP";
			this->Text = L"SetupAnalyzeSP";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox10->ResumeLayout(false);
			this->groupBox10->PerformLayout();
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
			this->groupBox11->ResumeLayout(false);
			this->groupBox11->PerformLayout();
			this->groupBox12->ResumeLayout(false);
			this->groupBox12->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		System::Windows::Forms::Form::Close();
	}
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e)
	{
		this->SaveSettings();
		System::Windows::Forms::Form::Close();
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		this->SaveSettings();
	}
	private: System::Void radioButton15_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		switch (radioButton15->Checked) {
		case true:
			textBox4->Enabled = true;
			textBox5->Enabled = true;
			textBox6->Enabled = true;
			textBox7->Enabled = true;
			textBox14->Enabled = false;
			textBox13->Enabled = false;
			break;
		case false:
			textBox4->Enabled = false;
			textBox5->Enabled = false;
			textBox6->Enabled = false;
			textBox7->Enabled = false;
			textBox14->Enabled = true;
			textBox13->Enabled = true;
			break;
		}
	}
	private: System::Void radioButton5_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		switch (radioButton5->Checked) {
		case true:
			textBox10->Enabled = true;
			break;
		case false:
			textBox10->Enabled = false;
			break;
		}
	}
	private: System::Void radioButton8_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		switch (radioButton8->Checked) {
		case true:
			textBox11->Enabled = true;
			break;
		case false:
			textBox11->Enabled = false;
			break;
		}
	}
	private: System::Void radioButton16_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		switch (radioButton16->Checked) {
		case true:
			comboBox3->Enabled = true;
			textBox9->Enabled = false;
			textBox8->Enabled = false;
			break;
		case false:
			comboBox3->Enabled = false;
			textBox9->Enabled = true;
			textBox8->Enabled = true;
			break;
		}
	}
	private: System::Void textBox9_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//		textBox10->Text = gcnew System::String(std::to_string(calcSurfaceArea(TKChargedParticleType::electron) * 1e-6).c_str());
		//		textBox11->Text = gcnew System::String(std::to_string(calcSurfaceArea(TKChargedParticleType::ion) * 1e-6).c_str());
	}
	private: System::Void textBox8_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//		textBox10->Text = gcnew System::String(std::to_string(calcSurfaceArea(TKChargedParticleType::electron) * 1e-6).c_str());
		//		textBox11->Text = gcnew System::String(std::to_string(calcSurfaceArea(TKChargedParticleType::ion) * 1e-6).c_str());
	}
	private: System::Void radioButton4_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//		textBox10->Text = gcnew System::String(std::to_string(calcSurfaceArea(TKChargedParticleType::electron) * 1e-6).c_str());
	}
	private: System::Void radioButton3_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//		textBox10->Text = gcnew System::String(std::to_string(calcSurfaceArea(TKChargedParticleType::electron) * 1e-6).c_str());
	}
	private: System::Void radioButton6_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//		textBox10->Text = gcnew System::String(std::to_string(calcSurfaceArea(TKChargedParticleType::electron) * 1e-6).c_str());
	}
	private: System::Void radioButton10_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//		textBox11->Text = gcnew System::String(std::to_string(calcSurfaceArea(TKChargedParticleType::ion) * 1e-6).c_str());
	}
	private: System::Void radioButton9_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//		textBox11->Text = gcnew System::String(std::to_string(calcSurfaceArea(TKChargedParticleType::ion) * 1e-6).c_str());
	}
	private: System::Void radioButton7_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//		textBox11->Text = gcnew System::String(std::to_string(calcSurfaceArea(TKChargedParticleType::ion) * 1e-6).c_str());
	}
	};
}
