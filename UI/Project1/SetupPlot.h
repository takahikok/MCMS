#pragma once
#include <string>
#include <iostream>
#include "clx/ini.h"
#include "clx/base64.h"
#include "tkutil.h"

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
			(*ShotSetting)["CH1.Plot"]["LabelName"] = TKUTIL::SystemStringToString(textBoxLN1->Text).c_str();

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
	private: System::Windows::Forms::CheckBox^  checkBoxLog1a;
	private: System::Windows::Forms::CheckBox^  checkBoxAS1a;



	private: System::Windows::Forms::TextBox^  textBoxFT1;






	protected:


































	private: System::Windows::Forms::Label^  label72;
	private: System::Windows::Forms::TextBox^  textBoxMYTics1a;

	private: System::Windows::Forms::TextBox^  textBoxYTics1a;







	private: System::Windows::Forms::Label^  label70;
	private: System::Windows::Forms::Label^  label68;
	private: System::Windows::Forms::Label^  label67;
	private: System::Windows::Forms::CheckBox^  checkBoxFig1a;





	private: System::Windows::Forms::Label^  label66;
private: System::Windows::Forms::TextBox^  textBoxYMax1a;

private: System::Windows::Forms::TextBox^  textBoxYmin1a;









	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label65;
private: System::Windows::Forms::TextBox^  textBoxXMax;

private: System::Windows::Forms::TextBox^  textBoxXmin;

	private: System::Windows::Forms::Label^  label62;
	private: System::Windows::Forms::CheckBox^  checkBox32;
	private: System::Windows::Forms::CheckBox^  checkBox30;
private: System::Windows::Forms::CheckBox^  checkBoxASX;

	private: System::Windows::Forms::Label^  label71;
	private: System::Windows::Forms::Label^  label69;
private: System::Windows::Forms::TextBox^  textBoxLNT;
private: System::Windows::Forms::TextBox^  textBoxMXTics;


	private: System::Windows::Forms::Label^  label11;
private: System::Windows::Forms::TextBox^  textBoxXTics;

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
private: System::Windows::Forms::CheckBox^  checkBoxLog2b;

private: System::Windows::Forms::CheckBox^  checkBoxLog2a;

private: System::Windows::Forms::CheckBox^  checkBoxlog1b;
private: System::Windows::Forms::CheckBox^  checkBoxAS2b;



private: System::Windows::Forms::CheckBox^  checkBoxAS2a;

private: System::Windows::Forms::CheckBox^  checkBoxAS1b;

private: System::Windows::Forms::TextBox^  textBox95;
private: System::Windows::Forms::TextBox^  textBoxMYTics2b;

private: System::Windows::Forms::TextBox^  textBoxYTics2b;

private: System::Windows::Forms::CheckBox^  checkBoxFig2b;
private: System::Windows::Forms::TextBox^  textBoxYMax2b;


private: System::Windows::Forms::TextBox^  textBoxYmin2b;

private: System::Windows::Forms::TextBox^  textBoxFT2;
private: System::Windows::Forms::TextBox^  textBoxMYTics2a;


private: System::Windows::Forms::TextBox^  textBoxYTics2a;

private: System::Windows::Forms::CheckBox^  checkBoxFig2a;
private: System::Windows::Forms::TextBox^  textBoxYMax2a;


private: System::Windows::Forms::TextBox^  textBoxYmin2a;

private: System::Windows::Forms::TextBox^  textBox85;
private: System::Windows::Forms::TextBox^  textBoxMYTics1b;

private: System::Windows::Forms::TextBox^  textBoxYTics1b;

private: System::Windows::Forms::CheckBox^  checkBoxFig1b;
private: System::Windows::Forms::TextBox^  textBoxYMax1b;


