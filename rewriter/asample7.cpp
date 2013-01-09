#define SQLC_STRING_SIZE 3
typedef unsigned char LicInt[SQLC_STRING_SIZE];

typedef enum alter_temporal_table_actions
{
  _ADD_VERSIONING  = 0x0000001,
  _DROP_SYS_PERIOD = 0x0000020
} alter_temporal_table_actions;


typedef struct SLicense
{
   bool          bLicenseFound;                    
   LicInt x ;

   #define MAX_ANNOTATION          257
   char          szAnnotation[MAX_ANNOTATION];     


   alter_temporal_table_actions b ;
   enum alter_temporal_table_actions c ;
} SLicense;

