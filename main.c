#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = ft_strlen(src);
	if (dstsize)
	{
		while (src[++i] && --dstsize)
			dst[i] = src[i];
		dst[i] = '\0';
	}
	return (j);
}

char *get_next_line(int fd)
{
	char *buf;
	int i;
	int nLocation;
	ssize_t	a;
	static char *intentoPrimeraLinea;
	char *primeraLinea;

	i = 0;
	nLocation = 0;
	buf = (char *)malloc(BUFFER_SIZE*sizeof(char));
	
	if(fd == -1)
	{
		printf("No hay archivo\n");
		return(NULL);
	}
	if(BUFFER_SIZE <= 0)
	{
		printf("BUFFER_SIZE tiene que ser mayor a 0\n");
		return(NULL);
	}
	else
	{
		a = read(fd, buf, BUFFER_SIZE);
		while(i < BUFFER_SIZE)
		{
			if(buf[i] == '\n')
			{
				printf("HAY UN BARRA ENE\n");
				nLocation = i + 1;
				break;
			}
			i++;
		}
		if(nLocation > 0)
		{
			ft_strlcpy(primeraLinea, buf, nLocation);
			printf("Primera linea:\n%s\n", primeraLinea);
		}
		else
		{
			intentoPrimeraLinea = buf;
			printf("Intento primera linea:\n%s\n", intentoPrimeraLinea);
		}
		printf("Lo que hay guardado en buf:\n%s\n", buf);
		printf("el size_t de read: %zd\n", a);
		printf("nlocation: %d\n", nLocation);
		return("primeraLinea");
	}
}

int	main ()
{
	int fd;

	fd = open("/Users/jelorria/cursus/get_next_line/text.txt", O_RDONLY);
	get_next_line(fd);
	return (0);
}
