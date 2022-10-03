#include "common.h"

#include <iostream>

void CheckInternal(const bool expr, const char* const file, const int line, const char* const function) {
  if (!expr) {
    std::cerr << "Check-fail at function " << function << " on " << file << ":" << line << "\n";
    throw "check-fail";
  }
}
