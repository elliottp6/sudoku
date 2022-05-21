use crate::Cell;
use std::fmt;

#[derive( Copy, Clone, Debug, Eq, PartialEq )]
pub struct Grid {
    cells: [Cell; Grid::SIZE]
}

impl Grid {
    // dimensions
    pub const WIDTH: usize = 9;
    pub const HEIGHT: usize = 9;
    pub const SIZE: usize = Grid::WIDTH * Grid::HEIGHT;

    // constructor
    pub fn new( values: &[u32; Grid::SIZE] ) -> Grid {
        let mut cells = [Cell::new( 0 ); Grid::SIZE];
        for (i, value) in values.iter().enumerate() { cells[i] = Cell::new( *value ); }
        Grid { cells: cells }
    }

    // properties
    pub fn solvable( &self ) -> bool { self.cells.iter().all( |&c| c.solvable() ) }
    pub fn solved( &self ) -> bool { self.cells.iter().all( |&c| c.solved() ) }
}

// serialization
impl fmt::Display for Grid {
    fn fmt( &self, f: &mut fmt::Formatter<'_> ) -> fmt::Result {
        // serialize all the cells
        for (i, cell) in self.cells.iter().enumerate() {
            // write separators
            if i > 0 {
                if 0 == i % 9 {
                    writeln!( f );
                    if 0 == i % 27 { writeln!( f, "------+------+------" ); }
                } else {
                    write!( f, " " );
                    if 0 == i % 3 { write!( f, "|" ); }
                }
            }
            
            // write value
            let value = cell.values();
            if value < 10 { write!( f, "{}", value ); } else { write!( f, "_" ); }
        }

        // return value
        write!( f, "" )
    }
}

// tests
#[cfg(test)] mod tests {
    use super::*;

    #[test] fn test() {
        // solved grid
        let mut g = Grid::new( &[4, 8, 3, 9, 2, 1, 6, 5, 7,
                                 9, 6, 7, 3, 4, 5, 8, 2, 1,
                                 2, 5, 1, 8, 7, 6, 4, 9, 3,
                                 5, 4, 8, 1, 3, 2, 9, 7, 6,
                                 7, 2, 9, 5, 6, 4, 1, 3, 8,
                                 1, 3, 6, 7, 9, 8, 2, 4, 5,
                                 3, 7, 2, 6, 8, 9, 5, 1, 4,
                                 8, 1, 4, 2, 5, 3, 7, 6, 9, 
                                 6, 9, 5, 4, 1, 7, 3, 8, 2] );
        assert!( g.solvable() );
        assert!( g.solved() );

        // unsolved grid
        g.cells[Grid::SIZE - 1] = Cell::new( 1289 );
        assert!( g.solvable() );
        assert!( !g.solved() );

        // unsolvable grid
        g.cells[0] = Cell::new( 0 );
        assert!( !g.solvable() );
        assert!( !g.solved() );

        // display
        assert_eq!( "0 8 3 |9 2 1 |6 5 7\n\
                     9 6 7 |3 4 5 |8 2 1\n\
                     2 5 1 |8 7 6 |4 9 3\n\
                     ------+------+------\n\
                     5 4 8 |1 3 2 |9 7 6\n\
                     7 2 9 |5 6 4 |1 3 8\n\
                     1 3 6 |7 9 8 |2 4 5\n\
                     ------+------+------\n\
                     3 7 2 |6 8 9 |5 1 4\n\
                     8 1 4 |2 5 3 |7 6 9\n\
                     6 9 5 |4 1 7 |3 8 _", format!( "{}", g ) );
    }
}
