#pragma once
#include "SystemHead.h"
#include "tinyxml2/tinyxml2.h"
#include "GameProgress.h"
#include "csvLoadUtils/CsvUtil.h"

class MyUtils
{
public:
	static MyUtils*getInstence();
	void dumpXmlNode(tinyxml2::XMLElement *node, std::string prefix);
	tinyxml2::XMLDocument *ParseXML(char* xmlFilePath, tinyxml2::XMLDocument * xmlDoc);
	void SaveXml();
	tinyxml2::XMLElement *buildXmlNode(tinyxml2::XMLDocument *doc);
	/*
	��ȡ��ǰ�Ľ�������,�������ݶ�ȡ���� ��������;
	*/
	GameProgress* createProgressNow(int index);
private:
	~MyUtils();
	static MyUtils * ptr_only;
};

 