#ifndef STRINGLIBRARY_H
#define STRINGLIBRARY_H

#include <string>
#include <algorithm>

namespace StringLibrary {
	inline std::string toLowerCase(const std::string& str) {
		std::string ans = str;
		std::for_each(ans.begin(), ans.end(), [](char& c) {
			c = ::tolower(c);
			});
		return ans;
	}
}

#endif