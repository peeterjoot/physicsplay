// Stroustrop 10.4:  constexpr capable integer square root function
constexpr int f( int sq, int d, int a )
{
	return sq <= a ? f( sq + d, d + 2, a ) : d ;
}

constexpr int isqrt( int x )
{
	return f( 1, 3, x)/2 - 1 ;
}
