#include "csapp.h"

/*
 * parsr_uri: parse uri, get filename and cgiargs
 *
 */
int parse_uri(char *uri, char* filename, char* cgiargs)  {
    
    char *ptr;

    // static content
    if (!strstr(uri, "cgi-bin"))  {
        strcpy(cgiargs, "");
        strcpy(filename, ".");
        strcat(filename, uri);
        if (uri[strlen(uri) - 1] == '/') {
            strcat(filename, "home.html");
        }
        return 1;
    }

    // dynamic content
    else  {
        ptr = strstr(uri, "?");
        if (ptr) {
            strcpy(cgiargs, ptr + 1);
            *ptr = '\0';
        }
        else  {
            strcpy(cgiargs, "");
        }
        strcpy(filename, ".");
        strcat(filename, uri);
        return 0;
    }
    
}
