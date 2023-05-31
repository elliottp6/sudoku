#pragma once
#include <stdint.h>
#include "grid.h"
namespace Sudoku {

class Solver {
public:
    static bool Solve( Grid& grid, bool guess, bool prompt );
};

} // namespace
