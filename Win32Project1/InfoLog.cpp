#include "InfoLog.h"

InfoLog* InfoLog::globalInfoLog = new InfoLog;

std::string InfoLog::retriveErrorMsg(const std::string & description) {
	void *lpMsgBuf;
	int err = GetLastError();

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&lpMsgBuf, 0, NULL);

	std::ostringstream oss;
	oss << description << std::endl << std::endl << "Report of Failiour with Error Code "
		<< err << std::endl << "meaning: " << (char*)lpMsgBuf;

	return oss.str();
}

InfoLog::InfoLog()
{
}


InfoLog::~InfoLog()
{
}

void InfoLog::printError(const std::string & description) {
	MessageBox(NULL, description.c_str(), "ERROR", MB_OK); //TODO: Improve this MessageBoxes are boring
}

void InfoLog::printWindowsError(const std::string & description) {
	MessageBox(NULL, retriveErrorMsg(description).c_str(), "WINDOWS ERROR", MB_OK);
}
