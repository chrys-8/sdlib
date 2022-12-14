#pragma once

#include <string>
#include <utility>

static constexpr TOML_STATIC_BUFFER_CAPACITY = 128;

enum TOMLObjectTypeID {
	TOMLInteger, TOMLString, TOMLFloat, TOMLBoolean,
	TOML_OFFDATETIME TOML_LCLDATETIME, TOML_LCLDATE, TOML_LCLTIME,
	TOMLTable
};

struct TOMLDateTime{
	unsigned short year, month, day, hour, minute, second, fraction = 0;
	short offsetHour = 0;
	unsigned short offsetMinute = 0;
};

// size of TOMLObject is 40 bytes
struct TOMLObject {
	union _data {
		long intData;				// default
		std::string stringData;
		double floatData;
		bool boolData;
		TOMLDateTime datetimeDate;

		~_data() {} // required for data.~basic_string
	};

	_data data { 0 };
	TOMLObjectTypeID typeId = TOMLInteger;
};

struct TOMLKey {
	std::string id;
	TOMLObjectTypeID typeId;
	std::pair<size_t, size_t> offset;
};

