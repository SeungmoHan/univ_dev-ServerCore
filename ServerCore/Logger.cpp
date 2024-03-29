﻿#include "pch.h"
#include "Logger.h"
#include <fstream>

#include "ThreadManager.h"

void Logger::PushLog(const wchar_t* format, ...)
{
	va_list args;
	va_start(args, format);


	wchar_t tempBuffer[1024];
	int length = vswprintf_s(tempBuffer, format, args);
	wcout << tempBuffer << endl;
	{
		WRITE_LOCK;
		m_LogBuffer.emplace_back(tempBuffer);
	}
	va_end(args);
}

void Logger::Flush()
{
	vector<wstring> tempBuffer;
	{
		WRITE_LOCK;
		tempBuffer = std::move(m_LogBuffer);
		m_LogBuffer.clear();
	}
	wfstream fs(m_LogFilePath, ios_base::app);

	for(auto& str : tempBuffer)
	{
		fs << str << endl;
	}
}



void Logger::RunLogger()
{
	m_RunningFlag = true;
	g_ThreadManager->Launch([]() { LoggerWorker(); });
	std::thread t(LoggerWorker);
}

void Logger::LoggerWorker()
{
	while (g_Logger->m_RunningFlag)
		g_Logger->Flush();
}
