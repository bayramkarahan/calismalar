#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <dirent.h>

int chown_recusive(const char *path,const char *user_name,const char *group_name)
{

/************************************************************************/
 uid_t          uid;
  gid_t          gid;
  struct passwd *pwd;
  struct group  *grp;

  pwd = getpwnam(user_name);
  if (pwd == NULL) {
      printf("Failed to get uid\n");
  }
  uid = pwd->pw_uid;

  grp = getgrnam(group_name);
  if (grp == NULL) {
      printf("Failed to get gid\n");
  }
  gid = grp->gr_gid;
/************************************************************************/
  if (chown(path, uid, gid) == -1) {
    printf("chown fail\n");
}
/********************************************************************/
    struct dirent *entry;
    DIR *dp;

    dp = opendir(path);
    if (dp == NULL)
    {
     printf("Failed to get gid\n");
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

        if (entry->d_type == DT_DIR)
        {
            if(entry->d_name[0]=='.'&&entry->d_name[1]=='.')continue;
            if(entry->d_name[0]=='.'&&entry->d_name[1]==NULL)continue;
           // printf("Dizin: %s %s %i %i\n",entry->d_name,fullpath,uid,gid);
          /*  if (chown(fullpath, uid, gid) == -1) {
              printf("chown fail\n");
          }*/
          chown_recusive(fullpath,user_name,group_name);
        }

        if (entry->d_type!= DT_DIR)
        {
           // printf("Dosya: %s %s %i %i\n",entry->d_name,fullpath,uid,gid);

          if (chown(fullpath, uid, gid) == -1) {
      		printf("chown fail\n");
  		}

  	}
    }

    closedir(dp);
    return 0;
}
/*
void do_chown (const char *file_path,
               const char *user_name,
               const char *group_name) 
{
  uid_t          uid;
  gid_t          gid;
  struct passwd *pwd;
  struct group  *grp;

  pwd = getpwnam(user_name);
  if (pwd == NULL) {
      die("Failed to get uid");
  }
  uid = pwd->pw_uid;

  grp = getgrnam(group_name);
  if (grp == NULL) {
      die("Failed to get gid");
  }
  gid = grp->gr_gid;




  if (chown(file_path, uid, gid) == -1) {
      die("chown fail");
  }
}*/
int main() {
//chown_recusive(const char *path,const char *user_name,const char *group_name)
chown_recusive("deneme","nova","karahan");
return 0;
}
