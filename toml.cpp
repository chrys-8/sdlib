#include "toml.h"

#include <locale>
#include <string>
#include <utility>

// Buffer storage
std::vector<long> &integerBuffer() {
	static std::vector<long> buffer;
	return buffer;
}

std::vector<std::string> &stringBuffer() {
	static std::vector<std::string> buffer;
	return buffer;
}

std::vector<double> &floatBuffer() {
	static std::vector<double> buffer;
	return buffer;
}

std::vector<bool> &booleanBuffer() {
	static std::vector<bool> buffer;
	return buffer;
}

std::vector<TOMLDateTime> &dateBuffer() {
	static std::vector<TOMLDateTime> buffer;
	return buffer;
}

