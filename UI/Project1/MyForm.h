﻿#include "SetupADCConnection.h"
#include "SetupADCMeasurement.h"
#include "SetupAnalyzeSP.h"
#include "SetupPlot.h"
#include "DialogQuickLoadShot.h"
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
#include "tkfileutil.h"
#include "tktemp.h"
#include "tinyxml2.h"


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
	/// MyForm の概要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form {
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



	private: System::Windows::Forms::StatusStrip^  statusStrip1;



	private: System::Windows::Forms::ColorDialog^  colorDialog1;






















	private:
		array<System::Windows::Forms::PictureBox^>^ pBPlot = gcnew array<System::Windows::Forms::PictureBox^>(MAX_PLOT_NUMBER);
		array<System::Windows::Forms::PictureBox^>^ pBPlot2 = gcnew array<System::Windows::Forms::PictureBox^>(MAX_PLOT_NUMBER);
		array<System::Windows::Forms::PictureBox^>^ pBPlot3 = gcnew array<System::Windows::Forms::PictureBox^>(MAX_PLOT_NUMBER);





		array<System::Windows::Forms::PictureBox^>^ pBVLine = gcnew array<System::Windows::Forms::PictureBox^>(MAX_PLOT_NUMBER);
		array<System::Windows::Forms::PictureBox^>^ pBHLine = gcnew array<System::Windows::Forms::PictureBox^>(MAX_PLOT_NUMBER);

































	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  faToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  新規ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  開くToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  生データを追加ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  保存ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  名前を付けて保存ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  すべて保存ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  終了ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  計測開始ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  計測停止ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  計測設定ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ハードウェアToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  計測器接続ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  計測器切断;
	private: System::Windows::Forms::ToolStripMenuItem^  計測器接続設定ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  グラフToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  グラフ描画ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  グラフ設定ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  さようならToolStripMenuItem;
	private: System::Windows::Forms::ToolStripTextBox^  toolStripTextBox1;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem2;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem3;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem4;
	private: System::Windows::Forms::ToolStripContainer^  toolStripContainer2;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;











	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::SplitContainer^  splitContainer2;
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown7;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown8;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown5;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown6;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown3;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown4;
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
	private: System::Windows::Forms::ToolStrip^  toolStrip2;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonStart;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonStop;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonSave;



	private: System::Windows::Forms::ToolStripButton^  toolStripButton6;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton7;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton4;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton5;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator4;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton8;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator5;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton9;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator6;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonGo;


	private: System::Windows::Forms::ToolStripButton^  toolStripButtonPrev;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonNext;

	private: System::Windows::Forms::WebBrowser^  webBrowser2;
	private: System::Windows::Forms::WebBrowser^  webBrowser3;
	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	private: System::Windows::Forms::WebBrowser^  webBrowser1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown2;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button1;
















		 array<System::Windows::Forms::PictureBox^>^ pBHLineText = gcnew array<System::Windows::Forms::PictureBox^>(MAX_PLOT_NUMBER);


	private:
		void startMeasurement(Project1::MyForm^ parent);
		//int Connection(bool on_startup)
		//{
		//	int error_no;
		//	if (!(on_startup ^ (bool)((*Setting)["DL750"]["ConnectOnStartup"] == "Enable")))
		//		if ((bool)((*Setting)["DL750"]["Control"] == "Enable"))
		//			if (error_no = TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->Open(TM_CTL_ETHER, ((*Setting)["DL750"]["IPAddress"] + ",anonymous,").c_str()))
		//				goto error;
		//	if (!(on_startup ^ (bool)((*Setting)["DL850"]["ConnectOnStartup"] == "Enable")))
		//		if ((bool)((*Setting)["DL850"]["Control"] == "Enable"))
		//			if (error_no = TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->Open(TM_CTL_VXI11, (*Setting)["DL850"]["IPAddress"].c_str()))
		//				goto error;
		//	flushADCState("Ready");
		//	return 0;
		//error:
		//	throw TKADCCONTROL::Exception(static_cast<int>(TKADCINFO_ADC_ID_DL850), error_no);
		//	return error_no;
		//}
		int Connection(bool on_startup)
		{
			try {
				int error_no;
				std::vector<TKADCCONTROL::Exception> exception;
				if (!(on_startup ^ (bool)((*Setting)["DL750"]["ConnectOnStartup"] == "Enable")))
					if ((bool)((*Setting)["DL750"]["Control"] == "Enable"))
						if (error_no = TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750)->Open(TM_CTL_ETHER,
							((*Setting)["DL750"]["IPAddress"] + ",anonymous,").c_str()))
							exception.push_back(TKADCCONTROL::Exception(static_cast<int>(TKADCINFO_ADC_ID_DL750), error_no));
				if (!(on_startup ^ (bool)((*Setting)["DL850"]["ConnectOnStartup"] == "Enable")))
					if ((bool)((*Setting)["DL850"]["Control"] == "Enable"))
						if (error_no = TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->Open(TM_CTL_VXI11,
							(*Setting)["DL850"]["IPAddress"].c_str()))
							exception.push_back(TKADCCONTROL::Exception(static_cast<int>(TKADCINFO_ADC_ID_DL850), error_no));
				if (exception.size())
					throw exception;

				flushADCState("Ready");

				this->toolStripButtonStart->Enabled = true;
				this->計測器切断->Enabled = true;

				return 0;
			}
			catch (std::vector<TKADCCONTROL::Exception> const &e) {
				std::string error_section;
				for (const auto& iter : e)
					error_section = error_section + "Section:\t"_s
					+ TKADCINFO::ADCIDToSectionName(static_cast<TKADCINFO::ADCID>(iter.adc_id)) + "\n";
				MessageBox::Show(gcnew System::String(("Connection failed.\n"_s + error_section).c_str()));
				return 1;
			}
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
		int uploadToFileServer(std::string source, std::string destination)
		{
			clx::ftp session((std::string)((*Setting)["DataStrage"]["IPAddress"]), 21);
			session.login((std::string)((*Setting)["DataStrage"]["UserName"].c_str()),
				(std::string)(clx::base64::decode((*Setting)["DataStrage"]["Password"].c_str())));
			session.cd((std::string)((*Setting)["DataStrage"]["StragePath"]));
			session.store(source, destination, clx::ftp::binary);
			session.finish();
			return 0;
		}
		int downloadFromFileServer(std::string source, std::string destination)
		{
			clx::ftp session((std::string)((*Setting)["DataStrage"]["IPAddress"]), 21);
			session.login((std::string)((*Setting)["DataStrage"]["UserName"].c_str()),
				(std::string)(clx::base64::decode((*Setting)["DataStrage"]["Password"].c_str())));
			session.cd((std::string)((*Setting)["DataStrage"]["StragePath"]));
			session.retrieve(source, destination, clx::ftp::binary);
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
		void plotRaw(unsigned int shot_number, bool replot)
		{
			//			static int total_plot;
			//
			//
			//			for (int i = 0; i < picture_box_total_number; i++) {
			//				//Plot
			//				pBPlot[i]->Visible = false;
			//				delete pBPlot[i]->Image;
			//
			//#ifdef ENABLE_HVLINE
			//				//Line
			//				pBVLine[i]->Visible = false;
			//				pBHLine[i]->Visible = false;
			//				pBHLineText[i]->Visible = false;
			//#endif
			//			}
			//this->toolStripButtonPrev->Enabled = true;
			//this->toolStripButtonNext->Enabled = true;
			thisPlot->PlotRaw(TKPLOT::PLOTSIZE::SMALL_SIZE, shot_number, replot);
			thisPlot->MakeHTML((*Setting)["Utility"]["TempPath"] + "ytsummary.html");
			webBrowser1->Navigate(to_SystemString((*Setting)["Utility"]["TempPath"] + "ytsummary.html"_s));
			webBrowser1->Refresh();

			//total_plot = static_cast<int>(thisPlot->GetPlotInfo().size());
			//std::vector<TKPLOT::PLOTINFO>::pointer pplot_info;
			//pplot_info = thisPlot->GetPlotInfoPtr();
			//for (int i = 0; i < total_plot; i++) {
			//	//Plot
			//	pBPlot[i]->Location = System::Drawing::Point((pplot_info[i].terminal_size.w + 10)*(i % 3), (pplot_info[i].terminal_size.h + 0)*(i / 3));
			//	pBPlot[i]->Size = System::Drawing::Size(pplot_info[i].terminal_size.w, pplot_info[i].terminal_size.h);
			//	try {
			//		pBPlot[i]->Image = dynamic_cast<Image^>(gcnew Bitmap(gcnew System::String((pplot_info[i].plot_file_name
			//			+ ".svg").c_str())));
			//	}
			//	catch (...) {
			//		pBPlot[i]->Image = gcnew Bitmap(1, 1);
			//		MessageBox::Show("描画に失敗しました\nフィッティング範囲を変更するかフィッティングを無効にしてみてください。");
			//	}

			//	pBPlot[i]->Visible = true;
			//}
//#ifdef ENABLE_HVLINE
//			refreshVLine();
//			refreshHLine();
//			for (int i = 0; i < total_plot; i++) {
//				//VLine
//				pBVLine[i]->Visible = true;
//
//				//HLine
//				pBHLine[i]->Visible = true;
//				pBHLineText[i]->Visible = true;
//			}
//#endif
//
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
		void plotSP(unsigned int shot_number, bool replot)
		{
			//static int total_plot;
			//for (int i = 0; i < picture_box_total_number; i++) {
			//	//Plot
			//	pBPlot2[i]->Visible = false;
			//	delete pBPlot2[i]->Image;
			//}

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

			thisAnalyzeSP->PlotAnalyzeSP(TKPLOT::PLOTSIZE::MEDIUM_SIZE, shot_number, replot);
			thisAnalyzeSP->MakeHTML((*Setting)["Utility"]["TempPath"] + "spsummary.html");
			webBrowser2->Navigate(to_SystemString((*Setting)["Utility"]["TempPath"] + "spsummary.html"_s));
			webBrowser2->Refresh();

			//std::vector<TKPLOT::PLOTINFO>::pointer pplot_info;
			//pplot_info = thisAnalyzeSP->GetPlotInfoPtr();
			//for (int i = 0; i < 4; i++) {
			//	//Plot
			//	pBPlot2[i]->Location = System::Drawing::Point(pplot_info[i].terminal_size.w*(i % 2), pplot_info[i].terminal_size.h*(i / 2));
			//	pBPlot2[i]->Size = System::Drawing::Size(pplot_info[i].terminal_size.w, pplot_info[i].terminal_size.h);
			//	try {
			//		pBPlot2[i]->Image = dynamic_cast<Image^>(gcnew Bitmap(gcnew System::String((pplot_info[i].plot_file_name + std::to_string(i)
			//			+ ".svg").c_str())));
			//	}
			//	catch (...) {
			//		pBPlot2[i]->Image = gcnew Bitmap(1, 1);
			//		MessageBox::Show("描画に失敗しました\nフィッティング範囲を変更するかフィッティングを無効にしてみてください。");
			//	}
			//	pBPlot2[i]->Visible = true;
			//}

			flushShotNumber();
		}
		void plotISP(unsigned int shot_number, bool replot)
		{
			//static int total_plot;
			//for (int i = 0; i < picture_box_total_number; i++) {
			//	//Plot
			//	pBPlot3[i]->Visible = false;
			//	delete pBPlot3[i]->Image;
			//}

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

			thisAnalyzeISP->PlotAnalyzeSP(TKPLOT::PLOTSIZE::MEDIUM_SIZE, shot_number, replot);
			thisAnalyzeISP->MakeHTML((*Setting)["Utility"]["TempPath"] + "ispsummary.html");
			webBrowser3->Navigate(to_SystemString((*Setting)["Utility"]["TempPath"] + "ispsummary.html"_s));
			webBrowser3->Refresh();

			//std::vector<TKPLOT::PLOTINFO>::pointer pplot_info;
			//pplot_info = thisAnalyzeISP->GetPlotInfoPtr();
			//for (int i = 0; i < 4; i++) {
			//	//Plot
			//	pBPlot3[i]->Location = System::Drawing::Point(pplot_info[i].terminal_size.w*(i % 2), pplot_info[i].terminal_size.h*(i / 2));
			//	pBPlot3[i]->Size = System::Drawing::Size(pplot_info[i].terminal_size.w, pplot_info[i].terminal_size.h);
			//	try {
			//		pBPlot3[i]->Image = dynamic_cast<Image^>(gcnew Bitmap(gcnew System::String((pplot_info[i].plot_file_name + std::to_string(i)
			//			+ ".svg").c_str())));
			//	}
			//	catch (...) {
			//		pBPlot3[i]->Image = gcnew Bitmap(1, 1);
			//		MessageBox::Show("描画に失敗しました\nフィッティング範囲を変更するかフィッティングを無効にしてみてください。");
			//	}
			//	pBPlot3[i]->Visible = true;
			//}

			flushShotNumber();
		}

	public:
		MyForm(clx::ini* Setting_, TKSHOT* thisShot_, TKPLOT* thisPlot_, TKADCCONTROL_DL750* DL750_, TKADCCONTROL_DL850* DL850_)
			: Setting(Setting_), thisShot(thisShot_), thisPlot(thisPlot_), DL750(DL750_), DL850(DL850_)
		{
			InitializeComponent();
			//for (int i = 0; i < MAX_PLOT_NUMBER; i++) {
			//	//Plot
			//	pBPlot[i] = (gcnew System::Windows::Forms::PictureBox());
			//	(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBPlot[i]))->BeginInit();
			//	this->splitContainer1->Panel1->Controls->Add(pBPlot[i]);
			//	pBPlot[i]->Location = System::Drawing::Point(184, 24);
			//	pBPlot[i]->Margin = System::Windows::Forms::Padding(2);
			//	pBPlot[i]->TabStop = false;
			//	(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBPlot[i]))->EndInit();

			//	//VLine
			//	pBVLine[i] = (gcnew System::Windows::Forms::PictureBox());
			//	(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBVLine[i]))->BeginInit();
			//	this->splitContainer1->Panel1->Controls->Add(pBVLine[i]);
			//	pBVLine[i]->Location = System::Drawing::Point(184, 24);
			//	pBVLine[i]->Margin = System::Windows::Forms::Padding(2);
			//	pBVLine[i]->TabStop = false;
			//	(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBVLine[i]))->EndInit();
			//	pBVLine[i]->Size = System::Drawing::Size(1, 130);
			//	Bitmap^ bmpPicBox = gcnew Bitmap(pBVLine[i]->Width, pBVLine[i]->Height);
			//	pBVLine[i]->Image = bmpPicBox;
			//	pBVLine[i]->BringToFront();
			//	pBVLine[i]->Visible = false;

			//	Graphics^ gV = Graphics::FromImage(pBVLine[i]->Image);
			//	Pen^ myPenV = gcnew Pen(Color::Red);
			//	myPenV->Width = 5;
			//	gV->DrawLine(myPenV, 0, 0, 0, pBVLine[i]->Height);

			//	//HLine
			//	pBHLine[i] = (gcnew System::Windows::Forms::PictureBox());
			//	(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBHLine[i]))->BeginInit();
			//	this->splitContainer1->Panel1->Controls->Add(pBHLine[i]);
			//	pBHLine[i]->Location = System::Drawing::Point(184, 24);
			//	pBHLine[i]->Margin = System::Windows::Forms::Padding(2);
			//	pBHLine[i]->TabStop = false;
			//	(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBHLine[i]))->EndInit();
			//	pBHLine[i]->Size = System::Drawing::Size(1000, 1);
			//	pBHLine[i]->Image = gcnew Bitmap(pBHLine[i]->Width, pBHLine[i]->Height);
			//	pBHLine[i]->BringToFront();
			//	pBHLine[i]->Visible = false;

			//	Graphics^ gH = Graphics::FromImage(pBHLine[i]->Image);
			//	Pen^ myPenH = gcnew Pen(Color::Blue);
			//	myPenH->Width = 5;
			//	gH->DrawLine(myPenH, 0, 0, pBHLine[i]->Width, 0);

			//	//HLineText
			//	pBHLineText[i] = (gcnew System::Windows::Forms::PictureBox());
			//	(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBHLineText[i]))->BeginInit();
			//	this->splitContainer1->Panel1->Controls->Add(pBHLineText[i]);
			//	pBHLineText[i]->Location = System::Drawing::Point(184, 24);
			//	pBHLineText[i]->Margin = System::Windows::Forms::Padding(2);
			//	pBHLineText[i]->TabStop = false;
			//	(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBHLineText[i]))->EndInit();
			//	pBHLineText[i]->Size = System::Drawing::Size(200, 16);
			//	pBHLineText[i]->Image = gcnew Bitmap(pBHLineText[i]->Width, pBHLineText[i]->Height);
			//	pBHLineText[i]->BringToFront();
			//	pBHLineText[i]->Visible = false;

			//	Graphics^ gHT = Graphics::FromImage(pBHLineText[i]->Image);
			//	String^ drawString = "V value";

			//	// Create font and brush.
			//	System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 11);
			//	SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);

			//	// Create point for upper-left corner of drawing.
			//	PointF drawPoint = PointF(150.0F, 150.0F);
			//	gHT->DrawString(drawString, drawFont, drawBrush, 0, 0);

			//	//Plot2
			//	pBPlot2[i] = (gcnew System::Windows::Forms::PictureBox());
			//	(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBPlot2[i]))->BeginInit();
			//	this->splitContainer2->Panel1->Controls->Add(pBPlot2[i]);
			//	pBPlot2[i]->Location = System::Drawing::Point(184, 24);
			//	pBPlot2[i]->Margin = System::Windows::Forms::Padding(2);
			//	pBPlot2[i]->TabStop = false;
			//	(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBPlot2[i]))->EndInit();
			//	//Plot3
			//	pBPlot3[i] = (gcnew System::Windows::Forms::PictureBox());
			//	(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBPlot3[i]))->BeginInit();
			//	this->splitContainer3->Panel1->Controls->Add(pBPlot3[i]);
			//	pBPlot3[i]->Location = System::Drawing::Point(184, 24);
			//	pBPlot3[i]->Margin = System::Windows::Forms::Padding(2);
			//	pBPlot3[i]->TabStop = false;
			//	(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pBPlot3[i]))->EndInit();
			//}
			//
			//TODO: ここにコンストラクター コードを追加します
			//
	//			TKADCCONTROL* DL850;
	//			DL850 = new TKADCCONTROL;
	//			TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850)->Close();

			//Setting = Setting_;
			(*Setting)["Utility"]["TempPath"] = TKFILEUTIL::GetTemporaryPath("MCMS\\"_s);
			//DL750 = DL750_;
			//DL850 = DL850_;
			TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL750) = DL750_;
			TKADCINFO::ADCIDToTKADCPtr(TKADCINFO_ADC_ID_DL850) = DL850_;
			//thisShot = thisShot_;
			//thisPlot = thisPlot_;
			thisAnalyzeSP = new TKANALYZESP(thisShot, Setting, "AnalyzeSP");
			thisAnalyzeISP = new TKANALYZEISP(thisShot, Setting, "AnalyzeISP");


			Connection(true);
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

			webBrowser1->Navigate(to_SystemString((*Setting)["Utility"]["TempPath"] + "ytsummary.html"_s));
			webBrowser2->Navigate(to_SystemString((*Setting)["Utility"]["TempPath"] + "spsummary.html"_s));
			webBrowser3->Navigate(to_SystemString((*Setting)["Utility"]["TempPath"] + "ispsummary.html"_s));
			//webBrowser2->Navigate("C:/Users/ppl/Source/Repos/MCMS/UI/Project1/spsummary.html");
			//webBrowser3->Navigate("C:/Users/user/Source/Repos/MCMS/UI/Project1/ispsummary.html");

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
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
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
			this->toolStripContainer2 = (gcnew System::Windows::Forms::ToolStripContainer());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->webBrowser1 = (gcnew System::Windows::Forms::WebBrowser());
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
			this->webBrowser2 = (gcnew System::Windows::Forms::WebBrowser());
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
			this->webBrowser3 = (gcnew System::Windows::Forms::WebBrowser());
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
			this->toolStrip2 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButton8 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton9 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator6 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripButtonPrev = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonNext = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonGo = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator5 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripButtonStart = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonStop = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButtonSave = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripButton6 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton7 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripButton4 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton5 = (gcnew System::Windows::Forms::ToolStripButton());
			this->menuStrip1->SuspendLayout();
			this->toolStripContainer2->ContentPanel->SuspendLayout();
			this->toolStripContainer2->TopToolStripPanel->SuspendLayout();
			this->toolStripContainer2->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer2))->BeginInit();
			this->splitContainer2->Panel1->SuspendLayout();
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
			this->splitContainer3->Panel1->SuspendLayout();
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
			this->toolStrip2->SuspendLayout();
			this->SuspendLayout();
			// 
			// statusStrip1
			// 
			this->statusStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->statusStrip1->Location = System::Drawing::Point(0, 440);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Padding = System::Windows::Forms::Padding(1, 0, 10, 0);
			this->statusStrip1->Size = System::Drawing::Size(784, 22);
			this->statusStrip1->TabIndex = 2;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7)
			{
				this->faToolStripMenuItem,
					this->toolStripMenuItem1, this->ハードウェアToolStripMenuItem, this->グラフToolStripMenuItem, this->さようならToolStripMenuItem, this->toolStripTextBox1,
					this->toolStripMenuItem2
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(5, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(784, 29);
			this->menuStrip1->TabIndex = 7;
			this->menuStrip1->Text = L"menuStrip1";
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
			// 
			// 新規ToolStripMenuItem
			// 
			this->新規ToolStripMenuItem->Name = L"新規ToolStripMenuItem";
			this->新規ToolStripMenuItem->Size = System::Drawing::Size(172, 22);
			this->新規ToolStripMenuItem->Text = L"新規";
			// 
			// 開くToolStripMenuItem
			// 
			this->開くToolStripMenuItem->Name = L"開くToolStripMenuItem";
			this->開くToolStripMenuItem->Size = System::Drawing::Size(172, 22);
			this->開くToolStripMenuItem->Text = L"新しく開く";
			// 
			// 生データを追加ToolStripMenuItem
			// 
			this->生データを追加ToolStripMenuItem->Name = L"生データを追加ToolStripMenuItem";
			this->生データを追加ToolStripMenuItem->Size = System::Drawing::Size(172, 22);
			this->生データを追加ToolStripMenuItem->Text = L"追加で開く";
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
			// 
			// 計測開始ToolStripMenuItem
			// 
			this->計測開始ToolStripMenuItem->Name = L"計測開始ToolStripMenuItem";
			this->計測開始ToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->計測開始ToolStripMenuItem->Text = L"計測開始";
			// 
			// 計測停止ToolStripMenuItem
			// 
			this->計測停止ToolStripMenuItem->Name = L"計測停止ToolStripMenuItem";
			this->計測停止ToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->計測停止ToolStripMenuItem->Text = L"計測停止";
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
			this->計測器接続ToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"計測器接続ToolStripMenuItem.Image")));
			this->計測器接続ToolStripMenuItem->Name = L"計測器接続ToolStripMenuItem";
			this->計測器接続ToolStripMenuItem->Size = System::Drawing::Size(160, 22);
			this->計測器接続ToolStripMenuItem->Text = L"計測器接続";
			// 
			// 計測器切断
			// 
			this->計測器切断->Enabled = false;
			this->計測器切断->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"計測器切断.Image")));
			this->計測器切断->Name = L"計測器切断";
			this->計測器切断->Size = System::Drawing::Size(160, 22);
			this->計測器切断->Text = L"計測器切断";
			// 
			// 計測器接続設定ToolStripMenuItem
			// 
			this->計測器接続設定ToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"計測器接続設定ToolStripMenuItem.Image")));
			this->計測器接続設定ToolStripMenuItem->Name = L"計測器接続設定ToolStripMenuItem";
			this->計測器接続設定ToolStripMenuItem->Size = System::Drawing::Size(160, 22);
			this->計測器接続設定ToolStripMenuItem->Text = L"計測器接続設定";
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
			// 
			// グラフ設定ToolStripMenuItem
			// 
			this->グラフ設定ToolStripMenuItem->Name = L"グラフ設定ToolStripMenuItem";
			this->グラフ設定ToolStripMenuItem->Size = System::Drawing::Size(136, 22);
			this->グラフ設定ToolStripMenuItem->Text = L"グラフ設定";
			// 
			// さようならToolStripMenuItem
			// 
			this->さようならToolStripMenuItem->Name = L"さようならToolStripMenuItem";
			this->さようならToolStripMenuItem->Size = System::Drawing::Size(41, 25);
			this->さようならToolStripMenuItem->Text = L"bye";
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
			this->toolStripContainer2->ContentPanel->Margin = System::Windows::Forms::Padding(2);
			this->toolStripContainer2->ContentPanel->Size = System::Drawing::Size(784, 384);
			this->toolStripContainer2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->toolStripContainer2->Location = System::Drawing::Point(0, 29);
			this->toolStripContainer2->Margin = System::Windows::Forms::Padding(2);
			this->toolStripContainer2->Name = L"toolStripContainer2";
			this->toolStripContainer2->Size = System::Drawing::Size(784, 411);
			this->toolStripContainer2->TabIndex = 8;
			this->toolStripContainer2->Text = L"toolStripContainer2";
			// 
			// toolStripContainer2.TopToolStripPanel
			// 
			this->toolStripContainer2->TopToolStripPanel->Controls->Add(this->toolStrip2);
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Margin = System::Windows::Forms::Padding(2);
			this->tabControl1->Multiline = true;
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(784, 384);
			this->tabControl1->TabIndex = 3;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->splitContainer1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Margin = System::Windows::Forms::Padding(0);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Size = System::Drawing::Size(776, 358);
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
			this->splitContainer1->Panel1->Controls->Add(this->webBrowser1);
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
			this->splitContainer1->Size = System::Drawing::Size(776, 358);
			this->splitContainer1->SplitterDistance = 332;
			this->splitContainer1->SplitterWidth = 1;
			this->splitContainer1->TabIndex = 27;
			// 
			// webBrowser1
			// 
			this->webBrowser1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->webBrowser1->Location = System::Drawing::Point(0, 0);
			this->webBrowser1->MinimumSize = System::Drawing::Size(20, 20);
			this->webBrowser1->Name = L"webBrowser1";
			this->webBrowser1->Size = System::Drawing::Size(776, 332);
			this->webBrowser1->TabIndex = 0;
			// 
			// numericUpDown2
			// 
			this->numericUpDown2->Location = System::Drawing::Point(264, 13);
			this->numericUpDown2->Name = L"numericUpDown2";
			this->numericUpDown2->Size = System::Drawing::Size(48, 19);
			this->numericUpDown2->TabIndex = 9;
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
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(48, 13);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(23, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"<";
			this->button2->UseVisualStyleBackColor = true;
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
			this->tabPage2->Size = System::Drawing::Size(776, 358);
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
			this->splitContainer2->Panel1->Controls->Add(this->webBrowser2);
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
			this->splitContainer2->Size = System::Drawing::Size(776, 358);
			this->splitContainer2->SplitterDistance = 301;
			this->splitContainer2->SplitterWidth = 1;
			this->splitContainer2->TabIndex = 28;
			// 
			// webBrowser2
			// 
			this->webBrowser2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->webBrowser2->Location = System::Drawing::Point(0, 0);
			this->webBrowser2->MinimumSize = System::Drawing::Size(20, 20);
			this->webBrowser2->Name = L"webBrowser2";
			this->webBrowser2->Size = System::Drawing::Size(776, 301);
			this->webBrowser2->TabIndex = 0;
			// 
			// button11
			// 
			this->button11->Location = System::Drawing::Point(558, 19);
			this->button11->Margin = System::Windows::Forms::Padding(2);
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
			this->button10->Margin = System::Windows::Forms::Padding(2);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(56, 18);
			this->button10->TabIndex = 22;
			this->button10->Text = L"結果表示";
			this->button10->UseVisualStyleBackColor = true;
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(426, 19);
			this->button9->Margin = System::Windows::Forms::Padding(2);
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
			this->groupBox3->Margin = System::Windows::Forms::Padding(2);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Padding = System::Windows::Forms::Padding(2);
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
			this->groupBox2->Margin = System::Windows::Forms::Padding(2);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Padding = System::Windows::Forms::Padding(2);
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
			this->groupBox1->Margin = System::Windows::Forms::Padding(2);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(2);
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
			this->tabPage3->Size = System::Drawing::Size(776, 358);
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
			this->splitContainer3->Panel1->Controls->Add(this->webBrowser3);
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
			this->splitContainer3->Size = System::Drawing::Size(776, 358);
			this->splitContainer3->SplitterDistance = 301;
			this->splitContainer3->SplitterWidth = 1;
			this->splitContainer3->TabIndex = 29;
			// 
			// webBrowser3
			// 
			this->webBrowser3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->webBrowser3->Location = System::Drawing::Point(0, 0);
			this->webBrowser3->MinimumSize = System::Drawing::Size(20, 20);
			this->webBrowser3->Name = L"webBrowser3";
			this->webBrowser3->Size = System::Drawing::Size(776, 301);
			this->webBrowser3->TabIndex = 0;
			// 
			// button12
			// 
			this->button12->Location = System::Drawing::Point(558, 19);
			this->button12->Margin = System::Windows::Forms::Padding(2);
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
			this->button13->Margin = System::Windows::Forms::Padding(2);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(56, 18);
			this->button13->TabIndex = 22;
			this->button13->Text = L"結果表示";
			this->button13->UseVisualStyleBackColor = true;
			// 
			// button14
			// 
			this->button14->Location = System::Drawing::Point(426, 19);
			this->button14->Margin = System::Windows::Forms::Padding(2);
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
			this->groupBox4->Margin = System::Windows::Forms::Padding(2);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Padding = System::Windows::Forms::Padding(2);
			this->groupBox4->Size = System::Drawing::Size(126, 38);
			this->groupBox4->TabIndex = 20;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Electron Saturation";
			// 
			// numericUpDown9
			// 
			this->numericUpDown9->Enabled = false;
			this->numericUpDown9->Location = System::Drawing::Point(66, 13);
			this->numericUpDown9->Name = L"numericUpDown9";
			this->numericUpDown9->Size = System::Drawing::Size(48, 19);
			this->numericUpDown9->TabIndex = 15;
			// 
			// numericUpDown10
			// 
			this->numericUpDown10->Enabled = false;
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
			this->groupBox5->Margin = System::Windows::Forms::Padding(2);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Padding = System::Windows::Forms::Padding(2);
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
			this->groupBox6->Margin = System::Windows::Forms::Padding(2);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Padding = System::Windows::Forms::Padding(2);
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
			// toolStrip2
			// 
			this->toolStrip2->CanOverflow = false;
			this->toolStrip2->Dock = System::Windows::Forms::DockStyle::None;
			this->toolStrip2->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolStrip2->ImageScalingSize = System::Drawing::Size(20, 20);
			this->toolStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(16)
			{
				this->toolStripButton8,
					this->toolStripButton9, this->toolStripSeparator6, this->toolStripButtonPrev, this->toolStripButtonNext, this->toolStripButtonGo,
					this->toolStripSeparator5, this->toolStripButtonStart, this->toolStripButtonStop, this->toolStripButtonSave, this->toolStripSeparator3,
					this->toolStripButton6, this->toolStripButton7, this->toolStripSeparator4, this->toolStripButton4, this->toolStripButton5
			});
			this->toolStrip2->Location = System::Drawing::Point(3, 0);
			this->toolStrip2->Name = L"toolStrip2";
			this->toolStrip2->Size = System::Drawing::Size(662, 27);
			this->toolStrip2->TabIndex = 2;
			// 
			// toolStripButton8
			// 
			this->toolStripButton8->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton8->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton8.Image")));
			this->toolStripButton8->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton8->Name = L"toolStripButton8";
			this->toolStripButton8->Size = System::Drawing::Size(24, 24);
			this->toolStripButton8->Text = L"Open local file";
			this->toolStripButton8->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton8_Click);
			// 
			// toolStripButton9
			// 
			this->toolStripButton9->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton9->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton9.Image")));
			this->toolStripButton9->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton9->Name = L"toolStripButton9";
			this->toolStripButton9->Size = System::Drawing::Size(24, 24);
			this->toolStripButton9->Text = L"Open server file";
			this->toolStripButton9->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton9_Click);
			// 
			// toolStripSeparator6
			// 
			this->toolStripSeparator6->Name = L"toolStripSeparator6";
			this->toolStripSeparator6->Size = System::Drawing::Size(6, 27);
			// 
			// toolStripButtonPrev
			// 
			this->toolStripButtonPrev->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButtonPrev->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButtonPrev.Image")));
			this->toolStripButtonPrev->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonPrev->Name = L"toolStripButtonPrev";
			this->toolStripButtonPrev->Size = System::Drawing::Size(24, 24);
			this->toolStripButtonPrev->Text = L"Previous shot";
			this->toolStripButtonPrev->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton10_Click);
			// 
			// toolStripButtonNext
			// 
			this->toolStripButtonNext->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButtonNext->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButtonNext.Image")));
			this->toolStripButtonNext->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonNext->Name = L"toolStripButtonNext";
			this->toolStripButtonNext->Size = System::Drawing::Size(24, 24);
			this->toolStripButtonNext->Text = L"Next shot";
			this->toolStripButtonNext->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton11_Click);
			// 
			// toolStripButtonGo
			// 
			this->toolStripButtonGo->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButtonGo.Image")));
			this->toolStripButtonGo->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonGo->Name = L"toolStripButtonGo";
			this->toolStripButtonGo->Size = System::Drawing::Size(50, 24);
			this->toolStripButtonGo->Text = L"GO";
			this->toolStripButtonGo->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton12_Click);
			// 
			// toolStripSeparator5
			// 
			this->toolStripSeparator5->Name = L"toolStripSeparator5";
			this->toolStripSeparator5->Size = System::Drawing::Size(6, 27);
			// 
			// toolStripButtonStart
			// 
			this->toolStripButtonStart->Enabled = false;
			this->toolStripButtonStart->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButtonStart.Image")));
			this->toolStripButtonStart->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonStart->Name = L"toolStripButtonStart";
			this->toolStripButtonStart->Size = System::Drawing::Size(62, 24);
			this->toolStripButtonStart->Text = L"Start";
			this->toolStripButtonStart->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton1_Click);
			// 
			// toolStripButtonStop
			// 
			this->toolStripButtonStop->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButtonStop->Enabled = false;
			this->toolStripButtonStop->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButtonStop.Image")));
			this->toolStripButtonStop->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonStop->Name = L"toolStripButtonStop";
			this->toolStripButtonStop->Size = System::Drawing::Size(24, 24);
			this->toolStripButtonStop->Text = L"□Stop";
			this->toolStripButtonStop->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton2_Click);
			// 
			// toolStripButtonSave
			// 
			this->toolStripButtonSave->Enabled = false;
			this->toolStripButtonSave->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButtonSave.Image")));
			this->toolStripButtonSave->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButtonSave->Name = L"toolStripButtonSave";
			this->toolStripButtonSave->Size = System::Drawing::Size(61, 24);
			this->toolStripButtonSave->Text = L"Save";
			this->toolStripButtonSave->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton3_Click);
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(6, 27);
			// 
			// toolStripButton6
			// 
			this->toolStripButton6->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton6->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton6.Image")));
			this->toolStripButton6->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton6->Name = L"toolStripButton6";
			this->toolStripButton6->Size = System::Drawing::Size(34, 24);
			this->toolStripButton6->Text = L"Plot";
			this->toolStripButton6->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton6_Click);
			// 
			// toolStripButton7
			// 
			this->toolStripButton7->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton7->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton7.Image")));
			this->toolStripButton7->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton7->Name = L"toolStripButton7";
			this->toolStripButton7->Size = System::Drawing::Size(78, 24);
			this->toolStripButton7->Text = L"Plot setting";
			// 
			// toolStripSeparator4
			// 
			this->toolStripSeparator4->Name = L"toolStripSeparator4";
			this->toolStripSeparator4->Size = System::Drawing::Size(6, 27);
			// 
			// toolStripButton4
			// 
			this->toolStripButton4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton4.Image")));
			this->toolStripButton4->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton4->Name = L"toolStripButton4";
			this->toolStripButton4->Size = System::Drawing::Size(79, 24);
			this->toolStripButton4->Text = L"Connect";
			this->toolStripButton4->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton4_Click);
			// 
			// toolStripButton5
			// 
			this->toolStripButton5->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton5.Image")));
			this->toolStripButton5->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton5->Name = L"toolStripButton5";
			this->toolStripButton5->Size = System::Drawing::Size(120, 24);
			this->toolStripButton5->Text = L"Connection setting";
			this->toolStripButton5->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton5_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 462);
			this->Controls->Add(this->toolStripContainer2);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->statusStrip1);
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"MyForm";
			this->Text = L"DT-ALPHA MCMS";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->toolStripContainer2->ContentPanel->ResumeLayout(false);
			this->toolStripContainer2->TopToolStripPanel->ResumeLayout(false);
			this->toolStripContainer2->TopToolStripPanel->PerformLayout();
			this->toolStripContainer2->ResumeLayout(false);
			this->toolStripContainer2->PerformLayout();
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->tabPage2->ResumeLayout(false);
			this->splitContainer2->Panel1->ResumeLayout(false);
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
			this->splitContainer3->Panel1->ResumeLayout(false);
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
		if (!Connection(false))
			MessageBox::Show("Connect!");
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
		this->toolStripButtonStart->Enabled = false;
		this->toolStripButtonStop->Enabled = true;
		startMeasurement(this);
		this->toolStripButtonStart->Enabled = true;
		this->toolStripButtonStop->Enabled = false;
		this->toolStripButtonSave->Enabled = true;
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
		uploadToFileServer(getLastLocalFileName(TKADCINFO_ADC_ID_DL750) + ".WVF",
			"#" + TKUTIL::ZeroFill(TKSHOTNO::GetNextShotNumber(), 8)
			+ "_" + TKADCINFO::ADCIDToSectionName(TKADCINFO_ADC_ID_DL750) + ".WVF");
		uploadToFileServer(getLastLocalFileName(TKADCINFO_ADC_ID_DL750) + ".HDR",
			"#" + TKUTIL::ZeroFill(TKSHOTNO::GetNextShotNumber(), 8)
			+ "_" + TKADCINFO::ADCIDToSectionName(TKADCINFO_ADC_ID_DL750) + ".HDR");
		uploadToFileServer(getLastLocalFileName(TKADCINFO_ADC_ID_DL750) + ".CSV",
			"#" + TKUTIL::ZeroFill(TKSHOTNO::GetNextShotNumber(), 8)
			+ "_" + TKADCINFO::ADCIDToSectionName(TKADCINFO_ADC_ID_DL750) + ".CSV");
		uploadToFileServer(getLastLocalFileName(TKADCINFO_ADC_ID_DL850) + ".WDF",
			"#" + TKUTIL::ZeroFill(TKSHOTNO::GetNextShotNumber(), 8)
			+ "_" + TKADCINFO::ADCIDToSectionName(TKADCINFO_ADC_ID_DL850) + ".WDF");
		uploadToFileServer(getLastLocalFileName(TKADCINFO_ADC_ID_DL850) + ".CSV",
			"#" + TKUTIL::ZeroFill(TKSHOTNO::GetNextShotNumber(), 8)
			+ "_" + TKADCINFO::ADCIDToSectionName(TKADCINFO_ADC_ID_DL850) + ".CSV");
		uploadToFileServer(SETTING_FILE_PATH,
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
		plotRaw(TKSHOTNO::GetLastShotNumber(), true);
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
		//this->plotRaw(0, true);
		plotRaw(0, true);
		plotSP(0, true);
		plotISP(0, true);
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

	private:
		void openLocalFile(std::string file_path)
		{
			//TKADCINFO::ADCID adcid;
			std::vector<std::string> tok;

			clx::split_if(file_path, tok, clx::is_any_of("."));

			//for (int i = 0; i < static_cast<int>(thisShot->GetADCNumber()); i++)
			//	if (thisShot->GetADCID(i) == adcid)
			//		MessageBox::Show("このADCのデータは既に読み込まれています。", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);

			std::vector<std::string> file_list = TKFILEUTIL::GetSameShotFileName(file_path);
			thisShot->Clear();
			for (size_t i = 0; i < file_list.size(); i++)
				thisShot->AppendDataFile(TKFILEUTIL::RemoveExtension(file_list[i]));
			(*Setting)["Utility"]["LastFile"] = file_list[0];
		}

		std::vector<std::string> downloadShot(TKFILEUTIL::SHOTFILENAME shot_file_name)
		{
			std::vector<std::string> downloadFileList; // 先頭にはXMLが入るものとする
			std::string tmp_root = (*Setting)["Utility"]["TempPath"];

			// XMLをダウンロード
			try {
				downloadFileList.push_back(tmp_root + shot_file_name.GetShotName() + ".XML");
				// XMLは更新されている可能性があるのでスキップしない
				downloadFromFileServer(shot_file_name.GetShotName() + ".XML", downloadFileList.front());
			}
			catch (...) {
				std::cerr << "Download \"" << shot_file_name.GetShotName() + ".XML" << "\" failed." << std::endl;
				MessageBox::Show(gcnew System::String(("Open failed.\n"_s + "file: "_s + shot_file_name.GetShotName() + ".XML").c_str()));
				return downloadFileList;
			}


			// XMLをパース
			tinyxml2::XMLDocument xmlShotDoc;
			xmlShotDoc.LoadFile(downloadFileList.front().c_str());
			std::cerr << "Download \"" << shot_file_name.GetShotName() + ".XML" << "\" succeed." << std::endl;

			tinyxml2::XMLElement* xmlShotRoot = xmlShotDoc.FirstChildElement("Shot");


			// 関連する生データファイルをダウンロード
			try {
				for (tinyxml2::XMLElement* element
					= xmlShotRoot->FirstChildElement("ShotInformation")->FirstChildElement("RawData")->FirstChildElement();
					element != NULL; element = element->NextSiblingElement()) {
					downloadFileList.push_back(tmp_root + element->GetText());

					// 既にローカルに存在する場合はスキップ
					if (!TKUTIL::IsExistFile(downloadFileList.back())) {
						downloadFromFileServer(element->GetText(), downloadFileList.back());
						std::cerr << "Download \"" << element->GetText() << "\" succeed." << std::endl;
					} else {
						std::cerr << "Download \"" << element->GetText() << "\" skipped. (already exist)" << std::endl;
					}
				}
			}
			catch (...) {
				std::cerr << "Download \"" << TKFILEUTIL::SHOTFILENAME(downloadFileList.back()).GetFileNameWithExtension() << "\" failed." << std::endl;
				MessageBox::Show(gcnew System::String(("Open failed.\n"_s + "file: "_s + TKFILEUTIL::SHOTFILENAME(downloadFileList.back()).GetFileNameWithExtension()).c_str()));
				return downloadFileList;
			}

			return downloadFileList;
		}

		enum class RELATIVELY {
			PREVIOUS,
			NEXT
		};

		void openShot(RELATIVELY direction)
		{
			TKFILEUTIL::SHOTFILENAME current_shot_file((*Setting)["Utility"]["LastFile"]);



			//if (!TKUTIL::IsExistFile(current_shot_file.GetFilePath()))
			//	return;

			switch (direction) {
			case RELATIVELY::PREVIOUS:
				current_shot_file.ShotNumber()--;
				break;
			case RELATIVELY::NEXT:
				current_shot_file.ShotNumber()++;
				break;
			}

			if ((*Setting)["Utility"]["LastLocale"] == "FileServer")
				downloadShot(current_shot_file);

			if (!TKUTIL::IsExistFile(current_shot_file.GetFilePath()))
				return;

			openLocalFile(current_shot_file.GetFilePath());
		}

	private: System::Void 生データを追加ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		OpenFileDialog ^ openFileDialog1 = gcnew OpenFileDialog();
		openFileDialog1->Filter = "YOKOGAWA Binary (*.WVF, *.WDF)|*.WVF;*.WDF|DL750 Binary (*.WVF)|*.WVF|DL850 Binary (*.WDF)|*.WDF";
		openFileDialog1->Title = "Select a Binary File";
		openFileDialog1->Multiselect = false;

		if (openFileDialog1->ShowDialog() != System::Windows::Forms::DialogResult::OK)
			return;

		openLocalFile(TKUTIL::SystemStringToString(openFileDialog1->FileNames[0]));
		(*Setting)["Utility"]["LastLocale"] = "Local";
		plotRaw(0, true);
	}

	private: System::Void 開くToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		新規ToolStripMenuItem_Click(sender, e);
		生データを追加ToolStripMenuItem_Click(sender, e);
	}

	private: System::Void button11_Click(System::Object^  sender, System::EventArgs^  e)
	{
		SetupAnalyzeSP^ f = gcnew SetupAnalyzeSP(Setting, thisShot, "AnalyzeSP");
		f->ShowDialog();
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
		plotSP(0, true);
	}

	private: System::Void button12_Click(System::Object^  sender, System::EventArgs^  e)
	{
		SetupAnalyzeSP^ f = gcnew SetupAnalyzeSP(Setting, thisShot, "AnalyzeISP");
		f->ShowDialog();
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
		plotISP(0, true);
	}

		 /**
		 * @blief Tool > Open local file
		 *
		 *	ローカルファイルを開きます
		 */
	private: System::Void toolStripButton8_Click(System::Object^  sender, System::EventArgs^  e)
	{
		開くToolStripMenuItem_Click(sender, e);
	}
	private: System::Void toolStripButton10_Click(System::Object^  sender, System::EventArgs^  e)
	{
		openShot(RELATIVELY::PREVIOUS);
		plotRaw(0, false);
		plotSP(0, false);
		plotISP(0, false);
	}
	private: System::Void toolStripButton11_Click(System::Object^  sender, System::EventArgs^  e)
	{
		openShot(RELATIVELY::NEXT);
		plotRaw(0, false);
		plotSP(0, false);
		plotISP(0, false);
	}
	private: System::Void toolStripButton12_Click(System::Object^  sender, System::EventArgs^  e)
	{
		TKFILEUTIL::SHOTFILENAME shot_file_name((*Setting)["Utility"]["LastFile"]);

		DialogQuickLoadShot^ f = gcnew DialogQuickLoadShot(shot_file_name.ShotNumber(), 0,
			std::stoi((*Setting)["ShotNumber"]["LastShotNumber"]));

		if (f->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			if (TKUTIL::IsExistFile(shot_file_name.GetFilePath())) {
				openLocalFile(shot_file_name.GetFilePath());
				(*Setting)["Utility"]["LastLocale"] = "Local";
				plotRaw(0, false);
				plotSP(0, false);
				plotISP(0, false);
			} else {
				MessageBox::Show(gcnew System::String(("Open failed.\n"_s
					+ "path: "_s + shot_file_name.GetFilePath()).c_str()));
				開くToolStripMenuItem_Click(sender, e);
			}
	}

	private: System::Void toolStripButton9_Click(System::Object^  sender, System::EventArgs^  e)
	{
		TKFILEUTIL::SHOTFILENAME shot_file_name((*Setting)["Utility"]["LastFile"]);

		DialogQuickLoadShot^ f = gcnew DialogQuickLoadShot(shot_file_name.ShotNumber(), 0,
			std::stoi((*Setting)["ShotNumber"]["LastShotNumber"]));

		if (f->ShowDialog() == System::Windows::Forms::DialogResult::OK) {

			// open, プロット
			openLocalFile(downloadShot(shot_file_name)[1]);
			(*Setting)["Utility"]["LastLocale"] = "FileServer";
			plotRaw(0, false);
			plotSP(0, false);
			plotISP(0, false);
		}
	}
	};
}
#if 1
class exadcstart {
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


class exfunctor {
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
