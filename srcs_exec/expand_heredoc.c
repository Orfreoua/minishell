/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akefeder <akefeder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 19:55:21 by akefeder          #+#    #+#             */
/*   Updated: 2022/12/22 20:35:30 by akefeder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*ft_heredoc_expand(char *str, char **env)
{
	char	**exp;
	int		i;

	
	if (str && ft_compare_char(str, '$') == FOUND)
	{
		i = 0;
		exp = ft_split_exp(str);
		free(str);
		str = modif_exp(exp, i, env);
		if (str == NULL)
			return (str);
	}
	return (str);
}
