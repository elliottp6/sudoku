using System; using NUnit.Framework; namespace Sudoku {

static class Solver {
    static bool ConstrainUnit( this ref Grid grid, int cellX, int cellY, int unitX, int unitY, int unitWidth, int unitHeight ) {
        // get cell
        Cell cell = grid[cellX, cellY];

        // NAKED SINGLE: if a cell has a single value, remove that value from its peers
        if( cell.Single ) {
            var modified = false;
            for( var y = unitY; y < unitY + unitHeight; y++ ) for( var x = unitX; x < unitX + unitWidth; x++ ) if( (x != cellX) | (y != cellY) ) {
                var peer = grid[x,y];
                var old = peer;
                peer-= cell;
                modified|= peer != old;
                grid[x,y] = peer;
            }
            return modified;
        }

        // HIDDEN SINGLE: if all the peers are missing the same value, this cell must have that value
        Cell unit = default;
        for( var y = unitY; y < unitY + unitHeight; y++ ) for( var x = unitX; x < unitX + unitWidth; x++ ) if( (x != cellX) | (y != cellY) ) {
            unit+= grid[x,y];
        }
        if( (unit = ~unit).Solved ) { grid[cellX,cellY] = unit; return true; }
        return false;
    }

    // constrain horizontal, veritcal, then 3x3
    public static bool Constrain( this ref Grid grid ) {
        var modified = false;
        for( var y = 0; y < Grid.HEIGHT; y++ ) for( var x = 0; x < Grid.WIDTH; x++ ) {
            modified|= grid.ConstrainUnit( x, y, 0, y, Grid.WIDTH, 1 ); 
            modified|= grid.ConstrainUnit( x, y, x, 0, 1, Grid.HEIGHT );
            modified|= grid.ConstrainUnit( x, y, 3 * (x / 3), 3 * (y / 3), 3, 3 );
        }
        return modified;
    }

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
        Grid solution = new(
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
        solution = new(
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
