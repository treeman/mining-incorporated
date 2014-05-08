#pragma once

#include <string>
using namespace std;

// Critical errors etc.
// Use instead of using exceptions when we know we don't want to continue.
// May change later.
void abort_game(string msg);
