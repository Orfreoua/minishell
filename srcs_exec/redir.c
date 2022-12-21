/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orfreoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:56:52 by orfreoua          #+#    #+#             */
/*   Updated: 2022/12/09 14:56:55 by orfreoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_redir(t_data *slot)
{
	if (slot->token == S_L_REDIR || slot->token == D_L_REDIR
		|| slot->token == S_R_REDIR || slot->token == D_R_REDIR)
		return (1);
	return (0);
}

int	openfile(char *filename, int mode)
{
	int	fd;

	if (!mode)
	{
		if (access(filename, F_OK))
			return (0);
		fd = open(filename, O_RDONLY);
		if (fd == -1)
		{
			close(fd);
			return (0);
		}
		return (fd);
	}
	else if (mode == 1)
	{
		fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (!access(filename, F_OK) && fd == -1)
			exit(1);
		return (fd);
	}
	fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0744);
	if (access(filename, F_OK) || fd == -1)
		exit(1);
	return (fd);
}

int	do_redir(int redir, char *str, t_exec *exec)
{
	if (redir == S_R_REDIR)
		exec->pipe.fd_pipe[1] = openfile(str, 1);
	else if (redir == D_R_REDIR)
		exec->pipe.fd_pipe[1] = openfile(str, 2);
	else if (redir == S_L_REDIR)
		exec->pipe.prev = openfile(str, 0);
	else if (redir == D_L_REDIR)
		exec->pipe.prev = openfile(str, 0);
	if (!exec->pipe.fd_pipe[0] || !exec->pipe.fd_pipe[1])
		return (ERROR);
	return (OK);
}

void	good_heredoc_to_redir(t_exec *exec, t_data *slot)
{
	while (1)
	{
		if (slot->suiv->suiv && slot->suiv->suiv->token == D_L_REDIR)
		{
			slot = slot->suiv->suiv;
			exec->hd.cpt++;
		}
		else
			return ;
	}
}

int	redir(t_data *data, t_exec *exec, int cpt_pipe)
{
	t_data	*slot;

	slot = pass_hold_pipe(data, cpt_pipe);
	while (slot && slot->token != PIPE)
	{
		if (is_redir(slot))
		{
			if (slot->token == D_L_REDIR)
			{
				good_heredoc_to_redir(exec, slot);
				if (do_redir(slot->token,
						exec->hd.tab_of_name_file[exec->hd.cpt], exec) == ERROR)
					return (ERROR);
			}
			else if (do_redir(slot->token, slot->suiv->str, exec) == ERROR)
				return (ERROR);
			break ;
		}
		slot = slot->suiv;
	}
	dup2(exec->pipe.prev, STDIN_FILENO);
	dup2(exec->pipe.fd_pipe[1], STDOUT_FILENO);
	return (OK);
}
