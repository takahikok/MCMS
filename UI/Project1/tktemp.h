#pragma once
#include <iostream>
#include <locale> 
#include <codecvt> 
#include <cstdio>	
#include <direct.h>
#include <string>
#include "windows.h"

namespace TKFILEUTIL {
	std::string GetTemporaryPath(std::string const project_directry = "");
}
