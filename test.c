#include "minishell.h"

int	main(void)
{
	struct stat *buf;
	lstat("./libft", buf);
	printf("%o\n", buf -> st_mode);
}