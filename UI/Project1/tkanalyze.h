/**
* @file
* @brief 解析に必要な基底クラスを提供します。
*	個々の解析手法に応じて派生させてください。
* @author Kobayashi Takahiko
* @date 2017
*/

#include "tkadc.h"
#include "tkadcinfo.h"
#include "tkshotinfo.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "clx/ini.h"
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <istream>
#include "clx/salgorithm.h"
#include "tkplot.h"
#include "tkutil.h"
#include "tkphysics.h"
#include <chrono>
#include <ctime>
#ifndef __TKANALYZE__
#define __TKANALYZE__

/**
* @class TKANALYZE
* @blief 解析クラス
*
*	解析を行うめの基底クラスです。<br>
*	静電計測法の解析に共通する基本計算、データ前処理、変数を提供します。<br>
* @par この基底クラスが作られた背景
*	SPとISPのデータ解析で共通する部分を基底クラス化しました。<br>
*	RFAやDP等の他の静電計測法の解析にも適用可能です。<br>
* @note
*	もし新たな静電計測器を追加し、解析コードを開発する場合はこの基底クラスを派生させてください。
*/
class TKANALYZE : public TKPLOT {
public:
	class FITRANGE {
	public:
		TKPLOT::RANGE<double> Iis;
		TKPLOT::RANGE<double> Ie;
		TKPLOT::RANGE<double> Ies;
	public:
		FITRANGE(TKPLOT::RANGE<double> Iis_, TKPLOT::RANGE<double> Ie_, TKPLOT::RANGE<double> Ies_)
			: Iis(Iis_), Ie(Ie_), Ies(Ies_)
		{
		}
		FITRANGE()
		{
		}
	};
	FITRANGE fitrange;

	/**
	* @enum PREDATAPROCESS
	* @blief データ前処理手法列挙型
	*
	*	データの前処理手法を区別するための型です。
	*/
	enum class PREDATAPROCESS {
		//! 生データを使用します
		Raw,
		//! 単純移動平均を行います
		SMA,
		//! 単純移動平均の後ヒステリシス除去処理を行います。掃引を\f$2\pi\f$以上の間行っている必要があります。\f$2\pi\f$を超える領域は無視されます。
		SMA_KH,
		//! 単純移動平均の後ヒステリシス除去処理を行い、さらに単純移動平均を行います。
		SMA_KH_SMA
	};


protected:
	TKSHOT* thisShot;
	clx::ini* Setting;
	std::string group;
	std::vector<PLOTINFO> plotInfo;
	std::string tmp_root;

	int ma_sample_number;

protected:
	/**
	* @fn calcSurfaceArea
	* @blief 粒子捕集面積を計算します。
	* @param[in] particle_type
	*	荷電粒子種を選択します。
	* @return
	*	計算結果を返します。
	* @note
	*	単位はmです。
	* @todo
	*	計算手法をPREDATAPROCESS同様enum化する。<br>
	*	引数が不適切であるので廃止してラッパ関数を用意する。
	*/
	double calcSurfaceArea(TKChargedParticleType particle_type)
	{
		double r = std::stod((*Setting)[group]["ProbeTipRadius"]);
		double l = std::stod((*Setting)[group]["ProbeTipLength"]);

		std::string prefix;
		switch (particle_type) {
		case TKChargedParticleType::electron:
			prefix = "Electron";
			break;
		case TKChargedParticleType::ion:
			prefix = "Ion";
			break;
		}
		if ((*Setting)[group][prefix + "CurrentCollectionSurfaceArea"] == "2rl")
			return 2 * r * l;
		else if ((*Setting)[group][prefix + "CurrentCollectionSurfaceArea"] == "4rl")
			return 4 * r * l;
		else if ((*Setting)[group][prefix + "CurrentCollectionSurfaceArea"] == "Cylinder")
			return 4 * M_PI * r * l + M_PI * r * r;
		else
			return std::stod((*Setting)[group][prefix + "CurrentCollectionSurfaceArea"]);
	}

public:
	TKANALYZE(TKSHOT* TKShot_, clx::ini* Setting_, std::string group_)
		: thisShot(TKShot_), Setting(Setting_), group(group_), TKPLOT(TKShot_, Setting_)
	{
		tmp_root = (*Setting)["Utility"]["TempPath"];
	}

