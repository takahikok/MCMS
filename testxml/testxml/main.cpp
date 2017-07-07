#include <iostream>
#include <string>
#include "tinyxml2.h"

int main()
{

	tinyxml2::XMLDocument xmlShotDoc;
	xmlShotDoc.LoadFile("test.xml");

	tinyxml2::XMLElement* xmlShotRoot = xmlShotDoc.FirstChildElement("Shot");
	std::cout << xmlShotRoot->Attribute("ShotNumber") << std::endl;

	for (tinyxml2::XMLElement* element
		= xmlShotRoot->FirstChildElement("ShotInformation")->FirstChildElement("RawData")->FirstChildElement();
		element != NULL; element = element->NextSiblingElement()) {
		std::cout << static_cast<std::string>(element->GetText()) << std::endl;
	}

	return 0;
}
