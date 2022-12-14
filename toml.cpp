#include "toml.h"

#include <locale>
#include <string>
#include <utility>

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

// PARSING FUNCTIONS
static constexpr const std::string PREFIX_HEX = "0x";
static constexpr const std::string PREFIX_OCT = "0x";
static constexpr const std::string PREFIX_BIN = "0b";

std::string toLower(const std::string &value) {
	auto lower = std::string{};
	for (auto ch : value)
		lower.append(std::tolower(ch, std::locale()));

	return lower;
}

std::pair<bool, long> parseDecimalInteger(const std::string &value) {
}

std::pair<bool, long> parseHexInteger(const std::string &value) {
}

std::pair<bool, long> parseOctalInteger(const std::string &value) {
}

std::pair<bool, long> parseBinaryInteger(const std::string &value) {
}

std::pair<bool, long> parseInteger(const std::string &value) {
	auto prefix = toLower(value.substr(0, 2));
	if (prefix == PREFIX_HEX) {

	}
	else if (prefix == PREFIX_OCT) {

	}
	else if (prefix == PREFIX_BIN) {

	}
	else {

	}
}

std::pair<bool, std::string> parseLiteralString(const std::string &value) {
	auto literal = std::string{};
	for (auto it = value.begin(); it != value.end(); it++) {
		// all escape sequences are broken
		// TODO optimize
		literal.append(*it);
		if (*it == '\'') literal.append(*it);
	}

	return { true, literal };
}

/*		Accepted escape sequences
 *	\b         - backspace       (U+0008)
 *	\t         - tab             (U+0009)
 *	\n         - linefeed        (U+000A)
 *	\f         - form feed       (U+000C)
 *	\r         - carriage return (U+000D)
 *	\"         - quote           (U+0022)
 *	\\         - backslash       (U+005C)
 *	\uXXXX     - unicode         (U+XXXX)
 *	\UXXXXXXXX - unicode         (U+XXXXXXXX)
 */

std::pair<bool, std::string> parseString(std::string value) {
}

std::pair<bool, double> parseFloat(std::string value) {
}

static constexpr const std::string TRUE_STRING = "true";
static constexpr const std::string FALSE_STRING = "false";

std::pair<bool, bool> parseBoolean(std::string value) {
	if (value == TRUE_STRING) return { true, true };
	if (value == FALSE_STRING) return { true, false };
	return { false, false };
}

// Taken from RFC3339: https://www.rfc-editor.org/rfc/rfc3339
bool isLeapYear(unsigned short year) {
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 1));
}

std::pair<bool, TOMLDateTime> parseDateTime(std::string value) {
}

void parseKeyValuePair(std::string key, std::string value) {
	// parse value as object, yielding its buffer offset
	// detect string
}

