#include <iostream>
#include <gtest/gtest.h>
#include "cell.h"
#include "grid.h"
#include "examples.h"
#include "solver.h"
using namespace Sudoku;

int main( int argc, char* argv[] ) {
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

    // solve an example grid
    if( "solve-example" == command ) {
        // for for example-name argument
        if( argc < 3 ) {
            std::cout << "must specify the name of an example grid to run" << std::endl;
            return 0;
        }

        // lookup example & solve
        const std::string name = argv[2];
        auto grid = Examples::Lookup( name );
        Solver::Solve( grid, true );
        return 0;
    }

    // solve a user-supplied grid
    if( "solve-custom" == command ) {
        // TODO
        return 0;
    }

    // otherwise, command was not recognized
    std::cout << "unrecognized command: " << command << std::endl;
    return 0;
}

