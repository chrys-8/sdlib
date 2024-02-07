#include "util_filesystem.h"

namespace sdlib {

  std::basic_istream<char>& stream_get_line(
      std::basic_istream<char>& stream,
      std::string& str,
      char delim)
  {
    str.erase();
    for (char c{}; stream.get(c); ) {
      if (c == delim)
        break;

      str += c;
    }

    return stream;
  }

  std::basic_istream<char>& stream_next_list(
      std::basic_istream<char>& stream,
      char delim)
  {
    for (char c{}; stream.get(c); )
      if (c == delim)
        break;

    return stream;
  }

}
