#include "csapp.h"

void doit(int fd);


#define MAX_PATH_LENGTH     512  

/*
 * main -- the main routine
 * get listening port as paragram, and listening with I/O block
 */
int main(int argc, char **argv) {
    int listenfd, connfd, port;
    socklen_t clientlen;
    struct sockaddr_in clientaddr;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <document root dir> <port>\n", argv[0]);
        exit(0);
    }

    const char *path = argv[1];
    if(chdir(path) < 0) {
        fprintf(stderr, "%s: directory no exist or you can't access to it.\n", argv[0]);
        exit(0);
    }

    port = atoi(argv[2]);

    listenfd = Open_listenfd(port);
    while (1) {
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        doit(connfd);
        Close(connfd);
    }
}







