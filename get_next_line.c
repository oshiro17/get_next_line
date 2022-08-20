#include "get_next_line.h"
#include <string.h>

char *get_next_line(int fd)
{
    static char *mem;
    char *line;
    ssize_t len;

    line = malloc(sizeof(char) * BUFFER_SIZE);
    if (line == NULL)
        return (NULL);
    len = read(fd,line,BUFFER_SIZE);
    if(strchr(line,'\0'))
        mem = strchr(line,'\0');
    // while()
    if (len == -1)
        return (NULL);
    return(line);
}

int main(void)
{
    char *line;
    int fd;

    fd = open("test.txt", O_RDONLY);
    line = get_next_line(fd);
    printf("%s", line);
}
