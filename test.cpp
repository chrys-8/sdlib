#include <fmt/core.h>

#include "util_filesystem.h"

static constexpr const char *TEST_FILE = "test_file.toml";

int main()
{
  std::ifstream file_stream(TEST_FILE);

  size_t counter = 0;
  for (std::string line{}; sdlib::stream_get_line(file_stream, line); ) {
    fmt::print("{}: {}\n", counter, line);
    ++counter;
  }
}
