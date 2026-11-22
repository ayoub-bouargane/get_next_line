
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line_bonus.h"
int main()
{
    int fd;
    int fd1;
     char *str;

    fd = open("file.txt", O_RDWR | O_CREAT, 0644);
    // str = get_next_line(fd);
    //     printf("%s",str);
    //     free(str);
    fd1 = open("file1.txt", O_RDWR | O_CREAT, 0644);
    str = get_next_line(fd);
        printf("%s",str);
        free(str);
    //  str = get_next_line(fd);
    //     printf("%s",str);
    //     free(str);
    str = get_next_line(fd1);
        printf("%s",str);
        free(str);
          str = get_next_line(fd);
        printf("%s",str);
        free(str);
          str = get_next_line(fd1);
        printf("%s",str);
        free(str);
}
