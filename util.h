/*  sdlib/util_filesystem.h
 *  Filesystem utilities
 */
#pragma once

#include <fstream>
#include <string>

namespace sdlib {
  auto stream_get_line(
      std::basic_istream<char>& stream,
      std::string& str,
      char delim = '\n')
    -> std::basic_istream<char>&;

  auto stream_next_list(
      std::basic_istream<char>& stream,
      char delim = '\n')
    -> std::basic_istream<char>&;
}
