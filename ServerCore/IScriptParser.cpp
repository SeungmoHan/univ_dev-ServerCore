#include "pch.h"
#include "IScriptParser.h"
#include <fstream>
#include <sstream>
#include <string>


bool IScriptParser::ReadColumnName(std::wfstream& file)
{
	if (file.is_open() == false)
		return false;

	wstring line;
	bool isReadAll = false;
	while(std::getline(file, line) && isReadAll == false)
	{
		// 林籍贸府
		if (line._Starts_with(L"//") || line._Starts_with(L"--"))
			continue;
		wstringstream stream(line);
		wstring word;
		while(stream >> word)
		{
			ASSERT_CRASH(m_RawData.find(word) == m_RawData.end());
			Vector<wstring> newVector{};
			m_RawData.emplace(make_pair(word, newVector));
			m_ColumnNames.push_back(word);
		}
		isReadAll = true;
	}
	return isReadAll;
}

bool IScriptParser::ReadColumn(std::wfstream& file)
{
	if (file.is_open() == false)
		return false;

	wstring line;
	while (std::getline(file, line))
	{
		// 林籍贸府
		if (line._Starts_with(L"//") || line._Starts_with(L"--"))
			continue;
		wstringstream stream(line);
		wstring word;
		uint32 curCounts = 0;
		while (stream >> word)
		{
			ASSERT_CRASH(!word.empty());
			m_RawData[m_ColumnNames[curCounts]].push_back(word);
			curCounts++;
		}
		cout << endl;
	}
	return true;
}



bool IScriptParser::LoadFile(const std::wstring& fileName)
{
	std::wfstream file(FILE_PATH + fileName);
	if(file.is_open() == false)
		return false;

	// HashMap吝 ColumnName 盲快绰 何盒
	if (ReadColumnName(file) == false)
		return false;
	if (ReadColumn(file) == false)
		return false;

	m_FileName.assign(fileName.begin(), fileName.end());
	m_ReadCompletedFlag = true;

	return m_ReadCompletedFlag;
}

bool IScriptParser::Get_string(const wstring& key, const uint32 row, wstring& data)
{
	if (!FindData(key))
		return false;

	data = m_RawData.find(key)->second[row];
	return true;
}

bool IScriptParser::Get_uint32(const wstring& key, const uint32 row, uint32& data)
{
	uint64 tempData;
	if (!Get_uint64(key, row, tempData))
		return false;
	data = static_cast<uint32>(tempData);
	return true;
}

bool IScriptParser::Get_int32(const wstring& key, const uint32 row, int32& data)
{
	int64 tempData;
	if (!Get_int64(key, row, tempData))
		return false;
	data = static_cast<int32>(tempData);
	return true;
}

bool IScriptParser::Get_int64(const wstring& key, const uint32 row, int64& data)
{
	if (!FindData(key))
		return false;
	const wstring& tempStr = m_RawData.find(key)->second[row];
	if (IsNumber(tempStr) == false)
		return false;

	data = std::stoll(tempStr);
	return true;
}

bool IScriptParser::Get_uint64(const wstring& key, const uint32 row, uint64& data)
{
	if (!FindData(key))
		return false;
	const wstring& tempStr = m_RawData.find(key)->second[row];
	if (IsNumber(tempStr) == false)
		return false;

	data = std::stoll(tempStr);
	return true;
}


bool IScriptParser::FindData(const wstring& key)
{
	if (m_RawData.empty())
		return false;
	if (m_RawData.find(key) == m_RawData.end())
		return false;
	return true;
}

