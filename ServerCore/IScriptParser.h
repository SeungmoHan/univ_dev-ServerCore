#pragma once

class IScriptParser
{
private:
	inline static const wstring FILE_PATH = 
				L"C:\\Users\\user\\Desktop\\Education\\Portfolio\\GameServer\\Server\\Binary\\Release\\";
public:
	virtual ~IScriptParser() = default;

protected:
	bool LoadFile(const wstring& fileName);

	bool Get_string (const wstring& key, const uint32 row, OUT wstring& data);
	bool Get_uint32 (const wstring& key, const uint32 row, OUT uint32& data);
	bool Get_int32  (const wstring& key, const uint32 row, OUT int32& data);
	bool Get_int64  (const wstring& key, const uint32 row, OUT int64& data);
	bool Get_uint64 (const wstring& key, const uint32 row, OUT uint64& data);
	uint32 GetRowCounts() const { return static_cast<uint32>(m_RawData.size()); }

private:
	bool FindData(const wstring& key);
	bool IsNumber(const wstring& numString) const {
		return std::all_of(numString.begin(), numString.end(), ::isdigit);
	}

	bool ReadColumnName(std::wfstream& file);
	bool ReadColumn(std::wfstream& file);
protected:
	//	 ColumnName,Datas
	Vector<wstring> m_ColumnNames;
	HashMap<wstring,Vector<wstring>> m_RawData;
	std::wstring m_FileName;
	bool m_ReadCompletedFlag = false;
};

using IScriptParserPtr = shared_ptr<IScriptParser>;