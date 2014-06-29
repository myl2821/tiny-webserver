#include "csapp.h"


static void sigchld_handler(int sig) {
   while(waitpid(-1, 0, WNOHANG)) {
        ;
    }
   return;
}

/*
 * serve_dynamic -- serve dynamic GET request
 *
 */
void serve_dynamic(int fd, char *filename, char *cgiargs) {
    char buf[MAXLINE], *emptylist[] =  { NULL };

    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Server: Tiny Web Server\r\n");
    Rio_writen(fd, buf, strlen(buf));

    Signal(SIGCHLD, sigchld_handler);
    if (Fork() == 0)  {
        setenv("QUERY_STRING", cgiargs, 1);
        Dup2(fd, STDOUT_FILENO);
        Execve(filename, emptylist, environ);
    }
}


