#pragma once
#include "grid.h"
#include <string>
namespace Sudoku {

class Examples {
public: 
    static Grid Lookup( const std::string& name );
};

} // namespace
