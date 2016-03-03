/** \file netcdfOpen.h
 */
#if !defined phy1610_netcdfOpen_h_included
#define phy1610_netcdfOpen_h_included

#include <netcdf>

/** netcdf is a strange class library, providing no means to close or open 
    a file other than a constructor and destructor.

   This wrapper class implements an open method, assuming a default constructed
   NcFile (or an actual NcFile object that will be closed before open).

   A close() method is also implemented for completeness sake.
 */  
class NcFileOpener
{
protected:
   netCDF::NcFile * h ; ///< hack.  allocate the handle on the heap since there's no open/close method.

public:

   void close()
   {
      if ( h )
      {
         delete h ;
         h = nullptr ;
      }
   }

   void open( const std::string &         filePath,
              netCDF::NcFile::FileMode    fMode )
   {
      close() ;

      h = new netCDF::NcFile( filePath, fMode ) ;
   }

   NcFileOpener() : h(nullptr)
   {
   }

   ~NcFileOpener()
   {
      close() ;
   }
} ;

#if 0
// doesn't work.  when ~netCDF::NcFile fires on the NcFileOpener, get a terminate call to due
// uncaught NcBadId exception.
class NcFileOpener : public netCDF::NcFile
{
   void close_if_opened()
   {
      using namespace netCDF ;

      // close the file if opened.
      try {
         this->~NcFile() ;
      }
      catch (netCDF::exceptions::NcBadId & e )
      {
         // std::cout << "unknown error" << std::endl ;
         // e.what() ;
      }
   }

public:
   void open( const std::string &         filePath,
              netCDF::NcFile::FileMode    fMode )
   {
      close_if_opened() ;

      new(this) netCDF::NcFile( filePath, fMode ) ;
   }

   void close()
   {
      close_if_opened() ;

      new(this) netCDF::NcFile( ) ;
   }
} ;
#endif

#endif
