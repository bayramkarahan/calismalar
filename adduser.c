#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static void createUser(char *userName, char *homeDir, int uid) {
    struct passwd * pwd = getpwent ();
    struct passwd pwd2;

    pwd =  getpwnam(userName);
    if (pwd != NULL) {
        return;
    }
    pwd2.pw_dir = homeDir;
    pwd2.pw_gecos=userName;
    pwd2.pw_name=userName;
    pwd2.pw_gid=uid;
    pwd2.pw_uid=uid;
    pwd2.pw_shell=strdup("/bin/bash");
    FILE *f = fopen("/etc/passwd", "a");
    if (f != NULL) {
        putpwent(&pwd2, f);
        fclose(f);
    }
    free (pwd2.pw_shell);
}

int main (int argc, char **argv) {
   createUser("test", "/home/test", 12345);
   return 0;
}

