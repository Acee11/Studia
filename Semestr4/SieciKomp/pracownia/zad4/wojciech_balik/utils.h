// Wojciech Balik
// 280254

#ifndef UTILS_H_
#define UTILS_H_

#include <map>
#include <stddef.h>
#include <sys/stat.h>
#include <memory>

namespace utils
{

	bool endOfHttpMsg(const std::unique_ptr<char[]>& buffer, size_t readBytes);
	bool isSafe(const std::string& path);
	bool isCatalog(const std::string& path);
	std::string getErrorPhrase(int errNumber);
	
	std::string getMime(const std::string& path);
	const std::map<std::string, std::string> mimeTranslator = {
		{"html", "text/html"},
		{"css", "text/css"},
		{"txt", "text/plain"},
		{"jpg", "image/jpeg"},
		{"jpeg", "image/jpeg"},
		{"png", "image/png"},
		{"pdf", "application/pdf"}
	};

}

#endif