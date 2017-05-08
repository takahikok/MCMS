#include "SetupADCConnection.h"
#include "SetupADCMeasurement.h"
#include "SetupAnalyzeSP.h"
#include "SetupPlot.h"
#include "tkadc.h"
#include "tkadcinfo.h"
#include "tkshotinfo.h"
#include "tkplot.h"
#include "tkshotno.h"
#include <iostream>
#include <string>
#include <sstream>
#include "clx/base64.h"
#include "clx/ini.h"
#include "clx/ftp.h"
#include <iomanip>
#include <fstream>
#include <vector>
#include "clx/thread.h"
#include "tkthread.h"
#include "tkanalyzesp.h"
#include "tkanalyzeisp.h"
#pragma once
#define SETTING_FILE_PATH "settings.ini"

//std::string data_file_name = "ECR00039";
#define data_file_name (std::string)"ECR00039"
#define data_file_name2 (std::string)"DTB00200"

#define MAX_PLOT_NUMBER 30

namespace Project1
{

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

		TKADCCONTROL_DL750* DL750;
		TKADCCONTROL_DL850* DL850;
		TKSHOT* thisShot;
		TKPLOT* thisPlot;
		TKANALYZESP* thisAnalyzeSP;
		TKANALYZEISP* thisAnalyzeISP;
		int picture_box_total_number = MAX_PLOT_NUMBER;

	private: System::Windows::Forms::ToolStripMenuItem^  計測停止ToolStripMenuItem;
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
	private: System::Windows::Forms::ToolStripMenuItem^  グラフToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  グラフ描画ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  グラフ設定ToolStripMenuItem;
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
		array<System::Windows::Forms::PictureBox^>^ pBPlot2 = gcnew array<System::Windows::Forms::PictureBox^>(MAX_PLOT_NUMBER);
		array<System::Windows::Forms::PictureBox^>^ pBPlot3 = gcnew array<System::Windows::Forms::PictureBox^>(MAX_PLOT_NUMBER);
	private: System::Windows::Forms::NumericUpDown^  numericUpDown2;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Button^  button8;
		 array<System::Windows::Forms::PictureBox^>^ pBVLine = gcnew array<System::Windows::Forms::PictureBox^>(MAX_PLOT_NUMBER);
		 array<System::Windows::Forms::PictureBox^>^ pBHLine = gcnew array<System::Windows::Forms::PictureBox^>(MAX_PLOT_NUMBER);
	private: System::Windows::Forms::ToolStripTextBox^  toolStripTextBox1;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem2;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem3;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem4;
	private: System::Windows::Forms::ToolStripMenuItem^  新規ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  生データを追加ToolStripMenuItem;
	private: System::Windows::Forms::SplitContainer^  splitContainer2;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown7;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown8;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown5;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown6;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown3;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown4;
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::SplitContainer^  splitContainer3;
	private: System::Windows::Forms::Button^  button12;
	private: System::Windows::Forms::Button^  button13;
	private: System::Windows::Forms::Button^  button14;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown9;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown10;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown11;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown12;
	private: System::Windows::Forms::GroupBox^  groupBox6;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown13;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown14;













		 array<System::Windows::Forms::PictureBox^>^ pBHLineText = gcnew array<System::Windows::Forms::PictureBox^>(MAX_PLOT_NUMBER);


	private:
		void startMeasurement(Project1::MyForm^ parent);
		int Connection(bool on_startup)
		{
			int error_no;
			if (!(on_startup ^ (bool)((*Setting)["DL750"]["ConnectOnStartup"] == "Enable")))
				if ((bool)((*Setting)["DL750"]["Control"] == "Enable"))
					if (error_no = TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->Open(TM_CTL_ETHER, ((*Setting)["DL750"]["IPAddress"] + ",anonymous,").c_str()))
						goto error;
			if (!(on_startup ^ (bool)((*Setting)["DL850"]["ConnectOnStartup"] == "Enable")))
				if ((bool)((*Setting)["DL850"]["Control"] == "Enable"))
					if (error_no = TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->Open(TM_CTL_VXI11, (*Setting)["DL850"]["IPAddress"].c_str()))
						goto error;
			flushADCState("Ready");
			return 0;
		error:
			return error_no;
		}

