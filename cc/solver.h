#pragma once
#include "grid.h"
namespace Sudoku {

class Solver {
public:
    // --Constraints--
    // (1) NAKED SINGLE: if a cell has a single value, remove that value from its peers
    // (2) HIDDEN SINGLE: if all the peers are missing the same value, this cell must have that value
    // return True if the grid was modified
    static bool Constrain( Grid& grid );
    
};

} // namespace
