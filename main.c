#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*s;
	char	**tmp;

	tmp = malloc(sizeof(char *) * 2);
	while (1)
	{
		s = readline("minishell : ");
		tmp[0] = s;
		tmp[1] = 0;
		printf("%s\n", argv[2]);
		exit(0);
		if (execve(s, tmp, env) < 0)
			write(2, "error\n", 6);
			//env
		add_history(s);
	}
	return (0);
}