//// ReSharper disable CppClangTidyCertErr33C
#include "pch.h"
//#include "Logger.h"
//#include <fstream>
//
//LoggerManager::LoggerManager()
//{
//	Init();
//}
//
//LoggerManager::~LoggerManager()
//{
//	Clear();
//}
//
//void LoggerManager::Clear()
//{
//	m_ServerTypeToPath.clear();
//	m_LoggerTypeToPath.clear();
//}
//
//void LoggerManager::Init()
//{
//	Clear();
//	const std::wstring baseDir = L"../../Log";
//	m_ServerTypeToPath[ServerType::NONE] = baseDir + L"/Common";
//
//	m_ServerTypeToPath[ServerType::GAME_SERVER] = baseDir + L"/GameServer";
//	m_ServerTypeToPath[ServerType::DB_SERVER] = baseDir + L"/DBServer";
//
//	m_LoggerTypeToPath[LoggerType::NONE] = L"/Default";
//	m_LoggerTypeToPath[LoggerType::DEBUG_LOG] = L"/Debug";
//	m_LoggerTypeToPath[LoggerType::ERROR_LOG] = L"/Error";
//	m_LoggerTypeToPath[LoggerType::WARNING_LOG] = L"/Warning";
//
//
//	_wmkdir(baseDir.c_str());
//	for (const auto& [serverType, serverString] : m_ServerTypeToPath)
//	{
//		_wmkdir(serverString.c_str());
//		for (auto& [logType, typeString] : m_LoggerTypeToPath)
//		{
//			if (typeString.empty()) continue;
//			_wmkdir((serverString + typeString).c_str());
//		}
//	}
//}
//
//Logger::Logger(const ServerType serverType, const LoggerType loggerType)
//	:m_ServerType(serverType), m_LoggerType(loggerType)
//{
//	//TODO Log Directory�� �ִµ� FileNAme�� ���,,,
//	tm tempDateTime{};
//	const time_t curTime = time(nullptr);
//	localtime_s(&tempDateTime, &curTime);
//	m_LogDay_YYYYMMDD = MakeDay_YYYYMMDD(tempDateTime);
//	m_LogTime_HHMMSS = MakeTime_HHMMSS(tempDateTime);
//
//	m_LogData += std::to_wstring(m_LogTime_HHMMSS) + L" : ";
//}
//
//Logger::~Logger()
//{
//	if(!flush())
//		std::cout << "File Log Failed" << endl;
//	return;
//}
//
//#pragma region <<OPERATOR
//auto Logger::operator<<(const uint8 data) -> Logger&
//{
//	m_LogData += std::to_wstring(data);
//	return *this;
//}
//
//auto Logger::operator<<(const uint16 data) -> Logger&
//{
//	m_LogData += std::to_wstring(data);
//	return *this;
//}
//
//auto Logger::operator<<(const uint32 data) -> Logger&
//{
//	m_LogData += std::to_wstring(data);
//	return *this;
//}
//
//auto Logger::operator<<(const uint64 data) -> Logger&
//{
//	m_LogData += std::to_wstring(data);
//	return *this;
//}
//
//auto Logger::operator<<(const int8 data) ->Logger&
//{
//	m_LogData += std::to_wstring(data);
//	return *this;
//}
//
//auto Logger::operator<<(const int16 data) ->Logger&
//{
//	m_LogData += std::to_wstring(data);
//	return *this;
//}
//
//auto Logger::operator<<(const int32 data) ->Logger&
//{
//	m_LogData += std::to_wstring(data);
//	return *this;
//}
//
//auto Logger::operator<<(const int64 data) ->Logger&
//{
//	m_LogData += std::to_wstring(data);
//	return *this;
//}
//
//auto Logger::operator<<(const float data) ->Logger&
//{
//	m_LogData += std::to_wstring(data);
//	return *this;
//}
//
//auto Logger::operator<<(const double data) ->Logger&
//{
//	m_LogData += std::to_wstring(data);
//	return *this;
//}
//
//auto Logger::operator<<(const std::string& str) ->Logger&
//{
//	std::wstring temp;
//	temp.assign(str.begin(), str.end());
//	m_LogData += temp;
//	return *this;
//}
//
//auto Logger::operator<<(const std::wstring& str) ->Logger&
//{
//	m_LogData += str;
//	return *this;
//}
//#pragma endregion
//
//uint32 Logger::MakeDay_YYYYMMDD(const tm& t)
//{
//	return	(t.tm_year + 1900) * 10000 + 
//			(t.tm_mon + 1) * 100 + 
//			(t.tm_mday);
//}
//
//uint32 Logger::MakeTime_HHMMSS(const tm& t)
//{
//	return	(t.tm_hour * 10000) +
//			(t.tm_min * 100) +
//			(t.tm_sec);
//}
//
//bool Logger::flush()
//{
//
//	std::wstring fileDir;
//	m_LogData += L"\n";
//	LoggerManager::Instance()->GetDirectory(OUT fileDir, m_ServerType, m_LoggerType);
//
//	// �α� �ۼ��� ������ �α� �Ŵ������� �α� �ۼ��� ��û�Ѵ�.
//	// �׷��� ó���ϸ� �α׾ȿ� �ִ� WRITE_LOCK_IDX�� �����Ӱ� ��� ������
//	// param ����
//	//	�α� ��¥, �α� �ð�, ���� Ÿ��, �α� Ÿ��, �α� ������ ����
//	//LoggerManager::Instance()->WriteLog(m_ServerType, m_LoggerType, m_LogData);
//	//LOG_YYMMDD_HHMMSS
//	const std::wstring fileName = L"/" + std::to_wstring(m_LogDay_YYYYMMDD) + L"_LOG.txt";
//
//	/*
//	 * TODO
//	 * file��ü�� �ٸ� ������ ����ϸ� ��� �Ұ����̶� �ϴ� ����ȭ ��ü�� �ɸ��ٵ�...
//	 * 3000�� ũ���ð� �ɷ��� ���ÿ� �ʹ����� write�� �ɸ��� ũ���ð� ����������...
//	 *
//	 * �α� ���� �� �б� ���� ���Ŵ°� ����� �غ����ҵ�...
//	 * �� �ϳ��� �ٰ��� ���°� ���� �����ȵ�...
//	*/
//	FILE* file = nullptr;
//	uint16 tryCount = 0;
//	while (file == nullptr)
//	{
//		_wfopen_s(&file, (fileDir + fileName).c_str(), L"ab");
//		if(tryCount++ > 3000)
//			CRASH("FileDir OpenCount Over 3000");
//	}
//	fwrite(m_LogData.c_str(), m_LogData.length() * sizeof(wchar_t), 1, file);
//	fclose(file);
//
//	return true;
//}
