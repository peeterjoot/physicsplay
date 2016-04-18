/** \file readem.h
 */
#if !defined phy1610_readem_h_included
#define phy1610_readem_h_included

#include <cstddef>

/** read, abort on error */
void readem( const int fd, void * buf, const size_t bytes ) ;

#endif
