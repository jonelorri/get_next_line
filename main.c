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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*ptr;
	const unsigned char	*ptr2;

	if (!dest && !src)
		return (NULL);
	ptr = (unsigned char *)dest;
	ptr2 = (unsigned char *)src;
	while (n-- > 0)
		*(ptr++) = *(ptr2++);
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char	*dest;

	dest = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, s1, ft_strlen(s1));
	*(dest + ft_strlen(s1)) = '\0';
	return (dest);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstl;
	size_t	srcl;
	size_t	i;

	dstl = ft_strlen(dst);
	srcl = ft_strlen(src);
	i = dstl;
	if (dstl >= dstsize)
		return (dstsize + srcl);
	while (dstl < dstsize - 1 && *src)
		*(dst + dstl++) = *src++;
	*(dst + dstl) = '\0';
	return (i + srcl);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1, s1_len + 1);
	ft_strlcat(&dest[s1_len], s2, s2_len + 1);
	return (dest);
}

char *get_next_line(int fd)
{
	char		*buf;
	int		i;
	int		nLocation;
	char		*intentoPrimeraLinea;
	char		*primeraLinea;
	int		contador;
	size_t		a;

	contador = 0;
	i = 0;
	nLocation = 0;
	buf = (char *)malloc((BUFFER_SIZE + 1)*sizeof(char));

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
		while(1)
		{
			a = read(fd, buf, BUFFER_SIZE);
			if(a == 0)
				return("");	// si el a es 0, se a terminado el file, porq read no ha leido nada. *manejo de erroes*
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
			i = 0;
			if(a != BUFFER_SIZE  && contador == 0 && nLocation == 0)
			{
				printf("el valor de a: %zu\n", a);
				primeraLinea = ft_strdup("");
				ft_strlcpy(primeraLinea, buf, a + 1);
				printf("linea con barra cero:\n%s\n", primeraLinea);	//bro que no se te olvide sumar un \n al final de primeraLinea
				return(primeraLinea);
			}
			if(a != BUFFER_SIZE && contador != 0)
			{
				ft_strlcpy(primeraLinea, buf, a + 1);
				primeraLinea = ft_strjoin(intentoPrimeraLinea, primeraLinea);	//aqui tmbn lo del barra ene
				printf("linea con barra cero: \n%s\n", primeraLinea);
				return(primeraLinea);
			}
			if(nLocation > 0 && contador == 0)
			{
				ft_strlcpy(primeraLinea, buf, nLocation);
				printf("Primera linea:\n%s\n", primeraLinea);
				break;
			}
			else if(nLocation > 0 && contador != 0)
			{
				ft_strlcpy(primeraLinea, buf, nLocation);
				primeraLinea = ft_strjoin(intentoPrimeraLinea, primeraLinea);
				printf("Primera linea:\n%s\n", primeraLinea);
				break;
			}
			else if(nLocation == 0 && contador == 0)
			{
				intentoPrimeraLinea = ft_strdup("");
				intentoPrimeraLinea = ft_strjoin(intentoPrimeraLinea, buf);
				printf("Vamos con el first try:\n%s\n", intentoPrimeraLinea);
			}
			else if(nLocation == 0 && contador != 0)	
			{
				intentoPrimeraLinea = ft_strjoin(intentoPrimeraLinea, buf);
				printf("Intento primera linea:\n%s\n", intentoPrimeraLinea);
			}
			printf("Lo que hay guardado en buf:\n%s\n", buf);
			printf("nlocation: %d\n", nLocation);
			printf("a = %zu\n", a);
			printf("----------------\n");
			contador++;
			sleep(2);
		}
	}
	free(buf);
	return("hola");
}

int	main ()
{
	int fd;

	fd = open("/Users/jonelorriaga/programacion/42/gnl/text2.txt", O_RDONLY);
	get_next_line(fd);
	return (0);
}
