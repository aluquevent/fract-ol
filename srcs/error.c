#include "fractol.h"
#include <stdlib.h>

void	malloc_error(void)
{
	perror("Error allocating memory");
	exit (EXIT_FAILURE);
}

void	putstr_fd(char *str, int fd)
{
	if (NULL == str || fd < 0)
		return ;
	while (*str)
	{
		write(fd, str, 1);
		str++;
	}
}
