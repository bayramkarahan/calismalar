#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

int main (int argc, char **argv)
  {
  const char *path;
  if (argc != 2) path = "/etc"; /* Set starting directory, if not passed */
  else
    path = argv[1];

  DIR *dir = opendir (path);
  if (dir)
    {
    struct dirent *dp;
    while ((dp = readdir(dir)) != NULL)
      {
      if (dp->d_name[0] != '.')
        {
        char *fullpath = malloc (strlen (path) + strlen (dp->d_name) + 2);
        strcpy (fullpath, path);
        strcat (fullpath, "/");
        strcat (fullpath, dp->d_name);
        if (dp->d_type == DT_DIR)
          {
          char **new_argv = malloc (2 * sizeof (char *));
          new_argv[0] = argv[0];
          new_argv[1] = fullpath;
          main (2, new_argv);
          free (new_argv);
          }
        else
          printf ("%s\n", fullpath);
        free (fullpath);
        }
      }
    closedir(dir);
    }
  else
    fprintf (stderr, "Can't open dir %s: %s", path, strerror (errno));
  return 0;
  }
