#pragma once
#include <stdint.h>
#include <iostream>
namespace Sudoku {

class Cell {
public:
    // public constructors
    Cell( int values );    
    Cell();
    
    // operators
    bool operator==( const Cell r ) const;
    bool operator!=( const Cell r ) const;
    Cell operator+( const Cell r ) const; // union of two cells [note: don't ever return 'const-by-value', see https://stackoverflow.com/questions/6299967/what-are-the-use-cases-for-having-a-function-return-by-const-value-for-non-built]
    Cell operator-( const Cell r ) const; // cell without contents of cell 'c'
    Cell operator&( const Cell r ) const; // intersection of two cells
    Cell operator~() const; // inverse of this cell
    Cell& operator+=( const Cell r );
    Cell& operator-=( const Cell r );
    Cell& operator&=( const Cell r );

    // properties
    int count() const; // # of values in this cell
    Cell min() const; // singlular cell w/ minimum value from this cell
    bool single() const;
    bool solvable() const;
    bool solved() const;
    int values() const;

    // serialization
    friend std::ostream& operator<<( std::ostream& out, const Cell r );

private:
    // private constructor
    Cell( uint16_t bits );

    // fields
    uint16_t bits_;
};

} // namespace
