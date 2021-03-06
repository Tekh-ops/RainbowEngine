#pragma once


#include <string>

#include "Debug/API/Export.h"

namespace Debug
{
	/**
	* Some log levels
	* ��־����
	*/
	enum class ELogLevel
	{
		LOG_DEFAULT,
		LOG_INFO,
		LOG_WARNING,
		LOG_ERROR
	};

	/**
	* Some log modes (Indicates the handler to use)
	* ��־��ģʽ
	*/
	enum class ELogMode
	{
		DEFAULT,
		CONSOLE,
		FILE,
		HISTORY,
		ALL
	};

	/**
	* Store the log information
	* ��־��Ϣ
	*/
	struct LogData
	{
		std::string message;
		ELogLevel logLevel;
		std::string date;
	};

	/*
	* Treat the log in a certain way (Defined by children)
	* ��־����ӿ�
	*/
	class API_DEBUG ILogHandler
	{
		friend class Logger;

	private:
		/**
		* Log the the handler
		* @param p_logData
		*/
		virtual void Log(const LogData& p_logData) = 0;
	};
}