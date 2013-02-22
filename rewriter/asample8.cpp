#include <signal.h>

// getTypeSize() drives an assert with this sample because I haven't setup the <signal.h> includes properly.
struct signalDisposition
{
   struct sigaction sigact ;
   int signum ;
} ;
