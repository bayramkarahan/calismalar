#define FUSE_USE_VERSION 31
#include <fuse3/fuse.h>
#include <stdio.h>
#include <stdlib.h>

static void* pre_init(struct fuse_conn_info *conn, struct fuse_config *cfg){
        printf("[init] called\n");
        (void) conn;
        return NULL;
}
static struct fuse_operations opr = {
        .init = pre_init,
};
int main(int argc, char *argv[]){
        return fuse_main(argc, argv, &opr, NULL);
}
