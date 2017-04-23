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
#ifndef __TKANALYZE__
#define __TKANALYZE__

class TKANALYZE : public TKPLOT
{
public:
	class FITRANGE
	{
	public:
		TKPLOT::RANGE<double> Iis;
		TKPLOT::RANGE<double> Ie;
		TKPLOT::RANGE<double> Ies;
	public:
		FITRANGE(TKPLOT::RANGE<double> Iis_, TKPLOT::RANGE<double> Ie_, TKPLOT::RANGE<double> Ies_)
		{
			Iis = Iis_;
			Ie = Ie_;
			Ies = Ies_;
		}
		FITRANGE()
		{
		}
	};
	FITRANGE fitrange;

	enum class PREDATAPROCESSS
	{
		Raw,
		SMA,
		SMA_KH,
		SMA_KH_SMA
	};
	PREDATAPROCESSS pre_data_process;

protected:
	TKSHOT* thisShot;
	clx::ini* Setting;
	std::string group;
	std::vector<PLOTINFO> plotInfo;

	int ma_sample_number;

protected:
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
	TKANALYZE(TKSHOT* TKShot_, clx::ini* Setting_, std::string group_) : TKPLOT(TKShot_)
	{
		thisShot = TKShot_;
		Setting = Setting_;
		group = group_;
	}

	void SetMASampleNumber(int sample_number)
	{
		ma_sample_number = sample_number;
	}

	virtual int PlotAnalyzeSP(TKPLOT::PLOTSIZE plot_size, int shot_number) = 0;

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
};
#endif