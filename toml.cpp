#include "toml.h"

// TODO test returing values (these are just here for completeness atm)

std::optional<int> TOML_integerValue(const TOMLKeyValue& keyvalue)
{
	if (keyvalue.valueType == TOML_INTEGER)
		return { keyvalue.value._int };

	return {};
}

std::optional<std::string_view> TOML_stringValue(const TOMLKeyValue& keyvalue)
{
	if (keyvalue.valueType == TOML_STRING)
		return { keyvalue.value._string };

	return {};
}

std::optional<double> TOML_floatValue(const TOMLKeyValue& keyvalue)
{
	if (keyvalue.valueType == TOML_FLOAT)
		return { keyvalue.value._float };

	return {};
}

std::optional<bool> TOML_boolValue(const TOMLKeyValue& keyvalue)
{
	if (keyvalue.valueType == TOML_BOOL)
		return { keyvalue.value._bool };

	return {};
}

std::optional<TOMLDateTime> TOML_datetimeValue(const TOMLKeyValue& keyvalue)
{
	if (keyvalue.valueType == TOML_OFFDATETIME)
		return { keyvalue.value._datetime };

	if (keyvalue.valueType == TOML_LCLDATETIME)
		return { keyvalue.value._datetime };

	if (keyvalue.valueType == TOML_LCLDATE)
		return { keyvalue.value._datetime };

	if (keyvalue.valueType == TOML_LCLTIME)
		return { keyvalue.value._datetime };

	return {};
}

