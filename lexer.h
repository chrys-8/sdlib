/*  sdlib/toml_lexer/h
 *  Lexer for parsing TOML
 */
#pragma once

#include <string>
#include <vector>
#include <utility>

// TODO: refactor name of constant
#ifndef SDLIB_FILEBUFFER_CAPACITY
static constexpr const size_t SDLIB_FILEBUFFER_CAPACITY_VALUE = 512;
#else
static constexpr const size_t SDLIB_FILEBUFFER_CAPACITY_VALUE = SDLIB_FILEBUFFER_CAPACITY;
#endif // !SDLIB_FILEBUFFER_CAPACITY



namespace sdlib {
  enum LineState {
    single_line, multi_line, escaped_line
  };

  struct Filebuffer {
    LineState last_state = single_line;
    std::vector<std::string> buffer{};
  };

  void buffer_line(Filebuffer& buf, std::string& line) {
    if (line.empty()) {
      return;
    }
    if (line[0] == '%') {
      return;
    }
    if (line.back() == '\\'){
      buf.last_state = escaped_line;
    }
    if (line.constains("\"\"\"")) {
      buf.last_state = multi_line
    }

    switch (buf.last_state){
      case single_line:
        buf.buffer.push_back(std::move(line));
        return;
      case multi_line:

    }
  }
}
