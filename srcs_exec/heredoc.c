/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orfreoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:57:55 by orfreoua          #+#    #+#             */
/*   Updated: 2022/12/09 14:57:58 by orfreoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	create_file(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH, 0744);
	if (fd == -1)
		return (print_error("file creation failed"));
	return (fd);
}

char	*gen_name(t_exec *exec, int i)
{
	char	*nb;

	nb = ft_itoa(i);
	if (!nb)
	{
		print_error("malloc fail, gen_name()");
		return (NULL);
	}
	exec->hd.tab_of_name_file[i] = ft_strjoin("hold/temp", nb, 0);
	if (!exec->hd.tab_of_name_file[i])
		print_error("malloc failed 1");
	free(nb);
	return (exec->hd.tab_of_name_file[i]);
}

char	*add_contents(char *contents, char *s)
{
	contents = ft_strjoin(contents, s, 1);
	if (!contents)
	{
		print_error("malloc failed 2");
		return (NULL);
	}
	contents = ft_strjoin(contents, "\n", 1);
	if (!contents)
		print_error("malloc failed 3");
	return (contents);
}

int	to_fill_heredoc(int i, t_exec *exec)
{
	char	*s;
	int		start;
	char	*contents;

	contents = malloc(sizeof(char) * 1);
	if (!contents)
		return (print_error("heredoc()"));
	contents[0] = 0;
	start = 0;
	while (!start || strcmp(contents, exec->hd.tab_exit_code[i]))
	{
		start = 1;
		s = readline("> ");
		if (g_exit_ret == 424242)
			return (OK);
		if (!s || !strcmp(s, exec->hd.tab_exit_code[i]))
		{
			write(exec->hd.tab_fd[i], contents, ft_strlen(contents));
			if (!s)
				print_error_heredoc(exec, i);
			break ;
		}
		else
		{
			if (ft_strlen(s))
			{
				contents = add_contents(contents, s);
				if (!contents)
					return (print_error("2 heredoc()"));
			}
		}
	}
	return (OK);
}

int	heredoc(t_exec *exec, int i)
{
	signal_catching_mode(HEREDOC);
	exec->hd.tab_fd[i] = create_file(gen_name(exec, i));
	if (exec->hd.tab_fd[i] == ERROR)
		return (ERROR);
	if (to_fill_heredoc(i, exec) == ERROR)
		return (ERROR);
	//free_string(contents);
	return (OK);
}
