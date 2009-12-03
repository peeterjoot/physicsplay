#!/usr/bin/perl

my $s0 = q(
Let's write
\begin{align*}
R &= \A + \D\Be_{21} + \S \Be_{32} + \F \Be_{31} \\\\
\A &= \cos\left(\frac{\theta}{2}\right) \cos\left( \inv{2}\left(\psi+\phi\right) \right) \\\\
\D &= \cos\left(\frac{\theta}{2}\right) \sin\left( \inv{2}\left(\psi+\phi\right) \right) \\\\
\S &= \sin\left(\frac{\theta}{2}\right) \cos\left( \inv{2}\left(\psi-\phi\right) \right) \\\\
\F &= \sin\left(\frac{\theta}{2}\right) \sin\left( \inv{2}\left(\psi-\phi\right) \right) \\\\
\end{align*}

By inspection, these have the required property $\A^2 + \S^2 + \F^2 + \D^2 = 1$, and 
multiplying out the rotors yields the rotation matrix
\begin{align*}
R =
\begin{bmatrix}
- \F^2 + \S^2 - \D^2 + \A^2 & -2 \S \F -2 \A \D & +2 \D \S -2 \A \F \\\\
- 2 \S \F + 2 \A \D & +\F^2 - \S^2 - \D^2 + \A^2 & -2 \D \F -2 \A \S \\\\
+ 2 \D \S + 2 \A \F & -2 \D \F + 2 \A \S & - \F^2 - \S^2 + \D^2 + \A^2 \\\\
\end{bmatrix}
\end{align*}
) ;

my $s1 = q(
\begin{align*}
R &= \A - \D\Be_{21} - \S \Be_{32} - \F \Be_{31} \\\\
\A &= \cos\left(\frac{\theta}{2}\right) \cos\left( \inv{2}\left(\psi+\phi\right) \right) \\\\
\D &= -\cos\left(\frac{\theta}{2}\right) \sin\left( \inv{2}\left(\psi+\phi\right) \right) \\\\
\S &= -\sin\left(\frac{\theta}{2}\right) \cos\left( \inv{2}\left(\psi-\phi\right) \right) \\\\
\F &= -\sin\left(\frac{\theta}{2}\right) \sin\left( \inv{2}\left(\psi-\phi\right) \right) \\\\
\end{align*}

\begin{align*}
\begin{bmatrix}
 - \F^2 + \S^2 - \D^2 + \A^2 & - 2  \S \F + 2 \A \D & + 2 \D \S + 2 \A \F \\\\
 - 2 \S \F - 2 \A \D & + \F^2 - \S^2 - \D^2 + \A^2 & - 2 \D \F + 2 \A \S \\\\
 + 2 \D \S - 2 \A \F & - 2 \D \F - 2 \A \S & - \F^2 - \S^2 + \D^2 + \A^2 \\\\
\end{bmatrix}
\end{align*}
) ;

my $s2 = q(
\begin{align*}
R &= \A + \S\Be_{21} - \D \Be_{32} - \F \Be_{31} \\\\
\A &= \cos\left(\frac{\theta}{2}\right) \cos\left( \inv{2}\left(\psi+\phi\right) \right) \\\\
\S &= \cos\left(\frac{\theta}{2}\right) \sin\left( \inv{2}\left(\psi+\phi\right) \right) \\\\
\D &= -\sin\left(\frac{\theta}{2}\right) \cos\left( \inv{2}\left(\psi-\phi\right) \right) \\\\
\F &= -\sin\left(\frac{\theta}{2}\right) \sin\left( \inv{2}\left(\psi-\phi\right) \right) \\\\
\end{align*}
#endif

\begin{align*}
\begin{bmatrix}
 - \F^2 + \D^2 - \S^2 + \A^2 & - 2 \D \F - 2 \A \S & - 2 \S \D + 2 \A \F \\\\
 - 2 \D \F + 2 \A \S & + \F^2 - \D^2 - \S^2 + \A^2 & + 2 \S \F + 2 \A \D \\\\
 - 2 \S \D - 2 \A \F & + 2 \S \F - 2 \A \D & - \F^2 - \D^2 + \S^2 + \A^2 \\\\
\end{bmatrix}
\end{align*}
) ;

