#include <gtest/gtest.h>
#include "examples.h"
#include "solver.h"
namespace Sudoku {

static bool ConstrainUnit( Grid& grid, int cell_x, int cell_y, int unit_x, int unit_y, int unit_width, int unit_height ) {
    // get cell
    Cell &cell = grid.at( cell_x, cell_y );

    // NAKED SINGLE: if a cell has a single value, remove that value from its peers
    if( cell.single() ) {
        auto modified = false;
        for( auto y = unit_y; y < unit_y + unit_height; y++ ) for( auto x = unit_x; x < unit_x + unit_width; x++ ) if( (x != cell_x) | (y != cell_y) ) {
            Cell& peer = grid.at( x, y );
            Cell old = peer;
            peer-=cell;
            modified|= peer != old;
        }
        return modified;
    }

    // HIDDEN SINGLE: if all the peers are missing the same value, this cell must have that value
    Cell unit = Cell();
    for( auto y = unit_y; y < unit_y + unit_height; y++ ) for( auto x = unit_x; x < unit_x + unit_width; x++ ) if( (x != cell_x) | (y != cell_y) ) {
        unit+= grid.at( x, y );
    }
    if( (unit = ~unit).solved() ) { cell = unit; return true; }
    return false;
}

static bool Constrain( Grid& grid ) {
    auto modified = false;
    for( auto y = 0; y < Grid::Height; y++ ) for( auto x = 0; x < Grid::Width; x++ ) {
        modified|= ConstrainUnit( grid, x, y, 0, y, Grid::Width, 1 ); 
        modified|= ConstrainUnit( grid, x, y, x, 0, 1, Grid::Height );
        modified|= ConstrainUnit( grid, x, y, 3 * (x / 3), 3 * (y / 3), 3, 3 );
    }
    return modified;
}

bool Solver::Solve( Grid& grid, bool guess, bool interactive ) {
    for(;;) {
        // constrain grid
        do {
            if( interactive ) {
                std::cout << "==state==" << std::endl;
                std::cout << grid << std::endl;
                while( std::cin.get() != '\n' );
            }
        } while( grid.solvable() && Constrain( grid ) );

        // check for end state
        if( grid.solved() ) {
            if( interactive ) std::cout << "solved!" << std::endl;
            return true;
        } else if( !grid.solvable() ) { 
            if( interactive ) std::cout << "unsolvable!" << std::endl;
            return false;
        }

        // check if we're allowed to guess
        if( !guess ) {
            if( interactive ) std::cout << "unsolvable without guessing!" << std::endl;
            return false;
        }

        // identify the simplest unsolved cell
        auto cell_index = grid.simplest_unsolved_cell_index();
        Cell &cell = grid.at( cell_index );

        // guess one of the values (just use the minimum)
        Cell guess = cell.min();

        // copy the grid to a guess-grid, with our guess in place
        Grid guess_grid = grid;
        guess_grid.at( cell_index ) = guess;
        if( interactive ) std::cout << "guessing" << std::endl;

        // try to solve the guess-grid. if we solved it, then our guess was correct.
        if( Solve( guess_grid, interactive ) ) {
            grid = guess_grid;
            return true;
        }

        // if guess-grid was not solvable, our guess was wrong. remove it, and continue solving
        cell -= guess;
        if( interactive ) std::cout << "bad guess" << std::endl;
    }
}

TEST( Sudoku, Solver ) {
    // try to solve "invalid", which has no solutions
    auto g = Examples::Lookup( "invalid" );
    EXPECT_FALSE( Solver::Solve( g ) );
    EXPECT_FALSE( g.solvable() );

    // solve "easy" w/o guessing
    g = Examples::Lookup( "easy" );
    EXPECT_TRUE( Solver::Solve( g, false ) );

    // TODO: check solution (needs equality overload)
    /*auto solution = Grid( {
        9, 6, 4, 5, 2, 7, 8, 1, 3,
        3, 2, 1, 4, 8, 6, 5, 9, 7,
        8, 7, 5, 1, 9, 3, 2, 6, 4,
        1, 5, 2, 8, 6, 4, 7, 3, 9,
        6, 3, 8, 9, 7, 2, 1, 4, 5,
        4, 9, 7, 3, 5, 1, 6, 2, 8,
        2, 4, 6, 7, 3, 8, 9, 5, 1,
        5, 8, 3, 6, 1, 9, 4, 7, 2,
        7, 1, 9, 2, 4, 5, 3, 8, 6 });*/
    // EXPECT_TRUE( g == solution );
  
    // solve "medium", "hard" w/o guessing
    g = Examples::Lookup( "medium" );
    EXPECT_TRUE( Solver::Solve( g, false ) );
    g = Examples::Lookup( "hard" );
    EXPECT_TRUE( Solver::Solve( g, false ) );
    
    // cannot solve "expert" w/o guessing
    g = Examples::Lookup( "expert" );
    EXPECT_FALSE( Solver::Solve( g, false ) );
    EXPECT_TRUE( Solver::Solve( g ) );
}

} // namespace
