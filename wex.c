#include <sys/inotify.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if(argc<3){
        printf("Usage : wex <file> <command>\n");
        return 1;
    }
    int inotify = inotify_init();
    int watch = inotify_add_watch(inotify, argv[1], IN_MODIFY);
    while(1) {
        struct inotify_event *buf = (struct inotify_event*)malloc(sizeof(struct inotify_event));
        read(inotify, buf, sizeof(struct inotify_event));
        if(buf->wd == watch) {
            system(argv[2]);
        }
        inotify_rm_watch(inotify, watch);
        watch = inotify_add_watch(inotify, argv[1], IN_MODIFY);
        free(buf);
    }
}
