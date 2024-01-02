#pragma once
#include <string>


// type define
// int8 		-> char
// uint8 		-> unsigned char
// int16		-> short
// uint16		-> unsigned short
// int32		-> int
// uint32		-> unsigned int
// int64		-> long long
// uint64		-> unsigned long long
// string		-> std::wstring


class ConfigParser
{
public:
	class Section
	{
	public:
		void Emplace(std::wstring variableName, std::wstring variable)
		{
			m_ValueMap.emplace(std::make_pair(variableName, variable));
		}
		bool Remove(const std::wstring& variableName)
		{
			if (m_ValueMap.find(variableName) == m_ValueMap.end())
				return false;
			m_ValueMap.erase(variableName);
			return true;
		}

		bool Get(IN const std::wstring& key, OUT std::wstring& value)
		{
			auto foundIter = m_ValueMap.find(key);
			if (foundIter == m_ValueMap.end())
				return false;
			value = foundIter->second;
			return true;
		}

		bool Get(IN const std::wstring& key, OUT uint64& value)
		{
			std::wstring get;
			if (Get(key, get) == false)
				return false;
			for (const wchar_t c : get)
			{
				if (iswdigit(c) == false)
					return false;
			}
			value = _wtoi(get.c_str());
			return true;
		}
	private:
		// VariableName, pair<ValueString>
		HashMap<std::wstring, std::wstring> m_ValueMap;
	};
	using SectionPtr = shared_ptr<Section>;
	using UniqueSectionPtr = unique_ptr<HashMap<std::wstring, SectionPtr>>;

	ConfigParser() : m_Sections(nullptr), m_CurrentSection(nullptr) {};

	bool LoadConfig(const std::wstring& fileName);

	bool SetCurrentSection(const std::wstring& sectionName)
	{
		const auto foundSection = (*m_Sections)[sectionName];
		if(foundSection == nullptr)
			return false;

		m_CurrentSection = foundSection;
		return true;
	}

	bool Get(IN const std::wstring& key, OUT std::wstring& value)
	{
		if (m_CurrentSection == nullptr)
			return false;

		m_CurrentSection->Get(key, value);
	}
	bool Get(IN const std::wstring& key, OUT uint64& value)
	{
		if (m_CurrentSection == nullptr)
			return false;

		m_CurrentSection->Get(key, value);
		return true;
	}
	bool Get(IN const std::wstring& key, OUT uint32& value)
	{
		if (m_CurrentSection == nullptr)
			return false;
		uint64 ret;
		m_CurrentSection->Get(key, ret);
		value = static_cast<uint32>(ret);
		return true;
	}
	bool Get(IN const std::wstring& key, OUT uint16& value)
	{
		if (m_CurrentSection == nullptr)
			return false;
		uint64 ret;
		m_CurrentSection->Get(key, ret);
		value = static_cast<uint16>(ret);
		return true;
	}
private:
	bool FindSection(std::wfstream& file, OUT std::wstring& sectionName);
	bool GetSection(std::wfstream& file, OUT SectionPtr section);
private:
	// Section
	UniqueSectionPtr m_Sections;
	SectionPtr m_CurrentSection;

	bool m_FindError = false;
	uint32 m_ErrorRow = 0;
	wstring m_ErrorFileName;
};


using ConfigParserPtr = shared_ptr<ConfigParser>;