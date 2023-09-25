#include <stdio.h>
#include <stdlib.h>
#include <grp.h>

int main() {
   FILE *f; 
    struct group *grp;
    char *group_name = "felik";
    gid_t group_id = 1030;
    char *group_members[] = {NULL};

    grp = getgrnam(group_name);
    if (grp == NULL) {
        // Grup bulunamadı, yeni bir grup oluşturulacak
        grp = (struct group *) malloc(sizeof(struct group));
        grp->gr_name = group_name;
        grp->gr_gid = group_id;
        grp->gr_mem = group_members;
        grp->gr_passwd = "x";
   f = fopen("/etc/group", "a+");
        // Yeni grup girdisini /etc/group dosyasına eklemek için putgrent kullanılır
        if (putgrent(grp,f) != 0) {
            perror("putgrent");
            exit(EXIT_FAILURE);
        }
    } else {
        // Grup zaten var, hata mesajı gösterilir
        printf("Grup zaten var\n");
    }
   fclose(f);
    return 0;
}

