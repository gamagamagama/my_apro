#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

char *append_char(char *line, char c, int len)
{
    char *new_line = malloc(len + 2);
    if(!new_line)
        return NULL;
    for(int i = 0; i < len; i++) new_line[i] = line[i];
    new_line[len] = c;
    new_line[len + 1] = '\0';
    free(line);
    return(new_line);
}

char *get_next_line(int fd)
{
    if(fd < 0 || BUFFER_SIZE <= 0)
        return(NULL);
    static char buffer[BUFFER_SIZE];
    static int buf_pos = 0;
    static int buf_size = 0;
    char *line = NULL;
    int len = 0;

    while (1)
    {
        if(buf_pos >= buf_size)
        {
            buf_size = read(fd, buffer, BUFFER_SIZE);
            buf_pos = 0;
            if(buf_size <= 0)
                break;
        }
        char c = buffer[buf_pos++];
        line = append_char(line, c, len++);
        if(!line) return NULL;
        if(c == '\n') break;
    }
    if(!line) return NULL;
    return(line);
    
}
int main()
{
    int fd = open("test.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Failed to open file");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return 0;
}
