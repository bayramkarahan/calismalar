#include <iostream>
#include <stdio.h>
#include <mntent.h>
#include <fcntl.h>
#include <string.h>
#include <err.h>
#include <fstab.h>
#include <blkid/blkid.h>
//sudo file -s /dev/sda1

int main(int argc, char *argv[])
{
   fstab * fs_rec; /* declare our pointer to the fstab structure */
   short i;
   if (setfsent() != 0)   /* set read pointer */
   {
      i = 1;
      fprintf( stdout, "fstab init successful\n");
      while (i == 1)
      {
         fs_rec = getfsent();
         if (fs_rec  != 0)
         {
            if (strcmp(fs_rec->fs_spec,"none") != 0 )  /* you will want to play with this to get just the partition(s) you are looking for */
            {
               fprintf( stdout,"%s,%s, %s\n",
                              fs_rec->fs_spec,
                              fs_rec->fs_vfstype,
                              blkid_get_tag_value(NULL,"UUID",fs_rec->fs_spec)
                      );
            }
         }
         else
         {
            fprintf( stdout,"got null pointer\n");
            i = 0;         /* got null opinter, end or error */
         }
      }
      fprintf( stdout,"cleaning up\n");
      endfsent();    /* free up resources */
   }
   else
   {
      fprintf( stdout, "fstab init failed\n");
   }

return 1;
}
