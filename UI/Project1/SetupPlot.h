#pragma once
#include <string>
#include <iostream>
#include "clx/ini.h"
#include "clx/base64.h"
#include "kbtnutil.h"

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// SetupPlot の概要
	/// </summary>
	public ref class SetupPlot : public System::Windows::Forms::Form
	{
	private:
		clx::ini* ShotSetting;
		int SaveSettings(void)
		{
			ShotSetting->insert("CH1.Plot");
			(*ShotSetting)["CH1.Plot"]["Plot"] = checkBoxEnCH1->Checked ? "Enable" : "Disable";
			(*ShotSetting)["CH1.Plot"]["TargetFigure"] = std::to_string(comboBoxFig1->SelectedIndex);
			(*ShotSetting)["CH1.Plot"]["LabelName"] = kbtn::SystemStringToString(textBoxLN1->Text).c_str();

			ShotSetting->write(((*ShotSetting)["This"]["FileName"] + ".ini").c_str());
			return 0;
		}
		int LoadSettings(void)
		{
			checkBoxEnCH1->Checked = (bool)((*ShotSetting)["CH1.Plot"]["Plot"] == "Enable");
			comboBoxFig1->SelectedIndex = std::strtol((*ShotSetting)["CH1.Plot"]["TargetFigure"].c_str(), nullptr, 10);
			textBoxLN1->Text = gcnew String((*ShotSetting)["CH1.Plot"]["LabelName"].c_str());
			return 0;
		}
	public:
		SetupPlot(clx::ini* ShotSetting_)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
			ShotSetting = ShotSetting_;
			//this->SaveSettings();
			this->LoadSettings();
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~SetupPlot()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^  groupBox3;
	protected:
	private: System::Windows::Forms::CheckBox^  checkBox50;
	private: System::Windows::Forms::CheckBox^  checkBox45;
	private: System::Windows::Forms::CheckBox^  checkBox40;
	private: System::Windows::Forms::CheckBox^  checkBox28;
	private: System::Windows::Forms::CheckBox^  checkBox46;
	private: System::Windows::Forms::CheckBox^  checkBox41;
	private: System::Windows::Forms::CheckBox^  checkBox36;
	private: System::Windows::Forms::CheckBox^  checkBox35;
	private: System::Windows::Forms::TextBox^  textBox95;


	private: System::Windows::Forms::TextBox^  textBox96;
	private: System::Windows::Forms::TextBox^  textBox97;
	private: System::Windows::Forms::CheckBox^  checkBox49;
	private: System::Windows::Forms::TextBox^  textBox98;
	private: System::Windows::Forms::TextBox^  textBox99;
	private: System::Windows::Forms::TextBox^  textBox90;


	private: System::Windows::Forms::TextBox^  textBox91;
	private: System::Windows::Forms::TextBox^  textBox92;
	private: System::Windows::Forms::CheckBox^  checkBox44;
	private: System::Windows::Forms::TextBox^  textBox93;
	private: System::Windows::Forms::TextBox^  textBox94;
	private: System::Windows::Forms::TextBox^  textBox85;


	private: System::Windows::Forms::TextBox^  textBox86;
	private: System::Windows::Forms::TextBox^  textBox87;
	private: System::Windows::Forms::CheckBox^  checkBox39;
	private: System::Windows::Forms::TextBox^  textBox88;
	private: System::Windows::Forms::TextBox^  textBox89;
	private: System::Windows::Forms::TextBox^  textBox84;
	private: System::Windows::Forms::Label^  label72;


	private: System::Windows::Forms::TextBox^  textBox80;
	private: System::Windows::Forms::TextBox^  textBox81;
	private: System::Windows::Forms::Label^  label70;
	private: System::Windows::Forms::Label^  label68;
	private: System::Windows::Forms::Label^  label67;
	private: System::Windows::Forms::CheckBox^  checkBox29;
	private: System::Windows::Forms::Label^  label66;
	private: System::Windows::Forms::TextBox^  textBox78;
	private: System::Windows::Forms::TextBox^  textBox79;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label65;
	private: System::Windows::Forms::TextBox^  textBox76;
	private: System::Windows::Forms::TextBox^  textBox77;
	private: System::Windows::Forms::Label^  label62;
	private: System::Windows::Forms::CheckBox^  checkBox32;
	private: System::Windows::Forms::CheckBox^  checkBox30;
	private: System::Windows::Forms::CheckBox^  checkBox31;
	private: System::Windows::Forms::Label^  label71;
	private: System::Windows::Forms::Label^  label69;
private: System::Windows::Forms::TextBox^  textBoxLNT;

	private: System::Windows::Forms::TextBox^  textBox82;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::TextBox^  textBox83;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::ComboBox^  comboBoxUn;

	private: System::Windows::Forms::ComboBox^  comboBox27;
	private: System::Windows::Forms::CheckBox^  checkBox26;
	private: System::Windows::Forms::CheckBox^  checkBox27;
	private: System::Windows::Forms::CheckBox^  checkBox25;
	private: System::Windows::Forms::GroupBox^  groupBox2;
private: System::Windows::Forms::ComboBox^  comboBoxFig12;

	private: System::Windows::Forms::Button^  button17;
private: System::Windows::Forms::ComboBox^  comboBoxFig11;

	private: System::Windows::Forms::Button^  button18;
private: System::Windows::Forms::ComboBox^  comboBoxFig10;

	private: System::Windows::Forms::Button^  button19;
private: System::Windows::Forms::ComboBox^  comboBoxFig9;

	private: System::Windows::Forms::Button^  button20;
private: System::Windows::Forms::ComboBox^  comboBoxFig24;

	private: System::Windows::Forms::Button^  button21;
private: System::Windows::Forms::ComboBox^  comboBoxFig23;

	private: System::Windows::Forms::Button^  button22;
private: System::Windows::Forms::ComboBox^  comboBoxFig22;

	private: System::Windows::Forms::Button^  button23;
private: System::Windows::Forms::ComboBox^  comboBoxFig21;

	private: System::Windows::Forms::Button^  button24;
	private: System::Windows::Forms::TextBox^  textBox50;
	private: System::Windows::Forms::Label^  label46;
	private: System::Windows::Forms::TextBox^  textBox51;
private: System::Windows::Forms::TextBox^  textBoxLN24;

private: System::Windows::Forms::CheckBox^  checkBoxEnCH24;

	private: System::Windows::Forms::Label^  label47;
	private: System::Windows::Forms::TextBox^  textBox53;
	private: System::Windows::Forms::Label^  label48;
	private: System::Windows::Forms::TextBox^  textBox54;
private: System::Windows::Forms::TextBox^  textBoxLN23;

private: System::Windows::Forms::CheckBox^  checkBoxEnCH23;

	private: System::Windows::Forms::Label^  label49;
	private: System::Windows::Forms::TextBox^  textBox56;
	private: System::Windows::Forms::Label^  label50;
	private: System::Windows::Forms::TextBox^  textBox57;
private: System::Windows::Forms::TextBox^  textBoxLN22;

private: System::Windows::Forms::CheckBox^  checkBoxEnCH22;

	private: System::Windows::Forms::Label^  label51;
	private: System::Windows::Forms::TextBox^  textBox59;
	private: System::Windows::Forms::Label^  label52;
	private: System::Windows::Forms::TextBox^  textBox60;
private: System::Windows::Forms::TextBox^  textBoxLN21;

private: System::Windows::Forms::CheckBox^  checkBoxEnCH21;

	private: System::Windows::Forms::Label^  label53;
	private: System::Windows::Forms::TextBox^  textBox62;
	private: System::Windows::Forms::Label^  label54;
	private: System::Windows::Forms::TextBox^  textBox63;
private: System::Windows::Forms::TextBox^  textBoxLN12;

private: System::Windows::Forms::CheckBox^  checkBoxEnCH12;

	private: System::Windows::Forms::Label^  label55;
	private: System::Windows::Forms::TextBox^  textBox65;
	private: System::Windows::Forms::Label^  label56;
	private: System::Windows::Forms::TextBox^  textBox66;
private: System::Windows::Forms::TextBox^  textBoxLN11;

private: System::Windows::Forms::CheckBox^  checkBoxEnCH11;

	private: System::Windows::Forms::Label^  label57;
	private: System::Windows::Forms::TextBox^  textBox68;
	private: System::Windows::Forms::Label^  label58;
	private: System::Windows::Forms::TextBox^  textBox69;
private: System::Windows::Forms::TextBox^  textBoxLN10;

private: System::Windows::Forms::CheckBox^  checkBoxEnCH10;

	private: System::Windows::Forms::Label^  label59;
	private: System::Windows::Forms::TextBox^  textBox71;
	private: System::Windows::Forms::Label^  label60;
	private: System::Windows::Forms::TextBox^  textBox72;
private: System::Windows::Forms::TextBox^  textBoxLN9;

private: System::Windows::Forms::CheckBox^  checkBoxEnCH9;

	private: System::Windows::Forms::Label^  label61;
private: System::Windows::Forms::ComboBox^  comboBoxFig8;

	private: System::Windows::Forms::Button^  button1;
private: System::Windows::Forms::ComboBox^  comboBoxFig7;

	private: System::Windows::Forms::Button^  button2;
private: System::Windows::Forms::ComboBox^  comboBoxFig6;

	private: System::Windows::Forms::Button^  button3;
private: System::Windows::Forms::ComboBox^  comboBoxFig5;

	private: System::Windows::Forms::Button^  button4;
private: System::Windows::Forms::ComboBox^  comboBoxFig4;

	private: System::Windows::Forms::Button^  button5;
private: System::Windows::Forms::ComboBox^  comboBoxFig3;

	private: System::Windows::Forms::Button^  button6;
private: System::Windows::Forms::ComboBox^  comboBoxFig2;

	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Label^  label8;
private: System::Windows::Forms::ComboBox^  comboBoxFig1;

	private: System::Windows::Forms::Label^  label10;
private: System::Windows::Forms::Button^  buttonCol1;

private: System::Windows::Forms::ComboBox^  comboBoxFig20;


	private: System::Windows::Forms::Button^  button9;
private: System::Windows::Forms::ComboBox^  comboBoxFig19;

	private: System::Windows::Forms::Button^  button10;
private: System::Windows::Forms::ComboBox^  comboBoxFig18;

	private: System::Windows::Forms::Button^  button11;
private: System::Windows::Forms::ComboBox^  comboBoxFig17;

	private: System::Windows::Forms::Button^  button12;
private: System::Windows::Forms::ComboBox^  comboBoxFig16;

	private: System::Windows::Forms::Button^  button13;
private: System::Windows::Forms::ComboBox^  comboBoxFig15;

	private: System::Windows::Forms::Button^  button14;
private: System::Windows::Forms::ComboBox^  comboBoxFig14;

	private: System::Windows::Forms::Button^  button15;
	private: System::Windows::Forms::Label^  label39;
private: System::Windows::Forms::ComboBox^  comboBoxFig13;

	private: System::Windows::Forms::Label^  label40;
	private: System::Windows::Forms::Button^  button16;
	private: System::Windows::Forms::TextBox^  textBox26;
	private: System::Windows::Forms::Label^  label25;
	private: System::Windows::Forms::TextBox^  textBox27;
private: System::Windows::Forms::TextBox^  textBoxLN20;

private: System::Windows::Forms::CheckBox^  checkBoxEnCH20;

	private: System::Windows::Forms::Label^  label26;
	private: System::Windows::Forms::TextBox^  textBox29;
	private: System::Windows::Forms::Label^  label27;
	private: System::Windows::Forms::TextBox^  textBox30;
private: System::Windows::Forms::TextBox^  textBoxLN19;

private: System::Windows::Forms::CheckBox^  checkBoxEnCH19;

	private: System::Windows::Forms::Label^  label28;
	private: System::Windows::Forms::TextBox^  textBox32;
	private: System::Windows::Forms::Label^  label29;
	private: System::Windows::Forms::TextBox^  textBox33;
private: System::Windows::Forms::TextBox^  textBoxLN18;

private: System::Windows::Forms::CheckBox^  checkBoxEnCH18;

	private: System::Windows::Forms::Label^  label30;
	private: System::Windows::Forms::TextBox^  textBox35;
	private: System::Windows::Forms::Label^  label31;
	private: System::Windows::Forms::TextBox^  textBox36;
private: System::Windows::Forms::TextBox^  textBoxLN17;

private: System::Windows::Forms::CheckBox^  checkBoxEnCH17;

	private: System::Windows::Forms::Label^  label32;
	private: System::Windows::Forms::TextBox^  textBox38;
	private: System::Windows::Forms::Label^  label33;
	private: System::Windows::Forms::TextBox^  textBox39;
private: System::Windows::Forms::TextBox^  textBoxLN16;

private: System::Windows::Forms::CheckBox^  checkBoxEnCH16;


	private: System::Windows::Forms::Label^  label34;
	private: System::Windows::Forms::TextBox^  textBox41;
	private: System::Windows::Forms::Label^  label35;
	private: System::Windows::Forms::TextBox^  textBox42;
private: System::Windows::Forms::TextBox^  textBoxLN15;

private: System::Windows::Forms::CheckBox^  checkBoxEnCH15;

	private: System::Windows::Forms::Label^  label36;
	private: System::Windows::Forms::TextBox^  textBox44;
	private: System::Windows::Forms::Label^  label37;
	private: System::Windows::Forms::TextBox^  textBox45;
private: System::Windows::Forms::TextBox^  textBoxLN14;

private: System::Windows::Forms::CheckBox^  checkBoxEnCH14;

	private: System::Windows::Forms::Label^  label38;
	private: System::Windows::Forms::TextBox^  textBox47;
	private: System::Windows::Forms::Label^  label41;
	private: System::Windows::Forms::TextBox^  textBox48;
	private: System::Windows::Forms::Label^  label42;
private: System::Windows::Forms::TextBox^  textBoxLN13;

	private: System::Windows::Forms::Label^  label43;
private: System::Windows::Forms::CheckBox^  checkBoxEnCH13;

	private: System::Windows::Forms::Label^  label44;
	private: System::Windows::Forms::Label^  label45;
	private: System::Windows::Forms::TextBox^  textBox14;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::TextBox^  textBox15;
private: System::Windows::Forms::TextBox^  textBoxLN8;

private: System::Windows::Forms::CheckBox^  checkBoxEnCH8;

	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::TextBox^  textBox17;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::TextBox^  textBox18;
private: System::Windows::Forms::TextBox^  textBoxLN7;

private: System::Windows::Forms::CheckBox^  checkBoxEnCH7;

	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::TextBox^  textBox20;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::TextBox^  textBox21;
private: System::Windows::Forms::TextBox^  textBoxLN6;

private: System::Windows::Forms::CheckBox^  checkBoxEnCH6;

	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::TextBox^  textBox23;
	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::TextBox^  textBox24;
private: System::Windows::Forms::TextBox^  textBoxLN5;

private: System::Windows::Forms::CheckBox^  checkBoxEnCH5;

	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::TextBox^  textBox9;
private: System::Windows::Forms::TextBox^  textBoxLN4;

private: System::Windows::Forms::CheckBox^  checkBoxEnCH4;

	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::TextBox^  textBox11;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::TextBox^  textBox12;
private: System::Windows::Forms::TextBox^  textBoxLN3;

private: System::Windows::Forms::CheckBox^  checkBoxEnCH3;

	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::TextBox^  textBox6;
private: System::Windows::Forms::TextBox^  textBoxLN2;

private: System::Windows::Forms::CheckBox^  checkBoxEnCH2;

	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::TextBox^  textBoxLN1;

	private: System::Windows::Forms::Label^  label5;
private: System::Windows::Forms::CheckBox^  checkBoxEnCH1;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
private: System::Windows::Forms::Button^  buttonOk;

private: System::Windows::Forms::Button^  buttonApply;
private: System::Windows::Forms::Button^  buttonCancel;
private: System::Windows::Forms::Button^  buttonLoad;




private: System::Windows::Forms::Label^  label63;

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
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox50 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox45 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox40 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox28 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox46 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox41 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox36 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox35 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox95 = (gcnew System::Windows::Forms::TextBox());
			this->textBox96 = (gcnew System::Windows::Forms::TextBox());
			this->textBox97 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox49 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox98 = (gcnew System::Windows::Forms::TextBox());
			this->textBox99 = (gcnew System::Windows::Forms::TextBox());
			this->textBox90 = (gcnew System::Windows::Forms::TextBox());
			this->textBox91 = (gcnew System::Windows::Forms::TextBox());
			this->textBox92 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox44 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox93 = (gcnew System::Windows::Forms::TextBox());
			this->textBox94 = (gcnew System::Windows::Forms::TextBox());
			this->textBox85 = (gcnew System::Windows::Forms::TextBox());
			this->textBox86 = (gcnew System::Windows::Forms::TextBox());
			this->textBox87 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox39 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox88 = (gcnew System::Windows::Forms::TextBox());
			this->textBox89 = (gcnew System::Windows::Forms::TextBox());
			this->textBox84 = (gcnew System::Windows::Forms::TextBox());
			this->label72 = (gcnew System::Windows::Forms::Label());
			this->textBox80 = (gcnew System::Windows::Forms::TextBox());
			this->textBox81 = (gcnew System::Windows::Forms::TextBox());
			this->label70 = (gcnew System::Windows::Forms::Label());
			this->label68 = (gcnew System::Windows::Forms::Label());
			this->label67 = (gcnew System::Windows::Forms::Label());
			this->checkBox29 = (gcnew System::Windows::Forms::CheckBox());
			this->label66 = (gcnew System::Windows::Forms::Label());
			this->textBox78 = (gcnew System::Windows::Forms::TextBox());
			this->textBox79 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label65 = (gcnew System::Windows::Forms::Label());
			this->textBox76 = (gcnew System::Windows::Forms::TextBox());
			this->textBox77 = (gcnew System::Windows::Forms::TextBox());
			this->label62 = (gcnew System::Windows::Forms::Label());
			this->checkBox32 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox30 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox31 = (gcnew System::Windows::Forms::CheckBox());
			this->label71 = (gcnew System::Windows::Forms::Label());
			this->label69 = (gcnew System::Windows::Forms::Label());
			this->textBoxLNT = (gcnew System::Windows::Forms::TextBox());
			this->textBox82 = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->textBox83 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBoxUn = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox27 = (gcnew System::Windows::Forms::ComboBox());
			this->checkBox26 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox27 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox25 = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->comboBoxFig12 = (gcnew System::Windows::Forms::ComboBox());
			this->button17 = (gcnew System::Windows::Forms::Button());
			this->comboBoxFig11 = (gcnew System::Windows::Forms::ComboBox());
			this->button18 = (gcnew System::Windows::Forms::Button());
			this->comboBoxFig10 = (gcnew System::Windows::Forms::ComboBox());
			this->button19 = (gcnew System::Windows::Forms::Button());
			this->comboBoxFig9 = (gcnew System::Windows::Forms::ComboBox());
			this->button20 = (gcnew System::Windows::Forms::Button());
			this->comboBoxFig24 = (gcnew System::Windows::Forms::ComboBox());
			this->button21 = (gcnew System::Windows::Forms::Button());
			this->comboBoxFig23 = (gcnew System::Windows::Forms::ComboBox());
			this->button22 = (gcnew System::Windows::Forms::Button());
			this->comboBoxFig22 = (gcnew System::Windows::Forms::ComboBox());
			this->button23 = (gcnew System::Windows::Forms::Button());
			this->comboBoxFig21 = (gcnew System::Windows::Forms::ComboBox());
			this->button24 = (gcnew System::Windows::Forms::Button());
			this->textBox50 = (gcnew System::Windows::Forms::TextBox());
			this->label46 = (gcnew System::Windows::Forms::Label());
			this->textBox51 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLN24 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxEnCH24 = (gcnew System::Windows::Forms::CheckBox());
			this->label47 = (gcnew System::Windows::Forms::Label());
			this->textBox53 = (gcnew System::Windows::Forms::TextBox());
			this->label48 = (gcnew System::Windows::Forms::Label());
			this->textBox54 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLN23 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxEnCH23 = (gcnew System::Windows::Forms::CheckBox());
			this->label49 = (gcnew System::Windows::Forms::Label());
			this->textBox56 = (gcnew System::Windows::Forms::TextBox());
			this->label50 = (gcnew System::Windows::Forms::Label());
			this->textBox57 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLN22 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxEnCH22 = (gcnew System::Windows::Forms::CheckBox());
			this->label51 = (gcnew System::Windows::Forms::Label());
			this->textBox59 = (gcnew System::Windows::Forms::TextBox());
			this->label52 = (gcnew System::Windows::Forms::Label());
			this->textBox60 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLN21 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxEnCH21 = (gcnew System::Windows::Forms::CheckBox());
			this->label53 = (gcnew System::Windows::Forms::Label());
			this->textBox62 = (gcnew System::Windows::Forms::TextBox());
			this->label54 = (gcnew System::Windows::Forms::Label());
			this->textBox63 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLN12 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxEnCH12 = (gcnew System::Windows::Forms::CheckBox());
			this->label55 = (gcnew System::Windows::Forms::Label());
			this->textBox65 = (gcnew System::Windows::Forms::TextBox());
			this->label56 = (gcnew System::Windows::Forms::Label());
			this->textBox66 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLN11 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxEnCH11 = (gcnew System::Windows::Forms::CheckBox());
			this->label57 = (gcnew System::Windows::Forms::Label());
			this->textBox68 = (gcnew System::Windows::Forms::TextBox());
			this->label58 = (gcnew System::Windows::Forms::Label());
			this->textBox69 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLN10 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxEnCH10 = (gcnew System::Windows::Forms::CheckBox());
			this->label59 = (gcnew System::Windows::Forms::Label());
			this->textBox71 = (gcnew System::Windows::Forms::TextBox());
			this->label60 = (gcnew System::Windows::Forms::Label());
			this->textBox72 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLN9 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxEnCH9 = (gcnew System::Windows::Forms::CheckBox());
			this->label61 = (gcnew System::Windows::Forms::Label());
			this->comboBoxFig8 = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->comboBoxFig7 = (gcnew System::Windows::Forms::ComboBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->comboBoxFig6 = (gcnew System::Windows::Forms::ComboBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->comboBoxFig5 = (gcnew System::Windows::Forms::ComboBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->comboBoxFig4 = (gcnew System::Windows::Forms::ComboBox());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->comboBoxFig3 = (gcnew System::Windows::Forms::ComboBox());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->comboBoxFig2 = (gcnew System::Windows::Forms::ComboBox());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->comboBoxFig1 = (gcnew System::Windows::Forms::ComboBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->buttonCol1 = (gcnew System::Windows::Forms::Button());
			this->comboBoxFig20 = (gcnew System::Windows::Forms::ComboBox());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->comboBoxFig19 = (gcnew System::Windows::Forms::ComboBox());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->comboBoxFig18 = (gcnew System::Windows::Forms::ComboBox());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->comboBoxFig17 = (gcnew System::Windows::Forms::ComboBox());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->comboBoxFig16 = (gcnew System::Windows::Forms::ComboBox());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->comboBoxFig15 = (gcnew System::Windows::Forms::ComboBox());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->comboBoxFig14 = (gcnew System::Windows::Forms::ComboBox());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->comboBoxFig13 = (gcnew System::Windows::Forms::ComboBox());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->textBox26 = (gcnew System::Windows::Forms::TextBox());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->textBox27 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLN20 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxEnCH20 = (gcnew System::Windows::Forms::CheckBox());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->textBox29 = (gcnew System::Windows::Forms::TextBox());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->textBox30 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLN19 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxEnCH19 = (gcnew System::Windows::Forms::CheckBox());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->textBox32 = (gcnew System::Windows::Forms::TextBox());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->textBox33 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLN18 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxEnCH18 = (gcnew System::Windows::Forms::CheckBox());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->textBox35 = (gcnew System::Windows::Forms::TextBox());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->textBox36 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLN17 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxEnCH17 = (gcnew System::Windows::Forms::CheckBox());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->textBox38 = (gcnew System::Windows::Forms::TextBox());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->textBox39 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLN16 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxEnCH16 = (gcnew System::Windows::Forms::CheckBox());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->textBox41 = (gcnew System::Windows::Forms::TextBox());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->textBox42 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLN15 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxEnCH15 = (gcnew System::Windows::Forms::CheckBox());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->textBox44 = (gcnew System::Windows::Forms::TextBox());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->textBox45 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLN14 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxEnCH14 = (gcnew System::Windows::Forms::CheckBox());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->textBox47 = (gcnew System::Windows::Forms::TextBox());
			this->label41 = (gcnew System::Windows::Forms::Label());
			this->textBox48 = (gcnew System::Windows::Forms::TextBox());
			this->label42 = (gcnew System::Windows::Forms::Label());
			this->textBoxLN13 = (gcnew System::Windows::Forms::TextBox());
			this->label43 = (gcnew System::Windows::Forms::Label());
			this->checkBoxEnCH13 = (gcnew System::Windows::Forms::CheckBox());
			this->label44 = (gcnew System::Windows::Forms::Label());
			this->label45 = (gcnew System::Windows::Forms::Label());
			this->textBox14 = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->textBox15 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLN8 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxEnCH8 = (gcnew System::Windows::Forms::CheckBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->textBox17 = (gcnew System::Windows::Forms::TextBox());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->textBox18 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLN7 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxEnCH7 = (gcnew System::Windows::Forms::CheckBox());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->textBox20 = (gcnew System::Windows::Forms::TextBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->textBox21 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLN6 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxEnCH6 = (gcnew System::Windows::Forms::CheckBox());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->textBox23 = (gcnew System::Windows::Forms::TextBox());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->textBox24 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLN5 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxEnCH5 = (gcnew System::Windows::Forms::CheckBox());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLN4 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxEnCH4 = (gcnew System::Windows::Forms::CheckBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->textBox12 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLN3 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxEnCH3 = (gcnew System::Windows::Forms::CheckBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLN2 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxEnCH2 = (gcnew System::Windows::Forms::CheckBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBoxLN1 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->checkBoxEnCH1 = (gcnew System::Windows::Forms::CheckBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->buttonOk = (gcnew System::Windows::Forms::Button());
			this->buttonApply = (gcnew System::Windows::Forms::Button());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			this->buttonLoad = (gcnew System::Windows::Forms::Button());
			this->label63 = (gcnew System::Windows::Forms::Label());
			this->groupBox3->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->checkBox50);
			this->groupBox3->Controls->Add(this->checkBox45);
			this->groupBox3->Controls->Add(this->checkBox40);
			this->groupBox3->Controls->Add(this->checkBox28);
			this->groupBox3->Controls->Add(this->checkBox46);
			this->groupBox3->Controls->Add(this->checkBox41);
			this->groupBox3->Controls->Add(this->checkBox36);
			this->groupBox3->Controls->Add(this->checkBox35);
			this->groupBox3->Controls->Add(this->textBox95);
			this->groupBox3->Controls->Add(this->textBox96);
			this->groupBox3->Controls->Add(this->textBox97);
			this->groupBox3->Controls->Add(this->checkBox49);
			this->groupBox3->Controls->Add(this->textBox98);
			this->groupBox3->Controls->Add(this->textBox99);
			this->groupBox3->Controls->Add(this->textBox90);
			this->groupBox3->Controls->Add(this->textBox91);
			this->groupBox3->Controls->Add(this->textBox92);
			this->groupBox3->Controls->Add(this->checkBox44);
			this->groupBox3->Controls->Add(this->textBox93);
			this->groupBox3->Controls->Add(this->textBox94);
			this->groupBox3->Controls->Add(this->textBox85);
			this->groupBox3->Controls->Add(this->textBox86);
			this->groupBox3->Controls->Add(this->textBox87);
			this->groupBox3->Controls->Add(this->checkBox39);
			this->groupBox3->Controls->Add(this->textBox88);
			this->groupBox3->Controls->Add(this->textBox89);
			this->groupBox3->Controls->Add(this->textBox84);
			this->groupBox3->Controls->Add(this->label72);
			this->groupBox3->Controls->Add(this->textBox80);
			this->groupBox3->Controls->Add(this->textBox81);
			this->groupBox3->Controls->Add(this->label70);
			this->groupBox3->Controls->Add(this->label68);
			this->groupBox3->Controls->Add(this->label67);
			this->groupBox3->Controls->Add(this->checkBox29);
			this->groupBox3->Controls->Add(this->label66);
			this->groupBox3->Controls->Add(this->textBox78);
			this->groupBox3->Controls->Add(this->textBox79);
			this->groupBox3->Location = System::Drawing::Point(16, 456);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(568, 152);
			this->groupBox3->TabIndex = 316;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Y axis";
			// 
			// checkBox50
			// 
			this->checkBox50->AutoSize = true;
			this->checkBox50->Location = System::Drawing::Point(200, 120);
			this->checkBox50->Name = L"checkBox50";
			this->checkBox50->Size = System::Drawing::Size(71, 16);
			this->checkBox50->TabIndex = 352;
			this->checkBox50->Text = L"logarithm";
			this->checkBox50->UseVisualStyleBackColor = true;
			// 
			// checkBox45
			// 
			this->checkBox45->AutoSize = true;
			this->checkBox45->Location = System::Drawing::Point(200, 96);
			this->checkBox45->Name = L"checkBox45";
			this->checkBox45->Size = System::Drawing::Size(71, 16);
			this->checkBox45->TabIndex = 351;
			this->checkBox45->Text = L"logarithm";
			this->checkBox45->UseVisualStyleBackColor = true;
			// 
			// checkBox40
			// 
			this->checkBox40->AutoSize = true;
			this->checkBox40->Location = System::Drawing::Point(200, 72);
			this->checkBox40->Name = L"checkBox40";
			this->checkBox40->Size = System::Drawing::Size(71, 16);
			this->checkBox40->TabIndex = 350;
			this->checkBox40->Text = L"logarithm";
			this->checkBox40->UseVisualStyleBackColor = true;
			// 
			// checkBox28
			// 
			this->checkBox28->AutoSize = true;
			this->checkBox28->Location = System::Drawing::Point(200, 48);
			this->checkBox28->Name = L"checkBox28";
			this->checkBox28->Size = System::Drawing::Size(71, 16);
			this->checkBox28->TabIndex = 349;
			this->checkBox28->Text = L"logarithm";
			this->checkBox28->UseVisualStyleBackColor = true;
			// 
			// checkBox46
			// 
			this->checkBox46->AutoSize = true;
			this->checkBox46->Location = System::Drawing::Point(280, 120);
			this->checkBox46->Name = L"checkBox46";
			this->checkBox46->Size = System::Drawing::Size(73, 16);
			this->checkBox46->TabIndex = 348;
			this->checkBox46->Text = L"autoscale";
			this->checkBox46->UseVisualStyleBackColor = true;
			// 
			// checkBox41
			// 
			this->checkBox41->AutoSize = true;
			this->checkBox41->Location = System::Drawing::Point(280, 96);
			this->checkBox41->Name = L"checkBox41";
			this->checkBox41->Size = System::Drawing::Size(73, 16);
			this->checkBox41->TabIndex = 347;
			this->checkBox41->Text = L"autoscale";
			this->checkBox41->UseVisualStyleBackColor = true;
			// 
			// checkBox36
			// 
			this->checkBox36->AutoSize = true;
			this->checkBox36->Location = System::Drawing::Point(280, 72);
			this->checkBox36->Name = L"checkBox36";
			this->checkBox36->Size = System::Drawing::Size(73, 16);
			this->checkBox36->TabIndex = 346;
			this->checkBox36->Text = L"autoscale";
			this->checkBox36->UseVisualStyleBackColor = true;
			// 
			// checkBox35
			// 
			this->checkBox35->AutoSize = true;
			this->checkBox35->Location = System::Drawing::Point(280, 48);
			this->checkBox35->Name = L"checkBox35";
			this->checkBox35->Size = System::Drawing::Size(73, 16);
			this->checkBox35->TabIndex = 345;
			this->checkBox35->Text = L"autoscale";
			this->checkBox35->UseVisualStyleBackColor = true;
			// 
			// textBox95
			// 
			this->textBox95->Location = System::Drawing::Point(64, 120);
			this->textBox95->Name = L"textBox95";
			this->textBox95->Size = System::Drawing::Size(120, 19);
			this->textBox95->TabIndex = 338;
			// 
			// textBox96
			// 
			this->textBox96->Location = System::Drawing::Point(520, 120);
			this->textBox96->Name = L"textBox96";
			this->textBox96->Size = System::Drawing::Size(32, 19);
			this->textBox96->TabIndex = 342;
			// 
			// textBox97
			// 
			this->textBox97->Location = System::Drawing::Point(480, 120);
			this->textBox97->Name = L"textBox97";
			this->textBox97->Size = System::Drawing::Size(32, 19);
			this->textBox97->TabIndex = 341;
			// 
			// checkBox49
			// 
			this->checkBox49->AutoSize = true;
			this->checkBox49->Location = System::Drawing::Point(16, 120);
			this->checkBox49->Name = L"checkBox49";
			this->checkBox49->Size = System::Drawing::Size(38, 16);
			this->checkBox49->TabIndex = 337;
			this->checkBox49->Text = L"(a)";
			this->checkBox49->UseVisualStyleBackColor = true;
			// 
			// textBox98
			// 
			this->textBox98->Location = System::Drawing::Point(416, 120);
			this->textBox98->Name = L"textBox98";
			this->textBox98->Size = System::Drawing::Size(48, 19);
			this->textBox98->TabIndex = 340;
			// 
			// textBox99
			// 
			this->textBox99->Location = System::Drawing::Point(360, 120);
			this->textBox99->Name = L"textBox99";
			this->textBox99->Size = System::Drawing::Size(48, 19);
			this->textBox99->TabIndex = 339;
			// 
			// textBox90
			// 
			this->textBox90->Location = System::Drawing::Point(64, 96);
			this->textBox90->Name = L"textBox90";
			this->textBox90->Size = System::Drawing::Size(120, 19);
			this->textBox90->TabIndex = 330;
			// 
			// textBox91
			// 
			this->textBox91->Location = System::Drawing::Point(520, 96);
			this->textBox91->Name = L"textBox91";
			this->textBox91->Size = System::Drawing::Size(32, 19);
			this->textBox91->TabIndex = 334;
			// 
			// textBox92
			// 
			this->textBox92->Location = System::Drawing::Point(480, 96);
			this->textBox92->Name = L"textBox92";
			this->textBox92->Size = System::Drawing::Size(32, 19);
			this->textBox92->TabIndex = 333;
			// 
			// checkBox44
			// 
			this->checkBox44->AutoSize = true;
			this->checkBox44->Location = System::Drawing::Point(16, 96);
			this->checkBox44->Name = L"checkBox44";
			this->checkBox44->Size = System::Drawing::Size(38, 16);
			this->checkBox44->TabIndex = 329;
			this->checkBox44->Text = L"(a)";
			this->checkBox44->UseVisualStyleBackColor = true;
			// 
			// textBox93
			// 
			this->textBox93->Location = System::Drawing::Point(416, 96);
			this->textBox93->Name = L"textBox93";
			this->textBox93->Size = System::Drawing::Size(48, 19);
			this->textBox93->TabIndex = 332;
			// 
			// textBox94
			// 
			this->textBox94->Location = System::Drawing::Point(360, 96);
			this->textBox94->Name = L"textBox94";
			this->textBox94->Size = System::Drawing::Size(48, 19);
			this->textBox94->TabIndex = 331;
			// 
			// textBox85
			// 
			this->textBox85->Location = System::Drawing::Point(64, 72);
			this->textBox85->Name = L"textBox85";
			this->textBox85->Size = System::Drawing::Size(120, 19);
			this->textBox85->TabIndex = 322;
			// 
			// textBox86
			// 
			this->textBox86->Location = System::Drawing::Point(520, 72);
			this->textBox86->Name = L"textBox86";
			this->textBox86->Size = System::Drawing::Size(32, 19);
			this->textBox86->TabIndex = 326;
			// 
			// textBox87
			// 
			this->textBox87->Location = System::Drawing::Point(480, 72);
			this->textBox87->Name = L"textBox87";
			this->textBox87->Size = System::Drawing::Size(32, 19);
			this->textBox87->TabIndex = 325;
			// 
			// checkBox39
			// 
			this->checkBox39->AutoSize = true;
			this->checkBox39->Location = System::Drawing::Point(16, 72);
			this->checkBox39->Name = L"checkBox39";
			this->checkBox39->Size = System::Drawing::Size(38, 16);
			this->checkBox39->TabIndex = 321;
			this->checkBox39->Text = L"(a)";
			this->checkBox39->UseVisualStyleBackColor = true;
			// 
			// textBox88
			// 
			this->textBox88->Location = System::Drawing::Point(416, 72);
			this->textBox88->Name = L"textBox88";
			this->textBox88->Size = System::Drawing::Size(48, 19);
			this->textBox88->TabIndex = 324;
			// 
			// textBox89
			// 
			this->textBox89->Location = System::Drawing::Point(360, 72);
			this->textBox89->Name = L"textBox89";
			this->textBox89->Size = System::Drawing::Size(48, 19);
			this->textBox89->TabIndex = 323;
			// 
			// textBox84
			// 
			this->textBox84->Location = System::Drawing::Point(64, 48);
			this->textBox84->Name = L"textBox84";
			this->textBox84->Size = System::Drawing::Size(120, 19);
			this->textBox84->TabIndex = 311;
			// 
			// label72
			// 
			this->label72->AutoSize = true;
			this->label72->Location = System::Drawing::Point(64, 24);
			this->label72->Name = L"label72";
			this->label72->Size = System::Drawing::Size(58, 12);
			this->label72->TabIndex = 310;
			this->label72->Text = L"figure title";
			// 
			// textBox80
			// 
			this->textBox80->Location = System::Drawing::Point(520, 48);
			this->textBox80->Name = L"textBox80";
			this->textBox80->Size = System::Drawing::Size(32, 19);
			this->textBox80->TabIndex = 318;
			// 
			// textBox81
			// 
			this->textBox81->Location = System::Drawing::Point(480, 48);
			this->textBox81->Name = L"textBox81";
			this->textBox81->Size = System::Drawing::Size(32, 19);
			this->textBox81->TabIndex = 317;
			// 
			// label70
			// 
			this->label70->AutoSize = true;
			this->label70->Location = System::Drawing::Point(520, 24);
			this->label70->Name = L"label70";
			this->label70->Size = System::Drawing::Size(39, 12);
			this->label70->TabIndex = 316;
			this->label70->Text = L"mytics";
			// 
			// label68
			// 
			this->label68->AutoSize = true;
			this->label68->Location = System::Drawing::Point(480, 24);
			this->label68->Name = L"label68";
			this->label68->Size = System::Drawing::Size(30, 12);
			this->label68->TabIndex = 315;
			this->label68->Text = L"ytics";
			// 
			// label67
			// 
			this->label67->AutoSize = true;
			this->label67->Location = System::Drawing::Point(16, 24);
			this->label67->Name = L"label67";
			this->label67->Size = System::Drawing::Size(34, 12);
			this->label67->TabIndex = 309;
			this->label67->Text = L"figure";
			// 
			// checkBox29
			// 
			this->checkBox29->AutoSize = true;
			this->checkBox29->Location = System::Drawing::Point(16, 48);
			this->checkBox29->Name = L"checkBox29";
			this->checkBox29->Size = System::Drawing::Size(38, 16);
			this->checkBox29->TabIndex = 308;
			this->checkBox29->Text = L"(a)";
			this->checkBox29->UseVisualStyleBackColor = true;
			// 
			// label66
			// 
			this->label66->AutoSize = true;
			this->label66->Location = System::Drawing::Point(360, 24);
			this->label66->Name = L"label66";
			this->label66->Size = System::Drawing::Size(108, 12);
			this->label66->TabIndex = 312;
			this->label66->Text = L"yrange (ymin, yMax)";
			// 
			// textBox78
			// 
			this->textBox78->Location = System::Drawing::Point(416, 48);
			this->textBox78->Name = L"textBox78";
			this->textBox78->Size = System::Drawing::Size(48, 19);
			this->textBox78->TabIndex = 314;
			// 
			// textBox79
			// 
			this->textBox79->Location = System::Drawing::Point(360, 48);
			this->textBox79->Name = L"textBox79";
			this->textBox79->Size = System::Drawing::Size(48, 19);
			this->textBox79->TabIndex = 313;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label65);
			this->groupBox1->Controls->Add(this->textBox76);
			this->groupBox1->Controls->Add(this->textBox77);
			this->groupBox1->Controls->Add(this->label62);
			this->groupBox1->Controls->Add(this->checkBox31);
			this->groupBox1->Controls->Add(this->label71);
			this->groupBox1->Controls->Add(this->label69);
			this->groupBox1->Controls->Add(this->textBoxLNT);
			this->groupBox1->Controls->Add(this->textBox82);
			this->groupBox1->Controls->Add(this->label11);
			this->groupBox1->Controls->Add(this->textBox83);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->comboBoxUn);
			this->groupBox1->Location = System::Drawing::Point(16, 368);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(568, 80);
			this->groupBox1->TabIndex = 315;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"X axis";
			// 
			// label65
			// 
			this->label65->AutoSize = true;
			this->label65->Location = System::Drawing::Point(360, 24);
			this->label65->Name = L"label65";
			this->label65->Size = System::Drawing::Size(108, 12);
			this->label65->TabIndex = 262;
			this->label65->Text = L"xrange (xmin, xMax)";
			// 
			// textBox76
			// 
			this->textBox76->Location = System::Drawing::Point(416, 48);
			this->textBox76->Name = L"textBox76";
			this->textBox76->Size = System::Drawing::Size(48, 19);
			this->textBox76->TabIndex = 264;
			// 
			// textBox77
			// 
			this->textBox77->Location = System::Drawing::Point(360, 48);
			this->textBox77->Name = L"textBox77";
			this->textBox77->Size = System::Drawing::Size(48, 19);
			this->textBox77->TabIndex = 263;
			// 
			// label62
			// 
			this->label62->AutoSize = true;
			this->label62->Location = System::Drawing::Point(200, 24);
			this->label62->Name = L"label62";
			this->label62->Size = System::Drawing::Size(24, 12);
			this->label62->TabIndex = 261;
			this->label62->Text = L"unit";
			// 
			// checkBox32
			// 
			this->checkBox32->AutoSize = true;
			this->checkBox32->Location = System::Drawing::Point(616, 512);
			this->checkBox32->Name = L"checkBox32";
			this->checkBox32->Size = System::Drawing::Size(105, 16);
			this->checkBox32->TabIndex = 260;
			this->checkBox32->Text = L"show minor grid";
			this->checkBox32->UseVisualStyleBackColor = true;
			// 
			// checkBox30
			// 
			this->checkBox30->AutoSize = true;
			this->checkBox30->Location = System::Drawing::Point(616, 488);
			this->checkBox30->Name = L"checkBox30";
			this->checkBox30->Size = System::Drawing::Size(105, 16);
			this->checkBox30->TabIndex = 259;
			this->checkBox30->Text = L"show major grid";
			this->checkBox30->UseVisualStyleBackColor = true;
			// 
			// checkBox31
			// 
			this->checkBox31->AutoSize = true;
			this->checkBox31->Location = System::Drawing::Point(280, 48);
			this->checkBox31->Name = L"checkBox31";
			this->checkBox31->Size = System::Drawing::Size(73, 16);
			this->checkBox31->TabIndex = 258;
			this->checkBox31->Text = L"autoscale";
			this->checkBox31->UseVisualStyleBackColor = true;
			// 
			// label71
			// 
			this->label71->AutoSize = true;
			this->label71->Location = System::Drawing::Point(520, 24);
			this->label71->Name = L"label71";
			this->label71->Size = System::Drawing::Size(39, 12);
			this->label71->TabIndex = 256;
			this->label71->Text = L"mxtics";
			// 
			// label69
			// 
			this->label69->AutoSize = true;
			this->label69->Location = System::Drawing::Point(480, 24);
			this->label69->Name = L"label69";
			this->label69->Size = System::Drawing::Size(30, 12);
			this->label69->TabIndex = 250;
			this->label69->Text = L"xtics";
			// 
			// textBoxLNT
			// 
			this->textBoxLNT->Location = System::Drawing::Point(64, 48);
			this->textBoxLNT->Name = L"textBoxLNT";
			this->textBoxLNT->Size = System::Drawing::Size(120, 19);
			this->textBoxLNT->TabIndex = 20;
			// 
			// textBox82
			// 
			this->textBox82->Location = System::Drawing::Point(520, 48);
			this->textBox82->Name = L"textBox82";
			this->textBox82->Size = System::Drawing::Size(32, 19);
			this->textBox82->TabIndex = 252;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(64, 24);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(60, 12);
			this->label11->TabIndex = 19;
			this->label11->Text = L"label name";
			// 
			// textBox83
			// 
			this->textBox83->Location = System::Drawing::Point(480, 48);
			this->textBox83->Name = L"textBox83";
			this->textBox83->Size = System::Drawing::Size(32, 19);
			this->textBox83->TabIndex = 251;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(16, 24);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(41, 12);
			this->label2->TabIndex = 6;
			this->label2->Text = L"column";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(16, 48);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(30, 12);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Time";
			// 
			// comboBoxUn
			// 
			this->comboBoxUn->FormattingEnabled = true;
			this->comboBoxUn->Location = System::Drawing::Point(200, 48);
			this->comboBoxUn->Name = L"comboBoxUn";
			this->comboBoxUn->Size = System::Drawing::Size(48, 20);
			this->comboBoxUn->TabIndex = 4;
			// 
			// comboBox27
			// 
			this->comboBox27->FormattingEnabled = true;
			this->comboBox27->Location = System::Drawing::Point(648, 464);
			this->comboBox27->Name = L"comboBox27";
			this->comboBox27->Size = System::Drawing::Size(40, 20);
			this->comboBox27->TabIndex = 313;
			// 
			// checkBox26
			// 
			this->checkBox26->AutoSize = true;
			this->checkBox26->Location = System::Drawing::Point(616, 416);
			this->checkBox26->Name = L"checkBox26";
			this->checkBox26->Size = System::Drawing::Size(79, 16);
			this->checkBox26->TabIndex = 314;
			this->checkBox26->Text = L"plot by dot";
			this->checkBox26->UseVisualStyleBackColor = true;
			// 
			// checkBox27
			// 
			this->checkBox27->AutoSize = true;
			this->checkBox27->Location = System::Drawing::Point(616, 440);
			this->checkBox27->Name = L"checkBox27";
			this->checkBox27->Size = System::Drawing::Size(81, 16);
			this->checkBox27->TabIndex = 311;
			this->checkBox27->Text = L"limit points";
			this->checkBox27->UseVisualStyleBackColor = true;
			// 
			// checkBox25
			// 
			this->checkBox25->AutoSize = true;
			this->checkBox25->Location = System::Drawing::Point(616, 392);
			this->checkBox25->Name = L"checkBox25";
			this->checkBox25->Size = System::Drawing::Size(132, 16);
			this->checkBox25->TabIndex = 312;
			this->checkBox25->Text = L"show satulation level";
			this->checkBox25->UseVisualStyleBackColor = true;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->comboBoxFig12);
			this->groupBox2->Controls->Add(this->button17);
			this->groupBox2->Controls->Add(this->comboBoxFig11);
			this->groupBox2->Controls->Add(this->button18);
			this->groupBox2->Controls->Add(this->comboBoxFig10);
			this->groupBox2->Controls->Add(this->button19);
			this->groupBox2->Controls->Add(this->comboBoxFig9);
			this->groupBox2->Controls->Add(this->button20);
			this->groupBox2->Controls->Add(this->comboBoxFig24);
			this->groupBox2->Controls->Add(this->button21);
			this->groupBox2->Controls->Add(this->comboBoxFig23);
			this->groupBox2->Controls->Add(this->button22);
			this->groupBox2->Controls->Add(this->comboBoxFig22);
			this->groupBox2->Controls->Add(this->button23);
			this->groupBox2->Controls->Add(this->comboBoxFig21);
			this->groupBox2->Controls->Add(this->button24);
			this->groupBox2->Controls->Add(this->textBox50);
			this->groupBox2->Controls->Add(this->label46);
			this->groupBox2->Controls->Add(this->textBox51);
			this->groupBox2->Controls->Add(this->textBoxLN24);
			this->groupBox2->Controls->Add(this->checkBoxEnCH24);
			this->groupBox2->Controls->Add(this->label47);
			this->groupBox2->Controls->Add(this->textBox53);
			this->groupBox2->Controls->Add(this->label48);
			this->groupBox2->Controls->Add(this->textBox54);
			this->groupBox2->Controls->Add(this->textBoxLN23);
			this->groupBox2->Controls->Add(this->checkBoxEnCH23);
			this->groupBox2->Controls->Add(this->label49);
			this->groupBox2->Controls->Add(this->textBox56);
			this->groupBox2->Controls->Add(this->label50);
			this->groupBox2->Controls->Add(this->textBox57);
			this->groupBox2->Controls->Add(this->textBoxLN22);
			this->groupBox2->Controls->Add(this->checkBoxEnCH22);
			this->groupBox2->Controls->Add(this->label51);
			this->groupBox2->Controls->Add(this->textBox59);
			this->groupBox2->Controls->Add(this->label52);
			this->groupBox2->Controls->Add(this->textBox60);
			this->groupBox2->Controls->Add(this->textBoxLN21);
			this->groupBox2->Controls->Add(this->checkBoxEnCH21);
			this->groupBox2->Controls->Add(this->label53);
			this->groupBox2->Controls->Add(this->textBox62);
			this->groupBox2->Controls->Add(this->label54);
			this->groupBox2->Controls->Add(this->textBox63);
			this->groupBox2->Controls->Add(this->textBoxLN12);
			this->groupBox2->Controls->Add(this->checkBoxEnCH12);
			this->groupBox2->Controls->Add(this->label55);
			this->groupBox2->Controls->Add(this->textBox65);
			this->groupBox2->Controls->Add(this->label56);
			this->groupBox2->Controls->Add(this->textBox66);
			this->groupBox2->Controls->Add(this->textBoxLN11);
			this->groupBox2->Controls->Add(this->checkBoxEnCH11);
			this->groupBox2->Controls->Add(this->label57);
			this->groupBox2->Controls->Add(this->textBox68);
			this->groupBox2->Controls->Add(this->label58);
			this->groupBox2->Controls->Add(this->textBox69);
			this->groupBox2->Controls->Add(this->textBoxLN10);
			this->groupBox2->Controls->Add(this->checkBoxEnCH10);
			this->groupBox2->Controls->Add(this->label59);
			this->groupBox2->Controls->Add(this->textBox71);
			this->groupBox2->Controls->Add(this->label60);
			this->groupBox2->Controls->Add(this->textBox72);
			this->groupBox2->Controls->Add(this->textBoxLN9);
			this->groupBox2->Controls->Add(this->checkBoxEnCH9);
			this->groupBox2->Controls->Add(this->label61);
			this->groupBox2->Controls->Add(this->comboBoxFig8);
			this->groupBox2->Controls->Add(this->button1);
			this->groupBox2->Controls->Add(this->comboBoxFig7);
			this->groupBox2->Controls->Add(this->button2);
			this->groupBox2->Controls->Add(this->comboBoxFig6);
			this->groupBox2->Controls->Add(this->button3);
			this->groupBox2->Controls->Add(this->comboBoxFig5);
			this->groupBox2->Controls->Add(this->button4);
			this->groupBox2->Controls->Add(this->comboBoxFig4);
			this->groupBox2->Controls->Add(this->button5);
			this->groupBox2->Controls->Add(this->comboBoxFig3);
			this->groupBox2->Controls->Add(this->button6);
			this->groupBox2->Controls->Add(this->comboBoxFig2);
			this->groupBox2->Controls->Add(this->button7);
			this->groupBox2->Controls->Add(this->label8);
			this->groupBox2->Controls->Add(this->comboBoxFig1);
			this->groupBox2->Controls->Add(this->label10);
			this->groupBox2->Controls->Add(this->buttonCol1);
			this->groupBox2->Controls->Add(this->comboBoxFig20);
			this->groupBox2->Controls->Add(this->button9);
			this->groupBox2->Controls->Add(this->comboBoxFig19);
			this->groupBox2->Controls->Add(this->button10);
			this->groupBox2->Controls->Add(this->comboBoxFig18);
			this->groupBox2->Controls->Add(this->button11);
			this->groupBox2->Controls->Add(this->comboBoxFig17);
			this->groupBox2->Controls->Add(this->button12);
			this->groupBox2->Controls->Add(this->comboBoxFig16);
			this->groupBox2->Controls->Add(this->button13);
			this->groupBox2->Controls->Add(this->comboBoxFig15);
			this->groupBox2->Controls->Add(this->button14);
			this->groupBox2->Controls->Add(this->comboBoxFig14);
			this->groupBox2->Controls->Add(this->button15);
			this->groupBox2->Controls->Add(this->label39);
			this->groupBox2->Controls->Add(this->comboBoxFig13);
			this->groupBox2->Controls->Add(this->label40);
			this->groupBox2->Controls->Add(this->button16);
			this->groupBox2->Controls->Add(this->textBox26);
			this->groupBox2->Controls->Add(this->label25);
			this->groupBox2->Controls->Add(this->textBox27);
			this->groupBox2->Controls->Add(this->textBoxLN20);
			this->groupBox2->Controls->Add(this->checkBoxEnCH20);
			this->groupBox2->Controls->Add(this->label26);
			this->groupBox2->Controls->Add(this->textBox29);
			this->groupBox2->Controls->Add(this->label27);
			this->groupBox2->Controls->Add(this->textBox30);
			this->groupBox2->Controls->Add(this->textBoxLN19);
			this->groupBox2->Controls->Add(this->checkBoxEnCH19);
			this->groupBox2->Controls->Add(this->label28);
			this->groupBox2->Controls->Add(this->textBox32);
			this->groupBox2->Controls->Add(this->label29);
			this->groupBox2->Controls->Add(this->textBox33);
			this->groupBox2->Controls->Add(this->textBoxLN18);
			this->groupBox2->Controls->Add(this->checkBoxEnCH18);
			this->groupBox2->Controls->Add(this->label30);
			this->groupBox2->Controls->Add(this->textBox35);
			this->groupBox2->Controls->Add(this->label31);
			this->groupBox2->Controls->Add(this->textBox36);
			this->groupBox2->Controls->Add(this->textBoxLN17);
			this->groupBox2->Controls->Add(this->checkBoxEnCH17);
			this->groupBox2->Controls->Add(this->label32);
			this->groupBox2->Controls->Add(this->textBox38);
			this->groupBox2->Controls->Add(this->label33);
			this->groupBox2->Controls->Add(this->textBox39);
			this->groupBox2->Controls->Add(this->textBoxLN16);
			this->groupBox2->Controls->Add(this->checkBoxEnCH16);
			this->groupBox2->Controls->Add(this->label34);
			this->groupBox2->Controls->Add(this->textBox41);
			this->groupBox2->Controls->Add(this->label35);
			this->groupBox2->Controls->Add(this->textBox42);
			this->groupBox2->Controls->Add(this->textBoxLN15);
			this->groupBox2->Controls->Add(this->checkBoxEnCH15);
			this->groupBox2->Controls->Add(this->label36);
			this->groupBox2->Controls->Add(this->textBox44);
			this->groupBox2->Controls->Add(this->label37);
			this->groupBox2->Controls->Add(this->textBox45);
			this->groupBox2->Controls->Add(this->textBoxLN14);
			this->groupBox2->Controls->Add(this->checkBoxEnCH14);
			this->groupBox2->Controls->Add(this->label38);
			this->groupBox2->Controls->Add(this->textBox47);
			this->groupBox2->Controls->Add(this->label41);
			this->groupBox2->Controls->Add(this->textBox48);
			this->groupBox2->Controls->Add(this->label42);
			this->groupBox2->Controls->Add(this->textBoxLN13);
			this->groupBox2->Controls->Add(this->label43);
			this->groupBox2->Controls->Add(this->checkBoxEnCH13);
			this->groupBox2->Controls->Add(this->label44);
			this->groupBox2->Controls->Add(this->label45);
			this->groupBox2->Controls->Add(this->textBox14);
			this->groupBox2->Controls->Add(this->label17);
			this->groupBox2->Controls->Add(this->textBox15);
			this->groupBox2->Controls->Add(this->textBoxLN8);
			this->groupBox2->Controls->Add(this->checkBoxEnCH8);
			this->groupBox2->Controls->Add(this->label18);
			this->groupBox2->Controls->Add(this->textBox17);
			this->groupBox2->Controls->Add(this->label19);
			this->groupBox2->Controls->Add(this->textBox18);
			this->groupBox2->Controls->Add(this->textBoxLN7);
			this->groupBox2->Controls->Add(this->checkBoxEnCH7);
			this->groupBox2->Controls->Add(this->label20);
			this->groupBox2->Controls->Add(this->textBox20);
			this->groupBox2->Controls->Add(this->label21);
			this->groupBox2->Controls->Add(this->textBox21);
			this->groupBox2->Controls->Add(this->textBoxLN6);
			this->groupBox2->Controls->Add(this->checkBoxEnCH6);
			this->groupBox2->Controls->Add(this->label22);
			this->groupBox2->Controls->Add(this->textBox23);
			this->groupBox2->Controls->Add(this->label23);
			this->groupBox2->Controls->Add(this->textBox24);
			this->groupBox2->Controls->Add(this->textBoxLN5);
			this->groupBox2->Controls->Add(this->checkBoxEnCH5);
			this->groupBox2->Controls->Add(this->label24);
			this->groupBox2->Controls->Add(this->textBox8);
			this->groupBox2->Controls->Add(this->label13);
			this->groupBox2->Controls->Add(this->textBox9);
			this->groupBox2->Controls->Add(this->textBoxLN4);
			this->groupBox2->Controls->Add(this->checkBoxEnCH4);
			this->groupBox2->Controls->Add(this->label14);
			this->groupBox2->Controls->Add(this->textBox11);
			this->groupBox2->Controls->Add(this->label15);
			this->groupBox2->Controls->Add(this->textBox12);
			this->groupBox2->Controls->Add(this->textBoxLN3);
			this->groupBox2->Controls->Add(this->checkBoxEnCH3);
			this->groupBox2->Controls->Add(this->label16);
			this->groupBox2->Controls->Add(this->textBox5);
			this->groupBox2->Controls->Add(this->label9);
			this->groupBox2->Controls->Add(this->textBox6);
			this->groupBox2->Controls->Add(this->textBoxLN2);
			this->groupBox2->Controls->Add(this->checkBoxEnCH2);
			this->groupBox2->Controls->Add(this->label12);
			this->groupBox2->Controls->Add(this->textBox3);
			this->groupBox2->Controls->Add(this->label7);
			this->groupBox2->Controls->Add(this->textBox2);
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Controls->Add(this->textBoxLN1);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Controls->Add(this->checkBoxEnCH1);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Location = System::Drawing::Point(16, 8);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(816, 344);
			this->groupBox2->TabIndex = 310;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Data set";
			// 
			// comboBoxFig12
			// 
			this->comboBoxFig12->FormattingEnabled = true;
			this->comboBoxFig12->Location = System::Drawing::Point(72, 312);
			this->comboBoxFig12->Name = L"comboBoxFig12";
			this->comboBoxFig12->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig12->TabIndex = 243;
			// 
			// button17
			// 
			this->button17->ForeColor = System::Drawing::Color::Red;
			this->button17->Location = System::Drawing::Point(120, 312);
			this->button17->Name = L"button17";
			this->button17->Size = System::Drawing::Size(24, 23);
			this->button17->TabIndex = 242;
			this->button17->Text = L"■";
			this->button17->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig11
			// 
			this->comboBoxFig11->FormattingEnabled = true;
			this->comboBoxFig11->Location = System::Drawing::Point(72, 288);
			this->comboBoxFig11->Name = L"comboBoxFig11";
			this->comboBoxFig11->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig11->TabIndex = 241;
			// 
			// button18
			// 
			this->button18->ForeColor = System::Drawing::Color::Red;
			this->button18->Location = System::Drawing::Point(120, 288);
			this->button18->Name = L"button18";
			this->button18->Size = System::Drawing::Size(24, 23);
			this->button18->TabIndex = 240;
			this->button18->Text = L"■";
			this->button18->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig10
			// 
			this->comboBoxFig10->FormattingEnabled = true;
			this->comboBoxFig10->Location = System::Drawing::Point(72, 264);
			this->comboBoxFig10->Name = L"comboBoxFig10";
			this->comboBoxFig10->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig10->TabIndex = 239;
			// 
			// button19
			// 
			this->button19->ForeColor = System::Drawing::Color::Red;
			this->button19->Location = System::Drawing::Point(120, 264);
			this->button19->Name = L"button19";
			this->button19->Size = System::Drawing::Size(24, 23);
			this->button19->TabIndex = 238;
			this->button19->Text = L"■";
			this->button19->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig9
			// 
			this->comboBoxFig9->FormattingEnabled = true;
			this->comboBoxFig9->Location = System::Drawing::Point(72, 240);
			this->comboBoxFig9->Name = L"comboBoxFig9";
			this->comboBoxFig9->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig9->TabIndex = 237;
			// 
			// button20
			// 
			this->button20->ForeColor = System::Drawing::Color::Red;
			this->button20->Location = System::Drawing::Point(120, 240);
			this->button20->Name = L"button20";
			this->button20->Size = System::Drawing::Size(24, 23);
			this->button20->TabIndex = 236;
			this->button20->Text = L"■";
			this->button20->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig24
			// 
			this->comboBoxFig24->FormattingEnabled = true;
			this->comboBoxFig24->Location = System::Drawing::Point(480, 312);
			this->comboBoxFig24->Name = L"comboBoxFig24";
			this->comboBoxFig24->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig24->TabIndex = 235;
			// 
			// button21
			// 
			this->button21->ForeColor = System::Drawing::Color::Red;
			this->button21->Location = System::Drawing::Point(528, 312);
			this->button21->Name = L"button21";
			this->button21->Size = System::Drawing::Size(24, 23);
			this->button21->TabIndex = 234;
			this->button21->Text = L"■";
			this->button21->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig23
			// 
			this->comboBoxFig23->FormattingEnabled = true;
			this->comboBoxFig23->Location = System::Drawing::Point(480, 288);
			this->comboBoxFig23->Name = L"comboBoxFig23";
			this->comboBoxFig23->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig23->TabIndex = 233;
			// 
			// button22
			// 
			this->button22->ForeColor = System::Drawing::Color::Red;
			this->button22->Location = System::Drawing::Point(528, 288);
			this->button22->Name = L"button22";
			this->button22->Size = System::Drawing::Size(24, 23);
			this->button22->TabIndex = 232;
			this->button22->Text = L"■";
			this->button22->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig22
			// 
			this->comboBoxFig22->FormattingEnabled = true;
			this->comboBoxFig22->Location = System::Drawing::Point(480, 264);
			this->comboBoxFig22->Name = L"comboBoxFig22";
			this->comboBoxFig22->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig22->TabIndex = 231;
			// 
			// button23
			// 
			this->button23->ForeColor = System::Drawing::Color::Red;
			this->button23->Location = System::Drawing::Point(528, 264);
			this->button23->Name = L"button23";
			this->button23->Size = System::Drawing::Size(24, 23);
			this->button23->TabIndex = 230;
			this->button23->Text = L"■";
			this->button23->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig21
			// 
			this->comboBoxFig21->FormattingEnabled = true;
			this->comboBoxFig21->Location = System::Drawing::Point(480, 240);
			this->comboBoxFig21->Name = L"comboBoxFig21";
			this->comboBoxFig21->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig21->TabIndex = 229;
			// 
			// button24
			// 
			this->button24->ForeColor = System::Drawing::Color::Red;
			this->button24->Location = System::Drawing::Point(528, 240);
			this->button24->Name = L"button24";
			this->button24->Size = System::Drawing::Size(24, 23);
			this->button24->TabIndex = 228;
			this->button24->Text = L"■";
			this->button24->UseVisualStyleBackColor = true;
			// 
			// textBox50
			// 
			this->textBox50->Location = System::Drawing::Point(768, 312);
			this->textBox50->Name = L"textBox50";
			this->textBox50->Size = System::Drawing::Size(32, 19);
			this->textBox50->TabIndex = 227;
			// 
			// label46
			// 
			this->label46->AutoSize = true;
			this->label46->Location = System::Drawing::Point(752, 312);
			this->label46->Name = L"label46";
			this->label46->Size = System::Drawing::Size(11, 12);
			this->label46->TabIndex = 226;
			this->label46->Text = L"+";
			// 
			// textBox51
			// 
			this->textBox51->Location = System::Drawing::Point(712, 312);
			this->textBox51->Name = L"textBox51";
			this->textBox51->Size = System::Drawing::Size(32, 19);
			this->textBox51->TabIndex = 225;
			// 
			// textBoxLN24
			// 
			this->textBoxLN24->Location = System::Drawing::Point(568, 312);
			this->textBoxLN24->Name = L"textBoxLN24";
			this->textBoxLN24->Size = System::Drawing::Size(120, 19);
			this->textBoxLN24->TabIndex = 224;
			// 
			// checkBoxEnCH24
			// 
			this->checkBoxEnCH24->AutoSize = true;
			this->checkBoxEnCH24->Location = System::Drawing::Point(424, 312);
			this->checkBoxEnCH24->Name = L"checkBoxEnCH24";
			this->checkBoxEnCH24->Size = System::Drawing::Size(46, 16);
			this->checkBoxEnCH24->TabIndex = 223;
			this->checkBoxEnCH24->Text = L"CH1";
			this->checkBoxEnCH24->UseVisualStyleBackColor = true;
			// 
			// label47
			// 
			this->label47->AutoSize = true;
			this->label47->Location = System::Drawing::Point(696, 312);
			this->label47->Name = L"label47";
			this->label47->Size = System::Drawing::Size(11, 12);
			this->label47->TabIndex = 222;
			this->label47->Text = L"*";
			// 
			// textBox53
			// 
			this->textBox53->Location = System::Drawing::Point(768, 288);
			this->textBox53->Name = L"textBox53";
			this->textBox53->Size = System::Drawing::Size(32, 19);
			this->textBox53->TabIndex = 221;
			// 
			// label48
			// 
			this->label48->AutoSize = true;
			this->label48->Location = System::Drawing::Point(752, 288);
			this->label48->Name = L"label48";
			this->label48->Size = System::Drawing::Size(11, 12);
			this->label48->TabIndex = 220;
			this->label48->Text = L"+";
			// 
			// textBox54
			// 
			this->textBox54->Location = System::Drawing::Point(712, 288);
			this->textBox54->Name = L"textBox54";
			this->textBox54->Size = System::Drawing::Size(32, 19);
			this->textBox54->TabIndex = 219;
			// 
			// textBoxLN23
			// 
			this->textBoxLN23->Location = System::Drawing::Point(568, 288);
			this->textBoxLN23->Name = L"textBoxLN23";
			this->textBoxLN23->Size = System::Drawing::Size(120, 19);
			this->textBoxLN23->TabIndex = 218;
			// 
			// checkBoxEnCH23
			// 
			this->checkBoxEnCH23->AutoSize = true;
			this->checkBoxEnCH23->Location = System::Drawing::Point(424, 288);
			this->checkBoxEnCH23->Name = L"checkBoxEnCH23";
			this->checkBoxEnCH23->Size = System::Drawing::Size(46, 16);
			this->checkBoxEnCH23->TabIndex = 217;
			this->checkBoxEnCH23->Text = L"CH1";
			this->checkBoxEnCH23->UseVisualStyleBackColor = true;
			// 
			// label49
			// 
			this->label49->AutoSize = true;
			this->label49->Location = System::Drawing::Point(696, 288);
			this->label49->Name = L"label49";
			this->label49->Size = System::Drawing::Size(11, 12);
			this->label49->TabIndex = 216;
			this->label49->Text = L"*";
			// 
			// textBox56
			// 
			this->textBox56->Location = System::Drawing::Point(768, 264);
			this->textBox56->Name = L"textBox56";
			this->textBox56->Size = System::Drawing::Size(32, 19);
			this->textBox56->TabIndex = 215;
			// 
			// label50
			// 
			this->label50->AutoSize = true;
			this->label50->Location = System::Drawing::Point(752, 264);
			this->label50->Name = L"label50";
			this->label50->Size = System::Drawing::Size(11, 12);
			this->label50->TabIndex = 214;
			this->label50->Text = L"+";
			// 
			// textBox57
			// 
			this->textBox57->Location = System::Drawing::Point(712, 264);
			this->textBox57->Name = L"textBox57";
			this->textBox57->Size = System::Drawing::Size(32, 19);
			this->textBox57->TabIndex = 213;
			// 
			// textBoxLN22
			// 
			this->textBoxLN22->Location = System::Drawing::Point(568, 264);
			this->textBoxLN22->Name = L"textBoxLN22";
			this->textBoxLN22->Size = System::Drawing::Size(120, 19);
			this->textBoxLN22->TabIndex = 212;
			// 
			// checkBoxEnCH22
			// 
			this->checkBoxEnCH22->AutoSize = true;
			this->checkBoxEnCH22->Location = System::Drawing::Point(424, 264);
			this->checkBoxEnCH22->Name = L"checkBoxEnCH22";
			this->checkBoxEnCH22->Size = System::Drawing::Size(46, 16);
			this->checkBoxEnCH22->TabIndex = 211;
			this->checkBoxEnCH22->Text = L"CH1";
			this->checkBoxEnCH22->UseVisualStyleBackColor = true;
			// 
			// label51
			// 
			this->label51->AutoSize = true;
			this->label51->Location = System::Drawing::Point(696, 264);
			this->label51->Name = L"label51";
			this->label51->Size = System::Drawing::Size(11, 12);
			this->label51->TabIndex = 210;
			this->label51->Text = L"*";
			// 
			// textBox59
			// 
			this->textBox59->Location = System::Drawing::Point(768, 240);
			this->textBox59->Name = L"textBox59";
			this->textBox59->Size = System::Drawing::Size(32, 19);
			this->textBox59->TabIndex = 209;
			// 
			// label52
			// 
			this->label52->AutoSize = true;
			this->label52->Location = System::Drawing::Point(752, 240);
			this->label52->Name = L"label52";
			this->label52->Size = System::Drawing::Size(11, 12);
			this->label52->TabIndex = 208;
			this->label52->Text = L"+";
			// 
			// textBox60
			// 
			this->textBox60->Location = System::Drawing::Point(712, 240);
			this->textBox60->Name = L"textBox60";
			this->textBox60->Size = System::Drawing::Size(32, 19);
			this->textBox60->TabIndex = 207;
			// 
			// textBoxLN21
			// 
			this->textBoxLN21->Location = System::Drawing::Point(568, 240);
			this->textBoxLN21->Name = L"textBoxLN21";
			this->textBoxLN21->Size = System::Drawing::Size(120, 19);
			this->textBoxLN21->TabIndex = 206;
			// 
			// checkBoxEnCH21
			// 
			this->checkBoxEnCH21->AutoSize = true;
			this->checkBoxEnCH21->Location = System::Drawing::Point(424, 240);
			this->checkBoxEnCH21->Name = L"checkBoxEnCH21";
			this->checkBoxEnCH21->Size = System::Drawing::Size(46, 16);
			this->checkBoxEnCH21->TabIndex = 205;
			this->checkBoxEnCH21->Text = L"CH1";
			this->checkBoxEnCH21->UseVisualStyleBackColor = true;
			// 
			// label53
			// 
			this->label53->AutoSize = true;
			this->label53->Location = System::Drawing::Point(696, 240);
			this->label53->Name = L"label53";
			this->label53->Size = System::Drawing::Size(11, 12);
			this->label53->TabIndex = 204;
			this->label53->Text = L"*";
			// 
			// textBox62
			// 
			this->textBox62->Location = System::Drawing::Point(360, 312);
			this->textBox62->Name = L"textBox62";
			this->textBox62->Size = System::Drawing::Size(32, 19);
			this->textBox62->TabIndex = 203;
			// 
			// label54
			// 
			this->label54->AutoSize = true;
			this->label54->Location = System::Drawing::Point(344, 312);
			this->label54->Name = L"label54";
			this->label54->Size = System::Drawing::Size(11, 12);
			this->label54->TabIndex = 202;
			this->label54->Text = L"+";
			// 
			// textBox63
			// 
			this->textBox63->Location = System::Drawing::Point(304, 312);
			this->textBox63->Name = L"textBox63";
			this->textBox63->Size = System::Drawing::Size(32, 19);
			this->textBox63->TabIndex = 201;
			// 
			// textBoxLN12
			// 
			this->textBoxLN12->Location = System::Drawing::Point(160, 312);
			this->textBoxLN12->Name = L"textBoxLN12";
			this->textBoxLN12->Size = System::Drawing::Size(120, 19);
			this->textBoxLN12->TabIndex = 200;
			// 
			// checkBoxEnCH12
			// 
			this->checkBoxEnCH12->AutoSize = true;
			this->checkBoxEnCH12->Location = System::Drawing::Point(16, 312);
			this->checkBoxEnCH12->Name = L"checkBoxEnCH12";
			this->checkBoxEnCH12->Size = System::Drawing::Size(52, 16);
			this->checkBoxEnCH12->TabIndex = 199;
			this->checkBoxEnCH12->Text = L"CH12";
			this->checkBoxEnCH12->UseVisualStyleBackColor = true;
			// 
			// label55
			// 
			this->label55->AutoSize = true;
			this->label55->Location = System::Drawing::Point(288, 312);
			this->label55->Name = L"label55";
			this->label55->Size = System::Drawing::Size(11, 12);
			this->label55->TabIndex = 198;
			this->label55->Text = L"*";
			// 
			// textBox65
			// 
			this->textBox65->Location = System::Drawing::Point(360, 288);
			this->textBox65->Name = L"textBox65";
			this->textBox65->Size = System::Drawing::Size(32, 19);
			this->textBox65->TabIndex = 197;
			// 
			// label56
			// 
			this->label56->AutoSize = true;
			this->label56->Location = System::Drawing::Point(344, 288);
			this->label56->Name = L"label56";
			this->label56->Size = System::Drawing::Size(11, 12);
			this->label56->TabIndex = 196;
			this->label56->Text = L"+";
			// 
			// textBox66
			// 
			this->textBox66->Location = System::Drawing::Point(304, 288);
			this->textBox66->Name = L"textBox66";
			this->textBox66->Size = System::Drawing::Size(32, 19);
			this->textBox66->TabIndex = 195;
			// 
			// textBoxLN11
			// 
			this->textBoxLN11->Location = System::Drawing::Point(160, 288);
			this->textBoxLN11->Name = L"textBoxLN11";
			this->textBoxLN11->Size = System::Drawing::Size(120, 19);
			this->textBoxLN11->TabIndex = 194;
			// 
			// checkBoxEnCH11
			// 
			this->checkBoxEnCH11->AutoSize = true;
			this->checkBoxEnCH11->Location = System::Drawing::Point(16, 288);
			this->checkBoxEnCH11->Name = L"checkBoxEnCH11";
			this->checkBoxEnCH11->Size = System::Drawing::Size(46, 16);
			this->checkBoxEnCH11->TabIndex = 193;
			this->checkBoxEnCH11->Text = L"CH1";
			this->checkBoxEnCH11->UseVisualStyleBackColor = true;
			// 
			// label57
			// 
			this->label57->AutoSize = true;
			this->label57->Location = System::Drawing::Point(288, 288);
			this->label57->Name = L"label57";
			this->label57->Size = System::Drawing::Size(11, 12);
			this->label57->TabIndex = 192;
			this->label57->Text = L"*";
			// 
			// textBox68
			// 
			this->textBox68->Location = System::Drawing::Point(360, 264);
			this->textBox68->Name = L"textBox68";
			this->textBox68->Size = System::Drawing::Size(32, 19);
			this->textBox68->TabIndex = 191;
			// 
			// label58
			// 
			this->label58->AutoSize = true;
			this->label58->Location = System::Drawing::Point(344, 264);
			this->label58->Name = L"label58";
			this->label58->Size = System::Drawing::Size(11, 12);
			this->label58->TabIndex = 190;
			this->label58->Text = L"+";
			// 
			// textBox69
			// 
			this->textBox69->Location = System::Drawing::Point(304, 264);
			this->textBox69->Name = L"textBox69";
			this->textBox69->Size = System::Drawing::Size(32, 19);
			this->textBox69->TabIndex = 189;
			// 
			// textBoxLN10
			// 
			this->textBoxLN10->Location = System::Drawing::Point(160, 264);
			this->textBoxLN10->Name = L"textBoxLN10";
			this->textBoxLN10->Size = System::Drawing::Size(120, 19);
			this->textBoxLN10->TabIndex = 188;
			// 
			// checkBoxEnCH10
			// 
			this->checkBoxEnCH10->AutoSize = true;
			this->checkBoxEnCH10->Location = System::Drawing::Point(16, 264);
			this->checkBoxEnCH10->Name = L"checkBoxEnCH10";
			this->checkBoxEnCH10->Size = System::Drawing::Size(46, 16);
			this->checkBoxEnCH10->TabIndex = 187;
			this->checkBoxEnCH10->Text = L"CH1";
			this->checkBoxEnCH10->UseVisualStyleBackColor = true;
			// 
			// label59
			// 
			this->label59->AutoSize = true;
			this->label59->Location = System::Drawing::Point(288, 264);
			this->label59->Name = L"label59";
			this->label59->Size = System::Drawing::Size(11, 12);
			this->label59->TabIndex = 186;
			this->label59->Text = L"*";
			// 
			// textBox71
			// 
			this->textBox71->Location = System::Drawing::Point(360, 240);
			this->textBox71->Name = L"textBox71";
			this->textBox71->Size = System::Drawing::Size(32, 19);
			this->textBox71->TabIndex = 185;
			// 
			// label60
			// 
			this->label60->AutoSize = true;
			this->label60->Location = System::Drawing::Point(344, 240);
			this->label60->Name = L"label60";
			this->label60->Size = System::Drawing::Size(11, 12);
			this->label60->TabIndex = 184;
			this->label60->Text = L"+";
			// 
			// textBox72
			// 
			this->textBox72->Location = System::Drawing::Point(304, 240);
			this->textBox72->Name = L"textBox72";
			this->textBox72->Size = System::Drawing::Size(32, 19);
			this->textBox72->TabIndex = 183;
			// 
			// textBoxLN9
			// 
			this->textBoxLN9->Location = System::Drawing::Point(160, 240);
			this->textBoxLN9->Name = L"textBoxLN9";
			this->textBoxLN9->Size = System::Drawing::Size(120, 19);
			this->textBoxLN9->TabIndex = 182;
			// 
			// checkBoxEnCH9
			// 
			this->checkBoxEnCH9->AutoSize = true;
			this->checkBoxEnCH9->Location = System::Drawing::Point(16, 240);
			this->checkBoxEnCH9->Name = L"checkBoxEnCH9";
			this->checkBoxEnCH9->Size = System::Drawing::Size(46, 16);
			this->checkBoxEnCH9->TabIndex = 181;
			this->checkBoxEnCH9->Text = L"CH1";
			this->checkBoxEnCH9->UseVisualStyleBackColor = true;
			// 
			// label61
			// 
			this->label61->AutoSize = true;
			this->label61->Location = System::Drawing::Point(288, 240);
			this->label61->Name = L"label61";
			this->label61->Size = System::Drawing::Size(11, 12);
			this->label61->TabIndex = 180;
			this->label61->Text = L"*";
			// 
			// comboBoxFig8
			// 
			this->comboBoxFig8->FormattingEnabled = true;
			this->comboBoxFig8->Location = System::Drawing::Point(72, 216);
			this->comboBoxFig8->Name = L"comboBoxFig8";
			this->comboBoxFig8->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig8->TabIndex = 179;
			// 
			// button1
			// 
			this->button1->ForeColor = System::Drawing::Color::Red;
			this->button1->Location = System::Drawing::Point(120, 216);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(24, 23);
			this->button1->TabIndex = 178;
			this->button1->Text = L"■";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig7
			// 
			this->comboBoxFig7->FormattingEnabled = true;
			this->comboBoxFig7->Location = System::Drawing::Point(72, 192);
			this->comboBoxFig7->Name = L"comboBoxFig7";
			this->comboBoxFig7->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig7->TabIndex = 177;
			// 
			// button2
			// 
			this->button2->ForeColor = System::Drawing::Color::Red;
			this->button2->Location = System::Drawing::Point(120, 192);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(24, 23);
			this->button2->TabIndex = 176;
			this->button2->Text = L"■";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig6
			// 
			this->comboBoxFig6->FormattingEnabled = true;
			this->comboBoxFig6->Location = System::Drawing::Point(72, 168);
			this->comboBoxFig6->Name = L"comboBoxFig6";
			this->comboBoxFig6->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig6->TabIndex = 175;
			// 
			// button3
			// 
			this->button3->ForeColor = System::Drawing::Color::Red;
			this->button3->Location = System::Drawing::Point(120, 168);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(24, 23);
			this->button3->TabIndex = 174;
			this->button3->Text = L"■";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig5
			// 
			this->comboBoxFig5->FormattingEnabled = true;
			this->comboBoxFig5->Location = System::Drawing::Point(72, 144);
			this->comboBoxFig5->Name = L"comboBoxFig5";
			this->comboBoxFig5->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig5->TabIndex = 173;
			// 
			// button4
			// 
			this->button4->ForeColor = System::Drawing::Color::Red;
			this->button4->Location = System::Drawing::Point(120, 144);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(24, 23);
			this->button4->TabIndex = 172;
			this->button4->Text = L"■";
			this->button4->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig4
			// 
			this->comboBoxFig4->FormattingEnabled = true;
			this->comboBoxFig4->Location = System::Drawing::Point(72, 120);
			this->comboBoxFig4->Name = L"comboBoxFig4";
			this->comboBoxFig4->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig4->TabIndex = 171;
			// 
			// button5
			// 
			this->button5->ForeColor = System::Drawing::Color::Red;
			this->button5->Location = System::Drawing::Point(120, 120);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(24, 23);
			this->button5->TabIndex = 170;
			this->button5->Text = L"■";
			this->button5->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig3
			// 
			this->comboBoxFig3->FormattingEnabled = true;
			this->comboBoxFig3->Location = System::Drawing::Point(72, 96);
			this->comboBoxFig3->Name = L"comboBoxFig3";
			this->comboBoxFig3->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig3->TabIndex = 169;
			// 
			// button6
			// 
			this->button6->ForeColor = System::Drawing::Color::Red;
			this->button6->Location = System::Drawing::Point(120, 96);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(24, 23);
			this->button6->TabIndex = 168;
			this->button6->Text = L"■";
			this->button6->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig2
			// 
			this->comboBoxFig2->FormattingEnabled = true;
			this->comboBoxFig2->Location = System::Drawing::Point(72, 72);
			this->comboBoxFig2->Name = L"comboBoxFig2";
			this->comboBoxFig2->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig2->TabIndex = 167;
			// 
			// button7
			// 
			this->button7->ForeColor = System::Drawing::Color::Red;
			this->button7->Location = System::Drawing::Point(120, 72);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(24, 23);
			this->button7->TabIndex = 166;
			this->button7->Text = L"■";
			this->button7->UseVisualStyleBackColor = true;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(72, 24);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(34, 12);
			this->label8->TabIndex = 165;
			this->label8->Text = L"figure";
			// 
			// comboBoxFig1
			// 
			this->comboBoxFig1->FormattingEnabled = true;
			this->comboBoxFig1->Items->AddRange(gcnew cli::array< System::Object^  >(8) {
				L"a1", L"a2", L"b1", L"b2", L"c1", L"c2", L"d1",
					L"d2"
			});
			this->comboBoxFig1->Location = System::Drawing::Point(72, 48);
			this->comboBoxFig1->Name = L"comboBoxFig1";
			this->comboBoxFig1->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig1->TabIndex = 164;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(120, 24);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(30, 12);
			this->label10->TabIndex = 163;
			this->label10->Text = L"color";
			// 
			// buttonCol1
			// 
			this->buttonCol1->ForeColor = System::Drawing::Color::Red;
			this->buttonCol1->Location = System::Drawing::Point(120, 48);
			this->buttonCol1->Name = L"buttonCol1";
			this->buttonCol1->Size = System::Drawing::Size(24, 23);
			this->buttonCol1->TabIndex = 162;
			this->buttonCol1->Text = L"■";
			this->buttonCol1->UseVisualStyleBackColor = true;
			this->buttonCol1->Click += gcnew System::EventHandler(this, &SetupPlot::buttonCol1_Click);
			// 
			// comboBoxFig20
			// 
			this->comboBoxFig20->FormattingEnabled = true;
			this->comboBoxFig20->Location = System::Drawing::Point(480, 216);
			this->comboBoxFig20->Name = L"comboBoxFig20";
			this->comboBoxFig20->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig20->TabIndex = 161;
			// 
			// button9
			// 
			this->button9->ForeColor = System::Drawing::Color::Red;
			this->button9->Location = System::Drawing::Point(528, 216);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(24, 23);
			this->button9->TabIndex = 160;
			this->button9->Text = L"■";
			this->button9->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig19
			// 
			this->comboBoxFig19->FormattingEnabled = true;
			this->comboBoxFig19->Location = System::Drawing::Point(480, 192);
			this->comboBoxFig19->Name = L"comboBoxFig19";
			this->comboBoxFig19->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig19->TabIndex = 159;
			// 
			// button10
			// 
			this->button10->ForeColor = System::Drawing::Color::Red;
			this->button10->Location = System::Drawing::Point(528, 192);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(24, 23);
			this->button10->TabIndex = 158;
			this->button10->Text = L"■";
			this->button10->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig18
			// 
			this->comboBoxFig18->FormattingEnabled = true;
			this->comboBoxFig18->Location = System::Drawing::Point(480, 168);
			this->comboBoxFig18->Name = L"comboBoxFig18";
			this->comboBoxFig18->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig18->TabIndex = 157;
			// 
			// button11
			// 
			this->button11->ForeColor = System::Drawing::Color::Red;
			this->button11->Location = System::Drawing::Point(528, 168);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(24, 23);
			this->button11->TabIndex = 156;
			this->button11->Text = L"■";
			this->button11->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig17
			// 
			this->comboBoxFig17->FormattingEnabled = true;
			this->comboBoxFig17->Location = System::Drawing::Point(480, 144);
			this->comboBoxFig17->Name = L"comboBoxFig17";
			this->comboBoxFig17->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig17->TabIndex = 155;
			// 
			// button12
			// 
			this->button12->ForeColor = System::Drawing::Color::Red;
			this->button12->Location = System::Drawing::Point(528, 144);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(24, 23);
			this->button12->TabIndex = 154;
			this->button12->Text = L"■";
			this->button12->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig16
			// 
			this->comboBoxFig16->FormattingEnabled = true;
			this->comboBoxFig16->Location = System::Drawing::Point(480, 120);
			this->comboBoxFig16->Name = L"comboBoxFig16";
			this->comboBoxFig16->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig16->TabIndex = 153;
			// 
			// button13
			// 
			this->button13->ForeColor = System::Drawing::Color::Red;
			this->button13->Location = System::Drawing::Point(528, 120);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(24, 23);
			this->button13->TabIndex = 152;
			this->button13->Text = L"■";
			this->button13->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig15
			// 
			this->comboBoxFig15->FormattingEnabled = true;
			this->comboBoxFig15->Location = System::Drawing::Point(480, 96);
			this->comboBoxFig15->Name = L"comboBoxFig15";
			this->comboBoxFig15->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig15->TabIndex = 151;
			// 
			// button14
			// 
			this->button14->ForeColor = System::Drawing::Color::Red;
			this->button14->Location = System::Drawing::Point(528, 96);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(24, 23);
			this->button14->TabIndex = 150;
			this->button14->Text = L"■";
			this->button14->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig14
			// 
			this->comboBoxFig14->FormattingEnabled = true;
			this->comboBoxFig14->Location = System::Drawing::Point(480, 72);
			this->comboBoxFig14->Name = L"comboBoxFig14";
			this->comboBoxFig14->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig14->TabIndex = 149;
			// 
			// button15
			// 
			this->button15->ForeColor = System::Drawing::Color::Red;
			this->button15->Location = System::Drawing::Point(528, 72);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(24, 23);
			this->button15->TabIndex = 148;
			this->button15->Text = L"■";
			this->button15->UseVisualStyleBackColor = true;
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->Location = System::Drawing::Point(480, 24);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(34, 12);
			this->label39->TabIndex = 147;
			this->label39->Text = L"figure";
			// 
			// comboBoxFig13
			// 
			this->comboBoxFig13->FormattingEnabled = true;
			this->comboBoxFig13->Location = System::Drawing::Point(480, 48);
			this->comboBoxFig13->Name = L"comboBoxFig13";
			this->comboBoxFig13->Size = System::Drawing::Size(40, 20);
			this->comboBoxFig13->TabIndex = 146;
			// 
			// label40
			// 
			this->label40->AutoSize = true;
			this->label40->Location = System::Drawing::Point(528, 24);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(30, 12);
			this->label40->TabIndex = 145;
			this->label40->Text = L"color";
			// 
			// button16
			// 
			this->button16->ForeColor = System::Drawing::Color::Red;
			this->button16->Location = System::Drawing::Point(528, 48);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(24, 23);
			this->button16->TabIndex = 144;
			this->button16->Text = L"■";
			this->button16->UseVisualStyleBackColor = true;
			// 
			// textBox26
			// 
			this->textBox26->Location = System::Drawing::Point(768, 216);
			this->textBox26->Name = L"textBox26";
			this->textBox26->Size = System::Drawing::Size(32, 19);
			this->textBox26->TabIndex = 141;
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(752, 216);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(11, 12);
			this->label25->TabIndex = 140;
			this->label25->Text = L"+";
			// 
			// textBox27
			// 
			this->textBox27->Location = System::Drawing::Point(712, 216);
			this->textBox27->Name = L"textBox27";
			this->textBox27->Size = System::Drawing::Size(32, 19);
			this->textBox27->TabIndex = 139;
			// 
			// textBoxLN20
			// 
			this->textBoxLN20->Location = System::Drawing::Point(568, 216);
			this->textBoxLN20->Name = L"textBoxLN20";
			this->textBoxLN20->Size = System::Drawing::Size(120, 19);
			this->textBoxLN20->TabIndex = 138;
			// 
			// checkBoxEnCH20
			// 
			this->checkBoxEnCH20->AutoSize = true;
			this->checkBoxEnCH20->Location = System::Drawing::Point(424, 216);
			this->checkBoxEnCH20->Name = L"checkBoxEnCH20";
			this->checkBoxEnCH20->Size = System::Drawing::Size(46, 16);
			this->checkBoxEnCH20->TabIndex = 137;
			this->checkBoxEnCH20->Text = L"CH1";
			this->checkBoxEnCH20->UseVisualStyleBackColor = true;
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(696, 216);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(11, 12);
			this->label26->TabIndex = 136;
			this->label26->Text = L"*";
			// 
			// textBox29
			// 
			this->textBox29->Location = System::Drawing::Point(768, 192);
			this->textBox29->Name = L"textBox29";
			this->textBox29->Size = System::Drawing::Size(32, 19);
			this->textBox29->TabIndex = 133;
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Location = System::Drawing::Point(752, 192);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(11, 12);
			this->label27->TabIndex = 132;
			this->label27->Text = L"+";
			// 
			// textBox30
			// 
			this->textBox30->Location = System::Drawing::Point(712, 192);
			this->textBox30->Name = L"textBox30";
			this->textBox30->Size = System::Drawing::Size(32, 19);
			this->textBox30->TabIndex = 131;
			// 
			// textBoxLN19
			// 
			this->textBoxLN19->Location = System::Drawing::Point(568, 192);
			this->textBoxLN19->Name = L"textBoxLN19";
			this->textBoxLN19->Size = System::Drawing::Size(120, 19);
			this->textBoxLN19->TabIndex = 130;
			// 
			// checkBoxEnCH19
			// 
			this->checkBoxEnCH19->AutoSize = true;
			this->checkBoxEnCH19->Location = System::Drawing::Point(424, 192);
			this->checkBoxEnCH19->Name = L"checkBoxEnCH19";
			this->checkBoxEnCH19->Size = System::Drawing::Size(46, 16);
			this->checkBoxEnCH19->TabIndex = 129;
			this->checkBoxEnCH19->Text = L"CH1";
			this->checkBoxEnCH19->UseVisualStyleBackColor = true;
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Location = System::Drawing::Point(696, 192);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(11, 12);
			this->label28->TabIndex = 128;
			this->label28->Text = L"*";
			// 
			// textBox32
			// 
			this->textBox32->Location = System::Drawing::Point(768, 168);
			this->textBox32->Name = L"textBox32";
			this->textBox32->Size = System::Drawing::Size(32, 19);
			this->textBox32->TabIndex = 125;
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Location = System::Drawing::Point(752, 168);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(11, 12);
			this->label29->TabIndex = 124;
			this->label29->Text = L"+";
			// 
			// textBox33
			// 
			this->textBox33->Location = System::Drawing::Point(712, 168);
			this->textBox33->Name = L"textBox33";
			this->textBox33->Size = System::Drawing::Size(32, 19);
			this->textBox33->TabIndex = 123;
			// 
			// textBoxLN18
			// 
			this->textBoxLN18->Location = System::Drawing::Point(568, 168);
			this->textBoxLN18->Name = L"textBoxLN18";
			this->textBoxLN18->Size = System::Drawing::Size(120, 19);
			this->textBoxLN18->TabIndex = 122;
			// 
			// checkBoxEnCH18
			// 
			this->checkBoxEnCH18->AutoSize = true;
			this->checkBoxEnCH18->Location = System::Drawing::Point(424, 168);
			this->checkBoxEnCH18->Name = L"checkBoxEnCH18";
			this->checkBoxEnCH18->Size = System::Drawing::Size(46, 16);
			this->checkBoxEnCH18->TabIndex = 121;
			this->checkBoxEnCH18->Text = L"CH1";
			this->checkBoxEnCH18->UseVisualStyleBackColor = true;
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Location = System::Drawing::Point(696, 168);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(11, 12);
			this->label30->TabIndex = 120;
			this->label30->Text = L"*";
			// 
			// textBox35
			// 
			this->textBox35->Location = System::Drawing::Point(768, 144);
			this->textBox35->Name = L"textBox35";
			this->textBox35->Size = System::Drawing::Size(32, 19);
			this->textBox35->TabIndex = 117;
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Location = System::Drawing::Point(752, 144);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(11, 12);
			this->label31->TabIndex = 116;
			this->label31->Text = L"+";
			// 
			// textBox36
			// 
			this->textBox36->Location = System::Drawing::Point(712, 144);
			this->textBox36->Name = L"textBox36";
			this->textBox36->Size = System::Drawing::Size(32, 19);
			this->textBox36->TabIndex = 115;
			// 
			// textBoxLN17
			// 
			this->textBoxLN17->Location = System::Drawing::Point(568, 144);
			this->textBoxLN17->Name = L"textBoxLN17";
			this->textBoxLN17->Size = System::Drawing::Size(120, 19);
			this->textBoxLN17->TabIndex = 114;
			// 
			// checkBoxEnCH17
			// 
			this->checkBoxEnCH17->AutoSize = true;
			this->checkBoxEnCH17->Location = System::Drawing::Point(424, 144);
			this->checkBoxEnCH17->Name = L"checkBoxEnCH17";
			this->checkBoxEnCH17->Size = System::Drawing::Size(46, 16);
			this->checkBoxEnCH17->TabIndex = 113;
			this->checkBoxEnCH17->Text = L"CH1";
			this->checkBoxEnCH17->UseVisualStyleBackColor = true;
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Location = System::Drawing::Point(696, 144);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(11, 12);
			this->label32->TabIndex = 112;
			this->label32->Text = L"*";
			// 
			// textBox38
			// 
			this->textBox38->Location = System::Drawing::Point(768, 120);
			this->textBox38->Name = L"textBox38";
			this->textBox38->Size = System::Drawing::Size(32, 19);
			this->textBox38->TabIndex = 109;
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Location = System::Drawing::Point(752, 120);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(11, 12);
			this->label33->TabIndex = 108;
			this->label33->Text = L"+";
			// 
			// textBox39
			// 
			this->textBox39->Location = System::Drawing::Point(712, 120);
			this->textBox39->Name = L"textBox39";
			this->textBox39->Size = System::Drawing::Size(32, 19);
			this->textBox39->TabIndex = 107;
			// 
			// textBoxLN16
			// 
			this->textBoxLN16->Location = System::Drawing::Point(568, 120);
			this->textBoxLN16->Name = L"textBoxLN16";
			this->textBoxLN16->Size = System::Drawing::Size(120, 19);
			this->textBoxLN16->TabIndex = 106;
			// 
			// checkBoxEnCH16
			// 
			this->checkBoxEnCH16->AutoSize = true;
			this->checkBoxEnCH16->Location = System::Drawing::Point(424, 120);
			this->checkBoxEnCH16->Name = L"checkBoxEnCH16";
			this->checkBoxEnCH16->Size = System::Drawing::Size(46, 16);
			this->checkBoxEnCH16->TabIndex = 105;
			this->checkBoxEnCH16->Text = L"CH1";
			this->checkBoxEnCH16->UseVisualStyleBackColor = true;
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->Location = System::Drawing::Point(696, 120);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(11, 12);
			this->label34->TabIndex = 104;
			this->label34->Text = L"*";
			// 
			// textBox41
			// 
			this->textBox41->Location = System::Drawing::Point(768, 96);
			this->textBox41->Name = L"textBox41";
			this->textBox41->Size = System::Drawing::Size(32, 19);
			this->textBox41->TabIndex = 101;
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->Location = System::Drawing::Point(752, 96);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(11, 12);
			this->label35->TabIndex = 100;
			this->label35->Text = L"+";
			// 
			// textBox42
			// 
			this->textBox42->Location = System::Drawing::Point(712, 96);
			this->textBox42->Name = L"textBox42";
			this->textBox42->Size = System::Drawing::Size(32, 19);
			this->textBox42->TabIndex = 99;
			// 
			// textBoxLN15
			// 
			this->textBoxLN15->Location = System::Drawing::Point(568, 96);
			this->textBoxLN15->Name = L"textBoxLN15";
			this->textBoxLN15->Size = System::Drawing::Size(120, 19);
			this->textBoxLN15->TabIndex = 98;
			// 
			// checkBoxEnCH15
			// 
			this->checkBoxEnCH15->AutoSize = true;
			this->checkBoxEnCH15->Location = System::Drawing::Point(424, 96);
			this->checkBoxEnCH15->Name = L"checkBoxEnCH15";
			this->checkBoxEnCH15->Size = System::Drawing::Size(46, 16);
			this->checkBoxEnCH15->TabIndex = 97;
			this->checkBoxEnCH15->Text = L"CH1";
			this->checkBoxEnCH15->UseVisualStyleBackColor = true;
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Location = System::Drawing::Point(696, 96);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(11, 12);
			this->label36->TabIndex = 96;
			this->label36->Text = L"*";
			// 
			// textBox44
			// 
			this->textBox44->Location = System::Drawing::Point(768, 72);
			this->textBox44->Name = L"textBox44";
			this->textBox44->Size = System::Drawing::Size(32, 19);
			this->textBox44->TabIndex = 93;
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Location = System::Drawing::Point(752, 72);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(11, 12);
			this->label37->TabIndex = 92;
			this->label37->Text = L"+";
			// 
			// textBox45
			// 
			this->textBox45->Location = System::Drawing::Point(712, 72);
			this->textBox45->Name = L"textBox45";
			this->textBox45->Size = System::Drawing::Size(32, 19);
			this->textBox45->TabIndex = 91;
			// 
			// textBoxLN14
			// 
			this->textBoxLN14->Location = System::Drawing::Point(568, 72);
			this->textBoxLN14->Name = L"textBoxLN14";
			this->textBoxLN14->Size = System::Drawing::Size(120, 19);
			this->textBoxLN14->TabIndex = 90;
			// 
			// checkBoxEnCH14
			// 
			this->checkBoxEnCH14->AutoSize = true;
			this->checkBoxEnCH14->Location = System::Drawing::Point(424, 72);
			this->checkBoxEnCH14->Name = L"checkBoxEnCH14";
			this->checkBoxEnCH14->Size = System::Drawing::Size(46, 16);
			this->checkBoxEnCH14->TabIndex = 89;
			this->checkBoxEnCH14->Text = L"CH1";
			this->checkBoxEnCH14->UseVisualStyleBackColor = true;
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->Location = System::Drawing::Point(696, 72);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(11, 12);
			this->label38->TabIndex = 88;
			this->label38->Text = L"*";
			// 
			// textBox47
			// 
			this->textBox47->Location = System::Drawing::Point(768, 48);
			this->textBox47->Name = L"textBox47";
			this->textBox47->Size = System::Drawing::Size(32, 19);
			this->textBox47->TabIndex = 83;
			// 
			// label41
			// 
			this->label41->AutoSize = true;
			this->label41->Location = System::Drawing::Point(752, 48);
			this->label41->Name = L"label41";
			this->label41->Size = System::Drawing::Size(11, 12);
			this->label41->TabIndex = 82;
			this->label41->Text = L"+";
			// 
			// textBox48
			// 
			this->textBox48->Location = System::Drawing::Point(712, 48);
			this->textBox48->Name = L"textBox48";
			this->textBox48->Size = System::Drawing::Size(32, 19);
			this->textBox48->TabIndex = 81;
			// 
			// label42
			// 
			this->label42->AutoSize = true;
			this->label42->Location = System::Drawing::Point(696, 24);
			this->label42->Name = L"label42";
			this->label42->Size = System::Drawing::Size(104, 12);
			this->label42->TabIndex = 80;
			this->label42->Text = L"calc (y = a * x + b)";
			// 
			// textBoxLN13
			// 
			this->textBoxLN13->Location = System::Drawing::Point(568, 48);
			this->textBoxLN13->Name = L"textBoxLN13";
			this->textBoxLN13->Size = System::Drawing::Size(120, 19);
			this->textBoxLN13->TabIndex = 79;
			// 
			// label43
			// 
			this->label43->AutoSize = true;
			this->label43->Location = System::Drawing::Point(424, 24);
			this->label43->Name = L"label43";
			this->label43->Size = System::Drawing::Size(41, 12);
			this->label43->TabIndex = 77;
			this->label43->Text = L"column";
			// 
			// checkBoxEnCH13
			// 
			this->checkBoxEnCH13->AutoSize = true;
			this->checkBoxEnCH13->Location = System::Drawing::Point(424, 48);
			this->checkBoxEnCH13->Name = L"checkBoxEnCH13";
			this->checkBoxEnCH13->Size = System::Drawing::Size(46, 16);
			this->checkBoxEnCH13->TabIndex = 78;
			this->checkBoxEnCH13->Text = L"CH1";
			this->checkBoxEnCH13->UseVisualStyleBackColor = true;
			// 
			// label44
			// 
			this->label44->AutoSize = true;
			this->label44->Location = System::Drawing::Point(568, 24);
			this->label44->Name = L"label44";
			this->label44->Size = System::Drawing::Size(60, 12);
			this->label44->TabIndex = 76;
			this->label44->Text = L"label name";
			// 
			// label45
			// 
			this->label45->AutoSize = true;
			this->label45->Location = System::Drawing::Point(696, 48);
			this->label45->Name = L"label45";
			this->label45->Size = System::Drawing::Size(11, 12);
			this->label45->TabIndex = 75;
			this->label45->Text = L"*";
			// 
			// textBox14
			// 
			this->textBox14->Location = System::Drawing::Point(360, 216);
			this->textBox14->Name = L"textBox14";
			this->textBox14->Size = System::Drawing::Size(32, 19);
			this->textBox14->TabIndex = 72;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(344, 216);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(11, 12);
			this->label17->TabIndex = 71;
			this->label17->Text = L"+";
			// 
			// textBox15
			// 
			this->textBox15->Location = System::Drawing::Point(304, 216);
			this->textBox15->Name = L"textBox15";
			this->textBox15->Size = System::Drawing::Size(32, 19);
			this->textBox15->TabIndex = 70;
			// 
			// textBoxLN8
			// 
			this->textBoxLN8->Location = System::Drawing::Point(160, 216);
			this->textBoxLN8->Name = L"textBoxLN8";
			this->textBoxLN8->Size = System::Drawing::Size(120, 19);
			this->textBoxLN8->TabIndex = 69;
			// 
			// checkBoxEnCH8
			// 
			this->checkBoxEnCH8->AutoSize = true;
			this->checkBoxEnCH8->Location = System::Drawing::Point(16, 216);
			this->checkBoxEnCH8->Name = L"checkBoxEnCH8";
			this->checkBoxEnCH8->Size = System::Drawing::Size(52, 16);
			this->checkBoxEnCH8->TabIndex = 68;
			this->checkBoxEnCH8->Text = L"CH12";
			this->checkBoxEnCH8->UseVisualStyleBackColor = true;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(288, 216);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(11, 12);
			this->label18->TabIndex = 67;
			this->label18->Text = L"*";
			// 
			// textBox17
			// 
			this->textBox17->Location = System::Drawing::Point(360, 192);
			this->textBox17->Name = L"textBox17";
			this->textBox17->Size = System::Drawing::Size(32, 19);
			this->textBox17->TabIndex = 64;
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(344, 192);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(11, 12);
			this->label19->TabIndex = 63;
			this->label19->Text = L"+";
			// 
			// textBox18
			// 
			this->textBox18->Location = System::Drawing::Point(304, 192);
			this->textBox18->Name = L"textBox18";
			this->textBox18->Size = System::Drawing::Size(32, 19);
			this->textBox18->TabIndex = 62;
			// 
			// textBoxLN7
			// 
			this->textBoxLN7->Location = System::Drawing::Point(160, 192);
			this->textBoxLN7->Name = L"textBoxLN7";
			this->textBoxLN7->Size = System::Drawing::Size(120, 19);
			this->textBoxLN7->TabIndex = 61;
			// 
			// checkBoxEnCH7
			// 
			this->checkBoxEnCH7->AutoSize = true;
			this->checkBoxEnCH7->Location = System::Drawing::Point(16, 192);
			this->checkBoxEnCH7->Name = L"checkBoxEnCH7";
			this->checkBoxEnCH7->Size = System::Drawing::Size(46, 16);
			this->checkBoxEnCH7->TabIndex = 60;
			this->checkBoxEnCH7->Text = L"CH1";
			this->checkBoxEnCH7->UseVisualStyleBackColor = true;
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(288, 192);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(11, 12);
			this->label20->TabIndex = 59;
			this->label20->Text = L"*";
			// 
			// textBox20
			// 
			this->textBox20->Location = System::Drawing::Point(360, 168);
			this->textBox20->Name = L"textBox20";
			this->textBox20->Size = System::Drawing::Size(32, 19);
			this->textBox20->TabIndex = 56;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(344, 168);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(11, 12);
			this->label21->TabIndex = 55;
			this->label21->Text = L"+";
			// 
			// textBox21
			// 
			this->textBox21->Location = System::Drawing::Point(304, 168);
			this->textBox21->Name = L"textBox21";
			this->textBox21->Size = System::Drawing::Size(32, 19);
			this->textBox21->TabIndex = 54;
			// 
			// textBoxLN6
			// 
			this->textBoxLN6->Location = System::Drawing::Point(160, 168);
			this->textBoxLN6->Name = L"textBoxLN6";
			this->textBoxLN6->Size = System::Drawing::Size(120, 19);
			this->textBoxLN6->TabIndex = 53;
			// 
			// checkBoxEnCH6
			// 
			this->checkBoxEnCH6->AutoSize = true;
			this->checkBoxEnCH6->Location = System::Drawing::Point(16, 168);
			this->checkBoxEnCH6->Name = L"checkBoxEnCH6";
			this->checkBoxEnCH6->Size = System::Drawing::Size(46, 16);
			this->checkBoxEnCH6->TabIndex = 52;
			this->checkBoxEnCH6->Text = L"CH1";
			this->checkBoxEnCH6->UseVisualStyleBackColor = true;
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(288, 168);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(11, 12);
			this->label22->TabIndex = 51;
			this->label22->Text = L"*";
			// 
			// textBox23
			// 
			this->textBox23->Location = System::Drawing::Point(360, 144);
			this->textBox23->Name = L"textBox23";
			this->textBox23->Size = System::Drawing::Size(32, 19);
			this->textBox23->TabIndex = 48;
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(344, 144);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(11, 12);
			this->label23->TabIndex = 47;
			this->label23->Text = L"+";
			// 
			// textBox24
			// 
			this->textBox24->Location = System::Drawing::Point(304, 144);
			this->textBox24->Name = L"textBox24";
			this->textBox24->Size = System::Drawing::Size(32, 19);
			this->textBox24->TabIndex = 46;
			// 
			// textBoxLN5
			// 
			this->textBoxLN5->Location = System::Drawing::Point(160, 144);
			this->textBoxLN5->Name = L"textBoxLN5";
			this->textBoxLN5->Size = System::Drawing::Size(120, 19);
			this->textBoxLN5->TabIndex = 45;
			// 
			// checkBoxEnCH5
			// 
			this->checkBoxEnCH5->AutoSize = true;
			this->checkBoxEnCH5->Location = System::Drawing::Point(16, 144);
			this->checkBoxEnCH5->Name = L"checkBoxEnCH5";
			this->checkBoxEnCH5->Size = System::Drawing::Size(46, 16);
			this->checkBoxEnCH5->TabIndex = 44;
			this->checkBoxEnCH5->Text = L"CH1";
			this->checkBoxEnCH5->UseVisualStyleBackColor = true;
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(288, 144);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(11, 12);
			this->label24->TabIndex = 43;
			this->label24->Text = L"*";
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(360, 120);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(32, 19);
			this->textBox8->TabIndex = 40;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(344, 120);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(11, 12);
			this->label13->TabIndex = 39;
			this->label13->Text = L"+";
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(304, 120);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(32, 19);
			this->textBox9->TabIndex = 38;
			// 
			// textBoxLN4
			// 
			this->textBoxLN4->Location = System::Drawing::Point(160, 120);
			this->textBoxLN4->Name = L"textBoxLN4";
			this->textBoxLN4->Size = System::Drawing::Size(120, 19);
			this->textBoxLN4->TabIndex = 37;
			// 
			// checkBoxEnCH4
			// 
			this->checkBoxEnCH4->AutoSize = true;
			this->checkBoxEnCH4->Location = System::Drawing::Point(16, 120);
			this->checkBoxEnCH4->Name = L"checkBoxEnCH4";
			this->checkBoxEnCH4->Size = System::Drawing::Size(46, 16);
			this->checkBoxEnCH4->TabIndex = 36;
			this->checkBoxEnCH4->Text = L"CH4";
			this->checkBoxEnCH4->UseVisualStyleBackColor = true;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(288, 120);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(11, 12);
			this->label14->TabIndex = 35;
			this->label14->Text = L"*";
			// 
			// textBox11
			// 
			this->textBox11->Location = System::Drawing::Point(360, 96);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(32, 19);
			this->textBox11->TabIndex = 32;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(344, 96);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(11, 12);
			this->label15->TabIndex = 31;
			this->label15->Text = L"+";
			// 
			// textBox12
			// 
			this->textBox12->Location = System::Drawing::Point(304, 96);
			this->textBox12->Name = L"textBox12";
			this->textBox12->Size = System::Drawing::Size(32, 19);
			this->textBox12->TabIndex = 30;
			// 
			// textBoxLN3
			// 
			this->textBoxLN3->Location = System::Drawing::Point(160, 96);
			this->textBoxLN3->Name = L"textBoxLN3";
			this->textBoxLN3->Size = System::Drawing::Size(120, 19);
			this->textBoxLN3->TabIndex = 29;
			// 
			// checkBoxEnCH3
			// 
			this->checkBoxEnCH3->AutoSize = true;
			this->checkBoxEnCH3->Location = System::Drawing::Point(16, 96);
			this->checkBoxEnCH3->Name = L"checkBoxEnCH3";
			this->checkBoxEnCH3->Size = System::Drawing::Size(46, 16);
			this->checkBoxEnCH3->TabIndex = 28;
			this->checkBoxEnCH3->Text = L"CH3";
			this->checkBoxEnCH3->UseVisualStyleBackColor = true;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(288, 96);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(11, 12);
			this->label16->TabIndex = 27;
			this->label16->Text = L"*";
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(360, 72);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(32, 19);
			this->textBox5->TabIndex = 24;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(344, 72);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(11, 12);
			this->label9->TabIndex = 23;
			this->label9->Text = L"+";
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(304, 72);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(32, 19);
			this->textBox6->TabIndex = 22;
			// 
			// textBoxLN2
			// 
			this->textBoxLN2->Location = System::Drawing::Point(160, 72);
			this->textBoxLN2->Name = L"textBoxLN2";
			this->textBoxLN2->Size = System::Drawing::Size(120, 19);
			this->textBoxLN2->TabIndex = 21;
			// 
			// checkBoxEnCH2
			// 
			this->checkBoxEnCH2->AutoSize = true;
			this->checkBoxEnCH2->Location = System::Drawing::Point(16, 72);
			this->checkBoxEnCH2->Name = L"checkBoxEnCH2";
			this->checkBoxEnCH2->Size = System::Drawing::Size(46, 16);
			this->checkBoxEnCH2->TabIndex = 20;
			this->checkBoxEnCH2->Text = L"CH2";
			this->checkBoxEnCH2->UseVisualStyleBackColor = true;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(288, 72);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(11, 12);
			this->label12->TabIndex = 19;
			this->label12->Text = L"*";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(360, 48);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(32, 19);
			this->textBox3->TabIndex = 13;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(344, 48);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(11, 12);
			this->label7->TabIndex = 12;
			this->label7->Text = L"+";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(304, 48);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(32, 19);
			this->textBox2->TabIndex = 11;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(288, 24);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(104, 12);
			this->label6->TabIndex = 10;
			this->label6->Text = L"calc (y = a * x + b)";
			// 
			// textBoxLN1
			// 
			this->textBoxLN1->Location = System::Drawing::Point(160, 48);
			this->textBoxLN1->Name = L"textBoxLN1";
			this->textBoxLN1->Size = System::Drawing::Size(120, 19);
			this->textBoxLN1->TabIndex = 9;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(16, 24);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(41, 12);
			this->label5->TabIndex = 7;
			this->label5->Text = L"column";
			// 
			// checkBoxEnCH1
			// 
			this->checkBoxEnCH1->AutoSize = true;
			this->checkBoxEnCH1->Location = System::Drawing::Point(16, 48);
			this->checkBoxEnCH1->Name = L"checkBoxEnCH1";
			this->checkBoxEnCH1->Size = System::Drawing::Size(46, 16);
			this->checkBoxEnCH1->TabIndex = 7;
			this->checkBoxEnCH1->Text = L"CH1";
			this->checkBoxEnCH1->UseVisualStyleBackColor = true;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(160, 24);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(60, 12);
			this->label3->TabIndex = 6;
			this->label3->Text = L"label name";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(288, 48);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(11, 12);
			this->label4->TabIndex = 3;
			this->label4->Text = L"*";
			// 
			// buttonOk
			// 
			this->buttonOk->Location = System::Drawing::Point(592, 696);
			this->buttonOk->Margin = System::Windows::Forms::Padding(2);
			this->buttonOk->Name = L"buttonOk";
			this->buttonOk->Size = System::Drawing::Size(75, 23);
			this->buttonOk->TabIndex = 319;
			this->buttonOk->Text = L"OK";
			this->buttonOk->UseVisualStyleBackColor = true;
			this->buttonOk->Click += gcnew System::EventHandler(this, &SetupPlot::button25_Click);
			// 
			// buttonApply
			// 
			this->buttonApply->Location = System::Drawing::Point(677, 696);
			this->buttonApply->Margin = System::Windows::Forms::Padding(2);
			this->buttonApply->Name = L"buttonApply";
			this->buttonApply->Size = System::Drawing::Size(75, 23);
			this->buttonApply->TabIndex = 318;
			this->buttonApply->Text = L"適用";
			this->buttonApply->UseVisualStyleBackColor = true;
			this->buttonApply->Click += gcnew System::EventHandler(this, &SetupPlot::button26_Click);
			// 
			// buttonCancel
			// 
			this->buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->buttonCancel->Location = System::Drawing::Point(760, 696);
			this->buttonCancel->Margin = System::Windows::Forms::Padding(2);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(75, 23);
			this->buttonCancel->TabIndex = 317;
			this->buttonCancel->Text = L"キャンセル";
			this->buttonCancel->UseVisualStyleBackColor = true;
			this->buttonCancel->Click += gcnew System::EventHandler(this, &SetupPlot::button27_Click);
			// 
			// buttonLoad
			// 
			this->buttonLoad->Location = System::Drawing::Point(16, 696);
			this->buttonLoad->Name = L"buttonLoad";
			this->buttonLoad->Size = System::Drawing::Size(75, 23);
			this->buttonLoad->TabIndex = 320;
			this->buttonLoad->Text = L"読込";
			this->buttonLoad->UseVisualStyleBackColor = true;
			// 
			// label63
			// 
			this->label63->AutoSize = true;
			this->label63->Location = System::Drawing::Point(696, 464);
			this->label63->Name = L"label63";
			this->label63->Size = System::Drawing::Size(36, 12);
			this->label63->TabIndex = 321;
			this->label63->Text = L"points";
			// 
			// SetupPlot
			// 
			this->AcceptButton = this->buttonOk;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->buttonCancel;
			this->ClientSize = System::Drawing::Size(847, 726);
			this->Controls->Add(this->label63);
			this->Controls->Add(this->buttonLoad);
			this->Controls->Add(this->buttonOk);
			this->Controls->Add(this->buttonApply);
			this->Controls->Add(this->checkBox32);
			this->Controls->Add(this->buttonCancel);
			this->Controls->Add(this->checkBox30);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->comboBox27);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->checkBox25);
			this->Controls->Add(this->checkBox26);
			this->Controls->Add(this->checkBox27);
			this->Name = L"SetupPlot";
			this->Text = L"SetupPlot";
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button25_Click(System::Object^  sender, System::EventArgs^  e) {
		this->SaveSettings();
		Close();
	}
	private: System::Void button26_Click(System::Object^  sender, System::EventArgs^  e) {
		this->SaveSettings();
	}

private: System::Void button27_Click(System::Object^  sender, System::EventArgs^  e) {
	Close();
}
private: System::Void buttonCol1_Click(System::Object^  sender, System::EventArgs^  e) {
	ColorDialog^ MyDialog = gcnew ColorDialog;
	// Keeps the user from selecting a custom color.
	MyDialog->AllowFullOpen = false;
	// Allows the user to get help. (The default is false.)
	MyDialog->ShowHelp = true;
	// Sets the initial color select to the current text color.
	MyDialog->Color = buttonCol1->ForeColor;

	// Update the text box color if the user clicks OK 
	if (MyDialog->ShowDialog() == ::System::Windows::Forms::DialogResult::OK)
	{
		buttonCol1->ForeColor = MyDialog->Color;
	}
}
};
}
