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

static void FullyConstrain( Grid& grid ) {
    while( Constrain( grid ) );
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

            // check if we found a solution
            if( grid.solved() ) return true;
            if( !grid.solvable() ) return false;

            // otherwise, fully constrain the grid
            FullyConstrain( grid );

            // TODO: use the guess & check method
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