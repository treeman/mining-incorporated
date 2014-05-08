#pragma once

#include <string>
using namespace std;

#include "fmt.hxx"

// Critical errors etc.
// Use instead of using exceptions when we know we don't want to continue.
// May change later.
void abort_game(string msg);

// printf with type checking.
template<typename... Ts>
void abort_game(const char *f, const Ts&... ts) { abort_game(fmt(f, ts...)); }

