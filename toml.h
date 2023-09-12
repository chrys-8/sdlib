#pragma once

#include <optional>
#include <string_view>

enum TOMLDataType {
	TOML_NONE,
	TOML_INTEGER, TOML_STRING, TOML_FLOAT, TOML_BOOL,
	TOML_OFFDATETIME, TOML_LCLDATETIME, TOML_LCLDATE, TOML_LCLTIME,
	TOML_ARRAY
};

struct TOMLDateTime{
	unsigned int year, month, day, hour, minute, second, fraction = 0;
	int offsetHour = 0;
	unsigned int offsetMinute = 0;
};

union _TOMLValue {
	int _int;
	std::string_view _string;
	double _float;
	bool _bool;
	TOMLDateTime _datetime;
	struct _array {
		_TOMLValue* pBegin;
		std::size_t extent;
	};
};

struct TOMLKeyValue {
	std::string_view key;
	TOMLDataType valueType;
	_TOMLValue value;
};

std::optional<int>
TOML_integerValue(const TOMLKeyValue&);

std::optional<std::string_view>
TOML_stringValue(const TOMLKeyValue&);

std::optional<double>
TOML_floatValue(const TOMLKeyValue&);

std::optional<bool>
TOML_boolValue(const TOMLKeyValue&);

std::optional<TOMLDateTime>
TOML_datetimeValue(const TOMLKeyValue&);

class TOMLHashMap {
private:
	// use memory pool allocation
};