	void SetMASampleNumber(int sample_number)
	{
		ma_sample_number = sample_number;
	}

	virtual int PlotAnalyzeSP(TKPLOT::PLOTSIZE plot_size, int shot_number, bool replot) = 0;

	std::vector<PLOTINFO> GetPlotInfo()
	{
		return plotInfo;
	}
	std::vector<TKPLOT::PLOTINFO>::pointer GetPlotInfoPtr()
	{
		return plotInfo.data();
	}
	FITRANGE &SetRange()
	{
		return fitrange;
	}

	double GetStartTime()
	{
		if ((*Setting)[group]["TimeRegion"] == "Auto") {
			double delay_cycle = std::stod((*Setting)[group]["FunctionDelayCycle"]);
			double delay_time = std::stod((*Setting)[group]["FunctionDelayTime"]);
			double frequency = std::stod((*Setting)[group]["FunctionFrequency"]);
			double sweep_cycle = std::stod((*Setting)[group]["FunctionSweepCycle"]);
			return delay_time + 1 / frequency*(delay_cycle);
		} else {
			return std::stod((*Setting)[group]["TimeRegionStart"]);
		}
	}
	double GetStopTime()
	{
		if ((*Setting)[group]["TimeRegion"] == "Auto") {
			double delay_cycle = std::stod((*Setting)[group]["FunctionDelayCycle"]);
			double delay_time = std::stod((*Setting)[group]["FunctionDelayTime"]);
			double frequency = std::stod((*Setting)[group]["FunctionFrequency"]);
			double sweep_cycle = std::stod((*Setting)[group]["FunctionSweepCycle"]);
			return delay_time + 1 / frequency*(delay_cycle + sweep_cycle);
		} else {
			return std::stod((*Setting)[group]["TimeRegionStop"]);
		}
	}

	unsigned int GetStartPoint(int adc_id)
	{
		if ((*Setting)[group]["TimeRegion"] == "Auto") {
			double delay_cycle = std::stod((*Setting)[group]["FunctionDelayCycle"]);
			double delay_time = std::stod((*Setting)[group]["FunctionDelayTime"]);
			double frequency = std::stod((*Setting)[group]["FunctionFrequency"]);
			double sweep_cycle = std::stod((*Setting)[group]["FunctionSweepCycle"]);
			return static_cast<unsigned int>((-thisShot->GetHOffset(adc_id) + delay_time + 1 / frequency*(delay_cycle)) / thisShot->GetHResolution(adc_id));
		} else {
			return static_cast<unsigned int>((-thisShot->GetHOffset(adc_id) + std::stod((*Setting)[group]["TimeRegionStart"])) / thisShot->GetHResolution(adc_id));
		}
	}

	unsigned int GetStopPoint(int adc_id)
	{
		if ((*Setting)[group]["TimeRegion"] == "Auto") {
			double delay_cycle = std::stod((*Setting)[group]["FunctionDelayCycle"]);
			double delay_time = std::stod((*Setting)[group]["FunctionDelayTime"]);
			double frequency = std::stod((*Setting)[group]["FunctionFrequency"]);
			double sweep_cycle = std::stod((*Setting)[group]["FunctionSweepCycle"]);
			return static_cast<unsigned int>((-thisShot->GetHOffset(adc_id) + delay_time + 1 / frequency*(delay_cycle + sweep_cycle)) / thisShot->GetHResolution(adc_id));
		} else {
			return static_cast<unsigned int>((-thisShot->GetHOffset(adc_id) + std::stod((*Setting)[group]["TimeRegionStop"])) / thisShot->GetHResolution(adc_id));
		}
	}

	unsigned int GetOneCycleStopPoint(int adc_id)
	{
		if ((*Setting)[group]["TimeRegion"] == "Auto") {
			double delay_cycle = std::stod((*Setting)[group]["FunctionDelayCycle"]);
			double delay_time = std::stod((*Setting)[group]["FunctionDelayTime"]);
			double frequency = std::stod((*Setting)[group]["FunctionFrequency"]);
			double sweep_cycle = std::stod((*Setting)[group]["FunctionSweepCycle"]);
			return static_cast<unsigned int>((1 / frequency) / thisShot->GetHResolution(adc_id));
		} else {
			return static_cast<unsigned int>((std::stod((*Setting)[group]["TimeRegionStop"]) - std::stod((*Setting)[group]["TimeRegionStart"])) / thisShot->GetHResolution(adc_id));
		}
	}

