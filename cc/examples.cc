#include "examples.h"
namespace Sudoku {

Grid Examples::Lookup( const std::string& name ) {
    const int _ = 123456789;
    if( "top-row-only" == name ) return Grid( std::array<int,Grid::Size>( {
        1, 2, 3, _, 5, 6, 7, 8, 9,
        _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _ } ) );
    
    else if( "invalid" == name ) return Grid( std::array<int,Grid::Size>( {
        9, 6, _, 9, 2, _, 8, 1, _,
        _, 2, 1, 4, _, _, _, _, _,
        _, _, 5, _, _, 3, 2, _, _,
        _, _, 2, _, _, 4, _, 3, 9,
        _, 3, 8, _, _, _, 1, 4, _,
        4, 9, _, 3, _, _, 6, _, _,
        _, _, 6, 7, _, _, 9, _, _,
        _, _, _, _, _, 9, 4, 7, _,
        _, 1, 9, _, 4, _, _, 8, 6 } ) );

    else if( "easy" == name ) return Grid( std::array<int,Grid::Size>( {
        9, 6, _, _, 2, _, 8, 1, _,
        _, 2, 1, 4, _, _, _, _, _,
        _, _, 5, _, _, 3, 2, _, _,
        _, _, 2, _, _, 4, _, 3, 9,
        _, 3, 8, _, _, _, 1, 4, _,
        4, 9, _, 3, _, _, 6, _, _,
        _, _, 6, 7, _, _, 9, _, _,
        _, _, _, _, _, 9, 4, 7, _,
        _, 1, 9, _, 4, _, _, 8, 6 } ) ); // 34 hints

    else if( "medium" == name ) return Grid( std::array<int,Grid::Size>( {
        2, _, 7, _, _, _, _, _, _,
        _, _, 5, 6, _, 7, _, _, 4,
        8, _, _, _, _, _, 1, _, _,
        _, 1, _, _, 7, 9, 6, _, 8,
        _, 5, _, _, 6, 2, _, 4, _,
        _, _, _, 5, 3, _, _, _, _,
        7, _, 1, _, _, 5, _, _, _,
        _, _, _, _, 2, 6, 8, _, 5,
        _, _, 6, 8, _, 1, 4, _, _ } ) ); // 30 hints

    else if( "hard" == name ) return Grid( std::array<int,Grid::Size>( {
        6, _, _, _, _, _, _, _, _,
        _, _, 1, _, _, _, 4, 6, _,
        5, _, _, _, _, 3, 2, _, _,
        _, _, _, _, 8, _, _, _, _,
        _, 9, 6, 4, _, _, _, _, _,
        2, _, 4, _, 1, _, 5, _, 3,
        _, _, 8, _, _, _, _, 3, _,
        _, _, 3, 2, 4, _, _, 1, _,
        _, _, _, _, _, 8, 6, _, 2 } ) ); // 25 hints

    else if( "expert" == name ) return Grid( std::array<int,Grid::Size>( {
        _, _, _, _, _, 7, 9, 1, _,
        _, _, _, _, 1, _, _, _, _,
        _, 2, _, _, 9, _, 5, _, _,
        _, 6, _, _, _, _, _, 7, _,
        _, _, _, 4, _, 6, _, _, 8,
        _, _, 5, _, _, _, _, _, 2,
        7, _, _, 3, _, _, _, _, _,
        2, _, _, 7, 8, _, _, _, _,
        9, 5, 1, _, _, _, _, _, _ } ) ); // 22 hints
    
    else return Grid( std::array<int,Grid::Size>( {
        _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _ } ) );
}

} // namespace
