#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

size_t		ft_strlen(const char *s)
{
	size_t strlen;

	strlen = 0;
	while (*s++)
		strlen++;
	return (strlen);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

int		main()
{
	int		fd;
	char	*buf;
	int		ret;
	char	bin[32];
	char	convert[8];

	buf = malloc(4096);
	fd = open("img.bmp", O_RDONLY);
	ret = read(fd, buf, 4095);
	buf[ret] = 0;

	int	i = 2;
	while (i < 6)
	{
		printf("%d\n", (int)buf[i]);
		i++;
	}
	free(buf);
	close(fd);
	return (0);
}
