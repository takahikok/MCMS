#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
namespace Project2 {

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
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
//			{
				std::ofstream os;
				os.open("plot.plt", std::ios::trunc);
//				std::ostringstream os;
				os << "set term png" << std::endl;
				os << "set out \"graph1.png\"" << std::endl;
				os << "plot sin(x), cos(x)" << std::endl;
//			}
			std::system("gnuplot plot.plt");
			Bitmap^ MyImage;
			MyImage = gcnew Bitmap("graph1.png");
//			this->pictureBox1->Location = System::Drawing::Point(0, 0);
//			this->pictureBox1->Size = System::Drawing::Size(1000,1000);
			this->pictureBox1->Image = dynamic_cast<Image^>(MyImage);
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
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;





	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label5;

	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::ComboBox^  comboBox3;
	private: System::Windows::Forms::Label^  label4;





	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::ComboBox^  comboBox19;
	private: System::Windows::Forms::Button^  button17;
	private: System::Windows::Forms::ComboBox^  comboBox20;
	private: System::Windows::Forms::Button^  button18;
	private: System::Windows::Forms::ComboBox^  comboBox21;
	private: System::Windows::Forms::Button^  button19;
	private: System::Windows::Forms::ComboBox^  comboBox22;
	private: System::Windows::Forms::Button^  button20;
	private: System::Windows::Forms::ComboBox^  comboBox23;
	private: System::Windows::Forms::Button^  button21;
	private: System::Windows::Forms::ComboBox^  comboBox24;
	private: System::Windows::Forms::Button^  button22;
	private: System::Windows::Forms::ComboBox^  comboBox25;
	private: System::Windows::Forms::Button^  button23;
	private: System::Windows::Forms::ComboBox^  comboBox26;
	private: System::Windows::Forms::Button^  button24;
	private: System::Windows::Forms::TextBox^  textBox50;
	private: System::Windows::Forms::Label^  label46;
	private: System::Windows::Forms::TextBox^  textBox51;
	private: System::Windows::Forms::TextBox^  textBox52;
	private: System::Windows::Forms::CheckBox^  checkBox17;
	private: System::Windows::Forms::Label^  label47;
	private: System::Windows::Forms::TextBox^  textBox53;
	private: System::Windows::Forms::Label^  label48;
	private: System::Windows::Forms::TextBox^  textBox54;
	private: System::Windows::Forms::TextBox^  textBox55;
	private: System::Windows::Forms::CheckBox^  checkBox18;
	private: System::Windows::Forms::Label^  label49;
	private: System::Windows::Forms::TextBox^  textBox56;
	private: System::Windows::Forms::Label^  label50;
	private: System::Windows::Forms::TextBox^  textBox57;
	private: System::Windows::Forms::TextBox^  textBox58;
	private: System::Windows::Forms::CheckBox^  checkBox19;
	private: System::Windows::Forms::Label^  label51;
	private: System::Windows::Forms::TextBox^  textBox59;
	private: System::Windows::Forms::Label^  label52;
	private: System::Windows::Forms::TextBox^  textBox60;
	private: System::Windows::Forms::TextBox^  textBox61;
	private: System::Windows::Forms::CheckBox^  checkBox20;
	private: System::Windows::Forms::Label^  label53;
	private: System::Windows::Forms::TextBox^  textBox62;
	private: System::Windows::Forms::Label^  label54;
	private: System::Windows::Forms::TextBox^  textBox63;
	private: System::Windows::Forms::TextBox^  textBox64;
	private: System::Windows::Forms::CheckBox^  checkBox21;
	private: System::Windows::Forms::Label^  label55;
	private: System::Windows::Forms::TextBox^  textBox65;
	private: System::Windows::Forms::Label^  label56;
	private: System::Windows::Forms::TextBox^  textBox66;
	private: System::Windows::Forms::TextBox^  textBox67;
	private: System::Windows::Forms::CheckBox^  checkBox22;
	private: System::Windows::Forms::Label^  label57;
	private: System::Windows::Forms::TextBox^  textBox68;
	private: System::Windows::Forms::Label^  label58;
	private: System::Windows::Forms::TextBox^  textBox69;
	private: System::Windows::Forms::TextBox^  textBox70;
	private: System::Windows::Forms::CheckBox^  checkBox23;
	private: System::Windows::Forms::Label^  label59;
	private: System::Windows::Forms::TextBox^  textBox71;
	private: System::Windows::Forms::Label^  label60;
	private: System::Windows::Forms::TextBox^  textBox72;
	private: System::Windows::Forms::TextBox^  textBox73;
	private: System::Windows::Forms::CheckBox^  checkBox24;
	private: System::Windows::Forms::Label^  label61;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::ComboBox^  comboBox4;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::ComboBox^  comboBox5;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::ComboBox^  comboBox6;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::ComboBox^  comboBox7;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::ComboBox^  comboBox8;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::ComboBox^  comboBox9;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::ComboBox^  comboBox10;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::ComboBox^  comboBox11;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::ComboBox^  comboBox12;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::ComboBox^  comboBox13;
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::ComboBox^  comboBox14;
	private: System::Windows::Forms::Button^  button12;
	private: System::Windows::Forms::ComboBox^  comboBox15;
	private: System::Windows::Forms::Button^  button13;
	private: System::Windows::Forms::ComboBox^  comboBox16;
	private: System::Windows::Forms::Button^  button14;
	private: System::Windows::Forms::ComboBox^  comboBox17;
	private: System::Windows::Forms::Button^  button15;
	private: System::Windows::Forms::Label^  label39;
	private: System::Windows::Forms::ComboBox^  comboBox18;
	private: System::Windows::Forms::Label^  label40;
	private: System::Windows::Forms::Button^  button16;
	private: System::Windows::Forms::TextBox^  textBox26;
	private: System::Windows::Forms::Label^  label25;
	private: System::Windows::Forms::TextBox^  textBox27;
	private: System::Windows::Forms::TextBox^  textBox28;
	private: System::Windows::Forms::CheckBox^  checkBox9;
	private: System::Windows::Forms::Label^  label26;
	private: System::Windows::Forms::TextBox^  textBox29;
	private: System::Windows::Forms::Label^  label27;
	private: System::Windows::Forms::TextBox^  textBox30;
	private: System::Windows::Forms::TextBox^  textBox31;
	private: System::Windows::Forms::CheckBox^  checkBox10;
	private: System::Windows::Forms::Label^  label28;
	private: System::Windows::Forms::TextBox^  textBox32;
	private: System::Windows::Forms::Label^  label29;
	private: System::Windows::Forms::TextBox^  textBox33;
	private: System::Windows::Forms::TextBox^  textBox34;
	private: System::Windows::Forms::CheckBox^  checkBox11;
	private: System::Windows::Forms::Label^  label30;
	private: System::Windows::Forms::TextBox^  textBox35;
	private: System::Windows::Forms::Label^  label31;
	private: System::Windows::Forms::TextBox^  textBox36;
	private: System::Windows::Forms::TextBox^  textBox37;
	private: System::Windows::Forms::CheckBox^  checkBox12;
	private: System::Windows::Forms::Label^  label32;
	private: System::Windows::Forms::TextBox^  textBox38;
	private: System::Windows::Forms::Label^  label33;
	private: System::Windows::Forms::TextBox^  textBox39;
	private: System::Windows::Forms::TextBox^  textBox40;
	private: System::Windows::Forms::CheckBox^  checkBox13;
	private: System::Windows::Forms::Label^  label34;
	private: System::Windows::Forms::TextBox^  textBox41;
	private: System::Windows::Forms::Label^  label35;
	private: System::Windows::Forms::TextBox^  textBox42;
	private: System::Windows::Forms::TextBox^  textBox43;
	private: System::Windows::Forms::CheckBox^  checkBox14;
	private: System::Windows::Forms::Label^  label36;
	private: System::Windows::Forms::TextBox^  textBox44;
	private: System::Windows::Forms::Label^  label37;
	private: System::Windows::Forms::TextBox^  textBox45;
	private: System::Windows::Forms::TextBox^  textBox46;
	private: System::Windows::Forms::CheckBox^  checkBox15;
	private: System::Windows::Forms::Label^  label38;
	private: System::Windows::Forms::TextBox^  textBox47;
	private: System::Windows::Forms::Label^  label41;
	private: System::Windows::Forms::TextBox^  textBox48;
	private: System::Windows::Forms::Label^  label42;
	private: System::Windows::Forms::TextBox^  textBox49;
	private: System::Windows::Forms::Label^  label43;
	private: System::Windows::Forms::CheckBox^  checkBox16;
	private: System::Windows::Forms::Label^  label44;
	private: System::Windows::Forms::Label^  label45;
	private: System::Windows::Forms::TextBox^  textBox14;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::TextBox^  textBox15;
	private: System::Windows::Forms::TextBox^  textBox16;
	private: System::Windows::Forms::CheckBox^  checkBox5;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::TextBox^  textBox17;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::TextBox^  textBox18;
	private: System::Windows::Forms::TextBox^  textBox19;
	private: System::Windows::Forms::CheckBox^  checkBox6;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::TextBox^  textBox20;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::TextBox^  textBox21;
	private: System::Windows::Forms::TextBox^  textBox22;
	private: System::Windows::Forms::CheckBox^  checkBox7;
	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::TextBox^  textBox23;
	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::TextBox^  textBox24;
	private: System::Windows::Forms::TextBox^  textBox25;
	private: System::Windows::Forms::CheckBox^  checkBox8;
	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::TextBox^  textBox9;
	private: System::Windows::Forms::TextBox^  textBox10;
	private: System::Windows::Forms::CheckBox^  checkBox3;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::TextBox^  textBox11;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::TextBox^  textBox12;
	private: System::Windows::Forms::TextBox^  textBox13;
	private: System::Windows::Forms::CheckBox^  checkBox4;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::CheckBox^  checkBox2;
	private: System::Windows::Forms::Label^  label12;





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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->textBox12 = (gcnew System::Windows::Forms::TextBox());
			this->textBox13 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->textBox14 = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->textBox15 = (gcnew System::Windows::Forms::TextBox());
			this->textBox16 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->textBox17 = (gcnew System::Windows::Forms::TextBox());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->textBox18 = (gcnew System::Windows::Forms::TextBox());
			this->textBox19 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox6 = (gcnew System::Windows::Forms::CheckBox());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->textBox20 = (gcnew System::Windows::Forms::TextBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->textBox21 = (gcnew System::Windows::Forms::TextBox());
			this->textBox22 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox7 = (gcnew System::Windows::Forms::CheckBox());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->textBox23 = (gcnew System::Windows::Forms::TextBox());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->textBox24 = (gcnew System::Windows::Forms::TextBox());
			this->textBox25 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox8 = (gcnew System::Windows::Forms::CheckBox());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->textBox26 = (gcnew System::Windows::Forms::TextBox());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->textBox27 = (gcnew System::Windows::Forms::TextBox());
			this->textBox28 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox9 = (gcnew System::Windows::Forms::CheckBox());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->textBox29 = (gcnew System::Windows::Forms::TextBox());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->textBox30 = (gcnew System::Windows::Forms::TextBox());
			this->textBox31 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox10 = (gcnew System::Windows::Forms::CheckBox());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->textBox32 = (gcnew System::Windows::Forms::TextBox());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->textBox33 = (gcnew System::Windows::Forms::TextBox());
			this->textBox34 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox11 = (gcnew System::Windows::Forms::CheckBox());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->textBox35 = (gcnew System::Windows::Forms::TextBox());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->textBox36 = (gcnew System::Windows::Forms::TextBox());
			this->textBox37 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox12 = (gcnew System::Windows::Forms::CheckBox());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->textBox38 = (gcnew System::Windows::Forms::TextBox());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->textBox39 = (gcnew System::Windows::Forms::TextBox());
			this->textBox40 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox13 = (gcnew System::Windows::Forms::CheckBox());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->textBox41 = (gcnew System::Windows::Forms::TextBox());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->textBox42 = (gcnew System::Windows::Forms::TextBox());
			this->textBox43 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox14 = (gcnew System::Windows::Forms::CheckBox());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->textBox44 = (gcnew System::Windows::Forms::TextBox());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->textBox45 = (gcnew System::Windows::Forms::TextBox());
			this->textBox46 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox15 = (gcnew System::Windows::Forms::CheckBox());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->textBox47 = (gcnew System::Windows::Forms::TextBox());
			this->label41 = (gcnew System::Windows::Forms::Label());
			this->textBox48 = (gcnew System::Windows::Forms::TextBox());
			this->label42 = (gcnew System::Windows::Forms::Label());
			this->textBox49 = (gcnew System::Windows::Forms::TextBox());
			this->label43 = (gcnew System::Windows::Forms::Label());
			this->checkBox16 = (gcnew System::Windows::Forms::CheckBox());
			this->label44 = (gcnew System::Windows::Forms::Label());
			this->label45 = (gcnew System::Windows::Forms::Label());
			this->comboBox11 = (gcnew System::Windows::Forms::ComboBox());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->comboBox12 = (gcnew System::Windows::Forms::ComboBox());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->comboBox13 = (gcnew System::Windows::Forms::ComboBox());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->comboBox14 = (gcnew System::Windows::Forms::ComboBox());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->comboBox15 = (gcnew System::Windows::Forms::ComboBox());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->comboBox16 = (gcnew System::Windows::Forms::ComboBox());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->comboBox17 = (gcnew System::Windows::Forms::ComboBox());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->comboBox18 = (gcnew System::Windows::Forms::ComboBox());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->comboBox4 = (gcnew System::Windows::Forms::ComboBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->comboBox5 = (gcnew System::Windows::Forms::ComboBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->comboBox6 = (gcnew System::Windows::Forms::ComboBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->comboBox7 = (gcnew System::Windows::Forms::ComboBox());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->comboBox8 = (gcnew System::Windows::Forms::ComboBox());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->comboBox9 = (gcnew System::Windows::Forms::ComboBox());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->comboBox10 = (gcnew System::Windows::Forms::ComboBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->comboBox19 = (gcnew System::Windows::Forms::ComboBox());
			this->button17 = (gcnew System::Windows::Forms::Button());
			this->comboBox20 = (gcnew System::Windows::Forms::ComboBox());
			this->button18 = (gcnew System::Windows::Forms::Button());
			this->comboBox21 = (gcnew System::Windows::Forms::ComboBox());
			this->button19 = (gcnew System::Windows::Forms::Button());
			this->comboBox22 = (gcnew System::Windows::Forms::ComboBox());
			this->button20 = (gcnew System::Windows::Forms::Button());
			this->comboBox23 = (gcnew System::Windows::Forms::ComboBox());
			this->button21 = (gcnew System::Windows::Forms::Button());
			this->comboBox24 = (gcnew System::Windows::Forms::ComboBox());
			this->button22 = (gcnew System::Windows::Forms::Button());
			this->comboBox25 = (gcnew System::Windows::Forms::ComboBox());
			this->button23 = (gcnew System::Windows::Forms::Button());
			this->comboBox26 = (gcnew System::Windows::Forms::ComboBox());
			this->button24 = (gcnew System::Windows::Forms::Button());
			this->textBox50 = (gcnew System::Windows::Forms::TextBox());
			this->label46 = (gcnew System::Windows::Forms::Label());
			this->textBox51 = (gcnew System::Windows::Forms::TextBox());
			this->textBox52 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox17 = (gcnew System::Windows::Forms::CheckBox());
			this->label47 = (gcnew System::Windows::Forms::Label());
			this->textBox53 = (gcnew System::Windows::Forms::TextBox());
			this->label48 = (gcnew System::Windows::Forms::Label());
			this->textBox54 = (gcnew System::Windows::Forms::TextBox());
			this->textBox55 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox18 = (gcnew System::Windows::Forms::CheckBox());
			this->label49 = (gcnew System::Windows::Forms::Label());
			this->textBox56 = (gcnew System::Windows::Forms::TextBox());
			this->label50 = (gcnew System::Windows::Forms::Label());
			this->textBox57 = (gcnew System::Windows::Forms::TextBox());
			this->textBox58 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox19 = (gcnew System::Windows::Forms::CheckBox());
			this->label51 = (gcnew System::Windows::Forms::Label());
			this->textBox59 = (gcnew System::Windows::Forms::TextBox());
			this->label52 = (gcnew System::Windows::Forms::Label());
			this->textBox60 = (gcnew System::Windows::Forms::TextBox());
			this->textBox61 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox20 = (gcnew System::Windows::Forms::CheckBox());
			this->label53 = (gcnew System::Windows::Forms::Label());
			this->textBox62 = (gcnew System::Windows::Forms::TextBox());
			this->label54 = (gcnew System::Windows::Forms::Label());
			this->textBox63 = (gcnew System::Windows::Forms::TextBox());
			this->textBox64 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox21 = (gcnew System::Windows::Forms::CheckBox());
			this->label55 = (gcnew System::Windows::Forms::Label());
			this->textBox65 = (gcnew System::Windows::Forms::TextBox());
			this->label56 = (gcnew System::Windows::Forms::Label());
			this->textBox66 = (gcnew System::Windows::Forms::TextBox());
			this->textBox67 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox22 = (gcnew System::Windows::Forms::CheckBox());
			this->label57 = (gcnew System::Windows::Forms::Label());
			this->textBox68 = (gcnew System::Windows::Forms::TextBox());
			this->label58 = (gcnew System::Windows::Forms::Label());
			this->textBox69 = (gcnew System::Windows::Forms::TextBox());
			this->textBox70 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox23 = (gcnew System::Windows::Forms::CheckBox());
			this->label59 = (gcnew System::Windows::Forms::Label());
			this->textBox71 = (gcnew System::Windows::Forms::TextBox());
			this->label60 = (gcnew System::Windows::Forms::Label());
			this->textBox72 = (gcnew System::Windows::Forms::TextBox());
			this->textBox73 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox24 = (gcnew System::Windows::Forms::CheckBox());
			this->label61 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(16, 528);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(384, 208);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->textBox4);
			this->groupBox1->Controls->Add(this->label11);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->comboBox1);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Location = System::Drawing::Point(16, 88);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(816, 88);
			this->groupBox1->TabIndex = 6;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"X axis";
			this->groupBox1->Enter += gcnew System::EventHandler(this, &MyForm::groupBox1_Enter);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(416, 40);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(12, 12);
			this->label1->TabIndex = 3;
			this->label1->Text = L"X";
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(16, 48);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(48, 20);
			this->comboBox1->TabIndex = 4;
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
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->comboBox19);
			this->groupBox2->Controls->Add(this->button17);
			this->groupBox2->Controls->Add(this->comboBox20);
			this->groupBox2->Controls->Add(this->button18);
			this->groupBox2->Controls->Add(this->comboBox21);
			this->groupBox2->Controls->Add(this->button19);
			this->groupBox2->Controls->Add(this->comboBox22);
			this->groupBox2->Controls->Add(this->button20);
			this->groupBox2->Controls->Add(this->comboBox23);
			this->groupBox2->Controls->Add(this->button21);
			this->groupBox2->Controls->Add(this->comboBox24);
			this->groupBox2->Controls->Add(this->button22);
			this->groupBox2->Controls->Add(this->comboBox25);
			this->groupBox2->Controls->Add(this->button23);
			this->groupBox2->Controls->Add(this->comboBox26);
			this->groupBox2->Controls->Add(this->button24);
			this->groupBox2->Controls->Add(this->textBox50);
			this->groupBox2->Controls->Add(this->label46);
			this->groupBox2->Controls->Add(this->textBox51);
			this->groupBox2->Controls->Add(this->textBox52);
			this->groupBox2->Controls->Add(this->checkBox17);
			this->groupBox2->Controls->Add(this->label47);
			this->groupBox2->Controls->Add(this->textBox53);
			this->groupBox2->Controls->Add(this->label48);
			this->groupBox2->Controls->Add(this->textBox54);
			this->groupBox2->Controls->Add(this->textBox55);
			this->groupBox2->Controls->Add(this->checkBox18);
			this->groupBox2->Controls->Add(this->label49);
			this->groupBox2->Controls->Add(this->textBox56);
			this->groupBox2->Controls->Add(this->label50);
			this->groupBox2->Controls->Add(this->textBox57);
			this->groupBox2->Controls->Add(this->textBox58);
			this->groupBox2->Controls->Add(this->checkBox19);
			this->groupBox2->Controls->Add(this->label51);
			this->groupBox2->Controls->Add(this->textBox59);
			this->groupBox2->Controls->Add(this->label52);
			this->groupBox2->Controls->Add(this->textBox60);
			this->groupBox2->Controls->Add(this->textBox61);
			this->groupBox2->Controls->Add(this->checkBox20);
			this->groupBox2->Controls->Add(this->label53);
			this->groupBox2->Controls->Add(this->textBox62);
			this->groupBox2->Controls->Add(this->label54);
			this->groupBox2->Controls->Add(this->textBox63);
			this->groupBox2->Controls->Add(this->textBox64);
			this->groupBox2->Controls->Add(this->checkBox21);
			this->groupBox2->Controls->Add(this->label55);
			this->groupBox2->Controls->Add(this->textBox65);
			this->groupBox2->Controls->Add(this->label56);
			this->groupBox2->Controls->Add(this->textBox66);
			this->groupBox2->Controls->Add(this->textBox67);
			this->groupBox2->Controls->Add(this->checkBox22);
			this->groupBox2->Controls->Add(this->label57);
			this->groupBox2->Controls->Add(this->textBox68);
			this->groupBox2->Controls->Add(this->label58);
			this->groupBox2->Controls->Add(this->textBox69);
			this->groupBox2->Controls->Add(this->textBox70);
			this->groupBox2->Controls->Add(this->checkBox23);
			this->groupBox2->Controls->Add(this->label59);
			this->groupBox2->Controls->Add(this->textBox71);
			this->groupBox2->Controls->Add(this->label60);
			this->groupBox2->Controls->Add(this->textBox72);
			this->groupBox2->Controls->Add(this->textBox73);
			this->groupBox2->Controls->Add(this->checkBox24);
			this->groupBox2->Controls->Add(this->label61);
			this->groupBox2->Controls->Add(this->comboBox2);
			this->groupBox2->Controls->Add(this->button1);
			this->groupBox2->Controls->Add(this->comboBox4);
			this->groupBox2->Controls->Add(this->button2);
			this->groupBox2->Controls->Add(this->comboBox5);
			this->groupBox2->Controls->Add(this->button3);
			this->groupBox2->Controls->Add(this->comboBox6);
			this->groupBox2->Controls->Add(this->button4);
			this->groupBox2->Controls->Add(this->comboBox7);
			this->groupBox2->Controls->Add(this->button5);
			this->groupBox2->Controls->Add(this->comboBox8);
			this->groupBox2->Controls->Add(this->button6);
			this->groupBox2->Controls->Add(this->comboBox9);
			this->groupBox2->Controls->Add(this->button7);
			this->groupBox2->Controls->Add(this->label8);
			this->groupBox2->Controls->Add(this->comboBox10);
			this->groupBox2->Controls->Add(this->label10);
			this->groupBox2->Controls->Add(this->button8);
			this->groupBox2->Controls->Add(this->comboBox11);
			this->groupBox2->Controls->Add(this->button9);
			this->groupBox2->Controls->Add(this->comboBox12);
			this->groupBox2->Controls->Add(this->button10);
			this->groupBox2->Controls->Add(this->comboBox13);
			this->groupBox2->Controls->Add(this->button11);
			this->groupBox2->Controls->Add(this->comboBox14);
			this->groupBox2->Controls->Add(this->button12);
			this->groupBox2->Controls->Add(this->comboBox15);
			this->groupBox2->Controls->Add(this->button13);
			this->groupBox2->Controls->Add(this->comboBox16);
			this->groupBox2->Controls->Add(this->button14);
			this->groupBox2->Controls->Add(this->comboBox17);
			this->groupBox2->Controls->Add(this->button15);
			this->groupBox2->Controls->Add(this->label39);
			this->groupBox2->Controls->Add(this->comboBox18);
			this->groupBox2->Controls->Add(this->label40);
			this->groupBox2->Controls->Add(this->button16);
			this->groupBox2->Controls->Add(this->textBox26);
			this->groupBox2->Controls->Add(this->label25);
			this->groupBox2->Controls->Add(this->textBox27);
			this->groupBox2->Controls->Add(this->textBox28);
			this->groupBox2->Controls->Add(this->checkBox9);
			this->groupBox2->Controls->Add(this->label26);
			this->groupBox2->Controls->Add(this->textBox29);
			this->groupBox2->Controls->Add(this->label27);
			this->groupBox2->Controls->Add(this->textBox30);
			this->groupBox2->Controls->Add(this->textBox31);
			this->groupBox2->Controls->Add(this->checkBox10);
			this->groupBox2->Controls->Add(this->label28);
			this->groupBox2->Controls->Add(this->textBox32);
			this->groupBox2->Controls->Add(this->label29);
			this->groupBox2->Controls->Add(this->textBox33);
			this->groupBox2->Controls->Add(this->textBox34);
			this->groupBox2->Controls->Add(this->checkBox11);
			this->groupBox2->Controls->Add(this->label30);
			this->groupBox2->Controls->Add(this->textBox35);
			this->groupBox2->Controls->Add(this->label31);
			this->groupBox2->Controls->Add(this->textBox36);
			this->groupBox2->Controls->Add(this->textBox37);
			this->groupBox2->Controls->Add(this->checkBox12);
			this->groupBox2->Controls->Add(this->label32);
			this->groupBox2->Controls->Add(this->textBox38);
			this->groupBox2->Controls->Add(this->label33);
			this->groupBox2->Controls->Add(this->textBox39);
			this->groupBox2->Controls->Add(this->textBox40);
			this->groupBox2->Controls->Add(this->checkBox13);
			this->groupBox2->Controls->Add(this->label34);
			this->groupBox2->Controls->Add(this->textBox41);
			this->groupBox2->Controls->Add(this->label35);
			this->groupBox2->Controls->Add(this->textBox42);
			this->groupBox2->Controls->Add(this->textBox43);
			this->groupBox2->Controls->Add(this->checkBox14);
			this->groupBox2->Controls->Add(this->label36);
			this->groupBox2->Controls->Add(this->textBox44);
			this->groupBox2->Controls->Add(this->label37);
			this->groupBox2->Controls->Add(this->textBox45);
			this->groupBox2->Controls->Add(this->textBox46);
			this->groupBox2->Controls->Add(this->checkBox15);
			this->groupBox2->Controls->Add(this->label38);
			this->groupBox2->Controls->Add(this->textBox47);
			this->groupBox2->Controls->Add(this->label41);
			this->groupBox2->Controls->Add(this->textBox48);
			this->groupBox2->Controls->Add(this->label42);
			this->groupBox2->Controls->Add(this->textBox49);
			this->groupBox2->Controls->Add(this->label43);
			this->groupBox2->Controls->Add(this->checkBox16);
			this->groupBox2->Controls->Add(this->label44);
			this->groupBox2->Controls->Add(this->label45);
			this->groupBox2->Controls->Add(this->textBox14);
			this->groupBox2->Controls->Add(this->label17);
			this->groupBox2->Controls->Add(this->textBox15);
			this->groupBox2->Controls->Add(this->textBox16);
			this->groupBox2->Controls->Add(this->checkBox5);
			this->groupBox2->Controls->Add(this->label18);
			this->groupBox2->Controls->Add(this->textBox17);
			this->groupBox2->Controls->Add(this->label19);
			this->groupBox2->Controls->Add(this->textBox18);
			this->groupBox2->Controls->Add(this->textBox19);
			this->groupBox2->Controls->Add(this->checkBox6);
			this->groupBox2->Controls->Add(this->label20);
			this->groupBox2->Controls->Add(this->textBox20);
			this->groupBox2->Controls->Add(this->label21);
			this->groupBox2->Controls->Add(this->textBox21);
			this->groupBox2->Controls->Add(this->textBox22);
			this->groupBox2->Controls->Add(this->checkBox7);
			this->groupBox2->Controls->Add(this->label22);
			this->groupBox2->Controls->Add(this->textBox23);
			this->groupBox2->Controls->Add(this->label23);
			this->groupBox2->Controls->Add(this->textBox24);
			this->groupBox2->Controls->Add(this->textBox25);
			this->groupBox2->Controls->Add(this->checkBox8);
			this->groupBox2->Controls->Add(this->label24);
			this->groupBox2->Controls->Add(this->textBox8);
			this->groupBox2->Controls->Add(this->label13);
			this->groupBox2->Controls->Add(this->textBox9);
			this->groupBox2->Controls->Add(this->textBox10);
			this->groupBox2->Controls->Add(this->checkBox3);
			this->groupBox2->Controls->Add(this->label14);
			this->groupBox2->Controls->Add(this->textBox11);
			this->groupBox2->Controls->Add(this->label15);
			this->groupBox2->Controls->Add(this->textBox12);
			this->groupBox2->Controls->Add(this->textBox13);
			this->groupBox2->Controls->Add(this->checkBox4);
			this->groupBox2->Controls->Add(this->label16);
			this->groupBox2->Controls->Add(this->textBox5);
			this->groupBox2->Controls->Add(this->label9);
			this->groupBox2->Controls->Add(this->textBox6);
			this->groupBox2->Controls->Add(this->textBox7);
			this->groupBox2->Controls->Add(this->checkBox2);
			this->groupBox2->Controls->Add(this->label12);
			this->groupBox2->Controls->Add(this->textBox3);
			this->groupBox2->Controls->Add(this->label7);
			this->groupBox2->Controls->Add(this->textBox2);
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Controls->Add(this->textBox1);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Controls->Add(this->checkBox1);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Location = System::Drawing::Point(16, 176);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(816, 336);
			this->groupBox2->TabIndex = 7;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Y axis";
			this->groupBox2->Enter += gcnew System::EventHandler(this, &MyForm::groupBox2_Enter);
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
			// comboBox3
			// 
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Location = System::Drawing::Point(496, 552);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(121, 20);
			this->comboBox3->TabIndex = 4;
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
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(16, 48);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(46, 16);
			this->checkBox1->TabIndex = 7;
			this->checkBox1->Text = L"CH1";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox1_CheckedChanged_1);
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
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(160, 48);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(120, 19);
			this->textBox1->TabIndex = 9;
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
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(72, 48);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(120, 19);
			this->textBox4->TabIndex = 20;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(72, 24);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(60, 12);
			this->label11->TabIndex = 19;
			this->label11->Text = L"label name";
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
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(160, 72);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(120, 19);
			this->textBox7->TabIndex = 21;
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(16, 72);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(46, 16);
			this->checkBox2->TabIndex = 20;
			this->checkBox2->Text = L"CH1";
			this->checkBox2->UseVisualStyleBackColor = true;
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
			// textBox10
			// 
			this->textBox10->Location = System::Drawing::Point(160, 120);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(120, 19);
			this->textBox10->TabIndex = 37;
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(16, 120);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(46, 16);
			this->checkBox3->TabIndex = 36;
			this->checkBox3->Text = L"CH1";
			this->checkBox3->UseVisualStyleBackColor = true;
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
			// textBox13
			// 
			this->textBox13->Location = System::Drawing::Point(160, 96);
			this->textBox13->Name = L"textBox13";
			this->textBox13->Size = System::Drawing::Size(120, 19);
			this->textBox13->TabIndex = 29;
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Location = System::Drawing::Point(16, 96);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(46, 16);
			this->checkBox4->TabIndex = 28;
			this->checkBox4->Text = L"CH1";
			this->checkBox4->UseVisualStyleBackColor = true;
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
			// textBox16
			// 
			this->textBox16->Location = System::Drawing::Point(160, 216);
			this->textBox16->Name = L"textBox16";
			this->textBox16->Size = System::Drawing::Size(120, 19);
			this->textBox16->TabIndex = 69;
			// 
			// checkBox5
			// 
			this->checkBox5->AutoSize = true;
			this->checkBox5->Location = System::Drawing::Point(16, 216);
			this->checkBox5->Name = L"checkBox5";
			this->checkBox5->Size = System::Drawing::Size(52, 16);
			this->checkBox5->TabIndex = 68;
			this->checkBox5->Text = L"CH12";
			this->checkBox5->UseVisualStyleBackColor = true;
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
			// textBox19
			// 
			this->textBox19->Location = System::Drawing::Point(160, 192);
			this->textBox19->Name = L"textBox19";
			this->textBox19->Size = System::Drawing::Size(120, 19);
			this->textBox19->TabIndex = 61;
			// 
			// checkBox6
			// 
			this->checkBox6->AutoSize = true;
			this->checkBox6->Location = System::Drawing::Point(16, 192);
			this->checkBox6->Name = L"checkBox6";
			this->checkBox6->Size = System::Drawing::Size(46, 16);
			this->checkBox6->TabIndex = 60;
			this->checkBox6->Text = L"CH1";
			this->checkBox6->UseVisualStyleBackColor = true;
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
			// textBox22
			// 
			this->textBox22->Location = System::Drawing::Point(160, 168);
			this->textBox22->Name = L"textBox22";
			this->textBox22->Size = System::Drawing::Size(120, 19);
			this->textBox22->TabIndex = 53;
			// 
			// checkBox7
			// 
			this->checkBox7->AutoSize = true;
			this->checkBox7->Location = System::Drawing::Point(16, 168);
			this->checkBox7->Name = L"checkBox7";
			this->checkBox7->Size = System::Drawing::Size(46, 16);
			this->checkBox7->TabIndex = 52;
			this->checkBox7->Text = L"CH1";
			this->checkBox7->UseVisualStyleBackColor = true;
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
			// textBox25
			// 
			this->textBox25->Location = System::Drawing::Point(160, 144);
			this->textBox25->Name = L"textBox25";
			this->textBox25->Size = System::Drawing::Size(120, 19);
			this->textBox25->TabIndex = 45;
			// 
			// checkBox8
			// 
			this->checkBox8->AutoSize = true;
			this->checkBox8->Location = System::Drawing::Point(16, 144);
			this->checkBox8->Name = L"checkBox8";
			this->checkBox8->Size = System::Drawing::Size(46, 16);
			this->checkBox8->TabIndex = 44;
			this->checkBox8->Text = L"CH1";
			this->checkBox8->UseVisualStyleBackColor = true;
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
			// textBox28
			// 
			this->textBox28->Location = System::Drawing::Point(568, 216);
			this->textBox28->Name = L"textBox28";
			this->textBox28->Size = System::Drawing::Size(120, 19);
			this->textBox28->TabIndex = 138;
			// 
			// checkBox9
			// 
			this->checkBox9->AutoSize = true;
			this->checkBox9->Location = System::Drawing::Point(424, 216);
			this->checkBox9->Name = L"checkBox9";
			this->checkBox9->Size = System::Drawing::Size(46, 16);
			this->checkBox9->TabIndex = 137;
			this->checkBox9->Text = L"CH1";
			this->checkBox9->UseVisualStyleBackColor = true;
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
			// textBox31
			// 
			this->textBox31->Location = System::Drawing::Point(568, 192);
			this->textBox31->Name = L"textBox31";
			this->textBox31->Size = System::Drawing::Size(120, 19);
			this->textBox31->TabIndex = 130;
			// 
			// checkBox10
			// 
			this->checkBox10->AutoSize = true;
			this->checkBox10->Location = System::Drawing::Point(424, 192);
			this->checkBox10->Name = L"checkBox10";
			this->checkBox10->Size = System::Drawing::Size(46, 16);
			this->checkBox10->TabIndex = 129;
			this->checkBox10->Text = L"CH1";
			this->checkBox10->UseVisualStyleBackColor = true;
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
			// textBox34
			// 
			this->textBox34->Location = System::Drawing::Point(568, 168);
			this->textBox34->Name = L"textBox34";
			this->textBox34->Size = System::Drawing::Size(120, 19);
			this->textBox34->TabIndex = 122;
			// 
			// checkBox11
			// 
			this->checkBox11->AutoSize = true;
			this->checkBox11->Location = System::Drawing::Point(424, 168);
			this->checkBox11->Name = L"checkBox11";
			this->checkBox11->Size = System::Drawing::Size(46, 16);
			this->checkBox11->TabIndex = 121;
			this->checkBox11->Text = L"CH1";
			this->checkBox11->UseVisualStyleBackColor = true;
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
			// textBox37
			// 
			this->textBox37->Location = System::Drawing::Point(568, 144);
			this->textBox37->Name = L"textBox37";
			this->textBox37->Size = System::Drawing::Size(120, 19);
			this->textBox37->TabIndex = 114;
			// 
			// checkBox12
			// 
			this->checkBox12->AutoSize = true;
			this->checkBox12->Location = System::Drawing::Point(424, 144);
			this->checkBox12->Name = L"checkBox12";
			this->checkBox12->Size = System::Drawing::Size(46, 16);
			this->checkBox12->TabIndex = 113;
			this->checkBox12->Text = L"CH1";
			this->checkBox12->UseVisualStyleBackColor = true;
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
			// textBox40
			// 
			this->textBox40->Location = System::Drawing::Point(568, 120);
			this->textBox40->Name = L"textBox40";
			this->textBox40->Size = System::Drawing::Size(120, 19);
			this->textBox40->TabIndex = 106;
			// 
			// checkBox13
			// 
			this->checkBox13->AutoSize = true;
			this->checkBox13->Location = System::Drawing::Point(424, 120);
			this->checkBox13->Name = L"checkBox13";
			this->checkBox13->Size = System::Drawing::Size(46, 16);
			this->checkBox13->TabIndex = 105;
			this->checkBox13->Text = L"CH1";
			this->checkBox13->UseVisualStyleBackColor = true;
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
			// textBox43
			// 
			this->textBox43->Location = System::Drawing::Point(568, 96);
			this->textBox43->Name = L"textBox43";
			this->textBox43->Size = System::Drawing::Size(120, 19);
			this->textBox43->TabIndex = 98;
			// 
			// checkBox14
			// 
			this->checkBox14->AutoSize = true;
			this->checkBox14->Location = System::Drawing::Point(424, 96);
			this->checkBox14->Name = L"checkBox14";
			this->checkBox14->Size = System::Drawing::Size(46, 16);
			this->checkBox14->TabIndex = 97;
			this->checkBox14->Text = L"CH1";
			this->checkBox14->UseVisualStyleBackColor = true;
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
			// textBox46
			// 
			this->textBox46->Location = System::Drawing::Point(568, 72);
			this->textBox46->Name = L"textBox46";
			this->textBox46->Size = System::Drawing::Size(120, 19);
			this->textBox46->TabIndex = 90;
			// 
			// checkBox15
			// 
			this->checkBox15->AutoSize = true;
			this->checkBox15->Location = System::Drawing::Point(424, 72);
			this->checkBox15->Name = L"checkBox15";
			this->checkBox15->Size = System::Drawing::Size(46, 16);
			this->checkBox15->TabIndex = 89;
			this->checkBox15->Text = L"CH1";
			this->checkBox15->UseVisualStyleBackColor = true;
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
			// textBox49
			// 
			this->textBox49->Location = System::Drawing::Point(568, 48);
			this->textBox49->Name = L"textBox49";
			this->textBox49->Size = System::Drawing::Size(120, 19);
			this->textBox49->TabIndex = 79;
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
			// checkBox16
			// 
			this->checkBox16->AutoSize = true;
			this->checkBox16->Location = System::Drawing::Point(424, 48);
			this->checkBox16->Name = L"checkBox16";
			this->checkBox16->Size = System::Drawing::Size(46, 16);
			this->checkBox16->TabIndex = 78;
			this->checkBox16->Text = L"CH1";
			this->checkBox16->UseVisualStyleBackColor = true;
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
			// comboBox11
			// 
			this->comboBox11->FormattingEnabled = true;
			this->comboBox11->Location = System::Drawing::Point(480, 216);
			this->comboBox11->Name = L"comboBox11";
			this->comboBox11->Size = System::Drawing::Size(40, 20);
			this->comboBox11->TabIndex = 161;
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
			// comboBox12
			// 
			this->comboBox12->FormattingEnabled = true;
			this->comboBox12->Location = System::Drawing::Point(480, 192);
			this->comboBox12->Name = L"comboBox12";
			this->comboBox12->Size = System::Drawing::Size(40, 20);
			this->comboBox12->TabIndex = 159;
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
			// comboBox13
			// 
			this->comboBox13->FormattingEnabled = true;
			this->comboBox13->Location = System::Drawing::Point(480, 168);
			this->comboBox13->Name = L"comboBox13";
			this->comboBox13->Size = System::Drawing::Size(40, 20);
			this->comboBox13->TabIndex = 157;
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
			// comboBox14
			// 
			this->comboBox14->FormattingEnabled = true;
			this->comboBox14->Location = System::Drawing::Point(480, 144);
			this->comboBox14->Name = L"comboBox14";
			this->comboBox14->Size = System::Drawing::Size(40, 20);
			this->comboBox14->TabIndex = 155;
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
			// comboBox15
			// 
			this->comboBox15->FormattingEnabled = true;
			this->comboBox15->Location = System::Drawing::Point(480, 120);
			this->comboBox15->Name = L"comboBox15";
			this->comboBox15->Size = System::Drawing::Size(40, 20);
			this->comboBox15->TabIndex = 153;
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
			// comboBox16
			// 
			this->comboBox16->FormattingEnabled = true;
			this->comboBox16->Location = System::Drawing::Point(480, 96);
			this->comboBox16->Name = L"comboBox16";
			this->comboBox16->Size = System::Drawing::Size(40, 20);
			this->comboBox16->TabIndex = 151;
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
			// comboBox17
			// 
			this->comboBox17->FormattingEnabled = true;
			this->comboBox17->Location = System::Drawing::Point(480, 72);
			this->comboBox17->Name = L"comboBox17";
			this->comboBox17->Size = System::Drawing::Size(40, 20);
			this->comboBox17->TabIndex = 149;
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
			this->label39->Size = System::Drawing::Size(44, 12);
			this->label39->TabIndex = 147;
			this->label39->Text = L"figure #";
			// 
			// comboBox18
			// 
			this->comboBox18->FormattingEnabled = true;
			this->comboBox18->Location = System::Drawing::Point(480, 48);
			this->comboBox18->Name = L"comboBox18";
			this->comboBox18->Size = System::Drawing::Size(40, 20);
			this->comboBox18->TabIndex = 146;
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
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Location = System::Drawing::Point(72, 216);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(40, 20);
			this->comboBox2->TabIndex = 179;
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
			// comboBox4
			// 
			this->comboBox4->FormattingEnabled = true;
			this->comboBox4->Location = System::Drawing::Point(72, 192);
			this->comboBox4->Name = L"comboBox4";
			this->comboBox4->Size = System::Drawing::Size(40, 20);
			this->comboBox4->TabIndex = 177;
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
			// comboBox5
			// 
			this->comboBox5->FormattingEnabled = true;
			this->comboBox5->Location = System::Drawing::Point(72, 168);
			this->comboBox5->Name = L"comboBox5";
			this->comboBox5->Size = System::Drawing::Size(40, 20);
			this->comboBox5->TabIndex = 175;
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
			// comboBox6
			// 
			this->comboBox6->FormattingEnabled = true;
			this->comboBox6->Location = System::Drawing::Point(72, 144);
			this->comboBox6->Name = L"comboBox6";
			this->comboBox6->Size = System::Drawing::Size(40, 20);
			this->comboBox6->TabIndex = 173;
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
			// comboBox7
			// 
			this->comboBox7->FormattingEnabled = true;
			this->comboBox7->Location = System::Drawing::Point(72, 120);
			this->comboBox7->Name = L"comboBox7";
			this->comboBox7->Size = System::Drawing::Size(40, 20);
			this->comboBox7->TabIndex = 171;
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
			// comboBox8
			// 
			this->comboBox8->FormattingEnabled = true;
			this->comboBox8->Location = System::Drawing::Point(72, 96);
			this->comboBox8->Name = L"comboBox8";
			this->comboBox8->Size = System::Drawing::Size(40, 20);
			this->comboBox8->TabIndex = 169;
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
			// comboBox9
			// 
			this->comboBox9->FormattingEnabled = true;
			this->comboBox9->Location = System::Drawing::Point(72, 72);
			this->comboBox9->Name = L"comboBox9";
			this->comboBox9->Size = System::Drawing::Size(40, 20);
			this->comboBox9->TabIndex = 167;
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
			this->label8->Size = System::Drawing::Size(44, 12);
			this->label8->TabIndex = 165;
			this->label8->Text = L"figure #";
			// 
			// comboBox10
			// 
			this->comboBox10->FormattingEnabled = true;
			this->comboBox10->Location = System::Drawing::Point(72, 48);
			this->comboBox10->Name = L"comboBox10";
			this->comboBox10->Size = System::Drawing::Size(40, 20);
			this->comboBox10->TabIndex = 164;
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
			// button8
			// 
			this->button8->ForeColor = System::Drawing::Color::Red;
			this->button8->Location = System::Drawing::Point(120, 48);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(24, 23);
			this->button8->TabIndex = 162;
			this->button8->Text = L"■";
			this->button8->UseVisualStyleBackColor = true;
			// 
			// comboBox19
			// 
			this->comboBox19->FormattingEnabled = true;
			this->comboBox19->Location = System::Drawing::Point(72, 312);
			this->comboBox19->Name = L"comboBox19";
			this->comboBox19->Size = System::Drawing::Size(40, 20);
			this->comboBox19->TabIndex = 243;
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
			// comboBox20
			// 
			this->comboBox20->FormattingEnabled = true;
			this->comboBox20->Location = System::Drawing::Point(72, 288);
			this->comboBox20->Name = L"comboBox20";
			this->comboBox20->Size = System::Drawing::Size(40, 20);
			this->comboBox20->TabIndex = 241;
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
			// comboBox21
			// 
			this->comboBox21->FormattingEnabled = true;
			this->comboBox21->Location = System::Drawing::Point(72, 264);
			this->comboBox21->Name = L"comboBox21";
			this->comboBox21->Size = System::Drawing::Size(40, 20);
			this->comboBox21->TabIndex = 239;
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
			// comboBox22
			// 
			this->comboBox22->FormattingEnabled = true;
			this->comboBox22->Location = System::Drawing::Point(72, 240);
			this->comboBox22->Name = L"comboBox22";
			this->comboBox22->Size = System::Drawing::Size(40, 20);
			this->comboBox22->TabIndex = 237;
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
			// comboBox23
			// 
			this->comboBox23->FormattingEnabled = true;
			this->comboBox23->Location = System::Drawing::Point(480, 312);
			this->comboBox23->Name = L"comboBox23";
			this->comboBox23->Size = System::Drawing::Size(40, 20);
			this->comboBox23->TabIndex = 235;
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
			// comboBox24
			// 
			this->comboBox24->FormattingEnabled = true;
			this->comboBox24->Location = System::Drawing::Point(480, 288);
			this->comboBox24->Name = L"comboBox24";
			this->comboBox24->Size = System::Drawing::Size(40, 20);
			this->comboBox24->TabIndex = 233;
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
			// comboBox25
			// 
			this->comboBox25->FormattingEnabled = true;
			this->comboBox25->Location = System::Drawing::Point(480, 264);
			this->comboBox25->Name = L"comboBox25";
			this->comboBox25->Size = System::Drawing::Size(40, 20);
			this->comboBox25->TabIndex = 231;
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
			// comboBox26
			// 
			this->comboBox26->FormattingEnabled = true;
			this->comboBox26->Location = System::Drawing::Point(480, 240);
			this->comboBox26->Name = L"comboBox26";
			this->comboBox26->Size = System::Drawing::Size(40, 20);
			this->comboBox26->TabIndex = 229;
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
			// textBox52
			// 
			this->textBox52->Location = System::Drawing::Point(568, 312);
			this->textBox52->Name = L"textBox52";
			this->textBox52->Size = System::Drawing::Size(120, 19);
			this->textBox52->TabIndex = 224;
			// 
			// checkBox17
			// 
			this->checkBox17->AutoSize = true;
			this->checkBox17->Location = System::Drawing::Point(424, 312);
			this->checkBox17->Name = L"checkBox17";
			this->checkBox17->Size = System::Drawing::Size(46, 16);
			this->checkBox17->TabIndex = 223;
			this->checkBox17->Text = L"CH1";
			this->checkBox17->UseVisualStyleBackColor = true;
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
			// textBox55
			// 
			this->textBox55->Location = System::Drawing::Point(568, 288);
			this->textBox55->Name = L"textBox55";
			this->textBox55->Size = System::Drawing::Size(120, 19);
			this->textBox55->TabIndex = 218;
			// 
			// checkBox18
			// 
			this->checkBox18->AutoSize = true;
			this->checkBox18->Location = System::Drawing::Point(424, 288);
			this->checkBox18->Name = L"checkBox18";
			this->checkBox18->Size = System::Drawing::Size(46, 16);
			this->checkBox18->TabIndex = 217;
			this->checkBox18->Text = L"CH1";
			this->checkBox18->UseVisualStyleBackColor = true;
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
			// textBox58
			// 
			this->textBox58->Location = System::Drawing::Point(568, 264);
			this->textBox58->Name = L"textBox58";
			this->textBox58->Size = System::Drawing::Size(120, 19);
			this->textBox58->TabIndex = 212;
			// 
			// checkBox19
			// 
			this->checkBox19->AutoSize = true;
			this->checkBox19->Location = System::Drawing::Point(424, 264);
			this->checkBox19->Name = L"checkBox19";
			this->checkBox19->Size = System::Drawing::Size(46, 16);
			this->checkBox19->TabIndex = 211;
			this->checkBox19->Text = L"CH1";
			this->checkBox19->UseVisualStyleBackColor = true;
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
			// textBox61
			// 
			this->textBox61->Location = System::Drawing::Point(568, 240);
			this->textBox61->Name = L"textBox61";
			this->textBox61->Size = System::Drawing::Size(120, 19);
			this->textBox61->TabIndex = 206;
			// 
			// checkBox20
			// 
			this->checkBox20->AutoSize = true;
			this->checkBox20->Location = System::Drawing::Point(424, 240);
			this->checkBox20->Name = L"checkBox20";
			this->checkBox20->Size = System::Drawing::Size(46, 16);
			this->checkBox20->TabIndex = 205;
			this->checkBox20->Text = L"CH1";
			this->checkBox20->UseVisualStyleBackColor = true;
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
			// textBox64
			// 
			this->textBox64->Location = System::Drawing::Point(160, 312);
			this->textBox64->Name = L"textBox64";
			this->textBox64->Size = System::Drawing::Size(120, 19);
			this->textBox64->TabIndex = 200;
			// 
			// checkBox21
			// 
			this->checkBox21->AutoSize = true;
			this->checkBox21->Location = System::Drawing::Point(16, 312);
			this->checkBox21->Name = L"checkBox21";
			this->checkBox21->Size = System::Drawing::Size(52, 16);
			this->checkBox21->TabIndex = 199;
			this->checkBox21->Text = L"CH12";
			this->checkBox21->UseVisualStyleBackColor = true;
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
			// textBox67
			// 
			this->textBox67->Location = System::Drawing::Point(160, 288);
			this->textBox67->Name = L"textBox67";
			this->textBox67->Size = System::Drawing::Size(120, 19);
			this->textBox67->TabIndex = 194;
			// 
			// checkBox22
			// 
			this->checkBox22->AutoSize = true;
			this->checkBox22->Location = System::Drawing::Point(16, 288);
			this->checkBox22->Name = L"checkBox22";
			this->checkBox22->Size = System::Drawing::Size(46, 16);
			this->checkBox22->TabIndex = 193;
			this->checkBox22->Text = L"CH1";
			this->checkBox22->UseVisualStyleBackColor = true;
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
			// textBox70
			// 
			this->textBox70->Location = System::Drawing::Point(160, 264);
			this->textBox70->Name = L"textBox70";
			this->textBox70->Size = System::Drawing::Size(120, 19);
			this->textBox70->TabIndex = 188;
			// 
			// checkBox23
			// 
			this->checkBox23->AutoSize = true;
			this->checkBox23->Location = System::Drawing::Point(16, 264);
			this->checkBox23->Name = L"checkBox23";
			this->checkBox23->Size = System::Drawing::Size(46, 16);
			this->checkBox23->TabIndex = 187;
			this->checkBox23->Text = L"CH1";
			this->checkBox23->UseVisualStyleBackColor = true;
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
			// textBox73
			// 
			this->textBox73->Location = System::Drawing::Point(160, 240);
			this->textBox73->Name = L"textBox73";
			this->textBox73->Size = System::Drawing::Size(120, 19);
			this->textBox73->TabIndex = 182;
			// 
			// checkBox24
			// 
			this->checkBox24->AutoSize = true;
			this->checkBox24->Location = System::Drawing::Point(16, 240);
			this->checkBox24->Name = L"checkBox24";
			this->checkBox24->Size = System::Drawing::Size(46, 16);
			this->checkBox24->TabIndex = 181;
			this->checkBox24->Text = L"CH1";
			this->checkBox24->UseVisualStyleBackColor = true;
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
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(841, 583);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->comboBox3);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

private: System::Void groupBox1_Enter(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void checkBox1_CheckedChanged_1(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void groupBox2_Enter(System::Object^  sender, System::EventArgs^  e) {
}
};
}
