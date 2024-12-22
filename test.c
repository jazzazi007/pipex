#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
	int fd;

	fd = open("example.txt", O_WRONLY | O_CREAT, 0644);
    printf("start of the file");
	dup2(fd, STDOUT_FILENO);
	close(fd);
	printf("This is printed in example.txt!\n");
    printf("this is another test\n");
    write(1, "hi", 2);

	return (0);
}

/*int main(int argc, char **argv, char **envp) {
int id = fork();
int id2 = fork();

printf("hello id1: %d id2: %d\n", id, id2);
return(0);
}*/
