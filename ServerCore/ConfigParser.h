#pragma once


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
	private:
		// VariableName, pair<ValueString>
		HashMap<std::wstring, std::wstring> m_ValueMap;
	};
	using SectionRef = shared_ptr<Section>;
	using UniqueSectionRef = unique_ptr<HashMap<std::wstring, SectionRef>>;


	bool LoadConfig(const std::wstring& fileName);

private:
	bool FindSection(std::wfstream& file, OUT std::wstring& sectionName);
	bool GetSection(std::wfstream& file, OUT SectionRef section);
private:
	// Section
	UniqueSectionRef m_Sections;
};
