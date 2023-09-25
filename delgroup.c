#include <stdio.h>
#include <grp.h>

int main() {
    struct group *grp;
    char *group_name = "mygroup";

    grp = getgrnam(group_name);
    if (grp == NULL) {
        printf("Grup bulunamadı.\n");
        return 1;
    }

    delete_group(grp);
    free(grp);

    printf("Grup başarıyla silindi.\n");

    return 0;
}

