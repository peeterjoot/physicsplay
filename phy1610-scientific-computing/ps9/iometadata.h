/** \file iometadata.h
 */
#if !defined phy1610_iometadata_h_included
#define phy1610_iometadata_h_included

/**
   metadata for the binary IO for wave1d

   Has the format:

   int      nper ;
   int      numPoints ;
   float    x[numPoints] ;
   float    time[] ;
 */
struct IOmetaData
{
    int    nper ;
    int    numPoints ;

    IOmetaData( ) {} 

    IOmetaData( int np, int npt ) : nper(np), numPoints(npt) { }
} ;

#endif