my $s3 = q(

\begin{align*}
R &= \A - \S\Be_{21} + \D \Be_{32} - \F \Be_{31} \\\\
\A &= \cos\left(\frac{\theta}{2}\right) \cos\left( \inv{2}\left(\psi+\phi\right) \right) \\\\
\S &= -\cos\left(\frac{\theta}{2}\right) \sin\left( \inv{2}\left(\psi+\phi\right) \right) \\\\
\D &= \sin\left(\frac{\theta}{2}\right) \cos\left( \inv{2}\left(\psi-\phi\right) \right) \\\\
\F &= -\sin\left(\frac{\theta}{2}\right) \sin\left( \inv{2}\left(\psi-\phi\right) \right) \\\\
\end{align*}

\begin{align*}
\begin{bmatrix}
 - \F^2 + \D^2 - \S^2 + \A^2 & + 2 \D \F + 2 \A \S & - 2  \S \D + 2 \A \F \\
+  2 \D \F - 2  \A \S & +  \F^2 - \D^2 - \S^2 + \A^2 & - 2  \S \F - 2  \A \D \\
 - 2  \S \D - 2  \A \F & - 2  \S \F + 2 \A \D & - \F^2 - \D^2 + \S^2 + \A^2 \\
\end{bmatrix}
\end{align*}
) ;

my $s = q(
\begin{align*}
R &= \A - \S\Be_{21} - \D \Be_{32} + \F \Be_{31} \\\\
\A &= \cos\left(\frac{\theta}{2}\right) \cos\left( \inv{2}\left(\psi+\phi\right) \right) \\\\
\S &= -\cos\left(\frac{\theta}{2}\right) \sin\left( \inv{2}\left(\psi+\phi\right) \right) \\\\
\D &= -\sin\left(\frac{\theta}{2}\right) \cos\left( \inv{2}\left(\psi-\phi\right) \right) \\\\
\F &= \sin\left(\frac{\theta}{2}\right) \sin\left( \inv{2}\left(\psi-\phi\right) \right) \\\\
\end{align*}

\begin{align*}
\begin{bmatrix}
 - \F^2 + \D^2 - \S^2 + \A^2 & + 2 \D \F + 2 \A \S & + 2 \S \D - 2 \A \F \\\\
+ 2 \D \F - 2 \A \S & + \F^2 - \D^2 - \S^2 + \A^2 & + 2 \S \F + 2 \A \D \\\\
+ 2 \S \D + 2 \A \F & + 2 \S \F - 2 \A \D & - \F^2 - \D^2 + \S^2 + \A^2 \\\\
\end{bmatrix}
\end{align*}
) ;

#print $s ;

my @a = (qw(alpha beta gamma delta)) ;
munge( $a[0], $a[1], $a[2], $a[3] ) ;
munge( $a[0], $a[1], $a[3], $a[2] ) ;
munge( $a[0], $a[2], $a[3], $a[1] ) ;
munge( $a[0], $a[2], $a[1], $a[3] ) ;
munge( $a[0], $a[3], $a[1], $a[2] ) ;
munge( $a[0], $a[3], $a[2], $a[1] ) ;

munge( $a[1], $a[0], $a[2], $a[3] ) ;
munge( $a[1], $a[0], $a[3], $a[2] ) ;
munge( $a[1], $a[2], $a[3], $a[0] ) ;
munge( $a[1], $a[2], $a[0], $a[3] ) ;
munge( $a[1], $a[3], $a[0], $a[2] ) ;
munge( $a[1], $a[3], $a[2], $a[0] ) ;

munge( $a[2], $a[1], $a[0], $a[3] ) ;
munge( $a[2], $a[1], $a[3], $a[0] ) ;
munge( $a[2], $a[0], $a[3], $a[1] ) ;
munge( $a[2], $a[0], $a[1], $a[3] ) ;
munge( $a[2], $a[3], $a[1], $a[0] ) ;
munge( $a[2], $a[3], $a[0], $a[1] ) ;

munge( $a[3], $a[1], $a[2], $a[0] ) ;
munge( $a[3], $a[1], $a[0], $a[2] ) ;
munge( $a[3], $a[2], $a[0], $a[1] ) ;
munge( $a[3], $a[2], $a[1], $a[0] ) ;
munge( $a[3], $a[0], $a[1], $a[2] ) ;
munge( $a[3], $a[0], $a[2], $a[1] ) ;

exit 0 ;

sub munge
{
   my (@replace) = @_ ;
   my $r = $s ;
   my @pats = (qw(A D S F)) ;

   $v++ ;
   print "\n\n\n\n VERSION $v\n\n\n\n" ;

   for ( my $i = 0 ; $i < 4 ; $i++ )
   {
      $r =~ s/$pats[$i]/$replace[$i]/sg ;
   }

   print $r ;
}
