#include <pwd.h>
#include <iostream>
#include <string.h>
#include <crypt.h>

//g++ -o upc passwdcmp.c -lcrypt
using namespace std;
int main()
{
    struct passwd *user;
    char login[200]="by", password[200]="2";

       if ((user= getpwnam(login)) == NULL)
            cout << "No such user\n";
       else if (!strcmp(user->pw_passwd, crypt(password, user->pw_passwd)))
            std::cout << "Password correct\n";
       else
            std::cout << "Password incorrect\n";
    return 0;
}
