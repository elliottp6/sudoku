#include "solver.h"
namespace Sudoku {

// --Constraints--
// (1) NAKED SINGLE: if a cell has a single value, remove that value from its peers
// (2) HIDDEN SINGLE: if all the peers are missing the same value, this cell must have that value
// return True if the grid was modified
__attribute__((unused)) static bool Constrain( Grid& grid ) {
    // keep track of if we modified any cells
    auto modified = false;
    
    // loop through each cell, applying constraints
    for( auto y = 0; y < Grid::Height; y++ ) for( auto x = 0; x < Grid::Width; x++ ) {
        // get cell @ [x,y]
        Cell &cell = grid.at( x, y );
        auto single = cell.single();

        // -- HORIZONTAL UNIT --
        auto unit = Cell();
        for( auto peer_x = 0; peer_x < Grid::Width; peer_x++ ) if( peer_x != x ) {
            Cell &peer = grid.at( peer_x, y );
            Cell peer_orig = peer;
            if( single ) modified|= peer_orig != (peer -= cell); // constraint # 1
            unit += peer;
        }
        if( !single & (unit = ~unit).solved() ) { single = modified = true; cell = unit; } // constraint #2

        // -- VERTICAL UNIT --
        unit = Cell();
        for( auto peer_y = 0; peer_y < Grid::Height; peer_y++ ) if( peer_y != y ) {
            Cell &peer = grid.at( x, peer_y );
            Cell peer_orig = peer;
            if( single ) modified|= peer_orig != (peer -= cell); // constraint # 1
            unit += peer;
        }
        if( !single & (unit = ~unit).solved() ) { single = modified = true; cell = unit; } // constraint #2

        // -- TILE UNIT --
        unit = Cell();
        auto tile_x = 3 * (x / 3), tile_y = 3 * (y / 3);
        for( auto peer_y = tile_y; peer_y < tile_y + 3; peer_y++ ) for( auto peer_x = tile_x; peer_x < tile_x + 3; peer_x++ ) if( !((peer_x == x) & (peer_y == y)) ) {
            Cell &peer = grid.at( peer_x, peer_y );
            Cell peer_orig = peer;
            if( single ) modified|= peer_orig != (peer -= cell); // constraint # 1
            unit += peer;
        }
        if( !single & (unit = ~unit).solved() ) { single = modified = true; cell = unit; } // constraint #2
    }

    // return true if we modified any of the cells
    return modified;
}

bool Solver::Solve( Grid& grid, __attribute__((unused)) bool guess, bool prompt ) {
    for(;;) {
        // first, constrain the puzzle as much as possible
        for( auto i = 0;; i++ ) {
            // print puzzle state and wait for user keypress
            if( prompt ) {
                std::cout << "==iteration " << i << "==" << std::endl;
                std::cout << grid << std::endl;

                // TODO: we want to wait for any keypress but std::getchar waits for 'enter' to be pressed
                if( 'q' == std::getchar() ) return false;
            }

            // 
        }
    }
}

} // namespace