	PREDATAPROCESS GetPreDataProcessType()
	{
		PREDATAPROCESS pre_data_process;
		if ((*Setting)[group]["PreDataProcessing"] == "Raw")
			pre_data_process = PREDATAPROCESS::Raw;
		if ((*Setting)[group]["PreDataProcessing"] == "SMA")
			pre_data_process = PREDATAPROCESS::SMA;
		if ((*Setting)[group]["PreDataProcessing"] == "SMA+KillHysteresis")
			pre_data_process = PREDATAPROCESS::SMA_KH;
		if ((*Setting)[group]["PreDataProcessing"] == "SMA+KillHysteresis+SMA")
			pre_data_process = PREDATAPROCESS::SMA_KH_SMA;
		return pre_data_process;
	}

	std::string ExecPreDataProcess(int plot_info_index)
	{
		std::string source_file, out_file;

		int ma_sample[2];
		for (int i = 0; i < 2; i++)
			ma_sample[i] = std::stoi((*Setting)[group]["PreDataProcessingSMA" + std::to_string(i + 1) + "Sample"]);

		auto execSMA = [&](const std::string source_file, const int sample_index) {
			out_file = source_file + (std::string)"_SMA_" + std::to_string(ma_sample[sample_index]);
			if (!TKUTIL::IsExistFile(out_file + ".CSV"))
				std::system(((std::string)"MovingAverage.exe " + source_file + ".CSV "
					+ std::to_string(ma_sample[sample_index])
					+ " > " + out_file + ".CSV").c_str());
			return out_file;
		};

		auto execKH = [&](const std::string source_file) {
			out_file = source_file
				+ "_KH_" + std::to_string(GetStartPoint(thisShot->GetADCID(plotInfo[plot_info_index].data_index)))
				+ "_" + std::to_string(GetOneCycleStopPoint(thisShot->GetADCID(plotInfo[plot_info_index].data_index)))
				+ "_" + (*Setting)[group]["PreDataProcessingPhase"];
			if (!TKUTIL::IsExistFile(out_file + ".CSV"))
				std::system(((std::string)"TKKillHysteresis.exe " + source_file + ".CSV"
					+ " " + std::to_string(GetStartPoint(thisShot->GetADCID(plotInfo[plot_info_index].data_index)))
					+ " " + std::to_string(GetOneCycleStopPoint(thisShot->GetADCID(plotInfo[plot_info_index].data_index)))
					+ " " + (*Setting)[group]["PreDataProcessingPhase"]
					+ " > " + out_file + ".CSV").c_str());
			return out_file;
		};

		switch (GetPreDataProcessType()) {
		case PREDATAPROCESS::SMA:
			out_file = execSMA(thisShot->GetDataFileName(thisShot->GetADCID(plotInfo[plot_info_index].data_index)), 0);
			break;

		case PREDATAPROCESS::SMA_KH:
			out_file = execSMA(thisShot->GetDataFileName(thisShot->GetADCID(plotInfo[plot_info_index].data_index)), 0);
			out_file = execKH(out_file);
			break;

		case PREDATAPROCESS::SMA_KH_SMA:
			out_file = execSMA(thisShot->GetDataFileName(thisShot->GetADCID(plotInfo[plot_info_index].data_index)), 0);
			out_file = execKH(out_file);
			out_file = execSMA(out_file, 1);
			break;

		case PREDATAPROCESS::Raw:
		default:
			out_file = thisShot->GetDataFileName(thisShot->GetADCID(plotInfo[plot_info_index].data_index));
		}
		return out_file;
	}

	unsigned int GetBGStartPoint(int adc_id)
	{
		return static_cast<unsigned int>((-thisShot->GetHOffset(adc_id) + std::stod((*Setting)[group]["BGStart"])) / thisShot->GetHResolution(adc_id));
	}

	unsigned int GetBGStopPoint(int adc_id)
	{
		return static_cast<unsigned int>((-thisShot->GetHOffset(adc_id) + std::stod((*Setting)[group]["BGStop"])) / thisShot->GetHResolution(adc_id));
	}

	virtual void MakeHTML(std::string html_path) = 0;

protected:
	std::string getExtension()
	{
		return TKPLOT::getExtension(group);
	}

};
#endif