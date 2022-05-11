#include <iostream> // C++ input/output
#include <gtest/gtest.h> // google test
#include "cell.h"
#include "grid.h"
#include "examples.h"
#include "solver.h"
using namespace Sudoku;

int main( int argc, char** argv ) {
    // check for at least one command argument
    if( argc < 2 ) {
        std::cout << "must specify a command to run" << std::endl;
        return 0;
    }

    // get name of command
    const std::string command = argv[1];

    // test command
    if( "test" == command ) {
        testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS();
    }

    /*
    // print out some stuff about cells
    auto a = Cell( 25 ), b = Cell( 125 );
    std::cout << "this is for the debugger!" << std::endl;
    std::cout << "Are equal: " << (a == b) << std::endl;
    std::cout << "Cell has " << a.count() << " values, which means single: " << a.single() << " with values " << a << std::endl;

    // print out some stuff about a grid
    auto g = Grid( std::array<int,Grid::Size> { 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9 } );
    std::cout << "\ngrid looks like:\n" << g << std::endl << std::endl;

    // solve the easy grid
    auto easy = Examples::Lookup( "easy" );
    auto i = 0;
    do {
        std::cout << "iteration: " << (i++) << std::endl;
        std::cout << easy << std::endl;
    } while( ' ' == std::cin.get() && Solver::Constrain( easy ) );

    // print out solution
    // TODO
    */
    std::cout << "unrecognized command: " << command << std::endl;
    return 0;
}

