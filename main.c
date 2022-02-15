#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char *get_next_line(int fd)
{
	char *buf;
	int i;

	i = 0;
	buf = (char *)malloc(BUFFER_SIZE*sizeof(char));
	
	if(fd == -1)
	{
		printf("no hay archivo\n");
		return("pene");
	}
	else
	{
		while(buf[i] != '\n')
		{
			read(fd, buf, i + 1);
			i++;
		}
		printf("%d\n", BUFFER_SIZE);
		printf("%s\n", buf);
		return("a");
	}
}

int	main ()
{
	int fd;

	fd = open("/Users/jelorria/cursus/get_next_line/text.txt", O_RDONLY);
	get_next_line(fd);
	return (0);
}
