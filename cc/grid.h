#pragma once
#include "cell.h"
#include <array>
#include <iostream>
namespace Sudoku {

class Grid {
public: 
    // constants
    static const int Width = 9, Height = 9, Size = Width * Height;
    
    // constructor
    Grid( const std::array<int,Size>& values );

    // methods
    Cell& at( int x, int y );

    // properties
    bool solvable() const;
    bool solved() const;

    // operators
    friend std::ostream& operator<<( std::ostream& out, const Grid& r );

private:
    // fields
    std::array<Cell,Size> _cells;
};

} // namespace