private: System::Windows::Forms::TextBox^  textBoxYmin1b;











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
			this->checkBoxLog1a = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxAS1a = (gcnew System::Windows::Forms::CheckBox());
			this->textBoxFT1 = (gcnew System::Windows::Forms::TextBox());
			this->label72 = (gcnew System::Windows::Forms::Label());
			this->textBoxMYTics1a = (gcnew System::Windows::Forms::TextBox());
			this->textBoxYTics1a = (gcnew System::Windows::Forms::TextBox());
			this->label70 = (gcnew System::Windows::Forms::Label());
			this->label68 = (gcnew System::Windows::Forms::Label());
			this->label67 = (gcnew System::Windows::Forms::Label());
			this->checkBoxFig1a = (gcnew System::Windows::Forms::CheckBox());
			this->label66 = (gcnew System::Windows::Forms::Label());
			this->textBoxYMax1a = (gcnew System::Windows::Forms::TextBox());
			this->textBoxYmin1a = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label65 = (gcnew System::Windows::Forms::Label());
			this->textBoxXMax = (gcnew System::Windows::Forms::TextBox());
			this->textBoxXmin = (gcnew System::Windows::Forms::TextBox());
			this->label62 = (gcnew System::Windows::Forms::Label());
			this->checkBoxASX = (gcnew System::Windows::Forms::CheckBox());
			this->label71 = (gcnew System::Windows::Forms::Label());
			this->label69 = (gcnew System::Windows::Forms::Label());
			this->textBoxLNT = (gcnew System::Windows::Forms::TextBox());
			this->textBoxMXTics = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->textBoxXTics = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBoxUn = (gcnew System::Windows::Forms::ComboBox());
			this->checkBox32 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox30 = (gcnew System::Windows::Forms::CheckBox());
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
			this->textBoxYmin1b = (gcnew System::Windows::Forms::TextBox());
			this->textBoxYMax1b = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxFig1b = (gcnew System::Windows::Forms::CheckBox());
			this->textBoxYTics1b = (gcnew System::Windows::Forms::TextBox());
			this->textBoxMYTics1b = (gcnew System::Windows::Forms::TextBox());
			this->textBox85 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxYmin2a = (gcnew System::Windows::Forms::TextBox());
			this->textBoxYMax2a = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxFig2a = (gcnew System::Windows::Forms::CheckBox());
			this->textBoxYTics2a = (gcnew System::Windows::Forms::TextBox());
			this->textBoxMYTics2a = (gcnew System::Windows::Forms::TextBox());
			this->textBoxFT2 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxYmin2b = (gcnew System::Windows::Forms::TextBox());
			this->textBoxYMax2b = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxFig2b = (gcnew System::Windows::Forms::CheckBox());
			this->textBoxYTics2b = (gcnew System::Windows::Forms::TextBox());
			this->textBoxMYTics2b = (gcnew System::Windows::Forms::TextBox());
			this->textBox95 = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxAS1b = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxAS2a = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxAS2b = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxlog1b = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxLog2a = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxLog2b = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox3->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->checkBoxLog2b);
			this->groupBox3->Controls->Add(this->checkBoxLog2a);
			this->groupBox3->Controls->Add(this->checkBoxlog1b);
			this->groupBox3->Controls->Add(this->checkBoxLog1a);
			this->groupBox3->Controls->Add(this->checkBoxAS2b);
			this->groupBox3->Controls->Add(this->checkBoxAS2a);
			this->groupBox3->Controls->Add(this->checkBoxAS1b);
			this->groupBox3->Controls->Add(this->checkBoxAS1a);
			this->groupBox3->Controls->Add(this->textBox95);
			this->groupBox3->Controls->Add(this->textBoxMYTics2b);
			this->groupBox3->Controls->Add(this->textBoxYTics2b);
			this->groupBox3->Controls->Add(this->checkBoxFig2b);
			this->groupBox3->Controls->Add(this->textBoxYMax2b);
			this->groupBox3->Controls->Add(this->textBoxYmin2b);
			this->groupBox3->Controls->Add(this->textBoxFT2);
			this->groupBox3->Controls->Add(this->textBoxMYTics2a);
			this->groupBox3->Controls->Add(this->textBoxYTics2a);
			this->groupBox3->Controls->Add(this->checkBoxFig2a);
			this->groupBox3->Controls->Add(this->textBoxYMax2a);
			this->groupBox3->Controls->Add(this->textBoxYmin2a);
			this->groupBox3->Controls->Add(this->textBox85);
			this->groupBox3->Controls->Add(this->textBoxMYTics1b);
			this->groupBox3->Controls->Add(this->textBoxYTics1b);
			this->groupBox3->Controls->Add(this->checkBoxFig1b);
			this->groupBox3->Controls->Add(this->textBoxYMax1b);
			this->groupBox3->Controls->Add(this->textBoxYmin1b);
			this->groupBox3->Controls->Add(this->textBoxFT1);
			this->groupBox3->Controls->Add(this->label72);
			this->groupBox3->Controls->Add(this->textBoxMYTics1a);
			this->groupBox3->Controls->Add(this->textBoxYTics1a);
			this->groupBox3->Controls->Add(this->label70);
			this->groupBox3->Controls->Add(this->label68);
			this->groupBox3->Controls->Add(this->label67);
			this->groupBox3->Controls->Add(this->checkBoxFig1a);
			this->groupBox3->Controls->Add(this->label66);
			this->groupBox3->Controls->Add(this->textBoxYMax1a);
			this->groupBox3->Controls->Add(this->textBoxYmin1a);
			this->groupBox3->Location = System::Drawing::Point(21, 570);
			this->groupBox3->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Padding = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox3->Size = System::Drawing::Size(757, 190);
			this->groupBox3->TabIndex = 316;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Y axis";
			// 
			// checkBoxLog1a
			// 
			this->checkBoxLog1a->AutoSize = true;
			this->checkBoxLog1a->Location = System::Drawing::Point(267, 60);
			this->checkBoxLog1a->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxLog1a->Name = L"checkBoxLog1a";
			this->checkBoxLog1a->Size = System::Drawing::Size(86, 19);
			this->checkBoxLog1a->TabIndex = 349;
			this->checkBoxLog1a->Text = L"logarithm";
			this->checkBoxLog1a->UseVisualStyleBackColor = true;
			// 
			// checkBoxAS1a
			// 
			this->checkBoxAS1a->AutoSize = true;
			this->checkBoxAS1a->Location = System::Drawing::Point(373, 60);
			this->checkBoxAS1a->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxAS1a->Name = L"checkBoxAS1a";
			this->checkBoxAS1a->Size = System::Drawing::Size(90, 19);
			this->checkBoxAS1a->TabIndex = 345;
			this->checkBoxAS1a->Text = L"autoscale";
			this->checkBoxAS1a->UseVisualStyleBackColor = true;
			// 
			// textBoxFT1
			// 
			this->textBoxFT1->Location = System::Drawing::Point(85, 60);
			this->textBoxFT1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxFT1->Name = L"textBoxFT1";
			this->textBoxFT1->Size = System::Drawing::Size(159, 22);
			this->textBoxFT1->TabIndex = 311;
			// 
			// label72
			// 
			this->label72->AutoSize = true;
			this->label72->Location = System::Drawing::Point(85, 30);
			this->label72->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label72->Name = L"label72";
			this->label72->Size = System::Drawing::Size(72, 15);
			this->label72->TabIndex = 310;
			this->label72->Text = L"figure title";
			// 
			// textBoxMYTics1a
			// 
			this->textBoxMYTics1a->Location = System::Drawing::Point(693, 60);
			this->textBoxMYTics1a->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxMYTics1a->Name = L"textBoxMYTics1a";
			this->textBoxMYTics1a->Size = System::Drawing::Size(41, 22);
			this->textBoxMYTics1a->TabIndex = 318;
			// 
			// textBoxYTics1a
			// 
			this->textBoxYTics1a->Location = System::Drawing::Point(640, 60);
			this->textBoxYTics1a->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxYTics1a->Name = L"textBoxYTics1a";
			this->textBoxYTics1a->Size = System::Drawing::Size(41, 22);
			this->textBoxYTics1a->TabIndex = 317;
			// 
			// label70
			// 
			this->label70->AutoSize = true;
			this->label70->Location = System::Drawing::Point(693, 30);
			this->label70->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label70->Name = L"label70";
			this->label70->Size = System::Drawing::Size(48, 15);
			this->label70->TabIndex = 316;
			this->label70->Text = L"mytics";
			// 
			// label68
			// 
			this->label68->AutoSize = true;
			this->label68->Location = System::Drawing::Point(640, 30);
			this->label68->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label68->Name = L"label68";
			this->label68->Size = System::Drawing::Size(37, 15);
			this->label68->TabIndex = 315;
			this->label68->Text = L"ytics";
			// 
			// label67
			// 
			this->label67->AutoSize = true;
			this->label67->Location = System::Drawing::Point(21, 30);
			this->label67->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label67->Name = L"label67";
			this->label67->Size = System::Drawing::Size(43, 15);
			this->label67->TabIndex = 309;
			this->label67->Text = L"figure";
			// 
			// checkBoxFig1a
			// 
			this->checkBoxFig1a->AutoSize = true;
			this->checkBoxFig1a->Location = System::Drawing::Point(21, 60);
			this->checkBoxFig1a->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxFig1a->Name = L"checkBoxFig1a";
			this->checkBoxFig1a->Size = System::Drawing::Size(46, 19);
			this->checkBoxFig1a->TabIndex = 308;
			this->checkBoxFig1a->Text = L"(a)";
			this->checkBoxFig1a->UseVisualStyleBackColor = true;
			// 
			// label66
			// 
			this->label66->AutoSize = true;
			this->label66->Location = System::Drawing::Point(480, 30);
			this->label66->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label66->Name = L"label66";
			this->label66->Size = System::Drawing::Size(133, 15);
			this->label66->TabIndex = 312;
			this->label66->Text = L"yrange (ymin, yMax)";
			// 
			// textBoxYMax1a
			// 
			this->textBoxYMax1a->Location = System::Drawing::Point(555, 60);
			this->textBoxYMax1a->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxYMax1a->Name = L"textBoxYMax1a";
			this->textBoxYMax1a->Size = System::Drawing::Size(63, 22);
			this->textBoxYMax1a->TabIndex = 314;
			// 
			// textBoxYmin1a
			// 
			this->textBoxYmin1a->Location = System::Drawing::Point(480, 60);
			this->textBoxYmin1a->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxYmin1a->Name = L"textBoxYmin1a";
			this->textBoxYmin1a->Size = System::Drawing::Size(63, 22);
			this->textBoxYmin1a->TabIndex = 313;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label65);
			this->groupBox1->Controls->Add(this->textBoxXMax);
			this->groupBox1->Controls->Add(this->textBoxXmin);
			this->groupBox1->Controls->Add(this->label62);
			this->groupBox1->Controls->Add(this->checkBoxASX);
			this->groupBox1->Controls->Add(this->label71);
			this->groupBox1->Controls->Add(this->label69);
			this->groupBox1->Controls->Add(this->textBoxLNT);
			this->groupBox1->Controls->Add(this->textBoxMXTics);
			this->groupBox1->Controls->Add(this->label11);
			this->groupBox1->Controls->Add(this->textBoxXTics);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->comboBoxUn);
			this->groupBox1->Location = System::Drawing::Point(21, 460);
			this->groupBox1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox1->Size = System::Drawing::Size(757, 100);
			this->groupBox1->TabIndex = 315;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"X axis";
			// 
			// label65
			// 
			this->label65->AutoSize = true;
			this->label65->Location = System::Drawing::Point(480, 30);
			this->label65->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label65->Name = L"label65";
			this->label65->Size = System::Drawing::Size(133, 15);
			this->label65->TabIndex = 262;
			this->label65->Text = L"xrange (xmin, xMax)";
			// 
			// textBoxXMax
			// 
			this->textBoxXMax->Location = System::Drawing::Point(555, 60);
			this->textBoxXMax->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxXMax->Name = L"textBoxXMax";
			this->textBoxXMax->Size = System::Drawing::Size(63, 22);
			this->textBoxXMax->TabIndex = 264;
			// 
			// textBoxXmin
			// 
			this->textBoxXmin->Location = System::Drawing::Point(480, 60);
			this->textBoxXmin->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxXmin->Name = L"textBoxXmin";
			this->textBoxXmin->Size = System::Drawing::Size(63, 22);
			this->textBoxXmin->TabIndex = 263;
			// 
			// label62
			// 
			this->label62->AutoSize = true;
			this->label62->Location = System::Drawing::Point(267, 30);
			this->label62->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label62->Name = L"label62";
			this->label62->Size = System::Drawing::Size(31, 15);
			this->label62->TabIndex = 261;
			this->label62->Text = L"unit";
			// 
			// checkBoxASX
			// 
			this->checkBoxASX->AutoSize = true;
			this->checkBoxASX->Location = System::Drawing::Point(373, 60);
			this->checkBoxASX->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxASX->Name = L"checkBoxASX";
			this->checkBoxASX->Size = System::Drawing::Size(90, 19);
			this->checkBoxASX->TabIndex = 258;
			this->checkBoxASX->Text = L"autoscale";
			this->checkBoxASX->UseVisualStyleBackColor = true;
			// 
			// label71
			// 
			this->label71->AutoSize = true;
			this->label71->Location = System::Drawing::Point(693, 30);
			this->label71->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label71->Name = L"label71";
			this->label71->Size = System::Drawing::Size(48, 15);
			this->label71->TabIndex = 256;
			this->label71->Text = L"mxtics";
			// 
			// label69
			// 
			this->label69->AutoSize = true;
			this->label69->Location = System::Drawing::Point(640, 30);
			this->label69->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label69->Name = L"label69";
			this->label69->Size = System::Drawing::Size(37, 15);
			this->label69->TabIndex = 250;
			this->label69->Text = L"xtics";
			// 
			// textBoxLNT
			// 
			this->textBoxLNT->Location = System::Drawing::Point(85, 60);
			this->textBoxLNT->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLNT->Name = L"textBoxLNT";
			this->textBoxLNT->Size = System::Drawing::Size(159, 22);
			this->textBoxLNT->TabIndex = 20;
			// 
			// textBoxMXTics
			// 
			this->textBoxMXTics->Location = System::Drawing::Point(693, 60);
			this->textBoxMXTics->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxMXTics->Name = L"textBoxMXTics";
			this->textBoxMXTics->Size = System::Drawing::Size(41, 22);
			this->textBoxMXTics->TabIndex = 252;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(85, 30);
			this->label11->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(74, 15);
			this->label11->TabIndex = 19;
			this->label11->Text = L"label name";
			// 
			// textBoxXTics
			// 
			this->textBoxXTics->Location = System::Drawing::Point(640, 60);
			this->textBoxXTics->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxXTics->Name = L"textBoxXTics";
			this->textBoxXTics->Size = System::Drawing::Size(41, 22);
			this->textBoxXTics->TabIndex = 251;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(21, 30);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(53, 15);
			this->label2->TabIndex = 6;
			this->label2->Text = L"column";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(21, 60);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(38, 15);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Time";
			// 
			// comboBoxUn
			// 
			this->comboBoxUn->FormattingEnabled = true;
			this->comboBoxUn->Location = System::Drawing::Point(267, 60);
			this->comboBoxUn->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxUn->Name = L"comboBoxUn";
			this->comboBoxUn->Size = System::Drawing::Size(63, 23);
			this->comboBoxUn->TabIndex = 4;
			// 
			// checkBox32
			// 
			this->checkBox32->AutoSize = true;
			this->checkBox32->Location = System::Drawing::Point(821, 640);
			this->checkBox32->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBox32->Name = L"checkBox32";
			this->checkBox32->Size = System::Drawing::Size(129, 19);
			this->checkBox32->TabIndex = 260;
			this->checkBox32->Text = L"show minor grid";
			this->checkBox32->UseVisualStyleBackColor = true;
			// 
			// checkBox30
			// 
			this->checkBox30->AutoSize = true;
			this->checkBox30->Location = System::Drawing::Point(821, 610);
			this->checkBox30->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBox30->Name = L"checkBox30";
			this->checkBox30->Size = System::Drawing::Size(128, 19);
			this->checkBox30->TabIndex = 259;
			this->checkBox30->Text = L"show major grid";
			this->checkBox30->UseVisualStyleBackColor = true;
			// 
			// comboBox27
			// 
			this->comboBox27->FormattingEnabled = true;
			this->comboBox27->Location = System::Drawing::Point(864, 580);
			this->comboBox27->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBox27->Name = L"comboBox27";
			this->comboBox27->Size = System::Drawing::Size(52, 23);
			this->comboBox27->TabIndex = 313;
			// 
			// checkBox26
			// 
			this->checkBox26->AutoSize = true;
			this->checkBox26->Location = System::Drawing::Point(821, 520);
			this->checkBox26->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBox26->Name = L"checkBox26";
			this->checkBox26->Size = System::Drawing::Size(96, 19);
			this->checkBox26->TabIndex = 314;
			this->checkBox26->Text = L"plot by dot";
			this->checkBox26->UseVisualStyleBackColor = true;
			// 
			// checkBox27
			// 
			this->checkBox27->AutoSize = true;
			this->checkBox27->Location = System::Drawing::Point(821, 550);
			this->checkBox27->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBox27->Name = L"checkBox27";
			this->checkBox27->Size = System::Drawing::Size(97, 19);
			this->checkBox27->TabIndex = 311;
			this->checkBox27->Text = L"limit points";
			this->checkBox27->UseVisualStyleBackColor = true;
			// 
			// checkBox25
			// 
			this->checkBox25->AutoSize = true;
			this->checkBox25->Location = System::Drawing::Point(821, 490);
			this->checkBox25->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBox25->Name = L"checkBox25";
			this->checkBox25->Size = System::Drawing::Size(162, 19);
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
			this->groupBox2->Location = System::Drawing::Point(21, 10);
			this->groupBox2->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Padding = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox2->Size = System::Drawing::Size(1088, 430);
			this->groupBox2->TabIndex = 310;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Data set";
			// 
			// comboBoxFig12
			// 
			this->comboBoxFig12->FormattingEnabled = true;
			this->comboBoxFig12->Location = System::Drawing::Point(96, 390);
			this->comboBoxFig12->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig12->Name = L"comboBoxFig12";
			this->comboBoxFig12->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig12->TabIndex = 243;
			// 
			// button17
			// 
			this->button17->ForeColor = System::Drawing::Color::Red;
			this->button17->Location = System::Drawing::Point(160, 390);
			this->button17->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button17->Name = L"button17";
			this->button17->Size = System::Drawing::Size(32, 29);
			this->button17->TabIndex = 242;
			this->button17->Text = L"■";
			this->button17->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig11
			// 
			this->comboBoxFig11->FormattingEnabled = true;
			this->comboBoxFig11->Location = System::Drawing::Point(96, 360);
			this->comboBoxFig11->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig11->Name = L"comboBoxFig11";
			this->comboBoxFig11->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig11->TabIndex = 241;
			// 
			// button18
			// 
			this->button18->ForeColor = System::Drawing::Color::Red;
			this->button18->Location = System::Drawing::Point(160, 360);
			this->button18->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button18->Name = L"button18";
			this->button18->Size = System::Drawing::Size(32, 29);
			this->button18->TabIndex = 240;
			this->button18->Text = L"■";
			this->button18->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig10
			// 
			this->comboBoxFig10->FormattingEnabled = true;
			this->comboBoxFig10->Location = System::Drawing::Point(96, 330);
			this->comboBoxFig10->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig10->Name = L"comboBoxFig10";
			this->comboBoxFig10->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig10->TabIndex = 239;
			// 
			// button19
			// 
			this->button19->ForeColor = System::Drawing::Color::Red;
			this->button19->Location = System::Drawing::Point(160, 330);
			this->button19->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button19->Name = L"button19";
			this->button19->Size = System::Drawing::Size(32, 29);
			this->button19->TabIndex = 238;
			this->button19->Text = L"■";
			this->button19->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig9
			// 
			this->comboBoxFig9->FormattingEnabled = true;
			this->comboBoxFig9->Location = System::Drawing::Point(96, 300);
			this->comboBoxFig9->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig9->Name = L"comboBoxFig9";
			this->comboBoxFig9->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig9->TabIndex = 237;
			// 
			// button20
			// 
			this->button20->ForeColor = System::Drawing::Color::Red;
			this->button20->Location = System::Drawing::Point(160, 300);
			this->button20->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button20->Name = L"button20";
			this->button20->Size = System::Drawing::Size(32, 29);
			this->button20->TabIndex = 236;
			this->button20->Text = L"■";
			this->button20->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig24
			// 
			this->comboBoxFig24->FormattingEnabled = true;
			this->comboBoxFig24->Location = System::Drawing::Point(640, 390);
			this->comboBoxFig24->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig24->Name = L"comboBoxFig24";
			this->comboBoxFig24->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig24->TabIndex = 235;
			// 
			// button21
			// 
			this->button21->ForeColor = System::Drawing::Color::Red;
			this->button21->Location = System::Drawing::Point(704, 390);
			this->button21->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button21->Name = L"button21";
			this->button21->Size = System::Drawing::Size(32, 29);
			this->button21->TabIndex = 234;
			this->button21->Text = L"■";
			this->button21->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig23
			// 
			this->comboBoxFig23->FormattingEnabled = true;
			this->comboBoxFig23->Location = System::Drawing::Point(640, 360);
			this->comboBoxFig23->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig23->Name = L"comboBoxFig23";
			this->comboBoxFig23->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig23->TabIndex = 233;
			// 
			// button22
			// 
			this->button22->ForeColor = System::Drawing::Color::Red;
			this->button22->Location = System::Drawing::Point(704, 360);
			this->button22->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button22->Name = L"button22";
			this->button22->Size = System::Drawing::Size(32, 29);
			this->button22->TabIndex = 232;
			this->button22->Text = L"■";
			this->button22->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig22
			// 
			this->comboBoxFig22->FormattingEnabled = true;
			this->comboBoxFig22->Location = System::Drawing::Point(640, 330);
			this->comboBoxFig22->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig22->Name = L"comboBoxFig22";
			this->comboBoxFig22->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig22->TabIndex = 231;
			// 
			// button23
			// 
			this->button23->ForeColor = System::Drawing::Color::Red;
			this->button23->Location = System::Drawing::Point(704, 330);
			this->button23->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button23->Name = L"button23";
			this->button23->Size = System::Drawing::Size(32, 29);
			this->button23->TabIndex = 230;
			this->button23->Text = L"■";
			this->button23->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig21
			// 
			this->comboBoxFig21->FormattingEnabled = true;
			this->comboBoxFig21->Location = System::Drawing::Point(640, 300);
			this->comboBoxFig21->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig21->Name = L"comboBoxFig21";
			this->comboBoxFig21->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig21->TabIndex = 229;
			// 
			// button24
			// 
			this->button24->ForeColor = System::Drawing::Color::Red;
			this->button24->Location = System::Drawing::Point(704, 300);
			this->button24->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button24->Name = L"button24";
			this->button24->Size = System::Drawing::Size(32, 29);
			this->button24->TabIndex = 228;
			this->button24->Text = L"■";
			this->button24->UseVisualStyleBackColor = true;
			// 
			// textBox50
			// 
			this->textBox50->Location = System::Drawing::Point(1024, 390);
			this->textBox50->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox50->Name = L"textBox50";
			this->textBox50->Size = System::Drawing::Size(41, 22);
			this->textBox50->TabIndex = 227;
			// 
			// label46
			// 
			this->label46->AutoSize = true;
			this->label46->Location = System::Drawing::Point(1003, 390);
			this->label46->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label46->Name = L"label46";
			this->label46->Size = System::Drawing::Size(15, 15);
			this->label46->TabIndex = 226;
			this->label46->Text = L"+";
			// 
			// textBox51
			// 
			this->textBox51->Location = System::Drawing::Point(949, 390);
			this->textBox51->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox51->Name = L"textBox51";
			this->textBox51->Size = System::Drawing::Size(41, 22);
			this->textBox51->TabIndex = 225;
			// 
			// textBoxLN24
			// 
			this->textBoxLN24->Location = System::Drawing::Point(757, 390);
			this->textBoxLN24->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN24->Name = L"textBoxLN24";
			this->textBoxLN24->Size = System::Drawing::Size(159, 22);
			this->textBoxLN24->TabIndex = 224;
			// 
			// checkBoxEnCH24
			// 
			this->checkBoxEnCH24->AutoSize = true;
			this->checkBoxEnCH24->Location = System::Drawing::Point(565, 390);
			this->checkBoxEnCH24->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH24->Name = L"checkBoxEnCH24";
			this->checkBoxEnCH24->Size = System::Drawing::Size(57, 19);
			this->checkBoxEnCH24->TabIndex = 223;
			this->checkBoxEnCH24->Text = L"CH1";
			this->checkBoxEnCH24->UseVisualStyleBackColor = true;
			// 
			// label47
			// 
			this->label47->AutoSize = true;
			this->label47->Location = System::Drawing::Point(928, 390);
			this->label47->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label47->Name = L"label47";
			this->label47->Size = System::Drawing::Size(15, 15);
			this->label47->TabIndex = 222;
			this->label47->Text = L"*";
			// 
			// textBox53
			// 
			this->textBox53->Location = System::Drawing::Point(1024, 360);
			this->textBox53->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox53->Name = L"textBox53";
			this->textBox53->Size = System::Drawing::Size(41, 22);
			this->textBox53->TabIndex = 221;
			// 
			// label48
			// 
			this->label48->AutoSize = true;
			this->label48->Location = System::Drawing::Point(1003, 360);
			this->label48->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label48->Name = L"label48";
			this->label48->Size = System::Drawing::Size(15, 15);
			this->label48->TabIndex = 220;
			this->label48->Text = L"+";
			// 
			// textBox54
			// 
			this->textBox54->Location = System::Drawing::Point(949, 360);
			this->textBox54->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox54->Name = L"textBox54";
			this->textBox54->Size = System::Drawing::Size(41, 22);
			this->textBox54->TabIndex = 219;
			// 
			// textBoxLN23
			// 
			this->textBoxLN23->Location = System::Drawing::Point(757, 360);
			this->textBoxLN23->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN23->Name = L"textBoxLN23";
			this->textBoxLN23->Size = System::Drawing::Size(159, 22);
			this->textBoxLN23->TabIndex = 218;
			// 
			// checkBoxEnCH23
			// 
			this->checkBoxEnCH23->AutoSize = true;
			this->checkBoxEnCH23->Location = System::Drawing::Point(565, 360);
			this->checkBoxEnCH23->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH23->Name = L"checkBoxEnCH23";
			this->checkBoxEnCH23->Size = System::Drawing::Size(57, 19);
			this->checkBoxEnCH23->TabIndex = 217;
			this->checkBoxEnCH23->Text = L"CH1";
			this->checkBoxEnCH23->UseVisualStyleBackColor = true;
			// 
			// label49
			// 
			this->label49->AutoSize = true;
			this->label49->Location = System::Drawing::Point(928, 360);
			this->label49->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label49->Name = L"label49";
			this->label49->Size = System::Drawing::Size(15, 15);
			this->label49->TabIndex = 216;
			this->label49->Text = L"*";
			// 
			// textBox56
			// 
			this->textBox56->Location = System::Drawing::Point(1024, 330);
			this->textBox56->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox56->Name = L"textBox56";
			this->textBox56->Size = System::Drawing::Size(41, 22);
			this->textBox56->TabIndex = 215;
			// 
			// label50
			// 
			this->label50->AutoSize = true;
			this->label50->Location = System::Drawing::Point(1003, 330);
			this->label50->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label50->Name = L"label50";
			this->label50->Size = System::Drawing::Size(15, 15);
			this->label50->TabIndex = 214;
			this->label50->Text = L"+";
			// 
			// textBox57
			// 
			this->textBox57->Location = System::Drawing::Point(949, 330);
			this->textBox57->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox57->Name = L"textBox57";
			this->textBox57->Size = System::Drawing::Size(41, 22);
			this->textBox57->TabIndex = 213;
			// 
			// textBoxLN22
			// 
			this->textBoxLN22->Location = System::Drawing::Point(757, 330);
			this->textBoxLN22->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN22->Name = L"textBoxLN22";
			this->textBoxLN22->Size = System::Drawing::Size(159, 22);
			this->textBoxLN22->TabIndex = 212;
			// 
			// checkBoxEnCH22
			// 
			this->checkBoxEnCH22->AutoSize = true;
			this->checkBoxEnCH22->Location = System::Drawing::Point(565, 330);
			this->checkBoxEnCH22->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH22->Name = L"checkBoxEnCH22";
			this->checkBoxEnCH22->Size = System::Drawing::Size(57, 19);
			this->checkBoxEnCH22->TabIndex = 211;
			this->checkBoxEnCH22->Text = L"CH1";
			this->checkBoxEnCH22->UseVisualStyleBackColor = true;
			// 
			// label51
			// 
			this->label51->AutoSize = true;
			this->label51->Location = System::Drawing::Point(928, 330);
			this->label51->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label51->Name = L"label51";
			this->label51->Size = System::Drawing::Size(15, 15);
			this->label51->TabIndex = 210;
			this->label51->Text = L"*";
			// 
			// textBox59
			// 
			this->textBox59->Location = System::Drawing::Point(1024, 300);
			this->textBox59->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox59->Name = L"textBox59";
			this->textBox59->Size = System::Drawing::Size(41, 22);
			this->textBox59->TabIndex = 209;
			// 
			// label52
			// 
			this->label52->AutoSize = true;
			this->label52->Location = System::Drawing::Point(1003, 300);
			this->label52->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label52->Name = L"label52";
			this->label52->Size = System::Drawing::Size(15, 15);
			this->label52->TabIndex = 208;
			this->label52->Text = L"+";
			// 
			// textBox60
			// 
			this->textBox60->Location = System::Drawing::Point(949, 300);
			this->textBox60->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox60->Name = L"textBox60";
			this->textBox60->Size = System::Drawing::Size(41, 22);
			this->textBox60->TabIndex = 207;
			// 
			// textBoxLN21
			// 
			this->textBoxLN21->Location = System::Drawing::Point(757, 300);
			this->textBoxLN21->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN21->Name = L"textBoxLN21";
			this->textBoxLN21->Size = System::Drawing::Size(159, 22);
			this->textBoxLN21->TabIndex = 206;
			// 
			// checkBoxEnCH21
			// 
			this->checkBoxEnCH21->AutoSize = true;
			this->checkBoxEnCH21->Location = System::Drawing::Point(565, 300);
			this->checkBoxEnCH21->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH21->Name = L"checkBoxEnCH21";
			this->checkBoxEnCH21->Size = System::Drawing::Size(57, 19);
			this->checkBoxEnCH21->TabIndex = 205;
			this->checkBoxEnCH21->Text = L"CH1";
			this->checkBoxEnCH21->UseVisualStyleBackColor = true;
			// 
			// label53
			// 
			this->label53->AutoSize = true;
			this->label53->Location = System::Drawing::Point(928, 300);
			this->label53->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label53->Name = L"label53";
			this->label53->Size = System::Drawing::Size(15, 15);
			this->label53->TabIndex = 204;
			this->label53->Text = L"*";
			// 
			// textBox62
			// 
			this->textBox62->Location = System::Drawing::Point(480, 390);
			this->textBox62->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox62->Name = L"textBox62";
			this->textBox62->Size = System::Drawing::Size(41, 22);
			this->textBox62->TabIndex = 203;
			// 
			// label54
			// 
			this->label54->AutoSize = true;
			this->label54->Location = System::Drawing::Point(459, 390);
			this->label54->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label54->Name = L"label54";
			this->label54->Size = System::Drawing::Size(15, 15);
			this->label54->TabIndex = 202;
			this->label54->Text = L"+";
			// 
			// textBox63
			// 
			this->textBox63->Location = System::Drawing::Point(405, 390);
			this->textBox63->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox63->Name = L"textBox63";
			this->textBox63->Size = System::Drawing::Size(41, 22);
			this->textBox63->TabIndex = 201;
			// 
			// textBoxLN12
			// 
			this->textBoxLN12->Location = System::Drawing::Point(213, 390);
			this->textBoxLN12->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN12->Name = L"textBoxLN12";
			this->textBoxLN12->Size = System::Drawing::Size(159, 22);
			this->textBoxLN12->TabIndex = 200;
			// 
			// checkBoxEnCH12
			// 
			this->checkBoxEnCH12->AutoSize = true;
			this->checkBoxEnCH12->Location = System::Drawing::Point(21, 390);
			this->checkBoxEnCH12->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH12->Name = L"checkBoxEnCH12";
			this->checkBoxEnCH12->Size = System::Drawing::Size(65, 19);
			this->checkBoxEnCH12->TabIndex = 199;
			this->checkBoxEnCH12->Text = L"CH12";
			this->checkBoxEnCH12->UseVisualStyleBackColor = true;
			// 
			// label55
			// 
			this->label55->AutoSize = true;
			this->label55->Location = System::Drawing::Point(384, 390);
			this->label55->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label55->Name = L"label55";
			this->label55->Size = System::Drawing::Size(15, 15);
			this->label55->TabIndex = 198;
			this->label55->Text = L"*";
			// 
			// textBox65
			// 
			this->textBox65->Location = System::Drawing::Point(480, 360);
			this->textBox65->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox65->Name = L"textBox65";
			this->textBox65->Size = System::Drawing::Size(41, 22);
			this->textBox65->TabIndex = 197;
			// 
			// label56
			// 
			this->label56->AutoSize = true;
			this->label56->Location = System::Drawing::Point(459, 360);
			this->label56->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label56->Name = L"label56";
			this->label56->Size = System::Drawing::Size(15, 15);
			this->label56->TabIndex = 196;
			this->label56->Text = L"+";
			// 
			// textBox66
			// 
			this->textBox66->Location = System::Drawing::Point(405, 360);
			this->textBox66->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox66->Name = L"textBox66";
			this->textBox66->Size = System::Drawing::Size(41, 22);
			this->textBox66->TabIndex = 195;
			// 
			// textBoxLN11
			// 
			this->textBoxLN11->Location = System::Drawing::Point(213, 360);
			this->textBoxLN11->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN11->Name = L"textBoxLN11";
			this->textBoxLN11->Size = System::Drawing::Size(159, 22);
			this->textBoxLN11->TabIndex = 194;
			// 
			// checkBoxEnCH11
			// 
			this->checkBoxEnCH11->AutoSize = true;
			this->checkBoxEnCH11->Location = System::Drawing::Point(21, 360);
			this->checkBoxEnCH11->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH11->Name = L"checkBoxEnCH11";
			this->checkBoxEnCH11->Size = System::Drawing::Size(57, 19);
			this->checkBoxEnCH11->TabIndex = 193;
			this->checkBoxEnCH11->Text = L"CH1";
			this->checkBoxEnCH11->UseVisualStyleBackColor = true;
			// 
			// label57
			// 
			this->label57->AutoSize = true;
			this->label57->Location = System::Drawing::Point(384, 360);
			this->label57->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label57->Name = L"label57";
			this->label57->Size = System::Drawing::Size(15, 15);
			this->label57->TabIndex = 192;
			this->label57->Text = L"*";
			// 
			// textBox68
			// 
			this->textBox68->Location = System::Drawing::Point(480, 330);
			this->textBox68->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox68->Name = L"textBox68";
			this->textBox68->Size = System::Drawing::Size(41, 22);
			this->textBox68->TabIndex = 191;
			// 
			// label58
			// 
			this->label58->AutoSize = true;
			this->label58->Location = System::Drawing::Point(459, 330);
			this->label58->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label58->Name = L"label58";
			this->label58->Size = System::Drawing::Size(15, 15);
			this->label58->TabIndex = 190;
			this->label58->Text = L"+";
			// 
			// textBox69
			// 
			this->textBox69->Location = System::Drawing::Point(405, 330);
			this->textBox69->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox69->Name = L"textBox69";
			this->textBox69->Size = System::Drawing::Size(41, 22);
			this->textBox69->TabIndex = 189;
			// 
			// textBoxLN10
			// 
			this->textBoxLN10->Location = System::Drawing::Point(213, 330);
			this->textBoxLN10->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN10->Name = L"textBoxLN10";
			this->textBoxLN10->Size = System::Drawing::Size(159, 22);
			this->textBoxLN10->TabIndex = 188;
			// 
			// checkBoxEnCH10
			// 
			this->checkBoxEnCH10->AutoSize = true;
			this->checkBoxEnCH10->Location = System::Drawing::Point(21, 330);
			this->checkBoxEnCH10->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH10->Name = L"checkBoxEnCH10";
			this->checkBoxEnCH10->Size = System::Drawing::Size(57, 19);
			this->checkBoxEnCH10->TabIndex = 187;
			this->checkBoxEnCH10->Text = L"CH1";
			this->checkBoxEnCH10->UseVisualStyleBackColor = true;
			// 
			// label59
			// 
			this->label59->AutoSize = true;
			this->label59->Location = System::Drawing::Point(384, 330);
			this->label59->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label59->Name = L"label59";
			this->label59->Size = System::Drawing::Size(15, 15);
			this->label59->TabIndex = 186;
			this->label59->Text = L"*";
			// 
			// textBox71
			// 
			this->textBox71->Location = System::Drawing::Point(480, 300);
			this->textBox71->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox71->Name = L"textBox71";
			this->textBox71->Size = System::Drawing::Size(41, 22);
			this->textBox71->TabIndex = 185;
			// 
			// label60
			// 
			this->label60->AutoSize = true;
			this->label60->Location = System::Drawing::Point(459, 300);
			this->label60->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label60->Name = L"label60";
			this->label60->Size = System::Drawing::Size(15, 15);
			this->label60->TabIndex = 184;
			this->label60->Text = L"+";
			// 
			// textBox72
			// 
			this->textBox72->Location = System::Drawing::Point(405, 300);
			this->textBox72->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox72->Name = L"textBox72";
			this->textBox72->Size = System::Drawing::Size(41, 22);
			this->textBox72->TabIndex = 183;
			// 
			// textBoxLN9
			// 
			this->textBoxLN9->Location = System::Drawing::Point(213, 300);
			this->textBoxLN9->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN9->Name = L"textBoxLN9";
			this->textBoxLN9->Size = System::Drawing::Size(159, 22);
			this->textBoxLN9->TabIndex = 182;
			// 
			// checkBoxEnCH9
			// 
			this->checkBoxEnCH9->AutoSize = true;
			this->checkBoxEnCH9->Location = System::Drawing::Point(21, 300);
			this->checkBoxEnCH9->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH9->Name = L"checkBoxEnCH9";
			this->checkBoxEnCH9->Size = System::Drawing::Size(57, 19);
			this->checkBoxEnCH9->TabIndex = 181;
			this->checkBoxEnCH9->Text = L"CH1";
			this->checkBoxEnCH9->UseVisualStyleBackColor = true;
			// 
			// label61
			// 
			this->label61->AutoSize = true;
			this->label61->Location = System::Drawing::Point(384, 300);
			this->label61->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label61->Name = L"label61";
			this->label61->Size = System::Drawing::Size(15, 15);
			this->label61->TabIndex = 180;
			this->label61->Text = L"*";
			// 
			// comboBoxFig8
			// 
			this->comboBoxFig8->FormattingEnabled = true;
			this->comboBoxFig8->Location = System::Drawing::Point(96, 270);
			this->comboBoxFig8->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig8->Name = L"comboBoxFig8";
			this->comboBoxFig8->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig8->TabIndex = 179;
			// 
			// button1
			// 
			this->button1->ForeColor = System::Drawing::Color::Red;
			this->button1->Location = System::Drawing::Point(160, 270);
			this->button1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(32, 29);
			this->button1->TabIndex = 178;
			this->button1->Text = L"■";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig7
			// 
			this->comboBoxFig7->FormattingEnabled = true;
			this->comboBoxFig7->Location = System::Drawing::Point(96, 240);
			this->comboBoxFig7->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig7->Name = L"comboBoxFig7";
			this->comboBoxFig7->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig7->TabIndex = 177;
			// 
			// button2
			// 
			this->button2->ForeColor = System::Drawing::Color::Red;
			this->button2->Location = System::Drawing::Point(160, 240);
			this->button2->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(32, 29);
			this->button2->TabIndex = 176;
			this->button2->Text = L"■";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig6
			// 
			this->comboBoxFig6->FormattingEnabled = true;
			this->comboBoxFig6->Location = System::Drawing::Point(96, 210);
			this->comboBoxFig6->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig6->Name = L"comboBoxFig6";
			this->comboBoxFig6->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig6->TabIndex = 175;
			// 
			// button3
			// 
			this->button3->ForeColor = System::Drawing::Color::Red;
			this->button3->Location = System::Drawing::Point(160, 210);
			this->button3->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(32, 29);
			this->button3->TabIndex = 174;
			this->button3->Text = L"■";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig5
			// 
			this->comboBoxFig5->FormattingEnabled = true;
			this->comboBoxFig5->Location = System::Drawing::Point(96, 180);
			this->comboBoxFig5->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig5->Name = L"comboBoxFig5";
			this->comboBoxFig5->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig5->TabIndex = 173;
			// 
			// button4
			// 
			this->button4->ForeColor = System::Drawing::Color::Red;
			this->button4->Location = System::Drawing::Point(160, 180);
			this->button4->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(32, 29);
			this->button4->TabIndex = 172;
			this->button4->Text = L"■";
			this->button4->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig4
			// 
			this->comboBoxFig4->FormattingEnabled = true;
			this->comboBoxFig4->Location = System::Drawing::Point(96, 150);
			this->comboBoxFig4->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig4->Name = L"comboBoxFig4";
			this->comboBoxFig4->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig4->TabIndex = 171;
			// 
			// button5
			// 
			this->button5->ForeColor = System::Drawing::Color::Red;
			this->button5->Location = System::Drawing::Point(160, 150);
			this->button5->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(32, 29);
			this->button5->TabIndex = 170;
			this->button5->Text = L"■";
			this->button5->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig3
			// 
			this->comboBoxFig3->FormattingEnabled = true;
			this->comboBoxFig3->Location = System::Drawing::Point(96, 120);
			this->comboBoxFig3->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig3->Name = L"comboBoxFig3";
			this->comboBoxFig3->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig3->TabIndex = 169;
			// 
			// button6
			// 
			this->button6->ForeColor = System::Drawing::Color::Red;
			this->button6->Location = System::Drawing::Point(160, 120);
			this->button6->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(32, 29);
			this->button6->TabIndex = 168;
			this->button6->Text = L"■";
			this->button6->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig2
			// 
			this->comboBoxFig2->FormattingEnabled = true;
			this->comboBoxFig2->Location = System::Drawing::Point(96, 90);
			this->comboBoxFig2->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig2->Name = L"comboBoxFig2";
			this->comboBoxFig2->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig2->TabIndex = 167;
			// 
			// button7
			// 
			this->button7->ForeColor = System::Drawing::Color::Red;
			this->button7->Location = System::Drawing::Point(160, 90);
			this->button7->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(32, 29);
			this->button7->TabIndex = 166;
			this->button7->Text = L"■";
			this->button7->UseVisualStyleBackColor = true;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(96, 30);
			this->label8->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(43, 15);
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
			this->comboBoxFig1->Location = System::Drawing::Point(96, 60);
			this->comboBoxFig1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig1->Name = L"comboBoxFig1";
			this->comboBoxFig1->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig1->TabIndex = 164;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(160, 30);
			this->label10->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(39, 15);
			this->label10->TabIndex = 163;
			this->label10->Text = L"color";
			// 
			// buttonCol1
			// 
			this->buttonCol1->ForeColor = System::Drawing::Color::Red;
			this->buttonCol1->Location = System::Drawing::Point(160, 60);
			this->buttonCol1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->buttonCol1->Name = L"buttonCol1";
			this->buttonCol1->Size = System::Drawing::Size(32, 29);
			this->buttonCol1->TabIndex = 162;
			this->buttonCol1->Text = L"■";
			this->buttonCol1->UseVisualStyleBackColor = true;
			this->buttonCol1->Click += gcnew System::EventHandler(this, &SetupPlot::buttonCol1_Click);
			// 
			// comboBoxFig20
			// 
			this->comboBoxFig20->FormattingEnabled = true;
			this->comboBoxFig20->Location = System::Drawing::Point(640, 270);
			this->comboBoxFig20->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig20->Name = L"comboBoxFig20";
			this->comboBoxFig20->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig20->TabIndex = 161;
			// 
			// button9
			// 
			this->button9->ForeColor = System::Drawing::Color::Red;
			this->button9->Location = System::Drawing::Point(704, 270);
			this->button9->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(32, 29);
			this->button9->TabIndex = 160;
			this->button9->Text = L"■";
			this->button9->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig19
			// 
			this->comboBoxFig19->FormattingEnabled = true;
			this->comboBoxFig19->Location = System::Drawing::Point(640, 240);
			this->comboBoxFig19->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig19->Name = L"comboBoxFig19";
			this->comboBoxFig19->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig19->TabIndex = 159;
			// 
			// button10
			// 
			this->button10->ForeColor = System::Drawing::Color::Red;
			this->button10->Location = System::Drawing::Point(704, 240);
			this->button10->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(32, 29);
			this->button10->TabIndex = 158;
			this->button10->Text = L"■";
			this->button10->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig18
			// 
			this->comboBoxFig18->FormattingEnabled = true;
			this->comboBoxFig18->Location = System::Drawing::Point(640, 210);
			this->comboBoxFig18->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig18->Name = L"comboBoxFig18";
			this->comboBoxFig18->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig18->TabIndex = 157;
			// 
			// button11
			// 
			this->button11->ForeColor = System::Drawing::Color::Red;
			this->button11->Location = System::Drawing::Point(704, 210);
			this->button11->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(32, 29);
			this->button11->TabIndex = 156;
			this->button11->Text = L"■";
			this->button11->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig17
			// 
			this->comboBoxFig17->FormattingEnabled = true;
			this->comboBoxFig17->Location = System::Drawing::Point(640, 180);
			this->comboBoxFig17->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig17->Name = L"comboBoxFig17";
			this->comboBoxFig17->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig17->TabIndex = 155;
			// 
			// button12
			// 
			this->button12->ForeColor = System::Drawing::Color::Red;
			this->button12->Location = System::Drawing::Point(704, 180);
			this->button12->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(32, 29);
			this->button12->TabIndex = 154;
			this->button12->Text = L"■";
			this->button12->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig16
			// 
			this->comboBoxFig16->FormattingEnabled = true;
			this->comboBoxFig16->Location = System::Drawing::Point(640, 150);
			this->comboBoxFig16->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig16->Name = L"comboBoxFig16";
			this->comboBoxFig16->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig16->TabIndex = 153;
			// 
			// button13
			// 
			this->button13->ForeColor = System::Drawing::Color::Red;
			this->button13->Location = System::Drawing::Point(704, 150);
			this->button13->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(32, 29);
			this->button13->TabIndex = 152;
			this->button13->Text = L"■";
			this->button13->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig15
			// 
			this->comboBoxFig15->FormattingEnabled = true;
			this->comboBoxFig15->Location = System::Drawing::Point(640, 120);
			this->comboBoxFig15->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig15->Name = L"comboBoxFig15";
			this->comboBoxFig15->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig15->TabIndex = 151;
			// 
			// button14
			// 
			this->button14->ForeColor = System::Drawing::Color::Red;
			this->button14->Location = System::Drawing::Point(704, 120);
			this->button14->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(32, 29);
			this->button14->TabIndex = 150;
			this->button14->Text = L"■";
			this->button14->UseVisualStyleBackColor = true;
			// 
			// comboBoxFig14
			// 
			this->comboBoxFig14->FormattingEnabled = true;
			this->comboBoxFig14->Location = System::Drawing::Point(640, 90);
			this->comboBoxFig14->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig14->Name = L"comboBoxFig14";
			this->comboBoxFig14->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig14->TabIndex = 149;
			// 
			// button15
			// 
			this->button15->ForeColor = System::Drawing::Color::Red;
			this->button15->Location = System::Drawing::Point(704, 90);
			this->button15->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(32, 29);
			this->button15->TabIndex = 148;
			this->button15->Text = L"■";
			this->button15->UseVisualStyleBackColor = true;
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->Location = System::Drawing::Point(640, 30);
			this->label39->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(43, 15);
			this->label39->TabIndex = 147;
			this->label39->Text = L"figure";
			// 
			// comboBoxFig13
			// 
			this->comboBoxFig13->FormattingEnabled = true;
			this->comboBoxFig13->Location = System::Drawing::Point(640, 60);
			this->comboBoxFig13->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBoxFig13->Name = L"comboBoxFig13";
			this->comboBoxFig13->Size = System::Drawing::Size(52, 23);
			this->comboBoxFig13->TabIndex = 146;
			// 
			// label40
			// 
			this->label40->AutoSize = true;
			this->label40->Location = System::Drawing::Point(704, 30);
			this->label40->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(39, 15);
			this->label40->TabIndex = 145;
			this->label40->Text = L"color";
			// 
			// button16
			// 
			this->button16->ForeColor = System::Drawing::Color::Red;
			this->button16->Location = System::Drawing::Point(704, 60);
			this->button16->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(32, 29);
			this->button16->TabIndex = 144;
			this->button16->Text = L"■";
			this->button16->UseVisualStyleBackColor = true;
			// 
			// textBox26
			// 
			this->textBox26->Location = System::Drawing::Point(1024, 270);
			this->textBox26->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox26->Name = L"textBox26";
			this->textBox26->Size = System::Drawing::Size(41, 22);
			this->textBox26->TabIndex = 141;
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(1003, 270);
			this->label25->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(15, 15);
			this->label25->TabIndex = 140;
			this->label25->Text = L"+";
			// 
			// textBox27
			// 
			this->textBox27->Location = System::Drawing::Point(949, 270);
			this->textBox27->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox27->Name = L"textBox27";
			this->textBox27->Size = System::Drawing::Size(41, 22);
			this->textBox27->TabIndex = 139;
			// 
			// textBoxLN20
			// 
			this->textBoxLN20->Location = System::Drawing::Point(757, 270);
			this->textBoxLN20->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN20->Name = L"textBoxLN20";
			this->textBoxLN20->Size = System::Drawing::Size(159, 22);
			this->textBoxLN20->TabIndex = 138;
			// 
			// checkBoxEnCH20
			// 
			this->checkBoxEnCH20->AutoSize = true;
			this->checkBoxEnCH20->Location = System::Drawing::Point(565, 270);
			this->checkBoxEnCH20->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH20->Name = L"checkBoxEnCH20";
			this->checkBoxEnCH20->Size = System::Drawing::Size(57, 19);
			this->checkBoxEnCH20->TabIndex = 137;
			this->checkBoxEnCH20->Text = L"CH1";
			this->checkBoxEnCH20->UseVisualStyleBackColor = true;
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(928, 270);
			this->label26->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(15, 15);
			this->label26->TabIndex = 136;
			this->label26->Text = L"*";
			// 
			// textBox29
			// 
			this->textBox29->Location = System::Drawing::Point(1024, 240);
			this->textBox29->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox29->Name = L"textBox29";
			this->textBox29->Size = System::Drawing::Size(41, 22);
			this->textBox29->TabIndex = 133;
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Location = System::Drawing::Point(1003, 240);
			this->label27->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(15, 15);
			this->label27->TabIndex = 132;
			this->label27->Text = L"+";
			// 
			// textBox30
			// 
			this->textBox30->Location = System::Drawing::Point(949, 240);
			this->textBox30->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox30->Name = L"textBox30";
			this->textBox30->Size = System::Drawing::Size(41, 22);
			this->textBox30->TabIndex = 131;
			// 
			// textBoxLN19
			// 
			this->textBoxLN19->Location = System::Drawing::Point(757, 240);
			this->textBoxLN19->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN19->Name = L"textBoxLN19";
			this->textBoxLN19->Size = System::Drawing::Size(159, 22);
			this->textBoxLN19->TabIndex = 130;
			// 
			// checkBoxEnCH19
			// 
			this->checkBoxEnCH19->AutoSize = true;
			this->checkBoxEnCH19->Location = System::Drawing::Point(565, 240);
			this->checkBoxEnCH19->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH19->Name = L"checkBoxEnCH19";
			this->checkBoxEnCH19->Size = System::Drawing::Size(57, 19);
			this->checkBoxEnCH19->TabIndex = 129;
			this->checkBoxEnCH19->Text = L"CH1";
			this->checkBoxEnCH19->UseVisualStyleBackColor = true;
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Location = System::Drawing::Point(928, 240);
			this->label28->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(15, 15);
			this->label28->TabIndex = 128;
			this->label28->Text = L"*";
			// 
			// textBox32
			// 
			this->textBox32->Location = System::Drawing::Point(1024, 210);
			this->textBox32->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox32->Name = L"textBox32";
			this->textBox32->Size = System::Drawing::Size(41, 22);
			this->textBox32->TabIndex = 125;
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Location = System::Drawing::Point(1003, 210);
			this->label29->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(15, 15);
			this->label29->TabIndex = 124;
			this->label29->Text = L"+";
			// 
			// textBox33
			// 
			this->textBox33->Location = System::Drawing::Point(949, 210);
			this->textBox33->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox33->Name = L"textBox33";
			this->textBox33->Size = System::Drawing::Size(41, 22);
			this->textBox33->TabIndex = 123;
			// 
			// textBoxLN18
			// 
			this->textBoxLN18->Location = System::Drawing::Point(757, 210);
			this->textBoxLN18->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN18->Name = L"textBoxLN18";
			this->textBoxLN18->Size = System::Drawing::Size(159, 22);
			this->textBoxLN18->TabIndex = 122;
			// 
			// checkBoxEnCH18
			// 
			this->checkBoxEnCH18->AutoSize = true;
			this->checkBoxEnCH18->Location = System::Drawing::Point(565, 210);
			this->checkBoxEnCH18->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH18->Name = L"checkBoxEnCH18";
			this->checkBoxEnCH18->Size = System::Drawing::Size(57, 19);
			this->checkBoxEnCH18->TabIndex = 121;
			this->checkBoxEnCH18->Text = L"CH1";
			this->checkBoxEnCH18->UseVisualStyleBackColor = true;
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Location = System::Drawing::Point(928, 210);
			this->label30->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(15, 15);
			this->label30->TabIndex = 120;
			this->label30->Text = L"*";
			// 
			// textBox35
			// 
			this->textBox35->Location = System::Drawing::Point(1024, 180);
			this->textBox35->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox35->Name = L"textBox35";
			this->textBox35->Size = System::Drawing::Size(41, 22);
			this->textBox35->TabIndex = 117;
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Location = System::Drawing::Point(1003, 180);
			this->label31->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(15, 15);
			this->label31->TabIndex = 116;
			this->label31->Text = L"+";
			// 
			// textBox36
			// 
			this->textBox36->Location = System::Drawing::Point(949, 180);
			this->textBox36->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox36->Name = L"textBox36";
			this->textBox36->Size = System::Drawing::Size(41, 22);
			this->textBox36->TabIndex = 115;
			// 
			// textBoxLN17
			// 
			this->textBoxLN17->Location = System::Drawing::Point(757, 180);
			this->textBoxLN17->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN17->Name = L"textBoxLN17";
			this->textBoxLN17->Size = System::Drawing::Size(159, 22);
			this->textBoxLN17->TabIndex = 114;
			// 
			// checkBoxEnCH17
			// 
			this->checkBoxEnCH17->AutoSize = true;
			this->checkBoxEnCH17->Location = System::Drawing::Point(565, 180);
			this->checkBoxEnCH17->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH17->Name = L"checkBoxEnCH17";
			this->checkBoxEnCH17->Size = System::Drawing::Size(57, 19);
			this->checkBoxEnCH17->TabIndex = 113;
			this->checkBoxEnCH17->Text = L"CH1";
			this->checkBoxEnCH17->UseVisualStyleBackColor = true;
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Location = System::Drawing::Point(928, 180);
			this->label32->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(15, 15);
			this->label32->TabIndex = 112;
			this->label32->Text = L"*";
			// 
			// textBox38
			// 
			this->textBox38->Location = System::Drawing::Point(1024, 150);
			this->textBox38->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox38->Name = L"textBox38";
			this->textBox38->Size = System::Drawing::Size(41, 22);
			this->textBox38->TabIndex = 109;
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Location = System::Drawing::Point(1003, 150);
			this->label33->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(15, 15);
			this->label33->TabIndex = 108;
			this->label33->Text = L"+";
			// 
			// textBox39
			// 
			this->textBox39->Location = System::Drawing::Point(949, 150);
			this->textBox39->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox39->Name = L"textBox39";
			this->textBox39->Size = System::Drawing::Size(41, 22);
			this->textBox39->TabIndex = 107;
			// 
			// textBoxLN16
			// 
			this->textBoxLN16->Location = System::Drawing::Point(757, 150);
			this->textBoxLN16->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN16->Name = L"textBoxLN16";
			this->textBoxLN16->Size = System::Drawing::Size(159, 22);
			this->textBoxLN16->TabIndex = 106;
			// 
			// checkBoxEnCH16
			// 
			this->checkBoxEnCH16->AutoSize = true;
			this->checkBoxEnCH16->Location = System::Drawing::Point(565, 150);
			this->checkBoxEnCH16->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH16->Name = L"checkBoxEnCH16";
			this->checkBoxEnCH16->Size = System::Drawing::Size(57, 19);
			this->checkBoxEnCH16->TabIndex = 105;
			this->checkBoxEnCH16->Text = L"CH1";
			this->checkBoxEnCH16->UseVisualStyleBackColor = true;
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->Location = System::Drawing::Point(928, 150);
			this->label34->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(15, 15);
			this->label34->TabIndex = 104;
			this->label34->Text = L"*";
			// 
			// textBox41
			// 
			this->textBox41->Location = System::Drawing::Point(1024, 120);
			this->textBox41->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox41->Name = L"textBox41";
			this->textBox41->Size = System::Drawing::Size(41, 22);
			this->textBox41->TabIndex = 101;
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->Location = System::Drawing::Point(1003, 120);
			this->label35->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(15, 15);
			this->label35->TabIndex = 100;
			this->label35->Text = L"+";
			// 
			// textBox42
			// 
			this->textBox42->Location = System::Drawing::Point(949, 120);
			this->textBox42->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox42->Name = L"textBox42";
			this->textBox42->Size = System::Drawing::Size(41, 22);
			this->textBox42->TabIndex = 99;
			// 
			// textBoxLN15
			// 
			this->textBoxLN15->Location = System::Drawing::Point(757, 120);
			this->textBoxLN15->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN15->Name = L"textBoxLN15";
			this->textBoxLN15->Size = System::Drawing::Size(159, 22);
			this->textBoxLN15->TabIndex = 98;
			// 
			// checkBoxEnCH15
			// 
			this->checkBoxEnCH15->AutoSize = true;
			this->checkBoxEnCH15->Location = System::Drawing::Point(565, 120);
			this->checkBoxEnCH15->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH15->Name = L"checkBoxEnCH15";
			this->checkBoxEnCH15->Size = System::Drawing::Size(57, 19);
			this->checkBoxEnCH15->TabIndex = 97;
			this->checkBoxEnCH15->Text = L"CH1";
			this->checkBoxEnCH15->UseVisualStyleBackColor = true;
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Location = System::Drawing::Point(928, 120);
			this->label36->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(15, 15);
			this->label36->TabIndex = 96;
			this->label36->Text = L"*";
			// 
			// textBox44
			// 
			this->textBox44->Location = System::Drawing::Point(1024, 90);
			this->textBox44->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox44->Name = L"textBox44";
			this->textBox44->Size = System::Drawing::Size(41, 22);
			this->textBox44->TabIndex = 93;
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Location = System::Drawing::Point(1003, 90);
			this->label37->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(15, 15);
			this->label37->TabIndex = 92;
			this->label37->Text = L"+";
			// 
			// textBox45
			// 
			this->textBox45->Location = System::Drawing::Point(949, 90);
			this->textBox45->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox45->Name = L"textBox45";
			this->textBox45->Size = System::Drawing::Size(41, 22);
			this->textBox45->TabIndex = 91;
			// 
			// textBoxLN14
			// 
			this->textBoxLN14->Location = System::Drawing::Point(757, 90);
			this->textBoxLN14->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN14->Name = L"textBoxLN14";
			this->textBoxLN14->Size = System::Drawing::Size(159, 22);
			this->textBoxLN14->TabIndex = 90;
			// 
			// checkBoxEnCH14
			// 
			this->checkBoxEnCH14->AutoSize = true;
			this->checkBoxEnCH14->Location = System::Drawing::Point(565, 90);
			this->checkBoxEnCH14->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH14->Name = L"checkBoxEnCH14";
			this->checkBoxEnCH14->Size = System::Drawing::Size(57, 19);
			this->checkBoxEnCH14->TabIndex = 89;
			this->checkBoxEnCH14->Text = L"CH1";
			this->checkBoxEnCH14->UseVisualStyleBackColor = true;
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->Location = System::Drawing::Point(928, 90);
			this->label38->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(15, 15);
			this->label38->TabIndex = 88;
			this->label38->Text = L"*";
			// 
			// textBox47
			// 
			this->textBox47->Location = System::Drawing::Point(1024, 60);
			this->textBox47->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox47->Name = L"textBox47";
			this->textBox47->Size = System::Drawing::Size(41, 22);
			this->textBox47->TabIndex = 83;
			// 
			// label41
			// 
			this->label41->AutoSize = true;
			this->label41->Location = System::Drawing::Point(1003, 60);
			this->label41->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label41->Name = L"label41";
			this->label41->Size = System::Drawing::Size(15, 15);
			this->label41->TabIndex = 82;
			this->label41->Text = L"+";
			// 
			// textBox48
			// 
			this->textBox48->Location = System::Drawing::Point(949, 60);
			this->textBox48->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox48->Name = L"textBox48";
			this->textBox48->Size = System::Drawing::Size(41, 22);
			this->textBox48->TabIndex = 81;
			// 
			// label42
			// 
			this->label42->AutoSize = true;
			this->label42->Location = System::Drawing::Point(928, 30);
			this->label42->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label42->Name = L"label42";
			this->label42->Size = System::Drawing::Size(130, 15);
			this->label42->TabIndex = 80;
			this->label42->Text = L"calc (y = a * x + b)";
			// 
			// textBoxLN13
			// 
			this->textBoxLN13->Location = System::Drawing::Point(757, 60);
			this->textBoxLN13->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN13->Name = L"textBoxLN13";
			this->textBoxLN13->Size = System::Drawing::Size(159, 22);
			this->textBoxLN13->TabIndex = 79;
			// 
			// label43
			// 
			this->label43->AutoSize = true;
			this->label43->Location = System::Drawing::Point(565, 30);
			this->label43->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label43->Name = L"label43";
			this->label43->Size = System::Drawing::Size(53, 15);
			this->label43->TabIndex = 77;
			this->label43->Text = L"column";
			// 
			// checkBoxEnCH13
			// 
			this->checkBoxEnCH13->AutoSize = true;
			this->checkBoxEnCH13->Location = System::Drawing::Point(565, 60);
			this->checkBoxEnCH13->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH13->Name = L"checkBoxEnCH13";
			this->checkBoxEnCH13->Size = System::Drawing::Size(57, 19);
			this->checkBoxEnCH13->TabIndex = 78;
			this->checkBoxEnCH13->Text = L"CH1";
			this->checkBoxEnCH13->UseVisualStyleBackColor = true;
			// 
			// label44
			// 
			this->label44->AutoSize = true;
			this->label44->Location = System::Drawing::Point(757, 30);
			this->label44->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label44->Name = L"label44";
			this->label44->Size = System::Drawing::Size(74, 15);
			this->label44->TabIndex = 76;
			this->label44->Text = L"label name";
			// 
			// label45
			// 
			this->label45->AutoSize = true;
			this->label45->Location = System::Drawing::Point(928, 60);
			this->label45->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label45->Name = L"label45";
			this->label45->Size = System::Drawing::Size(15, 15);
			this->label45->TabIndex = 75;
			this->label45->Text = L"*";
			// 
			// textBox14
			// 
			this->textBox14->Location = System::Drawing::Point(480, 270);
			this->textBox14->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox14->Name = L"textBox14";
			this->textBox14->Size = System::Drawing::Size(41, 22);
			this->textBox14->TabIndex = 72;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(459, 270);
			this->label17->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(15, 15);
			this->label17->TabIndex = 71;
			this->label17->Text = L"+";
			// 
			// textBox15
			// 
			this->textBox15->Location = System::Drawing::Point(405, 270);
			this->textBox15->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox15->Name = L"textBox15";
			this->textBox15->Size = System::Drawing::Size(41, 22);
			this->textBox15->TabIndex = 70;
			// 
			// textBoxLN8
			// 
			this->textBoxLN8->Location = System::Drawing::Point(213, 270);
			this->textBoxLN8->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN8->Name = L"textBoxLN8";
			this->textBoxLN8->Size = System::Drawing::Size(159, 22);
			this->textBoxLN8->TabIndex = 69;
			// 
			// checkBoxEnCH8
			// 
			this->checkBoxEnCH8->AutoSize = true;
			this->checkBoxEnCH8->Location = System::Drawing::Point(21, 270);
			this->checkBoxEnCH8->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH8->Name = L"checkBoxEnCH8";
			this->checkBoxEnCH8->Size = System::Drawing::Size(65, 19);
			this->checkBoxEnCH8->TabIndex = 68;
			this->checkBoxEnCH8->Text = L"CH12";
			this->checkBoxEnCH8->UseVisualStyleBackColor = true;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(384, 270);
			this->label18->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(15, 15);
			this->label18->TabIndex = 67;
			this->label18->Text = L"*";
			// 
			// textBox17
			// 
			this->textBox17->Location = System::Drawing::Point(480, 240);
			this->textBox17->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox17->Name = L"textBox17";
			this->textBox17->Size = System::Drawing::Size(41, 22);
			this->textBox17->TabIndex = 64;
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(459, 240);
			this->label19->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(15, 15);
			this->label19->TabIndex = 63;
			this->label19->Text = L"+";
			// 
			// textBox18
			// 
			this->textBox18->Location = System::Drawing::Point(405, 240);
			this->textBox18->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox18->Name = L"textBox18";
			this->textBox18->Size = System::Drawing::Size(41, 22);
			this->textBox18->TabIndex = 62;
			// 
			// textBoxLN7
			// 
			this->textBoxLN7->Location = System::Drawing::Point(213, 240);
			this->textBoxLN7->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN7->Name = L"textBoxLN7";
			this->textBoxLN7->Size = System::Drawing::Size(159, 22);
			this->textBoxLN7->TabIndex = 61;
			// 
			// checkBoxEnCH7
			// 
			this->checkBoxEnCH7->AutoSize = true;
			this->checkBoxEnCH7->Location = System::Drawing::Point(21, 240);
			this->checkBoxEnCH7->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH7->Name = L"checkBoxEnCH7";
			this->checkBoxEnCH7->Size = System::Drawing::Size(57, 19);
			this->checkBoxEnCH7->TabIndex = 60;
			this->checkBoxEnCH7->Text = L"CH1";
			this->checkBoxEnCH7->UseVisualStyleBackColor = true;
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(384, 240);
			this->label20->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(15, 15);
			this->label20->TabIndex = 59;
			this->label20->Text = L"*";
			// 
			// textBox20
			// 
			this->textBox20->Location = System::Drawing::Point(480, 210);
			this->textBox20->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox20->Name = L"textBox20";
			this->textBox20->Size = System::Drawing::Size(41, 22);
			this->textBox20->TabIndex = 56;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(459, 210);
			this->label21->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(15, 15);
			this->label21->TabIndex = 55;
			this->label21->Text = L"+";
			// 
			// textBox21
			// 
			this->textBox21->Location = System::Drawing::Point(405, 210);
			this->textBox21->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox21->Name = L"textBox21";
			this->textBox21->Size = System::Drawing::Size(41, 22);
			this->textBox21->TabIndex = 54;
			// 
			// textBoxLN6
			// 
			this->textBoxLN6->Location = System::Drawing::Point(213, 210);
			this->textBoxLN6->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN6->Name = L"textBoxLN6";
			this->textBoxLN6->Size = System::Drawing::Size(159, 22);
			this->textBoxLN6->TabIndex = 53;
			// 
			// checkBoxEnCH6
			// 
			this->checkBoxEnCH6->AutoSize = true;
			this->checkBoxEnCH6->Location = System::Drawing::Point(21, 210);
			this->checkBoxEnCH6->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH6->Name = L"checkBoxEnCH6";
			this->checkBoxEnCH6->Size = System::Drawing::Size(57, 19);
			this->checkBoxEnCH6->TabIndex = 52;
			this->checkBoxEnCH6->Text = L"CH1";
			this->checkBoxEnCH6->UseVisualStyleBackColor = true;
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(384, 210);
			this->label22->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(15, 15);
			this->label22->TabIndex = 51;
			this->label22->Text = L"*";
			// 
			// textBox23
			// 
			this->textBox23->Location = System::Drawing::Point(480, 180);
			this->textBox23->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox23->Name = L"textBox23";
			this->textBox23->Size = System::Drawing::Size(41, 22);
			this->textBox23->TabIndex = 48;
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(459, 180);
			this->label23->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(15, 15);
			this->label23->TabIndex = 47;
			this->label23->Text = L"+";
			// 
			// textBox24
			// 
			this->textBox24->Location = System::Drawing::Point(405, 180);
			this->textBox24->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox24->Name = L"textBox24";
			this->textBox24->Size = System::Drawing::Size(41, 22);
			this->textBox24->TabIndex = 46;
			// 
			// textBoxLN5
			// 
			this->textBoxLN5->Location = System::Drawing::Point(213, 180);
			this->textBoxLN5->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN5->Name = L"textBoxLN5";
			this->textBoxLN5->Size = System::Drawing::Size(159, 22);
			this->textBoxLN5->TabIndex = 45;
			// 
			// checkBoxEnCH5
			// 
			this->checkBoxEnCH5->AutoSize = true;
			this->checkBoxEnCH5->Location = System::Drawing::Point(21, 180);
			this->checkBoxEnCH5->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH5->Name = L"checkBoxEnCH5";
			this->checkBoxEnCH5->Size = System::Drawing::Size(57, 19);
			this->checkBoxEnCH5->TabIndex = 44;
			this->checkBoxEnCH5->Text = L"CH1";
			this->checkBoxEnCH5->UseVisualStyleBackColor = true;
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(384, 180);
			this->label24->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(15, 15);
			this->label24->TabIndex = 43;
			this->label24->Text = L"*";
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(480, 150);
			this->textBox8->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(41, 22);
			this->textBox8->TabIndex = 40;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(459, 150);
			this->label13->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(15, 15);
			this->label13->TabIndex = 39;
			this->label13->Text = L"+";
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(405, 150);
			this->textBox9->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(41, 22);
			this->textBox9->TabIndex = 38;
			// 
			// textBoxLN4
			// 
			this->textBoxLN4->Location = System::Drawing::Point(213, 150);
			this->textBoxLN4->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN4->Name = L"textBoxLN4";
			this->textBoxLN4->Size = System::Drawing::Size(159, 22);
			this->textBoxLN4->TabIndex = 37;
			// 
			// checkBoxEnCH4
			// 
			this->checkBoxEnCH4->AutoSize = true;
			this->checkBoxEnCH4->Location = System::Drawing::Point(21, 150);
			this->checkBoxEnCH4->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH4->Name = L"checkBoxEnCH4";
			this->checkBoxEnCH4->Size = System::Drawing::Size(57, 19);
			this->checkBoxEnCH4->TabIndex = 36;
			this->checkBoxEnCH4->Text = L"CH4";
			this->checkBoxEnCH4->UseVisualStyleBackColor = true;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(384, 150);
			this->label14->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(15, 15);
			this->label14->TabIndex = 35;
			this->label14->Text = L"*";
			// 
			// textBox11
			// 
			this->textBox11->Location = System::Drawing::Point(480, 120);
			this->textBox11->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(41, 22);
			this->textBox11->TabIndex = 32;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(459, 120);
			this->label15->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(15, 15);
			this->label15->TabIndex = 31;
			this->label15->Text = L"+";
			// 
			// textBox12
			// 
			this->textBox12->Location = System::Drawing::Point(405, 120);
			this->textBox12->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox12->Name = L"textBox12";
			this->textBox12->Size = System::Drawing::Size(41, 22);
			this->textBox12->TabIndex = 30;
			// 
			// textBoxLN3
			// 
			this->textBoxLN3->Location = System::Drawing::Point(213, 120);
			this->textBoxLN3->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN3->Name = L"textBoxLN3";
			this->textBoxLN3->Size = System::Drawing::Size(159, 22);
			this->textBoxLN3->TabIndex = 29;
			// 
			// checkBoxEnCH3
			// 
			this->checkBoxEnCH3->AutoSize = true;
			this->checkBoxEnCH3->Location = System::Drawing::Point(21, 120);
			this->checkBoxEnCH3->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH3->Name = L"checkBoxEnCH3";
			this->checkBoxEnCH3->Size = System::Drawing::Size(57, 19);
			this->checkBoxEnCH3->TabIndex = 28;
			this->checkBoxEnCH3->Text = L"CH3";
			this->checkBoxEnCH3->UseVisualStyleBackColor = true;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(384, 120);
			this->label16->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(15, 15);
			this->label16->TabIndex = 27;
			this->label16->Text = L"*";
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(480, 90);
			this->textBox5->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(41, 22);
			this->textBox5->TabIndex = 24;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(459, 90);
			this->label9->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(15, 15);
			this->label9->TabIndex = 23;
			this->label9->Text = L"+";
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(405, 90);
			this->textBox6->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(41, 22);
			this->textBox6->TabIndex = 22;
			// 
			// textBoxLN2
			// 
			this->textBoxLN2->Location = System::Drawing::Point(213, 90);
			this->textBoxLN2->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN2->Name = L"textBoxLN2";
			this->textBoxLN2->Size = System::Drawing::Size(159, 22);
			this->textBoxLN2->TabIndex = 21;
			// 
			// checkBoxEnCH2
			// 
			this->checkBoxEnCH2->AutoSize = true;
			this->checkBoxEnCH2->Location = System::Drawing::Point(21, 90);
			this->checkBoxEnCH2->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH2->Name = L"checkBoxEnCH2";
			this->checkBoxEnCH2->Size = System::Drawing::Size(57, 19);
			this->checkBoxEnCH2->TabIndex = 20;
			this->checkBoxEnCH2->Text = L"CH2";
			this->checkBoxEnCH2->UseVisualStyleBackColor = true;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(384, 90);
			this->label12->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(15, 15);
			this->label12->TabIndex = 19;
			this->label12->Text = L"*";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(480, 60);
			this->textBox3->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(41, 22);
			this->textBox3->TabIndex = 13;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(459, 60);
			this->label7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(15, 15);
			this->label7->TabIndex = 12;
			this->label7->Text = L"+";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(405, 60);
			this->textBox2->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(41, 22);
			this->textBox2->TabIndex = 11;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(384, 30);
			this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(130, 15);
			this->label6->TabIndex = 10;
			this->label6->Text = L"calc (y = a * x + b)";
			// 
			// textBoxLN1
			// 
			this->textBoxLN1->Location = System::Drawing::Point(213, 60);
			this->textBoxLN1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBoxLN1->Name = L"textBoxLN1";
			this->textBoxLN1->Size = System::Drawing::Size(159, 22);
			this->textBoxLN1->TabIndex = 9;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(21, 30);
			this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(53, 15);
			this->label5->TabIndex = 7;
			this->label5->Text = L"column";
			// 
			// checkBoxEnCH1
			// 
			this->checkBoxEnCH1->AutoSize = true;
			this->checkBoxEnCH1->Location = System::Drawing::Point(21, 60);
			this->checkBoxEnCH1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxEnCH1->Name = L"checkBoxEnCH1";
			this->checkBoxEnCH1->Size = System::Drawing::Size(57, 19);
			this->checkBoxEnCH1->TabIndex = 7;
			this->checkBoxEnCH1->Text = L"CH1";
			this->checkBoxEnCH1->UseVisualStyleBackColor = true;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(213, 30);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(74, 15);
			this->label3->TabIndex = 6;
			this->label3->Text = L"label name";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(384, 60);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(15, 15);
			this->label4->TabIndex = 3;
			this->label4->Text = L"*";
			// 
			// buttonOk
			// 
			this->buttonOk->Location = System::Drawing::Point(789, 870);
			this->buttonOk->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->buttonOk->Name = L"buttonOk";
			this->buttonOk->Size = System::Drawing::Size(100, 29);
			this->buttonOk->TabIndex = 319;
			this->buttonOk->Text = L"OK";
			this->buttonOk->UseVisualStyleBackColor = true;
			this->buttonOk->Click += gcnew System::EventHandler(this, &SetupPlot::button25_Click);
			// 
			// buttonApply
			// 
			this->buttonApply->Location = System::Drawing::Point(903, 870);
			this->buttonApply->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->buttonApply->Name = L"buttonApply";
			this->buttonApply->Size = System::Drawing::Size(100, 29);
			this->buttonApply->TabIndex = 318;
			this->buttonApply->Text = L"適用";
			this->buttonApply->UseVisualStyleBackColor = true;
			this->buttonApply->Click += gcnew System::EventHandler(this, &SetupPlot::button26_Click);
			// 
			// buttonCancel
			// 
			this->buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->buttonCancel->Location = System::Drawing::Point(1013, 870);
			this->buttonCancel->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(100, 29);
			this->buttonCancel->TabIndex = 317;
			this->buttonCancel->Text = L"キャンセル";
			this->buttonCancel->UseVisualStyleBackColor = true;
			this->buttonCancel->Click += gcnew System::EventHandler(this, &SetupPlot::button27_Click);
			// 
			// buttonLoad
			// 
			this->buttonLoad->Location = System::Drawing::Point(21, 870);
			this->buttonLoad->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->buttonLoad->Name = L"buttonLoad";
			this->buttonLoad->Size = System::Drawing::Size(100, 29);
			this->buttonLoad->TabIndex = 320;
			this->buttonLoad->Text = L"読込";
			this->buttonLoad->UseVisualStyleBackColor = true;
			// 
			// label63
			// 
			this->label63->AutoSize = true;
			this->label63->Location = System::Drawing::Point(928, 580);
			this->label63->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label63->Name = L"label63";
			this->label63->Size = System::Drawing::Size(45, 15);
			this->label63->TabIndex = 321;
			this->label63->Text = L"points";
			// 
			// textBoxYmin1b
			// 
			this->textBoxYmin1b->Location = System::Drawing::Point(480, 90);
			this->textBoxYmin1b->Margin = System::Windows::Forms::Padding(4);
			this->textBoxYmin1b->Name = L"textBoxYmin1b";
			this->textBoxYmin1b->Size = System::Drawing::Size(63, 22);
			this->textBoxYmin1b->TabIndex = 323;
			// 
			// textBoxYMax1b
			// 
			this->textBoxYMax1b->Location = System::Drawing::Point(555, 90);
			this->textBoxYMax1b->Margin = System::Windows::Forms::Padding(4);
			this->textBoxYMax1b->Name = L"textBoxYMax1b";
			this->textBoxYMax1b->Size = System::Drawing::Size(63, 22);
			this->textBoxYMax1b->TabIndex = 324;
			// 
			// checkBoxFig1b
			// 
			this->checkBoxFig1b->AutoSize = true;
			this->checkBoxFig1b->Location = System::Drawing::Point(21, 90);
			this->checkBoxFig1b->Margin = System::Windows::Forms::Padding(4);
			this->checkBoxFig1b->Name = L"checkBoxFig1b";
			this->checkBoxFig1b->Size = System::Drawing::Size(66, 19);
			this->checkBoxFig1b->TabIndex = 321;
			this->checkBoxFig1b->Text = L"(a) y2";
			this->checkBoxFig1b->UseVisualStyleBackColor = true;
			// 
			// textBoxYTics1b
			// 
			this->textBoxYTics1b->Location = System::Drawing::Point(640, 90);
			this->textBoxYTics1b->Margin = System::Windows::Forms::Padding(4);
			this->textBoxYTics1b->Name = L"textBoxYTics1b";
			this->textBoxYTics1b->Size = System::Drawing::Size(41, 22);
			this->textBoxYTics1b->TabIndex = 325;
			// 
			// textBoxMYTics1b
			// 
			this->textBoxMYTics1b->Location = System::Drawing::Point(693, 90);
			this->textBoxMYTics1b->Margin = System::Windows::Forms::Padding(4);
			this->textBoxMYTics1b->Name = L"textBoxMYTics1b";
			this->textBoxMYTics1b->Size = System::Drawing::Size(41, 22);
			this->textBoxMYTics1b->TabIndex = 326;
			// 
			// textBox85
			// 
			this->textBox85->Location = System::Drawing::Point(85, 90);
			this->textBox85->Margin = System::Windows::Forms::Padding(4);
			this->textBox85->Name = L"textBox85";
			this->textBox85->Size = System::Drawing::Size(159, 22);
			this->textBox85->TabIndex = 322;
			// 
			// textBoxYmin2a
			// 
			this->textBoxYmin2a->Location = System::Drawing::Point(480, 120);
			this->textBoxYmin2a->Margin = System::Windows::Forms::Padding(4);
			this->textBoxYmin2a->Name = L"textBoxYmin2a";
			this->textBoxYmin2a->Size = System::Drawing::Size(63, 22);
			this->textBoxYmin2a->TabIndex = 331;
			// 
			// textBoxYMax2a
			// 
			this->textBoxYMax2a->Location = System::Drawing::Point(555, 120);
			this->textBoxYMax2a->Margin = System::Windows::Forms::Padding(4);
			this->textBoxYMax2a->Name = L"textBoxYMax2a";
			this->textBoxYMax2a->Size = System::Drawing::Size(63, 22);
			this->textBoxYMax2a->TabIndex = 332;
			// 
			// checkBoxFig2a
			// 
			this->checkBoxFig2a->AutoSize = true;
			this->checkBoxFig2a->Location = System::Drawing::Point(21, 120);
			this->checkBoxFig2a->Margin = System::Windows::Forms::Padding(4);
			this->checkBoxFig2a->Name = L"checkBoxFig2a";
			this->checkBoxFig2a->Size = System::Drawing::Size(46, 19);
			this->checkBoxFig2a->TabIndex = 329;
			this->checkBoxFig2a->Text = L"(b)";
			this->checkBoxFig2a->UseVisualStyleBackColor = true;
			// 
			// textBoxYTics2a
			// 
			this->textBoxYTics2a->Location = System::Drawing::Point(640, 120);
			this->textBoxYTics2a->Margin = System::Windows::Forms::Padding(4);
			this->textBoxYTics2a->Name = L"textBoxYTics2a";
			this->textBoxYTics2a->Size = System::Drawing::Size(41, 22);
			this->textBoxYTics2a->TabIndex = 333;
			// 
			// textBoxMYTics2a
			// 
			this->textBoxMYTics2a->Location = System::Drawing::Point(693, 120);
			this->textBoxMYTics2a->Margin = System::Windows::Forms::Padding(4);
			this->textBoxMYTics2a->Name = L"textBoxMYTics2a";
			this->textBoxMYTics2a->Size = System::Drawing::Size(41, 22);
			this->textBoxMYTics2a->TabIndex = 334;
			// 
			// textBoxFT2
			// 
			this->textBoxFT2->Location = System::Drawing::Point(85, 120);
			this->textBoxFT2->Margin = System::Windows::Forms::Padding(4);
			this->textBoxFT2->Name = L"textBoxFT2";
			this->textBoxFT2->Size = System::Drawing::Size(159, 22);
			this->textBoxFT2->TabIndex = 330;
			// 
			// textBoxYmin2b
			// 
			this->textBoxYmin2b->Location = System::Drawing::Point(480, 150);
			this->textBoxYmin2b->Margin = System::Windows::Forms::Padding(4);
			this->textBoxYmin2b->Name = L"textBoxYmin2b";
			this->textBoxYmin2b->Size = System::Drawing::Size(63, 22);
			this->textBoxYmin2b->TabIndex = 339;
			// 
			// textBoxYMax2b
			// 
			this->textBoxYMax2b->Location = System::Drawing::Point(555, 150);
			this->textBoxYMax2b->Margin = System::Windows::Forms::Padding(4);
			this->textBoxYMax2b->Name = L"textBoxYMax2b";
			this->textBoxYMax2b->Size = System::Drawing::Size(63, 22);
			this->textBoxYMax2b->TabIndex = 340;
			// 
			// checkBoxFig2b
			// 
			this->checkBoxFig2b->AutoSize = true;
			this->checkBoxFig2b->Location = System::Drawing::Point(21, 150);
			this->checkBoxFig2b->Margin = System::Windows::Forms::Padding(4);
			this->checkBoxFig2b->Name = L"checkBoxFig2b";
			this->checkBoxFig2b->Size = System::Drawing::Size(66, 19);
			this->checkBoxFig2b->TabIndex = 337;
			this->checkBoxFig2b->Text = L"(b) y2";
			this->checkBoxFig2b->UseVisualStyleBackColor = true;
			// 
			// textBoxYTics2b
			// 
			this->textBoxYTics2b->Location = System::Drawing::Point(640, 150);
			this->textBoxYTics2b->Margin = System::Windows::Forms::Padding(4);
			this->textBoxYTics2b->Name = L"textBoxYTics2b";
			this->textBoxYTics2b->Size = System::Drawing::Size(41, 22);
			this->textBoxYTics2b->TabIndex = 341;
			// 
			// textBoxMYTics2b
			// 
			this->textBoxMYTics2b->Location = System::Drawing::Point(693, 150);
			this->textBoxMYTics2b->Margin = System::Windows::Forms::Padding(4);
			this->textBoxMYTics2b->Name = L"textBoxMYTics2b";
			this->textBoxMYTics2b->Size = System::Drawing::Size(41, 22);
			this->textBoxMYTics2b->TabIndex = 342;
			// 
			// textBox95
			// 
			this->textBox95->Location = System::Drawing::Point(85, 150);
			this->textBox95->Margin = System::Windows::Forms::Padding(4);
			this->textBox95->Name = L"textBox95";
			this->textBox95->Size = System::Drawing::Size(159, 22);
			this->textBox95->TabIndex = 338;
			// 
			// checkBoxAS1b
			// 
			this->checkBoxAS1b->AutoSize = true;
			this->checkBoxAS1b->Location = System::Drawing::Point(373, 90);
			this->checkBoxAS1b->Margin = System::Windows::Forms::Padding(4);
			this->checkBoxAS1b->Name = L"checkBoxAS1b";
			this->checkBoxAS1b->Size = System::Drawing::Size(90, 19);
			this->checkBoxAS1b->TabIndex = 346;
			this->checkBoxAS1b->Text = L"autoscale";
			this->checkBoxAS1b->UseVisualStyleBackColor = true;
			// 
			// checkBoxAS2a
			// 
			this->checkBoxAS2a->AutoSize = true;
			this->checkBoxAS2a->Location = System::Drawing::Point(373, 120);
			this->checkBoxAS2a->Margin = System::Windows::Forms::Padding(4);
			this->checkBoxAS2a->Name = L"checkBoxAS2a";
			this->checkBoxAS2a->Size = System::Drawing::Size(90, 19);
			this->checkBoxAS2a->TabIndex = 347;
			this->checkBoxAS2a->Text = L"autoscale";
			this->checkBoxAS2a->UseVisualStyleBackColor = true;
			// 
			// checkBoxAS2b
			// 
			this->checkBoxAS2b->AutoSize = true;
			this->checkBoxAS2b->Location = System::Drawing::Point(373, 150);
			this->checkBoxAS2b->Margin = System::Windows::Forms::Padding(4);
			this->checkBoxAS2b->Name = L"checkBoxAS2b";
			this->checkBoxAS2b->Size = System::Drawing::Size(90, 19);
			this->checkBoxAS2b->TabIndex = 348;
			this->checkBoxAS2b->Text = L"autoscale";
			this->checkBoxAS2b->UseVisualStyleBackColor = true;
			// 
			// checkBoxlog1b
			// 
			this->checkBoxlog1b->AutoSize = true;
			this->checkBoxlog1b->Location = System::Drawing::Point(267, 90);
			this->checkBoxlog1b->Margin = System::Windows::Forms::Padding(4);
			this->checkBoxlog1b->Name = L"checkBoxlog1b";
			this->checkBoxlog1b->Size = System::Drawing::Size(86, 19);
			this->checkBoxlog1b->TabIndex = 350;
			this->checkBoxlog1b->Text = L"logarithm";
			this->checkBoxlog1b->UseVisualStyleBackColor = true;
			// 
			// checkBoxLog2a
			// 
			this->checkBoxLog2a->AutoSize = true;
			this->checkBoxLog2a->Location = System::Drawing::Point(267, 120);
			this->checkBoxLog2a->Margin = System::Windows::Forms::Padding(4);
			this->checkBoxLog2a->Name = L"checkBoxLog2a";
			this->checkBoxLog2a->Size = System::Drawing::Size(86, 19);
			this->checkBoxLog2a->TabIndex = 351;
			this->checkBoxLog2a->Text = L"logarithm";
			this->checkBoxLog2a->UseVisualStyleBackColor = true;
			// 
			// checkBoxLog2b
			// 
			this->checkBoxLog2b->AutoSize = true;
			this->checkBoxLog2b->Location = System::Drawing::Point(267, 150);
			this->checkBoxLog2b->Margin = System::Windows::Forms::Padding(4);
			this->checkBoxLog2b->Name = L"checkBoxLog2b";
			this->checkBoxLog2b->Size = System::Drawing::Size(86, 19);
			this->checkBoxLog2b->TabIndex = 352;
			this->checkBoxLog2b->Text = L"logarithm";
			this->checkBoxLog2b->UseVisualStyleBackColor = true;
			// 
			// SetupPlot
			// 
			this->AcceptButton = this->buttonOk;
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->buttonCancel;
			this->ClientSize = System::Drawing::Size(1129, 908);
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
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
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
	MyDialog->Color = buttonCol1->ForeColor;
	if (MyDialog->ShowDialog() == ::System::Windows::Forms::DialogResult::OK)
		buttonCol1->ForeColor = MyDialog->Color;
}
};
}