		inline int downloadFromADC(TKADCINFO::ADCID adcid, std::string filename)
		{
			clx::ftp session((std::string)((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["IPAddress"]), 21);
			session.login((std::string)((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["UserName"].c_str()),
				(std::string)(clx::base64::decode((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["Password"].c_str())));
			session.cd((std::string)((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["StragePath"]));
			session.retrieve(filename, filename, clx::ftp::binary);
			session.finish();
			return 0;
		}
		int deleteOnADC(TKADCINFO::ADCID adcid, std::string filename)
		{
			return 0;
		}
		int uploadToStrage(std::string source, std::string destination)
		{
			clx::ftp session((std::string)((*Setting)["DataStrage"]["IPAddress"]), 21);
			session.login((std::string)((*Setting)["DataStrage"]["UserName"].c_str()),
				(std::string)(clx::base64::decode((*Setting)["DataStrage"]["Password"].c_str())));
			session.cd((std::string)((*Setting)["DataStrage"]["StragePath"]));
			session.store(source, destination, clx::ftp::binary);
			session.finish();
			return 0;
		}

		std::string makeLocalFileName(std::string prefix, int local_shot_number, int shot_number_length, std::string suffix)
		{
			std::ostringstream fname;
			fname << prefix << std::setfill('0') << std::setw(shot_number_length) << std::right << (local_shot_number) << suffix;
			return (std::string)fname.str();
		}
		inline std::string getLastLocalFileName(TKADCINFO::ADCID adcid)
		{
			return makeLocalFileName((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["LocalShotNamePrefix"],
				TKADCINFO::ADCIDToTKADCPtr(adcid)->GetLastLocalShotNumber(), 5, "");
		}
		inline std::string getNextLocalFileName(TKADCINFO::ADCID adcid)
		{
			return makeLocalFileName((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["LocalShotNamePrefix"],
				TKADCINFO::ADCIDToTKADCPtr(adcid)->GetNextLocalShotNumber(), 5, "");
		}
		void flushADCState(std::string state, System::Drawing::Color color)
		{
			this->toolStripMenuItem2->ForeColor = color;
			this->toolStripMenuItem2->Text = gcnew System::String(state.c_str());
			System::Windows::Forms::Application::DoEvents();
		}
		void flushADCState(std::string state)
		{
			this->toolStripMenuItem2->ForeColor = System::Drawing::Color::Black;
			this->toolStripMenuItem2->Text = gcnew System::String(state.c_str());
			System::Windows::Forms::Application::DoEvents();
		}
		void SetShotNumberColor(System::Drawing::Color color)
		{
			toolStripTextBox1->ForeColor = color;
		}
		void flushShotNumber(int shot_number, System::Drawing::Color color)
		{
			toolStripTextBox1->ForeColor = color;
			toolStripTextBox1->Text = gcnew System::String(("#" + TKUTIL::ZeroFill(shot_number, 8)).c_str());
		}
		void flushShotNumber(int shot_number)
		{
			toolStripTextBox1->ForeColor = System::Drawing::Color::Black;
			toolStripTextBox1->Text = gcnew System::String(("#" + TKUTIL::ZeroFill(shot_number, 8)).c_str());
		}
		void flushShotNumber()
		{
			toolStripTextBox1->ForeColor = System::Drawing::Color::Black;
			toolStripTextBox1->Text = gcnew System::String(("#" + TKUTIL::ZeroFill(TKSHOTNO::GetLastShotNumber(), 8)).c_str());
		}
		void plotRaw(unsigned int shot_number)
		{
			static int total_plot;
			for (int i = 0; i < picture_box_total_number; i++) {
				//Plot
				pBPlot[i]->Visible = false;
				delete pBPlot[i]->Image;

				//Line
				pBVLine[i]->Visible = false;
				pBHLine[i]->Visible = false;
				pBHLineText[i]->Visible = false;
			}
			thisPlot->PlotRaw(TKPLOT::PLOTSIZE::SMALL_SIZE, shot_number);
			total_plot = static_cast<int>(thisPlot->GetPlotInfo().size());
			std::vector<TKPLOT::PLOTINFO>::pointer pplot_info;
			pplot_info = thisPlot->GetPlotInfoPtr();
			for (int i = 0; i < total_plot; i++) {
				//Plot
				pBPlot[i]->Location = System::Drawing::Point((pplot_info[i].terminal_size.w + 10)*(i % 3), (pplot_info[i].terminal_size.h + 0)*(i / 3));
				pBPlot[i]->Size = System::Drawing::Size(pplot_info[i].terminal_size.w, pplot_info[i].terminal_size.h);
				try {
					pBPlot[i]->Image = dynamic_cast<Image^>(gcnew Bitmap(gcnew System::String((pplot_info[i].plot_file_name
						+ ".png").c_str())));
				}
				catch (...) {
					pBPlot[i]->Image = gcnew Bitmap(1, 1);
					MessageBox::Show("描画に失敗しました\nフィッティング範囲を変更するかフィッティングを無効にしてみてください。");
				}

				pBPlot[i]->Visible = true;
			}
			refreshVLine();
			refreshHLine();
			for (int i = 0; i < total_plot; i++) {
				//VLine
				pBVLine[i]->Visible = true;

				//HLine
				pBHLine[i]->Visible = true;
				pBHLineText[i]->Visible = true;
			}

			flushShotNumber();
		}
		void refreshVLine()
		{
			std::vector<TKPLOT::PLOTINFO>::pointer pplot_info;
			pplot_info = thisPlot->GetPlotInfoPtr();
			numericUpDown1->Maximum = 300;
			numericUpDown1->Minimum = 0;
			for (int i = 0; i < static_cast<int>(thisPlot->GetPlotInfo().size()); i++) {
				pBVLine[i]->Location = System::Drawing::Point(pBPlot[i]->Location.X + pplot_info[i].drawing_origin.x
					+ (int)(numericUpDown1->Value),
					pBPlot[i]->Location.Y
					+ pplot_info[i].terminal_size.h - (pplot_info[i].drawing_size.h + pplot_info[i].drawing_origin.y));
			}
		}
		void refreshHLine()
		{
			std::vector<TKPLOT::PLOTINFO>::pointer pplot_info;
			pplot_info = thisPlot->GetPlotInfoPtr();
			numericUpDown2->Maximum = pplot_info[0].drawing_size.h - 1;
			numericUpDown2->Minimum = 0;
			for (int i = 0; i < static_cast<int>(thisPlot->GetPlotInfo().size()); i++) {
				pBHLine[i]->Location = System::Drawing::Point(pBPlot[i]->Location.X + pplot_info[i].drawing_origin.x,
					pBPlot[i]->Location.Y
					+ pplot_info[i].terminal_size.h - (pplot_info[i].drawing_origin.y + (int)(numericUpDown2->Value))
					- 1);

				pBHLineText[i]->Image = gcnew Bitmap(pBHLineText[i]->Width, pBHLineText[i]->Height);
				//		pBHLineText[i]->BringToFront();
				//		pBHLineText[i]->Visible = false;

				Graphics^ gHT = Graphics::FromImage(pBHLineText[i]->Image);
				float vertical_position;
				float vertical_value;
				vertical_position = (float)(numericUpDown2->Value) / (pplot_info[i].drawing_size.h - 1);
				vertical_value = (float)(pplot_info[i].yrange.max - pplot_info[i].yrange.min) * vertical_position
					+ pplot_info[i].yrange.min;
				char ctext[12];
				std::sprintf(ctext, "%1.2E", vertical_value);
				String^ drawString = gcnew String(ctext);

				// Create font and brush.
				System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 11);
				SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);

				// Create point for upper-left corner of drawing.
				PointF drawPoint = PointF(150.0F, 150.0F);
				gHT->DrawString(drawString, drawFont, drawBrush, 0, 0);

				pBHLineText[i]->Location = System::Drawing::Point(pBPlot[i]->Location.X
					+ pplot_info[i].drawing_origin.x + pplot_info[i].drawing_size.w,
					pBPlot[i]->Location.Y
					+ pplot_info[i].terminal_size.h - (pplot_info[i].drawing_origin.y + (int)(numericUpDown2->Value))
					- (int)(gHT->MeasureString(drawString, drawFont).Height));
				pBHLineText[i]->Size = System::Drawing::Size((int)(gHT->MeasureString(drawString, drawFont).Width),
					(int)(gHT->MeasureString(drawString, drawFont).Height));
				pBHLine[i]->Size = System::Drawing::Size(pplot_info[i].drawing_size.w
					+ (int)(gHT->MeasureString(drawString, drawFont).Width), (int)(1));
			}

		}
		void plotSP(unsigned int shot_number)
		{
			static int total_plot;
			for (int i = 0; i < picture_box_total_number; i++) {
				//Plot
				pBPlot2[i]->Visible = false;
				delete pBPlot2[i]->Image;
			}

			const char group[] = "AnalyzeSP";

			(*Setting)[group]["FitRangeIisMin"] = std::to_string(static_cast<int>(numericUpDown4->Value));
			(*Setting)[group]["FitRangeIisMax"] = std::to_string(static_cast<int>(numericUpDown3->Value));
			(*Setting)[group]["FitRangeIeMin"] = std::to_string(static_cast<int>(numericUpDown6->Value));
			(*Setting)[group]["FitRangeIeMax"] = std::to_string(static_cast<int>(numericUpDown5->Value));
			(*Setting)[group]["FitRangeIesMin"] = std::to_string(static_cast<int>(numericUpDown8->Value));
			(*Setting)[group]["FitRangeIesMax"] = std::to_string(static_cast<int>(numericUpDown7->Value));

			//		thisAnalyzeSP->SetMASampleNumber(21);

			thisAnalyzeSP->SetRange() = TKANALYZESP::FITRANGE(
				TKPLOT::RANGE<double>(std::stod((*Setting)[group]["FitRangeIisMin"]),
					std::stod((*Setting)[group]["FitRangeIisMax"])),
				TKPLOT::RANGE<double>(std::stod((*Setting)[group]["FitRangeIeMin"]),
					std::stod((*Setting)[group]["FitRangeIeMax"])),
				TKPLOT::RANGE<double>(std::stod((*Setting)[group]["FitRangeIesMin"]),
					std::stod((*Setting)[group]["FitRangeIesMax"])));

			thisAnalyzeSP->PlotAnalyzeSP(TKPLOT::PLOTSIZE::MEDIUM_SIZE, shot_number);
			std::vector<TKPLOT::PLOTINFO>::pointer pplot_info;
			pplot_info = thisAnalyzeSP->GetPlotInfoPtr();
			for (int i = 0; i < 4; i++) {
				//Plot
				pBPlot2[i]->Location = System::Drawing::Point(pplot_info[i].terminal_size.w*(i % 2), pplot_info[i].terminal_size.h*(i / 2));
				pBPlot2[i]->Size = System::Drawing::Size(pplot_info[i].terminal_size.w, pplot_info[i].terminal_size.h);
				try {
					pBPlot2[i]->Image = dynamic_cast<Image^>(gcnew Bitmap(gcnew System::String((pplot_info[i].plot_file_name + std::to_string(i)
						+ ".png").c_str())));
				}
				catch (...) {
					pBPlot2[i]->Image = gcnew Bitmap(1, 1);
					MessageBox::Show("描画に失敗しました\nフィッティング範囲を変更するかフィッティングを無効にしてみてください。");
				}
				pBPlot2[i]->Visible = true;
			}

			flushShotNumber();
		}
		void plotISP(unsigned int shot_number)
		{
			static int total_plot;
			for (int i = 0; i < picture_box_total_number; i++) {
				//Plot
				pBPlot3[i]->Visible = false;
				delete pBPlot3[i]->Image;
			}

			const char group[] = "AnalyzeISP";

			(*Setting)[group]["FitRangeIisMin"] = std::to_string(static_cast<int>(numericUpDown14->Value));
			(*Setting)[group]["FitRangeIisMax"] = std::to_string(static_cast<int>(numericUpDown13->Value));
			(*Setting)[group]["FitRangeIeMin"] = std::to_string(static_cast<int>(numericUpDown12->Value));
			(*Setting)[group]["FitRangeIeMax"] = std::to_string(static_cast<int>(numericUpDown11->Value));
			(*Setting)[group]["FitRangeIesMin"] = std::to_string(static_cast<int>(numericUpDown10->Value));
			(*Setting)[group]["FitRangeIesMax"] = std::to_string(static_cast<int>(numericUpDown9->Value));

			//		thisAnalyzeISP->SetMASampleNumber(21);

			thisAnalyzeISP->SetRange() = TKANALYZESP::FITRANGE(
				TKPLOT::RANGE<double>(std::stod((*Setting)[group]["FitRangeIisMin"]),
					std::stod((*Setting)[group]["FitRangeIisMax"])),
				TKPLOT::RANGE<double>(std::stod((*Setting)[group]["FitRangeIeMin"]),
					std::stod((*Setting)[group]["FitRangeIeMax"])),
				TKPLOT::RANGE<double>(std::stod((*Setting)[group]["FitRangeIesMin"]),
					std::stod((*Setting)[group]["FitRangeIesMax"])));

			thisAnalyzeISP->PlotAnalyzeSP(TKPLOT::PLOTSIZE::MEDIUM_SIZE, shot_number);
			std::vector<TKPLOT::PLOTINFO>::pointer pplot_info;
			pplot_info = thisAnalyzeISP->GetPlotInfoPtr();
			for (int i = 0; i < 4; i++) {
				//Plot
				pBPlot3[i]->Location = System::Drawing::Point(pplot_info[i].terminal_size.w*(i % 2), pplot_info[i].terminal_size.h*(i / 2));
				pBPlot3[i]->Size = System::Drawing::Size(pplot_info[i].terminal_size.w, pplot_info[i].terminal_size.h);
				try {
					pBPlot3[i]->Image = dynamic_cast<Image^>(gcnew Bitmap(gcnew System::String((pplot_info[i].plot_file_name + std::to_string(i)
						+ ".png").c_str())));
				}
				catch (...) {
					pBPlot3[i]->Image = gcnew Bitmap(1, 1);
					MessageBox::Show("描画に失敗しました\nフィッティング範囲を変更するかフィッティングを無効にしてみてください。");
				}
				pBPlot3[i]->Visible = true;
			}

			flushShotNumber();
		}

	public:
		MyForm(clx::ini* Setting_, TKSHOT* thisShot_, TKPLOT* thisPlot_, TKADCCONTROL_DL750* DL750_, TKADCCONTROL_DL850* DL850_)
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

				//VLine
				pBVLine[i] = (gcnew System::Windows::Forms::PictureBox());
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBVLine[i]))->BeginInit();
				this->splitContainer1->Panel1->Controls->Add(pBVLine[i]);
				pBVLine[i]->Location = System::Drawing::Point(184, 24);
				pBVLine[i]->Margin = System::Windows::Forms::Padding(2);
				pBVLine[i]->TabStop = false;
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBVLine[i]))->EndInit();
				pBVLine[i]->Size = System::Drawing::Size(1, 130);
				Bitmap^ bmpPicBox = gcnew Bitmap(pBVLine[i]->Width, pBVLine[i]->Height);
				pBVLine[i]->Image = bmpPicBox;
				pBVLine[i]->BringToFront();
				pBVLine[i]->Visible = false;

