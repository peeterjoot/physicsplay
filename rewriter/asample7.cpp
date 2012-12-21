#define SQLC_STRING_SIZE 3
typedef unsigned char LicInt[SQLC_STRING_SIZE];

typedef struct SLicense
{
   bool          bLicenseFound;                    
   LicInt x ;

   #define MAX_ANNOTATION          257
   char          szAnnotation[MAX_ANNOTATION];     

} SLicense;

