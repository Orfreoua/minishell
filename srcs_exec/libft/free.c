/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orfreoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:00:27 by orfreoua          #+#    #+#             */
/*   Updated: 2022/12/09 15:00:30 by orfreoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_string(char *s)
{
	free(s);
	s = NULL;
}

int	free_tab_error(char **t, int n)
{
	int	i;

	i = 0;
	while (t && t[i] && i < n)
	{
		free(t[i]);
		t[i] = NULL;
		i++;
	}
	free(t);
	t = NULL;
	return (-1);
}

void	free_tab(char **t)
{
	int	i;

	i = 0;
	while (t && t[i])
	{
		free(t[i]);
		t[i] = NULL;
		i++;
	}
	free(t);
	t = NULL;
}