				Graphics^ gV = Graphics::FromImage(pBVLine[i]->Image);
				Pen^ myPenV = gcnew Pen(Color::Red);
				myPenV->Width = 5;
				gV->DrawLine(myPenV, 0, 0, 0, pBVLine[i]->Height);

				//HLine
				pBHLine[i] = (gcnew System::Windows::Forms::PictureBox());
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBHLine[i]))->BeginInit();
				this->splitContainer1->Panel1->Controls->Add(pBHLine[i]);
				pBHLine[i]->Location = System::Drawing::Point(184, 24);
				pBHLine[i]->Margin = System::Windows::Forms::Padding(2);
				pBHLine[i]->TabStop = false;
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBHLine[i]))->EndInit();
				pBHLine[i]->Size = System::Drawing::Size(1000, 1);
				pBHLine[i]->Image = gcnew Bitmap(pBHLine[i]->Width, pBHLine[i]->Height);
				pBHLine[i]->BringToFront();
				pBHLine[i]->Visible = false;

				Graphics^ gH = Graphics::FromImage(pBHLine[i]->Image);
				Pen^ myPenH = gcnew Pen(Color::Blue);
				myPenH->Width = 5;
				gH->DrawLine(myPenH, 0, 0, pBHLine[i]->Width, 0);

				//HLineText
				pBHLineText[i] = (gcnew System::Windows::Forms::PictureBox());
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBHLineText[i]))->BeginInit();
				this->splitContainer1->Panel1->Controls->Add(pBHLineText[i]);
				pBHLineText[i]->Location = System::Drawing::Point(184, 24);
				pBHLineText[i]->Margin = System::Windows::Forms::Padding(2);
				pBHLineText[i]->TabStop = false;
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBHLineText[i]))->EndInit();
				pBHLineText[i]->Size = System::Drawing::Size(200, 16);
				pBHLineText[i]->Image = gcnew Bitmap(pBHLineText[i]->Width, pBHLineText[i]->Height);
				pBHLineText[i]->BringToFront();
				pBHLineText[i]->Visible = false;

				Graphics^ gHT = Graphics::FromImage(pBHLineText[i]->Image);
				String^ drawString = "V value";

				// Create font and brush.
				System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 11);
				SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);

				// Create point for upper-left corner of drawing.
				PointF drawPoint = PointF(150.0F, 150.0F);
				gHT->DrawString(drawString, drawFont, drawBrush, 0, 0);

				//Plot2
				pBPlot2[i] = (gcnew System::Windows::Forms::PictureBox());
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBPlot2[i]))->BeginInit();
				this->splitContainer2->Panel1->Controls->Add(pBPlot2[i]);
				pBPlot2[i]->Location = System::Drawing::Point(184, 24);
				pBPlot2[i]->Margin = System::Windows::Forms::Padding(2);
				pBPlot2[i]->TabStop = false;
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBPlot2[i]))->EndInit();
				//Plot3
				pBPlot3[i] = (gcnew System::Windows::Forms::PictureBox());
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBPlot3[i]))->BeginInit();
				this->splitContainer3->Panel1->Controls->Add(pBPlot3[i]);
				pBPlot3[i]->Location = System::Drawing::Point(184, 24);
				pBPlot3[i]->Margin = System::Windows::Forms::Padding(2);
				pBPlot3[i]->TabStop = false;
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBPlot3[i]))->EndInit();
			}

			//
			//TODO: ここにコンストラクター コードを追加します
			//
	//			TKADCCONTROL* DL850;
	//			DL850 = new TKADCCONTROL;
	//			TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->Close();
			Setting = Setting_;
			DL750 = DL750_;
			DL850 = DL850_;
			TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750) = DL750_;
			TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850) = DL850_;
			thisShot = thisShot_;
			thisPlot = thisPlot_;
			thisAnalyzeSP = new TKANALYZESP(thisShot, Setting, "AnalyzeSP");
			thisAnalyzeISP = new TKANALYZEISP(thisShot, Setting, "AnalyzeISP");

			if (Connection(1))
				MessageBox::Show("Connection failed.");

			TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)
				->SetLastLocalShotNumber(std::stoi((*Setting)["DL750"]["LastLocalShotNumber"]));
			TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)
				->SetLocalShotNumberMax(std::stoi((*Setting)["DL750"]["LocalShotNumberMax"]));
			TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)
				->SetLastLocalShotNumber(std::stoi((*Setting)["DL850"]["LastLocalShotNumber"]));
			TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)
				->SetLocalShotNumberMax(std::stoi((*Setting)["DL850"]["LocalShotNumberMax"]));

			TKSHOTNO::SetLastShotNumber((unsigned int)std::stoi((*Setting)["ShotNumber"]["LastShotNumber"]));
			TKSHOTNO::SetShotNumberMax((unsigned int)std::stoi((*Setting)["ShotNumber"]["ShotNumberMax"]));

			flushADCState("N/A", System::Drawing::Color::OrangeRed);
			flushShotNumber();

			{
				char group[] = "AnalyzeSP";

				numericUpDown3->Minimum = std::stoi((*Setting)[group]["FitRangeMin"]);
				numericUpDown4->Minimum = std::stoi((*Setting)[group]["FitRangeMin"]);
				numericUpDown5->Minimum = std::stoi((*Setting)[group]["FitRangeMin"]);
				numericUpDown6->Minimum = std::stoi((*Setting)[group]["FitRangeMin"]);
				numericUpDown7->Minimum = std::stoi((*Setting)[group]["FitRangeMin"]);
				numericUpDown8->Minimum = std::stoi((*Setting)[group]["FitRangeMin"]);

				numericUpDown3->Maximum = std::stoi((*Setting)[group]["FitRangeMax"]);
				numericUpDown4->Maximum = std::stoi((*Setting)[group]["FitRangeMax"]);
				numericUpDown5->Maximum = std::stoi((*Setting)[group]["FitRangeMax"]);
				numericUpDown6->Maximum = std::stoi((*Setting)[group]["FitRangeMax"]);
				numericUpDown7->Maximum = std::stoi((*Setting)[group]["FitRangeMax"]);
				numericUpDown8->Maximum = std::stoi((*Setting)[group]["FitRangeMax"]);

				numericUpDown4->Value = std::stoi((*Setting)[group]["FitRangeIisMin"]);
				numericUpDown3->Value = std::stoi((*Setting)[group]["FitRangeIisMax"]);
				numericUpDown6->Value = std::stoi((*Setting)[group]["FitRangeIeMin"]);
				numericUpDown5->Value = std::stoi((*Setting)[group]["FitRangeIeMax"]);
				numericUpDown8->Value = std::stoi((*Setting)[group]["FitRangeIesMin"]);
				numericUpDown7->Value = std::stoi((*Setting)[group]["FitRangeIesMax"]);
			}
			{
				char group[] = "AnalyzeISP";

				numericUpDown14->Minimum = std::stoi((*Setting)[group]["FitRangeMin"]);
				numericUpDown13->Minimum = std::stoi((*Setting)[group]["FitRangeMin"]);
				numericUpDown12->Minimum = std::stoi((*Setting)[group]["FitRangeMin"]);
				numericUpDown11->Minimum = std::stoi((*Setting)[group]["FitRangeMin"]);
				numericUpDown10->Minimum = std::stoi((*Setting)[group]["FitRangeMin"]);
				numericUpDown9->Minimum = std::stoi((*Setting)[group]["FitRangeMin"]);

				numericUpDown14->Maximum = std::stoi((*Setting)[group]["FitRangeMax"]);
				numericUpDown13->Maximum = std::stoi((*Setting)[group]["FitRangeMax"]);
				numericUpDown12->Maximum = std::stoi((*Setting)[group]["FitRangeMax"]);
				numericUpDown11->Maximum = std::stoi((*Setting)[group]["FitRangeMax"]);
				numericUpDown10->Maximum = std::stoi((*Setting)[group]["FitRangeMax"]);
				numericUpDown9->Maximum = std::stoi((*Setting)[group]["FitRangeMax"]);

				numericUpDown14->Value = std::stoi((*Setting)[group]["FitRangeIisMin"]);
				numericUpDown13->Value = std::stoi((*Setting)[group]["FitRangeIisMax"]);
				numericUpDown12->Value = std::stoi((*Setting)[group]["FitRangeIeMin"]);
				numericUpDown11->Value = std::stoi((*Setting)[group]["FitRangeIeMax"]);
				numericUpDown10->Value = std::stoi((*Setting)[group]["FitRangeIesMin"]);
				numericUpDown9->Value = std::stoi((*Setting)[group]["FitRangeIesMax"]);
			}
		}


	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~MyForm()
		{
			if (components) {
				delete components;
			}
			TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->Close();
			TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->Close();
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
			this->新規ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->開くToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->生データを追加ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
			this->toolStripTextBox1 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem4 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButton1 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton2 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton3 = (gcnew System::Windows::Forms::ToolStripButton());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->splitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->numericUpDown7 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown8 = (gcnew System::Windows::Forms::NumericUpDown());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->numericUpDown5 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown6 = (gcnew System::Windows::Forms::NumericUpDown());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->numericUpDown3 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown4 = (gcnew System::Windows::Forms::NumericUpDown());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->splitContainer3 = (gcnew System::Windows::Forms::SplitContainer());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->numericUpDown9 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown10 = (gcnew System::Windows::Forms::NumericUpDown());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->numericUpDown11 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown12 = (gcnew System::Windows::Forms::NumericUpDown());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->numericUpDown13 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown14 = (gcnew System::Windows::Forms::NumericUpDown());
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer2))->BeginInit();
			this->splitContainer2->Panel2->SuspendLayout();
			this->splitContainer2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown8))->BeginInit();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown6))->BeginInit();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown4))->BeginInit();
			this->tabPage3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer3))->BeginInit();
			this->splitContainer3->Panel2->SuspendLayout();
			this->splitContainer3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown9))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown10))->BeginInit();
			this->groupBox5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown11))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown12))->BeginInit();
			this->groupBox6->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown13))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown14))->BeginInit();
			this->toolStripContainer2->ContentPanel->SuspendLayout();
			this->toolStripContainer2->TopToolStripPanel->SuspendLayout();
			this->toolStripContainer2->SuspendLayout();
			this->toolStrip3->SuspendLayout();
			this->toolStrip2->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Dock = System::Windows::Forms::DockStyle::None;
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7)
			{
				this->faToolStripMenuItem,
					this->toolStripMenuItem1, this->ハードウェアToolStripMenuItem, this->グラフToolStripMenuItem, this->さようならToolStripMenuItem, this->toolStripTextBox1,
					this->toolStripMenuItem2
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 75);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(5, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(737, 29);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			this->menuStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &MyForm::menuStrip1_ItemClicked);
			// 
			// faToolStripMenuItem
			// 
			this->faToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9)
			{
				this->新規ToolStripMenuItem,
					this->開くToolStripMenuItem, this->生データを追加ToolStripMenuItem, this->toolStripSeparator1, this->保存ToolStripMenuItem, this->名前を付けて保存ToolStripMenuItem,
					this->すべて保存ToolStripMenuItem, this->toolStripSeparator2, this->終了ToolStripMenuItem
			});
			this->faToolStripMenuItem->Name = L"faToolStripMenuItem";
			this->faToolStripMenuItem->Size = System::Drawing::Size(68, 25);
			this->faToolStripMenuItem->Text = L"ファイル";
			this->faToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::faToolStripMenuItem_Click);
			// 
			// 新規ToolStripMenuItem
			// 
			this->新規ToolStripMenuItem->Name = L"新規ToolStripMenuItem";
			this->新規ToolStripMenuItem->Size = System::Drawing::Size(172, 22);
			this->新規ToolStripMenuItem->Text = L"新規";
			this->新規ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::新規ToolStripMenuItem_Click);
			// 
			// 開くToolStripMenuItem
			// 
			this->開くToolStripMenuItem->Name = L"開くToolStripMenuItem";
			this->開くToolStripMenuItem->Size = System::Drawing::Size(172, 22);
			this->開くToolStripMenuItem->Text = L"新しく開く";
			this->開くToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::開くToolStripMenuItem_Click);
			// 
			// 生データを追加ToolStripMenuItem
			// 
			this->生データを追加ToolStripMenuItem->Name = L"生データを追加ToolStripMenuItem";
			this->生データを追加ToolStripMenuItem->Size = System::Drawing::Size(172, 22);
			this->生データを追加ToolStripMenuItem->Text = L"追加で開く";
			this->生データを追加ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::生データを追加ToolStripMenuItem_Click);
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
			this->toolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3)
			{
				this->計測開始ToolStripMenuItem,
					this->計測停止ToolStripMenuItem, this->計測設定ToolStripMenuItem
			});
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->ShortcutKeyDisplayString = L"";
			this->toolStripMenuItem1->Size = System::Drawing::Size(44, 25);
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
			this->ハードウェアToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3)
			{
				this->計測器接続ToolStripMenuItem,
					this->計測器切断, this->計測器接続設定ToolStripMenuItem
			});
			this->ハードウェアToolStripMenuItem->Name = L"ハードウェアToolStripMenuItem";
			this->ハードウェアToolStripMenuItem->ShowShortcutKeys = false;
			this->ハードウェアToolStripMenuItem->Size = System::Drawing::Size(44, 25);
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
			this->グラフToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2)
			{
				this->グラフ描画ToolStripMenuItem,
					this->グラフ設定ToolStripMenuItem
			});
			this->グラフToolStripMenuItem->Name = L"グラフToolStripMenuItem";
			this->グラフToolStripMenuItem->Size = System::Drawing::Size(56, 25);
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
			this->さようならToolStripMenuItem->Size = System::Drawing::Size(41, 25);
			this->さようならToolStripMenuItem->Text = L"bye";
			this->さようならToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::さようならToolStripMenuItem_Click);
			// 
			// toolStripTextBox1
			// 
			this->toolStripTextBox1->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->toolStripTextBox1->ForeColor = System::Drawing::SystemColors::ControlText;
			this->toolStripTextBox1->Name = L"toolStripTextBox1";
			this->toolStripTextBox1->ReadOnly = true;
			this->toolStripTextBox1->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->toolStripTextBox1->Size = System::Drawing::Size(100, 25);
			this->toolStripTextBox1->Text = L"#00000000";
			// 
			// toolStripMenuItem2
			// 
			this->toolStripMenuItem2->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->toolStripMenuItem2->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2)
			{
				this->toolStripMenuItem3,
					this->toolStripMenuItem4
			});
			this->toolStripMenuItem2->ForeColor = System::Drawing::Color::OrangeRed;
			this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
			this->toolStripMenuItem2->Size = System::Drawing::Size(56, 25);
			this->toolStripMenuItem2->Text = L"Ready";
			// 
			// toolStripMenuItem3
			// 
			this->toolStripMenuItem3->Name = L"toolStripMenuItem3";
			this->toolStripMenuItem3->Size = System::Drawing::Size(126, 22);
			this->toolStripMenuItem3->Text = L"DL750 - ";
			// 
			// toolStripMenuItem4
			// 
			this->toolStripMenuItem4->Name = L"toolStripMenuItem4";
			this->toolStripMenuItem4->Size = System::Drawing::Size(126, 22);
			this->toolStripMenuItem4->Text = L"DL850 - ";
			// 
			// toolStrip1
			// 
			this->toolStrip1->Dock = System::Windows::Forms::DockStyle::None;
			this->toolStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3)
			{
				this->toolStripButton1,
					this->toolStripButton2, this->toolStripButton3
			});
			this->toolStrip1->Location = System::Drawing::Point(3, 0);
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
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(737, 344);
			this->tabControl1->TabIndex = 3;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->splitContainer1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Margin = System::Windows::Forms::Padding(0);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Size = System::Drawing::Size(729, 318);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Plot YT";
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
			this->splitContainer1->Panel2->Controls->Add(this->numericUpDown2);
			this->splitContainer1->Panel2->Controls->Add(this->button5);
			this->splitContainer1->Panel2->Controls->Add(this->button6);
			this->splitContainer1->Panel2->Controls->Add(this->button7);
			this->splitContainer1->Panel2->Controls->Add(this->button8);
			this->splitContainer1->Panel2->Controls->Add(this->numericUpDown1);
			this->splitContainer1->Panel2->Controls->Add(this->button4);
			this->splitContainer1->Panel2->Controls->Add(this->button3);
			this->splitContainer1->Panel2->Controls->Add(this->button2);
			this->splitContainer1->Panel2->Controls->Add(this->button1);
			this->splitContainer1->Size = System::Drawing::Size(729, 318);
			this->splitContainer1->SplitterDistance = 268;
			this->splitContainer1->SplitterWidth = 1;
			this->splitContainer1->TabIndex = 27;
			// 
			// numericUpDown2
			// 
			this->numericUpDown2->Location = System::Drawing::Point(264, 13);
			this->numericUpDown2->Name = L"numericUpDown2";
			this->numericUpDown2->Size = System::Drawing::Size(48, 19);
			this->numericUpDown2->TabIndex = 9;
			this->numericUpDown2->ValueChanged += gcnew System::EventHandler(this, &MyForm::numericUpDown2_ValueChanged);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(344, 13);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(23, 23);
			this->button5->TabIndex = 8;
			this->button5->Text = L"≫";
			this->button5->UseVisualStyleBackColor = true;
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(320, 13);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(23, 23);
			this->button6->TabIndex = 7;
			this->button6->Text = L"<";
			this->button6->UseVisualStyleBackColor = true;
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(232, 13);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(23, 23);
			this->button7->TabIndex = 6;
			this->button7->Text = L"<";
			this->button7->UseVisualStyleBackColor = true;
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(208, 13);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(23, 23);
			this->button8->TabIndex = 5;
			this->button8->Text = L"≪";
			this->button8->UseVisualStyleBackColor = true;
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(80, 13);
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(48, 19);
			this->numericUpDown1->TabIndex = 4;
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &MyForm::numericUpDown1_ValueChanged);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(160, 13);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(23, 23);
			this->button4->TabIndex = 3;
			this->button4->Text = L"≫";
			this->button4->UseVisualStyleBackColor = true;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(136, 13);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(23, 23);
			this->button3->TabIndex = 2;
			this->button3->Text = L"<";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(48, 13);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(23, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"<";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(24, 13);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(23, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"≪";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->splitContainer2);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Margin = System::Windows::Forms::Padding(0);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(729, 344);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Analyze SP";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// splitContainer2
			// 
			this->splitContainer2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer2->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
			this->splitContainer2->IsSplitterFixed = true;
			this->splitContainer2->Location = System::Drawing::Point(0, 0);
			this->splitContainer2->Margin = System::Windows::Forms::Padding(0);
			this->splitContainer2->Name = L"splitContainer2";
			this->splitContainer2->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer2.Panel1
			// 
			this->splitContainer2->Panel1->AutoScroll = true;
			// 
			// splitContainer2.Panel2
			// 
			this->splitContainer2->Panel2->BackColor = System::Drawing::Color::MediumAquamarine;
			this->splitContainer2->Panel2->Controls->Add(this->button11);
			this->splitContainer2->Panel2->Controls->Add(this->button10);
			this->splitContainer2->Panel2->Controls->Add(this->button9);
			this->splitContainer2->Panel2->Controls->Add(this->groupBox3);
			this->splitContainer2->Panel2->Controls->Add(this->groupBox2);
			this->splitContainer2->Panel2->Controls->Add(this->groupBox1);
			this->splitContainer2->Size = System::Drawing::Size(729, 344);
			this->splitContainer2->SplitterDistance = 294;
			this->splitContainer2->SplitterWidth = 1;
			this->splitContainer2->TabIndex = 28;
			// 
			// button11
			// 
			this->button11->Location = System::Drawing::Point(558, 19);
			this->button11->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(56, 18);
			this->button11->TabIndex = 23;
			this->button11->Text = L"設定";
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Click += gcnew System::EventHandler(this, &MyForm::button11_Click);
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(486, 19);
			this->button10->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(56, 18);
			this->button10->TabIndex = 22;
			this->button10->Text = L"結果表示";
			this->button10->UseVisualStyleBackColor = true;
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(426, 19);
			this->button9->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(56, 18);
			this->button9->TabIndex = 21;
			this->button9->Text = L"再計算";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &MyForm::button9_Click);
			// 
			// groupBox3
			// 
			this->groupBox3->BackColor = System::Drawing::Color::Transparent;
			this->groupBox3->Controls->Add(this->numericUpDown7);
			this->groupBox3->Controls->Add(this->numericUpDown8);
			this->groupBox3->Location = System::Drawing::Point(288, 6);
			this->groupBox3->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Padding = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->groupBox3->Size = System::Drawing::Size(126, 38);
			this->groupBox3->TabIndex = 20;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Electron Saturation";
			// 
			// numericUpDown7
			// 
			this->numericUpDown7->Location = System::Drawing::Point(66, 13);
			this->numericUpDown7->Name = L"numericUpDown7";
			this->numericUpDown7->Size = System::Drawing::Size(48, 19);
			this->numericUpDown7->TabIndex = 15;
			// 
			// numericUpDown8
			// 
			this->numericUpDown8->Location = System::Drawing::Point(12, 13);
			this->numericUpDown8->Name = L"numericUpDown8";
			this->numericUpDown8->Size = System::Drawing::Size(48, 19);
			this->numericUpDown8->TabIndex = 14;
			// 
			// groupBox2
			// 
			this->groupBox2->BackColor = System::Drawing::Color::Transparent;
			this->groupBox2->Controls->Add(this->numericUpDown5);
			this->groupBox2->Controls->Add(this->numericUpDown6);
			this->groupBox2->Location = System::Drawing::Point(150, 6);
			this->groupBox2->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Padding = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->groupBox2->Size = System::Drawing::Size(126, 38);
			this->groupBox2->TabIndex = 20;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Electron Returding";
			// 
			// numericUpDown5
			// 
			this->numericUpDown5->Location = System::Drawing::Point(66, 13);
			this->numericUpDown5->Name = L"numericUpDown5";
			this->numericUpDown5->Size = System::Drawing::Size(48, 19);
			this->numericUpDown5->TabIndex = 13;
			// 
			// numericUpDown6
			// 
			this->numericUpDown6->Location = System::Drawing::Point(12, 13);
			this->numericUpDown6->Name = L"numericUpDown6";
			this->numericUpDown6->Size = System::Drawing::Size(48, 19);
			this->numericUpDown6->TabIndex = 12;
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::Color::Transparent;
			this->groupBox1->Controls->Add(this->numericUpDown3);
			this->groupBox1->Controls->Add(this->numericUpDown4);
			this->groupBox1->Location = System::Drawing::Point(12, 6);
			this->groupBox1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->groupBox1->Size = System::Drawing::Size(126, 38);
			this->groupBox1->TabIndex = 19;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Ion Saturation";
			// 
			// numericUpDown3
			// 
			this->numericUpDown3->Location = System::Drawing::Point(66, 13);
			this->numericUpDown3->Name = L"numericUpDown3";
			this->numericUpDown3->Size = System::Drawing::Size(48, 19);
			this->numericUpDown3->TabIndex = 11;
			// 
			// numericUpDown4
			// 
			this->numericUpDown4->Location = System::Drawing::Point(12, 13);
			this->numericUpDown4->Name = L"numericUpDown4";
			this->numericUpDown4->Size = System::Drawing::Size(48, 19);
			this->numericUpDown4->TabIndex = 10;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->splitContainer3);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Margin = System::Windows::Forms::Padding(0);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(729, 318);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Analyze ISP";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// splitContainer3
			// 
			this->splitContainer3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer3->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
			this->splitContainer3->IsSplitterFixed = true;
			this->splitContainer3->Location = System::Drawing::Point(0, 0);
			this->splitContainer3->Margin = System::Windows::Forms::Padding(0);
			this->splitContainer3->Name = L"splitContainer3";
			this->splitContainer3->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer3.Panel1
			// 
			this->splitContainer3->Panel1->AutoScroll = true;
			// 
			// splitContainer3.Panel2
			// 
			this->splitContainer3->Panel2->BackColor = System::Drawing::Color::MediumAquamarine;
			this->splitContainer3->Panel2->Controls->Add(this->button12);
			this->splitContainer3->Panel2->Controls->Add(this->button13);
			this->splitContainer3->Panel2->Controls->Add(this->button14);
			this->splitContainer3->Panel2->Controls->Add(this->groupBox4);
			this->splitContainer3->Panel2->Controls->Add(this->groupBox5);
			this->splitContainer3->Panel2->Controls->Add(this->groupBox6);
			this->splitContainer3->Size = System::Drawing::Size(729, 318);
			this->splitContainer3->SplitterDistance = 268;
			this->splitContainer3->SplitterWidth = 1;
			this->splitContainer3->TabIndex = 29;
			// 
			// button12
			// 
			this->button12->Location = System::Drawing::Point(558, 19);
			this->button12->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(56, 18);
			this->button12->TabIndex = 23;
			this->button12->Text = L"設定";
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Click += gcnew System::EventHandler(this, &MyForm::button12_Click);
			// 
			// button13
			// 
			this->button13->Location = System::Drawing::Point(486, 19);
			this->button13->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(56, 18);
			this->button13->TabIndex = 22;
			this->button13->Text = L"結果表示";
			this->button13->UseVisualStyleBackColor = true;
			// 
			// button14
			// 
			this->button14->Location = System::Drawing::Point(426, 19);
			this->button14->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(56, 18);
			this->button14->TabIndex = 21;
			this->button14->Text = L"再計算";
			this->button14->UseVisualStyleBackColor = true;
			this->button14->Click += gcnew System::EventHandler(this, &MyForm::button14_Click);
			// 
			// groupBox4
			// 
			this->groupBox4->BackColor = System::Drawing::Color::Transparent;
			this->groupBox4->Controls->Add(this->numericUpDown9);
			this->groupBox4->Controls->Add(this->numericUpDown10);
			this->groupBox4->Location = System::Drawing::Point(288, 6);
			this->groupBox4->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Padding = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->groupBox4->Size = System::Drawing::Size(126, 38);
			this->groupBox4->TabIndex = 20;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Electron Saturation";
			// 
			// numericUpDown9
			// 
			this->numericUpDown9->Location = System::Drawing::Point(66, 13);
			this->numericUpDown9->Name = L"numericUpDown9";
			this->numericUpDown9->Size = System::Drawing::Size(48, 19);
			this->numericUpDown9->TabIndex = 15;
			// 
			// numericUpDown10
			// 
			this->numericUpDown10->Location = System::Drawing::Point(12, 13);
			this->numericUpDown10->Name = L"numericUpDown10";
			this->numericUpDown10->Size = System::Drawing::Size(48, 19);
			this->numericUpDown10->TabIndex = 14;
			// 
			// groupBox5
			// 
			this->groupBox5->BackColor = System::Drawing::Color::Transparent;
			this->groupBox5->Controls->Add(this->numericUpDown11);
			this->groupBox5->Controls->Add(this->numericUpDown12);
			this->groupBox5->Location = System::Drawing::Point(150, 6);
			this->groupBox5->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Padding = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->groupBox5->Size = System::Drawing::Size(126, 38);
			this->groupBox5->TabIndex = 20;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Ion Returding";
			// 
			// numericUpDown11
			// 
			this->numericUpDown11->Location = System::Drawing::Point(66, 13);
			this->numericUpDown11->Name = L"numericUpDown11";
			this->numericUpDown11->Size = System::Drawing::Size(48, 19);
			this->numericUpDown11->TabIndex = 13;
			// 
			// numericUpDown12
			// 
			this->numericUpDown12->Location = System::Drawing::Point(12, 13);
			this->numericUpDown12->Name = L"numericUpDown12";
			this->numericUpDown12->Size = System::Drawing::Size(48, 19);
			this->numericUpDown12->TabIndex = 12;
			// 
			// groupBox6
			// 
			this->groupBox6->BackColor = System::Drawing::Color::Transparent;
			this->groupBox6->Controls->Add(this->numericUpDown13);
			this->groupBox6->Controls->Add(this->numericUpDown14);
			this->groupBox6->Location = System::Drawing::Point(12, 6);
			this->groupBox6->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Padding = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->groupBox6->Size = System::Drawing::Size(126, 38);
			this->groupBox6->TabIndex = 19;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"Ion Saturation";
			// 
			// numericUpDown13
			// 
			this->numericUpDown13->Enabled = false;
			this->numericUpDown13->Location = System::Drawing::Point(66, 13);
			this->numericUpDown13->Name = L"numericUpDown13";
			this->numericUpDown13->Size = System::Drawing::Size(48, 19);
			this->numericUpDown13->TabIndex = 11;
			// 
			// numericUpDown14
			// 
			this->numericUpDown14->Enabled = false;
			this->numericUpDown14->Location = System::Drawing::Point(12, 13);
			this->numericUpDown14->Name = L"numericUpDown14";
			this->numericUpDown14->Size = System::Drawing::Size(48, 19);
			this->numericUpDown14->TabIndex = 10;
			// 
			// toolStripContainer2
			// 
			// 
			// toolStripContainer2.BottomToolStripPanel
			// 
			this->toolStripContainer2->BottomToolStripPanel->Enabled = false;
			// 
			// toolStripContainer2.ContentPanel
			// 
			this->toolStripContainer2->ContentPanel->Controls->Add(this->tabControl1);
			this->toolStripContainer2->ContentPanel->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->toolStripContainer2->ContentPanel->Size = System::Drawing::Size(737, 344);
			this->toolStripContainer2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->toolStripContainer2->Location = System::Drawing::Point(0, 0);
			this->toolStripContainer2->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->toolStripContainer2->Name = L"toolStripContainer2";
			this->toolStripContainer2->Size = System::Drawing::Size(737, 448);
			this->toolStripContainer2->TabIndex = 6;
			this->toolStripContainer2->Text = L"toolStripContainer2";
			// 
			// toolStripContainer2.TopToolStripPanel
			// 
			this->toolStripContainer2->TopToolStripPanel->Controls->Add(this->toolStrip1);
			this->toolStripContainer2->TopToolStripPanel->Controls->Add(this->toolStrip3);
			this->toolStripContainer2->TopToolStripPanel->Controls->Add(this->toolStrip2);
			this->toolStripContainer2->TopToolStripPanel->Controls->Add(this->menuStrip1);
			// 
			// toolStrip3
			// 
			this->toolStrip3->Dock = System::Windows::Forms::DockStyle::None;
			this->toolStrip3->ImageScalingSize = System::Drawing::Size(20, 20);
			this->toolStrip3->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2)
			{
				this->toolStripButton6,
					this->toolStripButton7
			});
			this->toolStrip3->Location = System::Drawing::Point(3, 25);
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
			this->toolStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2)
			{
				this->toolStripButton4,
					this->toolStripButton5
			});
			this->toolStrip2->Location = System::Drawing::Point(3, 50);
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
			this->ClientSize = System::Drawing::Size(737, 470);
			this->Controls->Add(this->toolStripContainer2);
			this->Controls->Add(this->statusStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->tabPage2->ResumeLayout(false);
			this->splitContainer2->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer2))->EndInit();
			this->splitContainer2->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown8))->EndInit();
			this->groupBox2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown6))->EndInit();
			this->groupBox1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown4))->EndInit();
			this->tabPage3->ResumeLayout(false);
			this->splitContainer3->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer3))->EndInit();
			this->splitContainer3->ResumeLayout(false);
			this->groupBox4->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown9))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown10))->EndInit();
			this->groupBox5->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown11))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown12))->EndInit();
			this->groupBox6->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown13))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown14))->EndInit();
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
	private: System::Void faToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
	}
	private: System::Void toolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e)
	{
	}
	private: System::Void 終了ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		Close();
	}
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e)
	{
	}
	private: System::Void 計測器接続設定ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		SetupADCConnection^ f = gcnew SetupADCConnection(Setting);
		f->Show();
	}
	private: System::Void さようならToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		Close();
	}
	private: System::Void toolStripMenuItem2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (!TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->Close())
			MessageBox::Show("Disconnected!");
		else
			MessageBox::Show("Disconnection failed.");
		if (!TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->Close())
			MessageBox::Show("Disconnected!");
		else
			MessageBox::Show("Disconnection failed.");
	}
	private: System::Void 計測器接続ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (!Connection(0))
			MessageBox::Show("Connect!");
		else
			MessageBox::Show("Connection failed.");
	}
	private: System::Void すべて保存ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		MessageBox::Show("huge");
	}
	private:
