#include <gtest/gtest.h>
#include <stdexcept>
#include "grid.h"
namespace Sudoku {

// constructor
Grid::Grid( const std::array<int,Size>& values ) {
    for( auto i = 0; i < Size; i++ )
        cells_[i] = Cell( values[i] );
}

// methods
Cell& Grid::at( int x, int y ) {
    return cells_.at( y * Grid::Width + x );
}

// properties
bool Grid::solvable() const {
    for( auto& cell : cells_ )
        if( !cell.solvable() ) return false;
    return true;
}

bool Grid::solved() const {
    for( auto& cell : cells_ )
        if( !cell.solved() ) return false;
    return true;
}

// operators
std::ostream& operator<<( std::ostream& out, const Grid& r ) {
    for( size_t i = 0; i < r.cells_.size(); i++ ) {
        // write separators
        if( i > 0 ) {
            if( 0 == i % 9 ) {
                out << std::endl;
                if( 0 == i % 27 ) out << "------+------+------\n"; }
            else {
                out << ' ';
                if( 0 == i % 3 ) out << '|';
            }            
        }
          
        // write values
        auto value = r.cells_[i].values();
        if( value < 10 ) out << value; else out << '_';
    }
    return out;
}

TEST( Sudoku, Grid ) {
    // solved grid
    auto g = Grid({
        4, 8, 3, 9, 2, 1, 6, 5, 7,
        9, 6, 7, 3, 4, 5, 8, 2, 1,
        2, 5, 1, 8, 7, 6, 4, 9, 3,
        5, 4, 8, 1, 3, 2, 9, 7, 6,
        7, 2, 9, 5, 6, 4, 1, 3, 8,
        1, 3, 6, 7, 9, 8, 2, 4, 5,
        3, 7, 2, 6, 8, 9, 5, 1, 4,
        8, 1, 4, 2, 5, 3, 7, 6, 9, 
        6, 9, 5, 4, 1, 7, 3, 8, 2 });
    EXPECT_TRUE( g.solvable() );
    EXPECT_TRUE( g.solved() );

    // unsolved grid
    g.at( 8, 8 ) = Cell( 1289 );
    EXPECT_TRUE( g.solvable() );
    EXPECT_FALSE( g.solved() );

    // unsolvable grid
    g.at( 4, 4 ) = Cell( 0 );
    EXPECT_FALSE( g.solvable() );
    EXPECT_FALSE( g.solved() );

    // test serialization
    std::ostringstream stream;
    stream << g;
    EXPECT_STREQ(
        "4 8 3 |9 2 1 |6 5 7\n"
        "9 6 7 |3 4 5 |8 2 1\n"
        "2 5 1 |8 7 6 |4 9 3\n"
        "------+------+------\n"
        "5 4 8 |1 3 2 |9 7 6\n"
        "7 2 9 |5 0 4 |1 3 8\n"
        "1 3 6 |7 9 8 |2 4 5\n"
        "------+------+------\n"
        "3 7 2 |6 8 9 |5 1 4\n"
        "8 1 4 |2 5 3 |7 6 9\n"
        "6 9 5 |4 1 7 |3 8 _", stream.str().c_str() );
}

} // namespace
