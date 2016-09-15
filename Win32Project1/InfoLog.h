#pragma once

#include "StdAfx.h"

class InfoLog {
private:

	static std::string retriveErrorMsg(const std::string & description);

public:

	InfoLog();
	~InfoLog();

	void printError(const std::string & description);
	void printWindowsError(const std::string & description);

	static InfoLog* globalInfoLog;
};

#define ilog (InfoLog::globalInfoLog)