#define _MULTI_THREAD_
#ifndef _MULTI_THREAD_
		void threadADCStart(TKADCINFO::ADCID adcid)
		{
			TKADCINFO::ADCIDToTKADCPtr(adcid)->Start();
		}
		void threadADCWait(TKADCINFO::ADCID adcid)
		{
			TKADCINFO::ADCIDToTKADCPtr(adcid)->WaitADC();
		}
		void threadADCWaitandDownload(TKADCINFO::ADCID adcid)
		{
			TKADCINFO::ADCIDToTKADCPtr(adcid)->SaveShot(getNextLocalFileName(adcid));
			TKADCINFO::ADCIDToTKADCPtr(adcid)->WaitADC();
			switch (TKADCINFO::ADCIDToTKADCPtr(adcid)->Model()) {
			case TKADC_ADC_MODEL_DL750:
				downloadFromADC(adcid, getNextLocalFileName(adcid) + ".WVF");
				downloadFromADC(adcid, getNextLocalFileName(adcid) + ".HDR");
				break;
			case TKADC_ADC_MODEL_DL850:
				downloadFromADC(adcid, getNextLocalFileName(adcid) + ".WDF");
				break;
			}
			TKADCINFO::ADCIDToTKADCPtr(adcid)->IncrementLocalShotNumber();
			(*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["LastLocalShotNumber"]
				= std::to_string(TKADCINFO::ADCIDToTKADCPtr(adcid)->GetLastLocalShotNumber());
	}
#else
		static void threadADCStart(System::Object^ adcid)
		{
			TKADCINFO::ADCIDToTKADCPtr((TKADCINFO::ADCID)(Int32)adcid)->Start();
		}
		static void threadADCWait(System::Object^ adcid)
		{
			TKADCINFO::ADCIDToTKADCPtr((TKADCINFO::ADCID)(Int32)adcid)->WaitADC();
		}

#endif
	private: System::Void 計測開始ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		startMeasurement(this);
	}
	private: System::Void 計測停止ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->Stop();
		TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->Stop();
	}
	private: System::Void menuStrip1_ItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e)
	{
	}
	private: System::Void toolStripButton1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		計測開始ToolStripMenuItem_Click(sender, e);
	}
	private: System::Void toolStripButton5_Click(System::Object^  sender, System::EventArgs^  e)
	{
		計測器接続設定ToolStripMenuItem_Click(sender, e);
	}
	private: System::Void toolStripButton4_Click(System::Object^  sender, System::EventArgs^  e)
	{
		計測器接続ToolStripMenuItem_Click(sender, e);
	}
	private: System::Void toolStripButton2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		計測停止ToolStripMenuItem_Click(sender, e);
	}
	private: System::Void 保存ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		uploadToStrage(getLastLocalFileName(TKADCINFO_ADC_ID_DL750) + ".WVF",
			"#" + TKUTIL::ZeroFill(TKSHOTNO::GetNextShotNumber(), 8)
			+ "_" + TKADCINFO::ADCIDToSectionName(TKADCINFO_ADC_ID_DL750) + ".WVF");
		uploadToStrage(getLastLocalFileName(TKADCINFO_ADC_ID_DL750) + ".HDR",
			"#" + TKUTIL::ZeroFill(TKSHOTNO::GetNextShotNumber(), 8)
			+ "_" + TKADCINFO::ADCIDToSectionName(TKADCINFO_ADC_ID_DL750) + ".HDR");
		uploadToStrage(getLastLocalFileName(TKADCINFO_ADC_ID_DL750) + ".CSV",
			"#" + TKUTIL::ZeroFill(TKSHOTNO::GetNextShotNumber(), 8)
			+ "_" + TKADCINFO::ADCIDToSectionName(TKADCINFO_ADC_ID_DL750) + ".CSV");
		uploadToStrage(getLastLocalFileName(TKADCINFO_ADC_ID_DL850) + ".WDF",
			"#" + TKUTIL::ZeroFill(TKSHOTNO::GetNextShotNumber(), 8)
			+ "_" + TKADCINFO::ADCIDToSectionName(TKADCINFO_ADC_ID_DL850) + ".WDF");
		uploadToStrage(getLastLocalFileName(TKADCINFO_ADC_ID_DL850) + ".CSV",
			"#" + TKUTIL::ZeroFill(TKSHOTNO::GetNextShotNumber(), 8)
			+ "_" + TKADCINFO::ADCIDToSectionName(TKADCINFO_ADC_ID_DL850) + ".CSV");
		uploadToStrage(SETTING_FILE_PATH,
			"#" + TKUTIL::ZeroFill(TKSHOTNO::GetNextShotNumber(), 8)
			+ "_" + "shotinfo" + ".inf");
		//		SetShotNumberColor(System::Drawing::Color::OrangeRed);
		//		SetShotNumberColor(System::Drawing::Color::Black);

		TKSHOTNO::IncrementShotNumber();

		(*Setting)["ShotNumber"]["LastShotNumber"] = std::to_string(TKSHOTNO::GetLastShotNumber());
		Setting->write(SETTING_FILE_PATH);

		thisShot->Clear();
		thisShot->AppendDataFile(getLastLocalFileName(TKADCINFO_ADC_ID_DL750));
		thisShot->AppendDataFile(getLastLocalFileName(TKADCINFO_ADC_ID_DL850));
		plotRaw(TKSHOTNO::GetLastShotNumber());
		SetShotNumberColor(System::Drawing::Color::OrangeRed);
	}
	private: System::Void toolStripButton3_Click(System::Object^  sender, System::EventArgs^  e)
	{
		保存ToolStripMenuItem_Click(sender, e);
	}
	private: System::Void グラフ設定ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		ShotSetting = new clx::ini((data_file_name + ".ini").c_str());
		ShotSetting->insert("This");
		(*ShotSetting)["This"]["FileName"] = data_file_name;
		ShotSetting->write((data_file_name + ".ini").c_str());
		SetupPlot^ f = gcnew SetupPlot(ShotSetting);
		f->Show();
	}
	private: System::Void グラフ描画ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		this->plotRaw(0);
	}
	private: System::Void toolStripButton6_Click(System::Object^  sender, System::EventArgs^  e)
	{
		グラフ描画ToolStripMenuItem_Click(sender, e);
	}
	private: System::Void toolStripButton7_Click(System::Object^  sender, System::EventArgs^  e)
	{
		グラフ設定ToolStripMenuItem_Click(sender, e);
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//	pBVLine[24]->Location = System::Drawing::Point(20, 24);
	}
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//	pBVLine[24]->Location = System::Drawing::Point(40, 24);
	}
	private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		refreshVLine();
	}
	private: System::Void numericUpDown2_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		refreshHLine();
	}

	private: System::Void 新規ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		thisShot->Clear();
	}
