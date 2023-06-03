use crate::Cell;
use crate::Grid;

// --Constraints--
// (1) NAKED SINGLE: if a cell has a single value, remove that value from its peers
// (2) HIDDEN SINGLE: if all the peers are missing the same value, this cell must have that value
pub fn constrain( grid: &mut Grid ) -> bool {
    let mut modified = false;
    for y in 0..Grid::HEIGHT { for x in 0..Grid::HEIGHT {
          
    }}
    modified
}

pub fn solve( grid: &mut Grid, interactive: bool, guess: i32 ) -> bool {
    loop {
        // constrain grid
        loop {
            if interactive {
                println!( "--STATE----------------------------" );
                println!( "{}", grid );
                //var k = Console.ReadKey( true ).Key;
                //if( ConsoleKey.Escape == k || ConsoleKey.Q == k ) return true;
            }
            if !grid.solvable() || !constrain( grid ) { break; }
        }

        // 
    }
}

// tests
#[cfg(test)] mod tests {
    use super::*;

    #[test] fn test() {
    }
}

/*
    public static bool Constrain( this ref Grid grid ) {
        var modified = false;
        for( var y = 0; y < Grid.HEIGHT; y++ ) for( var x = 0; x < Grid.WIDTH; x++ ) {
            // get cell
            Cell cell = grid[x,y], peer, peer1;
            var singleton = cell.Singleton;

            // -- HORIZONTAL UNIT --
            Cell unit = default;
            for( var peer_x = 0; peer_x < Grid.WIDTH; peer_x++ ) if( peer_x != x ) {
                peer = peer1 = grid[peer_x,y];
                if( singleton ) modified|= (peer-=cell) != peer1; // CONSTRAINT #1
                unit += peer;
                grid[peer_x,y] = peer;
            }
            if( !singleton & (unit = ~unit).Solved ) { singleton = modified = true; cell = unit; } // CONSTRAINT #2

            // -- VERITCAL UNIT --
            unit = default;
            for( var peer_y = 0; peer_y < Grid.HEIGHT; peer_y++ ) if( peer_y != y ) {
                peer = peer1 = grid[x,peer_y];
                if( singleton ) modified|= (peer-=cell) != peer1; // CONSTRIANT #1
                unit += peer;
                grid[x,peer_y] = peer;
            }
            if( !singleton & (unit = ~unit).Solved ) { singleton = modified = true; cell = unit; } // CONSTRAINT #2

            // -- TILE UNIT --
            unit = default;
            int tile_x = 3 * (x / 3), tile_y = 3 * (y / 3);
            for( var peer_y = tile_y; peer_y < tile_y + 3; peer_y++ ) for( var peer_x = tile_x; peer_x < tile_x + 3; peer_x++ ) if( !((peer_x == x) & (peer_y == y)) ) {
                peer = peer1 = grid[peer_x,peer_y];
                if( singleton ) modified|= (peer-=cell) != peer1; // CONSTRAINT #1
                unit += peer;
                grid[peer_x,peer_y] = peer;
            }
            if( !singleton & (unit = ~unit).Solved ) { singleton = modified = true; cell = unit; } // CONSTRAINT #2

            // set cell
            grid[x,y] = cell;
        }
        return modified;
    }

    public static bool Solve( this ref Grid g, bool interactive = false, bool showSets = false, bool allowGuessing = true, int guesses = 0 ) {
        for(;;) {
            // first, constrain the puzzle as much as possible
            ...

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
        Assert.IsFalse( g.Solved );
        Assert.IsFalse( g.Unsolvable );

        // solve "invalid", which has no solutions
        g = Examples.Get( "invalid" );
        g.Solve();
        Assert.IsFalse( g.Solved );
        Assert.IsTrue( g.Unsolvable );
        
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
        Assert.IsTrue( g.Solved );
        Assert.IsFalse( g.Unsolvable );

        // solve "medium" without guessing
        g = Examples.Get( "medium" );
        g.Solve( allowGuessing: false );
        Assert.IsTrue( g.Solved );
        Assert.IsFalse( g.Unsolvable );

        // solve "hard" without guessing
        g = Examples.Get( "hard" );
        g.Solve(  allowGuessing: false  );
        Assert.IsTrue( g.Solved );
        Assert.IsFalse( g.Unsolvable );

        // solve "expert" without guessing (we cannot do this yet!)
        g = Examples.Get( "expert" );
        g.Solve( allowGuessing: false );
        Assert.IsFalse( g.Solved );
        Assert.IsFalse( g.Unsolvable );

        // however, we can solve with guessing
        g = Examples.Get( "expert" );
        g.Solve();
        Assert.IsTrue( g.Solved );
        Assert.IsFalse( g.Unsolvable );*/