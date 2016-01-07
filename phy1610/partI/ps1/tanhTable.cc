/* 
A program that generates a table of data. 

The table should have two columns, one column with x values ranging from -2.0 to 2.0, and a second column with values y=tanh(2x). 

In particular, your program should:

(a) Provide and use a function f that takes x as input and returns the value of tanh(2x).
(b) Divides the interval [-2,2] into n=100 segments.
(c) Compute the value (x) of the midpoint of each segment and the value (y) of the function f at those midpoints.

Write out the x and y values in tabular form (i.e. two-column ascii text), either to a file or to screen.
 */

double f(double x)
{
   return tanh( 2 * x ) ;
}