#include "clx/salgorithm.h"

	private: System::Void 生データを追加ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		// Displays an OpenFileDialog so the user can select a Cursor.
		OpenFileDialog ^ openFileDialog1 = gcnew OpenFileDialog();
		openFileDialog1->Filter = "YOKOGAWA Binary (*.WVF, *.WDF)|*.WVF;*.WDF|DL750 Binary (*.WVF)|*.WVF|DL850 Binary (*.WDF)|*.WDF";
		openFileDialog1->Title = "Select a Binary File";
		openFileDialog1->Multiselect = false;

		// Show the Dialog.
		// If the user clicked OK in the dialog and
		// a .CUR file was selected, open it.
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			//TKADCINFO::ADCID adcid;
			std::vector<std::string> tok;

			clx::split_if(TKUTIL::SystemStringToString(openFileDialog1->FileNames[0]), tok, clx::is_any_of("."));
			System::IO::FileInfo^ fInfo;


			// 

			/*

			for (int i = 0; i < static_cast<int>(thisShot->GetADCNumber()); i++) {
				if (thisShot->GetADCID(i) == adcid) {
					MessageBox::Show("このADCのデータは既に読み込まれています。", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					return;
				}
			}
			*/

			if (clx::upcase_copy(tok[1]) == "WVF") {
				fInfo = gcnew System::IO::FileInfo(gcnew System::String((tok[0] + ".CSV").c_str()));
				if (!fInfo->Exists)
					std::system(((std::string)"wvfconv.exe " + tok[0] + " > " + tok[0] + ".CSV").c_str());
				delete fInfo;
			}
			if (clx::upcase_copy(tok[1]) == "WDF") {
				fInfo = gcnew System::IO::FileInfo(gcnew System::String((tok[0] + ".WVF").c_str()));
				if (!fInfo->Exists)
					std::system(((std::string)"WDFCon.exe " + tok[0] + ".WDF").c_str());
				delete fInfo;
				fInfo = gcnew System::IO::FileInfo(gcnew System::String((tok[0] + ".CSV").c_str()));
				if (!fInfo->Exists)
					std::system(((std::string)"wvfconv.exe " + tok[0] + " > " + tok[0] + ".CSV").c_str());
				delete fInfo;
			}


			thisShot->AppendDataFile(tok[0]);
			plotRaw(0);
		}
	}

	private: System::Void 開くToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		新規ToolStripMenuItem_Click(sender, e);
		生データを追加ToolStripMenuItem_Click(sender, e);
	}

	private: System::Void button11_Click(System::Object^  sender, System::EventArgs^  e)
	{
		SetupAnalyzeSP^ f = gcnew SetupAnalyzeSP(Setting, thisShot, "AnalyzeSP");
		f->Show();
	}
	private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (!thisShot->GetADCNumber()) {
			MessageBox::Show("データが読み込まれていません");
			return;
		}
		if (std::stoi((*Setting)["AnalyzeSP"]["VChannelIndex"]) < 0 || std::stoi((*Setting)["AnalyzeSP"]["IChannelIndex"]) < 0) {
			MessageBox::Show("電流軸、電圧軸を設定してください");
			button11_Click(sender, e);
			return;
		}
		plotSP(0);
	}

	private: System::Void button12_Click(System::Object^  sender, System::EventArgs^  e)
	{
		SetupAnalyzeSP^ f = gcnew SetupAnalyzeSP(Setting, thisShot, "AnalyzeISP");
		f->Show();
	}
	private: System::Void button14_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (!thisShot->GetADCNumber()) {
			MessageBox::Show("データが読み込まれていません");
			return;
		}
		if (std::stoi((*Setting)["AnalyzeISP"]["VChannelIndex"]) < 0 || std::stoi((*Setting)["AnalyzeISP"]["IChannelIndex"]) < 0) {
			MessageBox::Show("電流軸、電圧軸を設定してください");
			button12_Click(sender, e);
			return;
		}
		plotISP(0);
	}
	};
}
#if 1
class exadcstart
{
private:
	TKADCINFO::ADCID adcid;
	TKADCCONTROL::CONDITIONFLAG flag;
public:
	exadcstart(TKADCINFO::ADCID const adcid_, TKADCCONTROL::CONDITIONFLAG flag_)
	{
		adcid = adcid_;
		flag = flag_;
	}

