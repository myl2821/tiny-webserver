#include "csapp.h"

void get_filetype(char *filename, char *filetype);
/*
 * serve_static -- serve static GET request
 *
 */
void serve_static(int fd, char *filename, int filesize)  {
    int srcfd;
    char *srcp, filetype[MAXLINE], buf[MAXBUF];
    
    // send response headers to client
    get_filetype(filename, filetype);
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    sprintf(buf, "%sServer: Tiny Web Server\r\n", buf);
    sprintf(buf, "%sContent-type: %s\r\n", buf, filetype);
    sprintf(buf, "%sContent-length: %d\r\n\r\n", buf, filesize);
    Rio_writen(fd, buf, strlen(buf));

    // send reponse body to client
    srcfd = Open(filename, O_RDONLY, 0);
        // copy file content into memory 
    srcp = Mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
    Close(srcfd);
    Rio_writen(fd, srcp, filesize);
    Munmap(srcp, filesize); // avoid memory leak
}


/*
 * get_filetype -- simple implement for getting content file type
 *
 */
void get_filetype(char *filename, char *filetype)  {
    if (strstr(filename, ".html")) {
        strcpy(filetype, "text/html");
    }
    else if (strstr(filename, ".gif"))  {
        strcpy(filename, "image/gif");
    }
    else if (strstr(filename, ".jpg"))  {
        strcpy(filename, "image/jpeg");
    }
    else {
        strcpy(filename, "text/plain");
    }
}