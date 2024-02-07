/*  sdlib/toml.h
 *  Specific to TOML parsing
 */
#pragma once

#include <optional>
#include <string_view>

namespace sdlib {

  enum TOMLDataType {
    TOML_NONE,
    TOML_INTEGER, TOML_STRING, TOML_FLOAT, TOML_BOOL,
    TOML_OFFDATETIME, TOML_LCLDATETIME, TOML_LCLDATE, TOML_LCLTIME,
    TOML_ARRAY
  };

}

