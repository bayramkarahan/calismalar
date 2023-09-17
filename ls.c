/**************************************************************
 * A simpler and shorter implementation of ls(1)
 * ls(1) is very similar to the DIR command on DOS and Windows.
 **************************************************************/
#include <stdio.h>
#include <dirent.h>

int listdir(const char *path) 
{
  struct dirent *entry;
  DIR *dp;

  dp = opendir(path);
  if (dp == NULL) 
  {
    perror("opendir");
    return -1;
  }

  while((entry = readdir(dp)))
   {
       if (entry->d_type == DT_DIR&&entry->d_name[0]!='.')
            {
           char *fullpath = malloc (strlen (path) + strlen (entry->d_name) + 2);
           strcpy (fullpath, path);
           strcat (fullpath, "/");
           strcat (fullpath, entry->d_name);
            printf("Dizin :%s\n",fullpath);
                listdir(fullpath);
                }

       if (entry->d_type!= DT_DIR&&entry->d_name[0]!='.')
           printf("Dosya: %s\n",entry->d_name);
   //puts(entry->d_name);
   }

  closedir(dp);
  return 0;
}

int main(int argc, char **argv)
{
  int counter = 1;

  if (argc == 1)
    listdir(".");

  while (++counter <= argc) {
    printf("\nListing %s...\n", argv[counter-1]);
    listdir(argv[counter-1]);
  }

  return 0;
}
