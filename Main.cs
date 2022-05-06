using System; using System.Linq; namespace Sudoku {
	
static class MainClass {
	static void Main( params string[] args ) {
		switch( args.TryGet( 0 ) ) {
			case "test":
				Cell.Test();
				Grid.Test();
				Solver.Test();
				return;

			case "solve": {
				var arg1 = args.TryGet( 1, "easy" );
				var grid = 81 == arg1.Length ?
					new Grid( arg1.Select( c => int.TryParse( c.ToString(), out var n ) ? n : 123456789 ).ToArray<int>() ) :
					Examples.Get( arg1 );
				grid.Solve( interactive: true, showSets: args.TryGet( 2, "" ).Equals( "showSets", StringComparison.OrdinalIgnoreCase ) );
				return;
			}

			// unrecognized command
			default:
				Console.WriteLine( "invalid command: '" + args.TryGet( 0, "" ) + "'" );
				Console.WriteLine( "valid comamnds are: " );
				Console.WriteLine( "test" );
				Console.WriteLine( "solve [example-name] [optional - showSets]" );
				Console.WriteLine( "solve 1,2,3,4,5,6,7,8,9 ... (need 81 values) [optional - showSets]" );
				return;
		}
	}

	// private extension methods
	static string TryGet( this string[] s, int i, string @default = null ) => (i >= 0) & (i < s.Length) ? s[i] : @default;
}

} // namespace
