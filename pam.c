#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <stdio.h>
//gcc -o pam pam.c -lpam -lpam_misc
//sudo apt-get install libpam0g-dev

int main(int argc, char** argv)
{
if (argc < 2) {
fprintf(stderr, "Usage: %s <username>\n", argv[0]);
return 1;
}

const char* user = argv[1];
static struct pam_conv pam_conversation = { misc_conv, NULL };
pam_handle_t* pamh;

int res = pam_start(argv[0], user, &pam_conversation, &pamh);

if (res == PAM_SUCCESS) {
res = pam_authenticate(pamh, 0);
}

if (res == PAM_SUCCESS) {
res = pam_acct_mgmt(pamh, 0);
}

if (res == PAM_SUCCESS) {
fprintf(stdout, "Authenticated(Parola Doğru Yetkilendirildi).\n");
}
else {
fprintf(stdout, "Not Authenticated(Parola Doğrulanamadı Yetkilendirilemedi.\n");
}

pam_end(pamh, res);

return res == PAM_SUCCESS ? 0 : 1;
}