	virtual ~exadcstart() {};
	void operator()()
	{
		TKADCINFO::ADCIDToTKADCPtr(adcid)->Start();
		TKADCINFO::ADCIDToTKADCPtr(adcid)->GetStatusCondition(flag);
	}
};


class exfunctor
{
private:
	TKADCINFO::ADCID adcid;
	clx::ini* Setting;
	std::string makeLocalFileName(std::string prefix, int local_shot_number, int shot_number_length, std::string suffix)
	{
		std::ostringstream fname;
		fname << prefix << std::setfill('0') << std::setw(shot_number_length) << std::right << (local_shot_number) << suffix;
		return (std::string)fname.str();
	}

	inline std::string getLastLocalFileName(TKADCINFO::ADCID adcid)
	{
		return makeLocalFileName((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["LocalShotNamePrefix"],
			TKADCINFO::ADCIDToTKADCPtr(adcid)->GetLastLocalShotNumber(), 5, "");
	}

	inline std::string getNextLocalFileName(TKADCINFO::ADCID adcid)
	{
		return makeLocalFileName((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["LocalShotNamePrefix"],
			TKADCINFO::ADCIDToTKADCPtr(adcid)->GetNextLocalShotNumber(), 5, "");
	}

	inline int downloadFromADC(TKADCINFO::ADCID adcid, std::string filename)
	{
		clx::ftp session((std::string)((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["IPAddress"]), 21);
		session.login((std::string)((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["UserName"].c_str()),
			(std::string)(clx::base64::decode((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["Password"].c_str())));
		session.cd((std::string)((*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["StragePath"]));
		session.retrieve(filename, filename, clx::ftp::binary);
		session.finish();
		return 0;
	}

public:
	exfunctor(clx::ini* const Setting_, TKADCINFO::ADCID const adcid_, TKADCCONTROL::CONDITIONFLAG flag_)
	{
		adcid = adcid_;
		Setting = Setting_;
	}

	virtual ~exfunctor() {};
	void operator()()
	{
		TKADCINFO::ADCIDToTKADCPtr(adcid)->WaitADC();
		TKADCINFO::ADCIDToTKADCPtr(adcid)->SaveShot(getNextLocalFileName(adcid));
		TKADCINFO::ADCIDToTKADCPtr(adcid)->WaitADC();
		switch (TKADCINFO::ADCIDToTKADCPtr(adcid)->Model()) {
		case TKADC_ADC_MODEL_DL750:
			downloadFromADC(adcid, getNextLocalFileName(adcid) + ".WVF");
			downloadFromADC(adcid, getNextLocalFileName(adcid) + ".HDR");
			std::system(((std::string)"wvfconv.exe " + getNextLocalFileName(TKADCINFO_ADC_ID_DL750)
				+ " > " + getNextLocalFileName(TKADCINFO_ADC_ID_DL750) + ".CSV").c_str());
			break;
		case TKADC_ADC_MODEL_DL850:
			downloadFromADC(adcid, getNextLocalFileName(adcid) + ".WDF");
			std::system(((std::string)"WDFCon.exe " + getNextLocalFileName(TKADCINFO_ADC_ID_DL850) + ".WDF").c_str());
			std::system(((std::string)"wvfconv.exe " + getNextLocalFileName(TKADCINFO_ADC_ID_DL850)
				+ " > " + getNextLocalFileName(TKADCINFO_ADC_ID_DL850) + ".CSV").c_str());
			break;
		}
		TKADCINFO::ADCIDToTKADCPtr(adcid)->IncrementLocalShotNumber();
		(*Setting)[TKADCINFO::ADCIDToSectionName(adcid)]["LastLocalShotNumber"]
			= std::to_string(TKADCINFO::ADCIDToTKADCPtr(adcid)->GetLastLocalShotNumber());
	}
};
#endif
