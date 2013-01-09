// http://stackoverflow.com/questions/11250464/how-to-do-a-runtime-check-for-power7-or-greater-on-linuxppc
// http://stackoverflow.com/questions/11593890/programatic-way-to-find-elf-aux-header-or-envp-in-shared-library-code
// http://stackoverflow.com/questions/8875876/getting-the-elf-header-of-the-main-executable?rq=1

#include <stdio.h>
#include <elf.h>
#include <link.h>

static int
callback(struct dl_phdr_info *info, size_t size, void *data)
{
  int j;
  static int once = 0;

  if (once) return 0;
  once = 1;

  printf("relocation: 0x%lx\n", (long)info->dlpi_addr);

  for (j = 0; j < info->dlpi_phnum; j++) {
    if (info->dlpi_phdr[j].p_type == PT_NOTE) {
      printf("aux at loaded at %p\n",
             (void *) (info->dlpi_addr + info->dlpi_phdr[j].p_vaddr));
      break;
    }
  }
  return 0;
}

int main( int argc, char **argv, char **envp )
{
   /* walk past all env pointers */
   while ( *envp++ != NULL )
      ;

   /* and find ELF auxiliary vectors (if this was an ELF binary) */
#if 0
   Elf32_auxv_t * auxv = (Elf32_auxv_t *) envp ;
#else
   Elf64_auxv_t * auxv = (Elf64_auxv_t *) envp ;
#endif

printf( "aux: %p\n", auxv ) ;
   char * platform = NULL ;

   for ( ; auxv->a_type != AT_NULL ; auxv++ )
   {
      if ( auxv->a_type == AT_PLATFORM )
      {
         platform = (char *)auxv->a_un.a_val ;
         break;
      }
   }

   if ( platform )
   {
      printf( "%s\n", platform ) ;
   }

   dl_iterate_phdr(callback, NULL);

   return 0 ;
}
