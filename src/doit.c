#include "csapp.h"

/*
 * doit -- deal with single client connect
 *
 */

#ifndef DEBUG
//#define DEBUG
#endif

void read_requesthdrs(rio_t *rp);
void clienterror(int fd, char *cause,  char *errnum, char *shortmsg, char *longmsg);
int parse_uri(char *uri, char* filename, char* cgiargs); 
void serve_static(int fd, char *filename, int filesize, int head);
void serve_dynamic(int fd, char *filename, char *cgiargs, int head); 

void doit (int fd)  {
    int is_static;
    struct stat sbuf;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char filename[MAXLINE], cgiargs[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, fd);
    Rio_readlineb(&rio, buf, MAXLINE);

    sscanf(buf, "%s %s %s", method, uri, version);
    // get request 
    // e.g. GET / HTTP/1.1 

    if (!strcasecmp(method, "GET") || !strcasecmp(method, "HEAD")) {

        read_requesthdrs(&rio);

        int head = strcasecmp(method, "HEAD") ? 0 : 1;

        is_static = parse_uri(uri, filename, cgiargs);
        if (stat(filename, &sbuf) < 0) {
            clienterror(fd, filename, "404", "Not found", 
                    "Tiny couldn't find this file");
            return;
        }

        if (is_static) { //serve static content
            if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)) {
                clienterror(fd, filename, "403", "Forbidden", 
                        "Tiny couldn't read the file");
                return;
            }
            serve_static(fd, filename, sbuf.st_size, head);
        }

        else  { // serve dynamic content
            if(!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)) {
                clienterror(fd, filename, "403", "Forbidden", 
                        "Tiny couldn't run the CGI program");
                return;
            }
            serve_dynamic(fd, filename, cgiargs, head);
        }

    }

    else if (!strcmp(method, "POST")) {
        read_requesthdrs(&rio);
        parse_uri(uri, filename, cgiargs);
        Rio_readlineb(&rio, cgiargs, MAXLINE);
        Rio_readlineb(&rio, buf, MAXLINE);

        if (stat(filename, &sbuf) < 0) {
            clienterror(fd, filename, "404", "Not found", 
                    "Tiny couldn't find this file");
            return;
        }

        if(!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)) {
            clienterror(fd, filename, "403", "Forbidden", 
                    "Tiny couldn't run the CGI program");
            return;
        }
        serve_dynamic(fd, filename, cgiargs, 0);
    }

    else {
        clienterror(fd, method, "501", "Not Implemented", 
                "Tiny does not implement this method");
        return;
    }
}


/*
 * read_requesthdrs: just bypass the request headers
 *                   
 */
void read_requesthdrs(rio_t *rp) {
    char buf[MAXLINE];

    Rio_readlineb(rp, buf, MAXLINE);
    while(strcmp(buf, "\r\n")) {
        Rio_readlineb(rp, buf, MAXLINE);
#ifdef DEBUG
        printf("%s", buf);
#endif
    }
    return;
}

