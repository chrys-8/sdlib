#include <algorithm>
#include <iostream>
#include <iterator>
#include <locale>
#include <vector>

#include "toml.h"

enum SyntaxSpecies {
  SYNTAX_STRING, SYNTAX_INT, SYNTAX_FLOAT, SYNTAX_BOOL, SYNTAX_DATE,
  SYNTAX_KEYNAME, SYNTAX_VALUE, SYNTAX_ARRAY, SYNTAX_TABLE,
  SYNTAX_KEYDEF, SYNTAX_TABLE_HEADER, SYNTAX_ARRAY_TABLE_HEADER
};

struct LinePos {
  uint32_t line, pos;
};

struct SyntaxTreeNode {
  SyntaxSpecies species;
  LinePos start, extent;
  SyntaxTreeNode *pChildren, *pNext;
  size_t nChildren;
};

bool maybeInteger(const char c)
{
  if (std::isxdigit(c, std::locale(""))) return true;
  if (c == '_') return true;
  return false;
}

void fn()
{
  const char *str1 = "0x1f2_3dmnn";

  auto buffer1 = std::vector<bool>{};
  std::transform(str1, str1 + 11, std::back_inserter(buffer1),
      maybeInteger);

  std::cout << str1 << '\n';
  for (auto b : buffer1) std::cout << b;
  std::cout << '\n';
}

int main()
{
  fn();
}