/*
    auto i = 0;
    do {
        std::cout << "iteration: " << (i++) << std::endl;
        std::cout << easy << std::endl;
    } while( ' ' == std::cin.get() && Solver::Constrain( easy ) );

    public static bool Solve( this ref Grid g, bool interactive = false, bool showSets = false, bool allowGuessing = true, int guesses = 0 ) {
        for(;;) {
            // first, constrain the puzzle as much as possible
            var iteration = 0;
            do {
                if( interactive ) {
                    Console.WriteLine( $"--iteration {iteration++}---------------------------------------------------" );
                    Console.WriteLine( g.ToString( showSets ) );
                    var k = Console.ReadKey( true ).Key;
                    if( ConsoleKey.Escape == k || ConsoleKey.Q == k ) return true;
                }
            } while( g.Solvable && g.Constrain() );

            // find the index of an unsolved cell with the least possibilities
            var solved = true;
            int unsolvedIndex = -1, unsolvedCount = 10;
            for( var i = 0; i < Grid.SIZE; i++ ) {
                var count = g[i].Count;
                if( 0 == count ) { if( interactive ) Console.WriteLine( "Dead end!" ); return false; } // found unsolvable cell
                solved&= (1 == count); // check if the entire puzzle is solved
                if( (count > 1) & (count < unsolvedCount) ) { unsolvedCount = count; unsolvedIndex = i; }
            }

            // if solved, then return true
            if( solved ) {
                if( interactive ) Console.WriteLine( "Solved!" );
                return true;
            }

            // use the guess method to remove values
            if( !allowGuessing ) return false;
            var cell = g[unsolvedIndex];
            var guess = cell.Min;
            var copy = g;
            copy[unsolvedIndex] = guess;
            if( interactive ) Console.WriteLine( $"guess {guess} at {1 + unsolvedIndex % 9},{1 + unsolvedIndex / 9} from potentials {cell} (# guesses: {guesses + 1})" );
            if( Solve( ref copy, interactive, showSets, true, guesses + 1 ) ) { g = copy; return true; }

            // otherwise, that was a bad guess, so remove it and restart the process
            g[unsolvedIndex]-=guess;
            if( interactive ) Console.WriteLine( $"bad guess! removing {guess} from {1 + unsolvedIndex % 9},{1 + unsolvedIndex / 9} leaving {g[unsolvedIndex]} (# guesses: {guesses})" );           
        }
    }

    // tests
    [Test] public static void Test() {
        // solve "top-row-only", which has multiple solutions. don't use the guess method
        var g = Examples.Get( "top-row-only" );
        g.Solve( allowGuessing: false );
        var solution = new Grid(
            1, 2, 3, 4, 5, 6, 7, 8, 9,
            456789, 456789, 456789, 123789, 123789, 123789, 123456, 123456, 123456,
            456789, 456789, 456789, 123789, 123789, 123789, 123456, 123456, 123456,
            23456789, 13456789, 12456789, 12356789, 12346789, 12345789, 12345689, 12345679, 12345678,
            23456789, 13456789, 12456789, 12356789, 12346789, 12345789, 12345689, 12345679, 12345678,
            23456789, 13456789, 12456789, 12356789, 12346789, 12345789, 12345689, 12345679, 12345678,
            23456789, 13456789, 12456789, 12356789, 12346789, 12345789, 12345689, 12345679, 12345678,
            23456789, 13456789, 12456789, 12356789, 12346789, 12345789, 12345689, 12345679, 12345678,
            23456789, 13456789, 12456789, 12356789, 12346789, 12345789, 12345689, 12345679, 12345678 );
        Assert.IsTrue( g.Solvable );
        Assert.IsFalse( g.Solved );

        // solve "invalid", which has no solutions
        g = Examples.Get( "invalid" );
        g.Solve();
        Assert.IsFalse( g.Solvable );
        Assert.IsFalse( g.Solved );
        
        // solve "easy" without guessing
        g = Examples.Get( "easy" );
        g.Solve( allowGuessing: false );
        solution = new Grid(
            9, 6, 4, 5, 2, 7, 8, 1, 3,
            3, 2, 1, 4, 8, 6, 5, 9, 7,
            8, 7, 5, 1, 9, 3, 2, 6, 4,
            1, 5, 2, 8, 6, 4, 7, 3, 9,
            6, 3, 8, 9, 7, 2, 1, 4, 5,
            4, 9, 7, 3, 5, 1, 6, 2, 8,
            2, 4, 6, 7, 3, 8, 9, 5, 1,
            5, 8, 3, 6, 1, 9, 4, 7, 2,
            7, 1, 9, 2, 4, 5, 3, 8, 6 );
        Assert.IsTrue( g.Equals( ref solution ) );
        Assert.IsTrue( g.Solvable );
        Assert.IsTrue( g.Solved );

        // solve "medium" without guessing
        g = Examples.Get( "medium" );
        g.Solve( allowGuessing: false );
        Assert.IsTrue( g.Solvable );
        Assert.IsTrue( g.Solved );

        // solve "hard" without guessing
        g = Examples.Get( "hard" );
        g.Solve(  allowGuessing: false  );
        Assert.IsTrue( g.Solvable );
        Assert.IsTrue( g.Solved );

        // solve "expert" without guessing (we cannot do this yet!)
        g = Examples.Get( "expert" );
        g.Solve( allowGuessing: false );
        Assert.IsTrue( g.Solvable );
        Assert.IsFalse( g.Solved );

        // however, we can solve with guessing
        g = Examples.Get( "expert" );
        g.Solve();
        Assert.IsTrue( g.Solvable );
        Assert.IsTrue( g.Solved );
    }
}

} // namespace
*/