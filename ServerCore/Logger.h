#pragma once



class Logger
{
public:
	// Logger 전용 쓰레드 하나 파고 콘텐츠에서는 푸쉬만 하고 이벤트만 주자...
	// 그러면 로거 쓰레드가 깨어나서 그때까지 쌓여있던 로그 처리,,, 혹은 n초마다 한번씩 해도좋고,,,
	// 로거 워커들이 호출할 함수들
	static void LoggerWorker();
	void Flush();

	// 로거 워커가 아닌 쓰레드가 호출할 함수
	void RunLogger();
	void PushLog(const wchar_t* format, ...);

	Logger() = default;

private:
	bool m_RunningFlag = false;
	vector<wstring> m_LogBuffer;
	wstring m_LogFilePath;
	USE_LOCK
};




