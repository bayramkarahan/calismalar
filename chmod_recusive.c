#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#include <stdio.h>
#include <dirent.h>

int chmod_recusive(const char *path, char *permision)
{
    int i = strtol(permision, 0, 8);
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
        int ln=strlen (path) + strlen (entry->d_name) + 2;

       // char *fullpath = malloc(ln);
        char *fullpath = (char *)malloc(ln * sizeof(char));

        strcpy (fullpath, path);
        strcat (fullpath, "/");
        strcat (fullpath, entry->d_name);

        if (entry->d_type == DT_DIR&&entry->d_name[0]!='.')
        {

          //  printf("Dizin :%s\n",fullpath);

            chmod_recusive(fullpath,permision);
        }

        if (entry->d_type!= DT_DIR&&entry->d_name[0]!='.')
           // printf("Dosya: %s\n",entry->d_name);
        //puts(entry->d_name);
        if (chmod ( fullpath,i) < 0)
        {
            fprintf(stderr, "%s: error in chmod(%s, %s) - %d (%s)\n",
                    path, entry->d_name, permision, errno, strerror(errno));
            //exit(1);
        }
    }

    closedir(dp);
    return 0;
}

int main(int argc, char **argv)
{
    chmod_recusive("deneme","0777");
    /* char mode[] = "0700";
    char buf[100] = "deneme";
    int i;
    i = strtol(mode, 0, 8);
    if (chmod (buf,i) < 0)
    {
        fprintf(stderr, "%s: error in chmod(%s, %s) - %d (%s)\n",
                argv[0], buf, mode, errno, strerror(errno));
        exit(1);
    }*/
    return(0);
}

