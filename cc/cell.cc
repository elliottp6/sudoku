#include <gtest/gtest.h>
#include "cell.h"
namespace Sudoku {

// primary public constructor
Cell::Cell( int values ) {
    auto bits = 0;
    while( values > 0 ) { bits|= 1 << (values % 10); values/= 10; }
    bits_ = static_cast<uint16_t>( bits >> 1 );
}

// default constructor
Cell::Cell() { bits_ = 0; }

// operators
bool Cell::operator==( const Cell r ) const { return bits_ == r.bits_; }
bool Cell::operator!=( const Cell r ) const { return bits_ != r.bits_; } 
Cell Cell::operator+( const Cell r ) const { return Cell( (uint16_t)(bits_ | r.bits_) ); }
Cell Cell::operator-( const Cell r ) const { return Cell( (uint16_t)(bits_ & ~r.bits_) ); }
Cell Cell::operator&( const Cell r ) const { return Cell( (uint16_t)(bits_ & r.bits_) ); }
Cell Cell::operator~() const { return Cell( (uint16_t)(~bits_ & 0x1FF) ); }
Cell& Cell::operator+=( const Cell r ) { *this = *this + r; return *this; }
Cell& Cell::operator-=( const Cell r ) { *this = *this - r; return *this; }
Cell& Cell::operator&=( const Cell r ) { *this = *this & r; return *this; }

// properties
int Cell::count() const { return __builtin_popcount( static_cast<int>( bits_ ) ); }
Cell Cell::min() const { return Cell( (uint16_t)(bits_ & ~(bits_ - 1)) ); } // minimum set bit
bool Cell::single() const { return (bits_ & (~bits_ + 1)) == bits_; } // zero or power-of-2?
bool Cell::solvable() const { return 0 != bits_; }
bool Cell::solved() const { return single() & solvable(); }

int Cell::values() const {
    int value = 0, bits = bits_;
    for( auto place = 1; 0 != bits; place*=10 ) {
        auto max_bit_index = __builtin_clz( bits ) ^ 31; // log2( bits )
        bits&= ~(1 << max_bit_index); // remove bit
        value+= (max_bit_index + 1) * place;
    }
    return value;
}

// serialization
std::ostream& operator<<( std::ostream& out, const Cell r ) { return out << r.values(); }

// private constructor
Cell::Cell( uint16_t bits ) { bits_ = bits; }

// tests https://blog.jetbrains.com/rscpp/2015/09/01/unit-testing-google-test/
TEST( Sudoku, Cell ) {
    // solved cell
    Cell a( 3 );
    EXPECT_TRUE( a.single() );
    EXPECT_TRUE( a.solvable() );
    EXPECT_TRUE( a.solved() );
    EXPECT_EQ( 1, a.count() );
    EXPECT_EQ( 3, a.values() );
    EXPECT_EQ( a, a.min() );

    // unsolved cell
    Cell b( 125687 );
    EXPECT_FALSE( b.single() );
    EXPECT_TRUE( b.solvable() );
    EXPECT_FALSE( b.solved() );
    EXPECT_EQ( 6, b.count() );
    EXPECT_EQ( 125678, b.values() );
    EXPECT_EQ( Cell( 1 ), b.min() );

    // unsolvable cell
    Cell c( 0 );
    EXPECT_TRUE( c.single() );
    EXPECT_FALSE( c.solvable() );
    EXPECT_FALSE( c.solved() );
    EXPECT_EQ( 0, c.count() );
    EXPECT_EQ( 0, c.values() );
    EXPECT_EQ( c, c.min() );

    // check that invalid values do not round-trip
    EXPECT_EQ( Cell(), Cell( -1 ) );
    EXPECT_EQ( Cell( 1 ), Cell( 10 ) );
    EXPECT_EQ( Cell( 12 ), Cell( 121 ) );

    // operators
    EXPECT_TRUE( Cell( 12 ) == Cell( 21 ) );
    EXPECT_TRUE( Cell( 0 ) != Cell( 1 ) );
    EXPECT_EQ( Cell( 1234589 ), Cell( 12345 ) + Cell( 98 ) ); // union
    EXPECT_EQ( Cell( 34 ), Cell( 12345 ) - Cell( 1256 ) ); // removal
    EXPECT_EQ( Cell( 7 ), Cell( 123457 ) & Cell( 987 ) ); // intersection
    EXPECT_EQ( Cell( 13 ), ~Cell( 2456789 ) ); // inverse
}

} // namespace
