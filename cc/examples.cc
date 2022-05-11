#include "examples.h"
namespace Sudoku {

Grid Examples::Lookup( const std::string& name ) {
    const int X = 123456789;
    if( "top-row-only" == name ) return Grid( std::array<int,Grid::Size>( {
        1, 2, 3, X, 5, 6, 7, 8, 9,
        X, X, X, X, X, X, X, X, X,
        X, X, X, X, X, X, X, X, X,
        X, X, X, X, X, X, X, X, X,
        X, X, X, X, X, X, X, X, X,
        X, X, X, X, X, X, X, X, X,
        X, X, X, X, X, X, X, X, X,
        X, X, X, X, X, X, X, X, X,
        X, X, X, X, X, X, X, X, X } ) );
    
    else if( "invalid" == name ) return Grid( std::array<int,Grid::Size>( {
        9, 6, X, 9, 2, X, 8, 1, X,
        X, 2, 1, 4, X, X, X, X, X,
        X, X, 5, X, X, 3, 2, X, X,
        X, X, 2, X, X, 4, X, 3, 9,
        X, 3, 8, X, X, X, 1, 4, X,
        4, 9, X, 3, X, X, 6, X, X,
        X, X, 6, 7, X, X, 9, X, X,
        X, X, X, X, X, 9, 4, 7, X,
        X, 1, 9, X, 4, X, X, 8, 6 } ) );

    else if( "easy" == name ) return Grid( std::array<int,Grid::Size>( {
        9, 6, X, X, 2, X, 8, 1, X,
        X, 2, 1, 4, X, X, X, X, X,
        X, X, 5, X, X, 3, 2, X, X,
        X, X, 2, X, X, 4, X, 3, 9,
        X, 3, 8, X, X, X, 1, 4, X,
        4, 9, X, 3, X, X, 6, X, X,
        X, X, 6, 7, X, X, 9, X, X,
        X, X, X, X, X, 9, 4, 7, X,
        X, 1, 9, X, 4, X, X, 8, 6 } ) ); // 34 hints

    else if( "medium" == name ) return Grid( std::array<int,Grid::Size>( {
        2, X, 7, X, X, X, X, X, X,
        X, X, 5, 6, X, 7, X, X, 4,
        8, X, X, X, X, X, 1, X, X,
        X, 1, X, X, 7, 9, 6, X, 8,
        X, 5, X, X, 6, 2, X, 4, X,
        X, X, X, 5, 3, X, X, X, X,
        7, X, 1, X, X, 5, X, X, X,
        X, X, X, X, 2, 6, 8, X, 5,
        X, X, 6, 8, X, 1, 4, X, X } ) ); // 30 hints

    else if( "hard" == name ) return Grid( std::array<int,Grid::Size>( {
        6, X, X, X, X, X, X, X, X,
        X, X, 1, X, X, X, 4, 6, X,
        5, X, X, X, X, 3, 2, X, X,
        X, X, X, X, 8, X, X, X, X,
        X, 9, 6, 4, X, X, X, X, X,
        2, X, 4, X, 1, X, 5, X, 3,
        X, X, 8, X, X, X, X, 3, X,
        X, X, 3, 2, 4, X, X, 1, X,
        X, X, X, X, X, 8, 6, X, 2 } ) ); // 25 hints

    else if( "expert" == name ) return Grid( std::array<int,Grid::Size>( {
        X, X, X, X, X, 7, 9, 1, X,
        X, X, X, X, 1, X, X, X, X,
        X, 2, X, X, 9, X, 5, X, X,
        X, 6, X, X, X, X, X, 7, X,
        X, X, X, 4, X, 6, X, X, 8,
        X, X, 5, X, X, X, X, X, 2,
        7, X, X, 3, X, X, X, X, X,
        2, X, X, 7, 8, X, X, X, X,
        9, 5, 1, X, X, X, X, X, X } ) ); // 22 hints
    
    else return Grid( std::array<int,Grid::Size>( {
        X, X, X, X, X, X, X, X, X,
        X, X, X, X, X, X, X, X, X,
        X, X, X, X, X, X, X, X, X,
        X, X, X, X, X, X, X, X, X,
        X, X, X, X, X, X, X, X, X,
        X, X, X, X, X, X, X, X, X,
        X, X, X, X, X, X, X, X, X,
        X, X, X, X, X, X, X, X, X,
        X, X, X, X, X, X, X, X, X } ) );
}

} // namespace
