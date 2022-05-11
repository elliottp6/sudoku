#include <gtest/gtest.h>
#include <stdexcept>
#include "grid.h"
namespace Sudoku {

// public constructor
Grid::Grid( const std::array<int,Size>& values ) {
    for( auto i = 0; i < Size; i++ ) _cells[i] = Cell( values[i] );
}

// methods
Cell& Grid::at( int x, int y ) { return _cells.at( y * Grid::Width + x ); }

// properties
bool Grid::solvable() const {
    for( auto& cell : _cells ) if( !cell.solvable() ) return false;
    return true;
}

bool Grid::solved() const {
    for( auto& cell : _cells ) if( !cell.solved() ) return false;
    return true;
}

// operators
std::ostream& operator<<( std::ostream& out, const Grid& r ) {
    for( auto i = 0; i < r._cells.size(); i++ ) {
        // write separators
        if( i > 0 ) {
            if( 0 == i % 9 ) { out << std::endl; if( 0 == i % 27 ) out << "------+------+------\n"; }
            else { out << ' '; if( 0 == i % 3 ) out << '|'; }            
        }
        
        // write values
        auto value = r._cells[i].values();
        if( value < 10 ) out << value; else out << '_';
    }
    return out;
}

} // namespace
