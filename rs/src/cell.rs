use std::fmt;
use std::ops;

#[derive( Copy, Clone, Debug, Eq, PartialEq )]
pub struct Cell {
    bits: u16
}

impl Cell {
    // constructors
    pub fn new( mut values: u32 ) -> Cell {
        let mut bits = 0;
        while values > 0 { bits|= 1 << (values % 10); values/=10; }
        Cell { bits: (bits >> 1) as u16 }
    }

    // TODO: can use a constant for this Cell
    pub fn full() -> Cell { Cell { bits: 0x1FF } }
    
    // properties
    pub fn count( &self ) -> u32 { self.bits.count_ones() }
    pub fn min( &self ) -> Cell { Cell { bits: min_bit( self.bits ) } }    
    pub fn single( &self ) -> bool { is_pow2_or_zero( self.bits ) }
    pub fn solvable( &self ) -> bool { self.bits > 0 }    
    pub fn solved( &self ) -> bool { self.single() & self.solvable() }
    
    pub fn values( &self ) -> u32 {
        let mut values = 0;
        let mut place = 1;
        let mut bits = self.bits as u32;
        while bits > 0 {
            let max_bit_index = log2( bits );
            values+=(max_bit_index + 1) * place;
            place*=10;
            bits = clear_bit( bits, max_bit_index );
        }
        values
    }
}

// utility functions
fn clear_bit( x: u32, index: u32 ) -> u32 { x & !(1 << index) }
fn log2( x: u32 ) -> u32 { x.leading_zeros() ^ 31 }
fn is_pow2_or_zero( x: u16 ) -> bool { (x & (!x).wrapping_add( 1 )) == x }
fn min_bit( x: u16 ) -> u16 { x & !x.wrapping_sub( 1 ) }

// serialization
impl fmt::Display for Cell {
    fn fmt( &self, f: &mut fmt::Formatter<'_> ) -> fmt::Result {
        write!( f, "{}", self.values() )
    }
}

// '+' operator gives union of two cells
impl ops::Add for Cell {
    type Output = Cell;
    fn add( self, r: Cell ) -> Cell { Cell { bits: self.bits | r.bits } }
}

impl ops::AddAssign for Cell {
    fn add_assign( &mut self, r: Cell ) { *self = Cell { bits: self.bits | r.bits }; }
}

// '-' operator removes contents of cell
impl ops::Sub for Cell {
    type Output = Cell;
    fn sub( self, r: Cell ) -> Cell { Cell { bits: self.bits & !r.bits } }
}

impl ops::SubAssign for Cell {
    fn sub_assign( &mut self, r: Cell ) { *self = Cell { bits: self.bits & !r.bits } }
}

// '&' operator gives intersection of two cells
impl ops::BitAnd for Cell {
    type Output = Cell;
    fn bitand( self, r: Cell ) -> Cell { Cell { bits: self.bits & r.bits } }
}

impl ops::BitAndAssign for Cell {
    fn bitand_assign( &mut self, r: Cell ) { *self = Cell { bits: self.bits & r.bits } }
}

// '!' operater gives the inverse of a cell
impl ops::Not for Cell {
    type Output = Cell;
    fn not( self ) -> Cell { Cell { bits: !self.bits & 0x1FF } }
}

// tests
#[cfg(test)] mod tests {
    use super::*;

    #[test] fn test() {
        // zero cell
        let c = Cell::new( 0 );
        assert_eq!( 0, c.values() );
        assert_eq!( Cell::new( 0 ), c.min() );
        assert_eq!( 0, c.count() );
        assert!( c.single() );
        assert!( !c.solvable() );
        assert!( !c.solved() );
        assert_eq!( "0", format!( "{}", c ) );

        // solved cell
        let c = Cell::new( 500055550 );
        assert_eq!( 5, c.values() );
        assert_eq!( 1, c.count() );
        assert_eq!( Cell::new( 5 ), c.min() );
        assert!( c.single() );
        assert!( c.solvable() );
        assert!( c.solved() );
        assert_eq!( "5", format!( "{}", c ) );

        // unsolved cell
        let c = Cell::new( 1257007 );
        assert_eq!( 1257, c.values() );
        assert_eq!( 4, c.count() );
        assert_eq!( Cell::new( 1 ), c.min() );
        assert!( !c.single() );
        assert!( c.solvable() );
        assert!( !c.solved() );
        assert_eq!( "1257", format!( "{}", c ) );

        // full cell
        let c = Cell::full();
        assert_eq!( 123456789, c.values() );
        assert_eq!( 9, c.count() );

        // operators
        assert!( Cell::new( 12 ) == Cell::new( 21 ) );
        assert!( Cell::new( 0 ) != Cell::new( 1 ) );
        assert_eq!( Cell::new( 1234589 ), Cell::new( 12345 ) + Cell::new( 98 ) );
        assert_eq!( Cell::new( 34 ), Cell::new( 12345 ) - Cell::new( 1256 ) );
        assert_eq!( Cell::new( 7 ), Cell::new( 123457 ) & Cell::new( 987 ) );
        assert_eq!( Cell::new( 13 ), !Cell::new( 2456789 ) );

        // assignment operators
        let mut c = Cell::new( 123 );
        c+= Cell::new( 4 );
        assert_eq!( Cell::new( 1234 ), c );
        c-= Cell::new( 4 );
        assert_eq!( Cell::new( 123 ), c );
        c&= Cell::new( 13 );
        assert_eq!( Cell::new( 13 ), c );
    }
}
