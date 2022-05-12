mod cell;
mod grid;
mod examples;
mod solver;

use cell::Cell;
use grid::Grid;

fn main() {
    let c = Cell::new( 505 );
    let g = examples::lookup( "easy" );
    println!( "Hello, world! min: {}, count: {}, values: {}, solvable: {}, solved: {}", c.min(), c.count(), c.values(), c.solvable(), c.solved() );
    println!( "grid is solvable: {}, solved: {}", g.solvable(), g.solved() );
    println!( "{}", g );
}
