#pragma once
#include <stdint.h>
#include "grid.h"
namespace Sudoku {

class Solver {
public:
    static bool Solve( Grid& grid, bool interactive = false, bool guessing = true );
};

} // namespace
