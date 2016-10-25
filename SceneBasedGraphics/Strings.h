#pragma once

#include <string>
#include <sstream>
#include <algorithm>

class Strings
{
public:
	Strings();
	~Strings();

	static std::string stripQuotes(std::string const & s);
	static std::string pathInSameDir(std::string const & dirPath, std::string const & path);
	static std::size_t findLastOf(std::string const & s, const char c);
};

