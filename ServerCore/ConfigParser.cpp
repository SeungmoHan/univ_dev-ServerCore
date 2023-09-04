#include "pch.h"
#include "ConfigParser.h"
#include <fstream>
#include <sstream>
#include <string>


bool ConfigParser::LoadConfig(const std::wstring& fileName)
{
	std::wfstream file(fileName);
	if (!file.is_open())
		return false;
	auto tempSections = std::make_unique<HashMap<std::wstring, SectionRef>>();

	while(true)
	{
		std::wstring sectionName;
		if (FindSection(file, sectionName) == false)
			break;

		auto newSection = std::make_shared<Section>();
		

		if (GetSection(file, newSection) == false)
		{
			newSection = nullptr;
			continue;
		}
		tempSections->emplace(make_pair(sectionName, newSection));
	}

	if (tempSections->empty())
		return false;

	m_Sections = std::move(tempSections);
	return true;
}

bool ConfigParser::FindSection(std::wfstream& file, OUT std::wstring& sectionName)
{
	sectionName.clear();
	std::wstring line;
	while (getline(file, line))
	{
		// 주석처리
		if (line._Starts_with(L"--") || line._Starts_with(L"//"))
			continue;
		// 섹션이 아니면 건너뜀
		if (line._Starts_with(L"!") == false)
			continue;
		line.erase(line.begin());

		std::wstringstream ss(line);
		std::wstring tempName;
		bool canSectionName = true;
		ss >> tempName;
		for (const auto c : tempName)
		{
			if (isalpha(c) || isdigit(c) || c == L'_')
				continue;
			canSectionName = false;
			break;
		}
		if (!canSectionName)
			continue;
		sectionName = line;
		break;
	}

	return !sectionName.empty();
}

bool ConfigParser::GetSection(std::wfstream& file, SectionRef section)
{
	//	Vector<string>
	//	[0] = VariableName, 
	//	[1] = equal, 
	//	[2] = Value

	auto openSuccess = false;
	auto closeSucess = false;

	std::wstring line;
	while(true)
	{
		if (!getline(file, line))
			break;
		// 주석
		if(line._Starts_with(L"//") || line._Starts_with(L"--"))
			continue;
		// 시작처리
		if(line[0] == L'}')
		{
			closeSucess = true;
			break;
		}
		// 끝처리
		if(line[0] == L'{')
		{
			openSuccess = true;
			continue;
		}
		// 여기부턴 실질적인 variable들
		wstringstream ss(line);

		wstring variableName, _, variable;
		ss >> variableName >> _ >> variable;

		section->Emplace(variableName, variable);
	}


	return openSuccess && closeSucess;
}
