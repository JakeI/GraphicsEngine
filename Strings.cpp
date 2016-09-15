#include "Strings.h"



Strings::Strings()
{
}


Strings::~Strings()
{
}

std::string Strings::stripQuotes(std::string const & s) {
	std::size_t first = s.find('"', 0);
	if (first == std::string::npos)  // no qoutes found
		return s;
	std::size_t second = s.find('"', first + 1);
	if (second == std::string::npos) // no second quote found
		second = s.size();
	return s.substr(first + 1, second - 1);
}

std::string Strings::pathInSameDir(std::string const & dirPath, std::string const & path) {
	
	std::string p(dirPath);
	replace(p.begin(), p.end(), '\\', '/');
	std::string dir = p.substr(0, findLastOf(p, '/'));
	return dir + '/' + path;
}

std::size_t Strings::findLastOf(std::string const & s, const char c) {
	
	std::size_t last = 0;
	{
		std::size_t next = 0;
		while (true) {
			next = s.find('/', next + 1);
			if (next == std::string::npos)
				return last;
			last = next;
		}
	}

	return std::string::npos;
}
