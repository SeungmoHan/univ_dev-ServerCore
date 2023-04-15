//#pragma once
//#include <string>
//
//// TODO TextFile로 빼낼거임
//enum class LoggerType
//{
//	NONE,
//	DEBUG_LOG,
//	WARNING_LOG,
//	ERROR_LOG,
//	MAX,
//	// 추가
//};
//
//enum class ServerType
//{
//	NONE,
//	DB_SERVER,
//	GAME_SERVER,
//	DUMMY_CLIENT,
//	MAX,
//};
//
//class LoggerManager
//{
//public:
//	static LoggerManager* Instance()
//	{
//		static auto instance = new LoggerManager();
//		return instance;
//	}
//	void Init();
//	void Clear();
//	void GetDirectory(OUT std::wstring& stringRet, const ServerType serverType = ServerType::NONE, const LoggerType loggerType = LoggerType::NONE)
//	{
//		stringRet = m_ServerTypeToPath[serverType] + m_LoggerTypeToPath[loggerType];
//	}
//
//	void BeginWrite(ServerType type);
//	void EndWrite(ServerType type);
//
//	class LoggerLockGuard
//	{
//		LoggerLockGuard(Lock& lock) : lock(lock){ lock.WriteLock("Log Lock"); }
//		~LoggerLockGuard() { lock.WriteUnlock("Log Lock"); }
//		Lock& lock;
//	};
//
//private:
//	LoggerManager();
//	~LoggerManager();
//
//
//
//	HashMap<LoggerType, std::wstring> m_LoggerTypeToPath;
//	HashMap<ServerType, std::wstring> m_ServerTypeToPath;
//	USE_MANY_LOCKS(static_cast<uint32>(ServerType::MAX))
//};
//
//class Logger
//{
//public:
//	explicit Logger(const ServerType serverType = ServerType::NONE, const LoggerType loggerType = LoggerType::NONE);
//	virtual ~Logger();
//
//	Logger& operator<<(const uint8 data);
//	Logger& operator<<(const uint16 data);
//	Logger& operator<<(const uint32 data);
//	Logger& operator<<(const uint64 data);
//
//	Logger& operator<<(const int8 data);
//	Logger& operator<<(const int16 data);
//	Logger& operator<<(const int32 data);
//	Logger& operator<<(const int64 data);
//
//	Logger& operator<<(const float data);
//	Logger& operator<<(const double data);
//
//	Logger& operator<<(const std::string& str);
//	Logger& operator<<(const std::wstring& str);
//
//protected:
//	static uint32 MakeDay_YYYYMMDD(IN const tm& t);
//	static uint32 MakeTime_HHMMSS(IN const tm& t);
//
//private:
//	
//	bool flush();
//	ServerType m_ServerType;
//	LoggerType m_LoggerType;
//	std::wstring m_LogData;
//	uint32 m_LogDay_YYYYMMDD;
//	uint32 m_LogTime_HHMMSS;
//};
//
