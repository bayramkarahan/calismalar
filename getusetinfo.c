#include <stdio.h>
#include <pwd.h>
#include <iostream>


using namespace std;

int main()
{
    struct passwd *p_entry1, *p_entry2;
    char* username;



    cout<<"Insert username: ";
    cin>>username;
    /* Find user data by entered username */
    p_entry1 = getpwnam(username);

    printf("username = %s = %s"
                   " userid = %d group id = %d"
                   " real name = %s directory = %s"
                   " primary shell = %s",
    p_entry1->pw_name, p_entry1->pw_passwd,
            p_entry1->pw_uid, p_entry1->pw_gid,
            p_entry1->pw_gecos, p_entry1->pw_dir,
            p_entry1->pw_shell);

}

