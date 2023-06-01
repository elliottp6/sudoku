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
    Cell& at( int i );
    Cell& at( int x, int y );

    // properties
    int simplest_unsolved_cell_index() const;
    bool solvable() const;
    bool solved() const;

    // operators
    friend std::ostream& operator<<( std::ostream& out, const Grid& r );

private:
    // fields
    std::array<Cell,Size> cells_;
};

} // namespace
