using System; using System.Text; using NUnit.Framework; namespace Sudoku {

unsafe struct Grid {
    public const int WIDTH = 9, HEIGHT = 9, SIZE = WIDTH * HEIGHT;
    fixed ushort _cells[SIZE];
    
    // constructor
    public Grid( params int[] numbers ) {
        if( numbers.Length != SIZE ) throw new ArgumentOutOfRangeException( $"must specify {SIZE} values, but got {numbers.Length} values" );
        for( var i = 0; i < SIZE; i++ ) this[i] = new Cell( numbers[i] );
    }

    // properties
    public bool Solvable { get { for( var i = 0; i < SIZE; i++ ) if( !this[i].Solvable ) return false; return true; }}
    public bool Solved { get { for( var i = 0; i < SIZE; i++ ) if( !this[i].Solved ) return false; return true; } }

    // indexers
    public Cell this[int x, int y] { get => this[x + y*WIDTH]; set => this[x + y*WIDTH] = value; }
    public Cell this[int i] {
        get { if( (i < 0) | (i >= SIZE) ) throw new IndexOutOfRangeException(); var c = _cells[i]; return *(Cell*)&c; }
        set { if( (i < 0) | (i >= SIZE) ) throw new IndexOutOfRangeException(); _cells[i] = *(ushort*)&value; }
    }

    // methods
    public bool Equals( ref Grid g ) {
        for( var i = 0; i < SIZE; i++ ) if( _cells[i] != g._cells[i] ) return false;
        return true;
    }

    // overrides
    public override string ToString() => ToString( false );
    public string ToString( bool showSets ) {
        var b = new StringBuilder();
        for( var i = 0; i < SIZE; i++ ) {
            if( i > 0 ) {
                if( 0 == i % 9 ) { b.AppendLine(); if( 0 == i % 27 ) b.AppendLine( "------+------+------" ); }
                else { b.Append( ' ' ); if( 0 == i % 3 ) b.Append( '|' ); }
            }
            var values = this[i].Values;
            if( showSets | (values < 10) ) b.Append( values ); else b.Append( '_' );
        }
        return b.ToString();
    }

    // tests
    [Test] public static void Test() {
        // solved grid
        var g = new Grid(
            4, 8, 3, 9, 2, 1, 6, 5, 7,
            9, 6, 7, 3, 4, 5, 8, 2, 1,
            2, 5, 1, 8, 7, 6, 4, 9, 3,
            5, 4, 8, 1, 3, 2, 9, 7, 6,
            7, 2, 9, 5, 6, 4, 1, 3, 8,
            1, 3, 6, 7, 9, 8, 2, 4, 5,
            3, 7, 2, 6, 8, 9, 5, 1, 4,
            8, 1, 4, 2, 5, 3, 7, 6, 9, 
            6, 9, 5, 4, 1, 7, 3, 8, 2 );
        Assert.IsTrue( g.Solvable );
        Assert.IsTrue( g.Solved );

        // unsolved grid
        g[8,8] = new Cell( 1289 );
        Assert.IsTrue( g.Solvable );
        Assert.IsFalse( g.Solved );
        
        // unsolvable grid
        g[4,4] = new Cell( 0 );
        Assert.IsFalse( g.Solvable );
        Assert.IsFalse( g.Solved );
        
        // tostring
        Assert.AreEqual(
@"4 8 3 |9 2 1 |6 5 7
9 6 7 |3 4 5 |8 2 1
2 5 1 |8 7 6 |4 9 3
------+------+------
5 4 8 |1 3 2 |9 7 6
7 2 9 |5 0 4 |1 3 8
1 3 6 |7 9 8 |2 4 5
------+------+------
3 7 2 |6 8 9 |5 1 4
8 1 4 |2 5 3 |7 6 9
6 9 5 |4 1 7 |3 8 _", g.ToString() );

        // toString w/ showSets
        Assert.AreEqual(
@"4 8 3 |9 2 1 |6 5 7
9 6 7 |3 4 5 |8 2 1
2 5 1 |8 7 6 |4 9 3
------+------+------
5 4 8 |1 3 2 |9 7 6
7 2 9 |5 0 4 |1 3 8
1 3 6 |7 9 8 |2 4 5
------+------+------
3 7 2 |6 8 9 |5 1 4
8 1 4 |2 5 3 |7 6 9
6 9 5 |4 1 7 |3 8 1289", g.ToString( showSets: true ) );
    }
}

} // namespace
