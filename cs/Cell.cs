using System; using static System.Numerics.BitOperations; using NUnit.Framework; namespace Sudoku {

readonly struct Cell : IEquatable<Cell> {
    readonly ushort bits_;

    // public constructor
    public Cell( int values ) {
        var bits = 0;
        while( values > 0 ) { bits|= 1 << (values % 10); values/= 10; }
        bits_ = (ushort)(bits >> 1);
    }

    // private constructor
    Cell( ushort bits ) => bits_ = bits;

    // operators
    public static bool operator==( Cell a, Cell b ) => a.bits_ == b.bits_;
    public static bool operator!=( Cell a, Cell b ) => a.bits_ != b.bits_;
    public static Cell operator+( Cell a, Cell b ) => new( (ushort)( a.bits_ | b.bits_ ) ); // union of two cells
    public static Cell operator-( Cell a, Cell b ) => new( (ushort)( a.bits_ & ~b.bits_ ) ); // remove contents of cell 'b' from cell 'a'
    public static Cell operator&( Cell a, Cell b ) => new( (ushort)( a.bits_ & b.bits_ ) ); // intersection of two cells
    public static Cell operator~( Cell a ) => new( (ushort)( ~a.bits_ & 0x1FF ) ); // inverse of a cell

    // properties
    public int Count => PopCount( bits_ );
    public Cell Min => new( (ushort)MinSetBit( bits_ ) );
    public bool Single => IsPow2Or0( bits_ );
    public bool Solvable => 0 != bits_;
    public bool Solved => Single & Solvable;
    
    // converts bit flags back into numbers i.e. 1245
    public int Values { get {
        int value = 0;
        uint bits = bits_;
        for( var place = 1; 0 != bits; place*=10 ) {
            var maxBitIndex = Log2( bits );
            bits&= ~(1U << maxBitIndex); // remove the highest bit
            value+=(maxBitIndex + 1) * place; // add digit to result
        }
        return value;
    }}

    // indexer
    public Cell this[int i] { get {
        uint b = bits_;
        while( i-- > 0 ) b = RemoveMinSetBit( b );
        return new( (ushort)MinSetBit( b ) );
    }}

    // overrides
    public override int GetHashCode() => throw new NotImplementedException( "'cell' type not suitable for hashmap (too many collisions)" );
    public bool Equals( Cell c ) => bits_ == c.bits_;
    public override bool Equals( object o ) => throw new InvalidOperationException( "performance bug (boxing)" );
    public override string ToString() => Values.ToString();

    // utility functions
    static bool IsPow2Or0( int x ) => (x & (~x + 1)) == x;
    static uint MinSetBit( uint x ) => x & ~(x - 1);
    static uint RemoveMinSetBit( uint x ) => x & (x - 1);

    // tests
    [Test] public static void Test() {
        // solved cell
        Cell a = new( 3 );
        Assert.AreEqual( 4, a.bits_ );
        Assert.IsTrue( a.Single );
        Assert.IsTrue( a.Solvable );
        Assert.IsTrue( a.Solved );
        Assert.AreEqual( 1, a.Count );
        Assert.AreEqual( 3, a.Values );
        Assert.AreEqual( a, a.Min );
        Assert.AreEqual( "3", a.ToString() );
        Assert.AreEqual( new Cell( 3 ), a[0] );
        Assert.AreEqual( default( Cell ), a[1] );

        // unsolved cell
        a = new( 125687 );
        Assert.IsFalse( a.Single );
        Assert.IsTrue( a.Solvable );
        Assert.IsFalse( a.Solved );
        Assert.AreEqual( 6, a.Count );
        Assert.AreEqual( new Cell( 1 ), a.Min );
        Assert.AreEqual( 125678, a.Values );
        Assert.AreEqual( new Cell( 1 ), a[0] );
        Assert.AreEqual( new Cell( 2 ), a[1] );
        Assert.AreEqual( new Cell( 5 ), a[2] );
        Assert.AreEqual( new Cell( 6 ), a[3] );
        Assert.AreEqual( new Cell( 7 ), a[4] );
        Assert.AreEqual( new Cell( 8 ), a[5] );
        Assert.AreEqual( default( Cell ), a[6] );
        Assert.AreEqual( "125678", a.ToString() );

        // unsolvable cell
        a = new( 0 );
        Assert.AreEqual( 0, a.bits_ );
        Assert.IsTrue( a.Single );
        Assert.IsFalse( a.Solvable );
        Assert.IsFalse( a.Solved );
        Assert.AreEqual( 0, a.Count );
        Assert.AreEqual( 0, a.Values );
        Assert.AreEqual( default( Cell ), a.Min );
        Assert.AreEqual( default( Cell ), a[0] );
        Assert.AreEqual( "0", a.ToString() );

        // invalid value does not round-trip
        Assert.AreEqual( default( Cell ), new Cell( -1 ) );
        Assert.AreEqual( new Cell( 1 ), new Cell( 10 ) );
        Assert.AreEqual( new Cell( 12 ), new Cell( 121 ) );

        // operators
        Assert.IsTrue( new Cell( 12 ) == new Cell( 21 ) );
        Assert.IsTrue( new Cell( 0 ) != new Cell( 1 ) );
        Assert.AreEqual( new Cell( 1234589 ), new Cell( 12345 ) + new Cell( 98 ) );
        Assert.AreEqual( new Cell( 34 ), new Cell( 12345 ) - new Cell( 1256 ) );
        Assert.AreEqual( new Cell( 7 ), new Cell( 123457 ) & new Cell( 987 ) );
        Assert.AreEqual( new Cell( 13 ), ~new Cell( 2456789 ) );
    }
}

} // namespace
