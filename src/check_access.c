/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:05:19 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/02/20 21:41:44 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*px_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = (char *) ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!res)
		return (0);
	i = -1;
	while (++i < s1_len)
		res[i] = s1[i];
	i = -1;
	while (++i < s2_len)
		res[s1_len + i] = s2[i];
	return (res);
}

int	px_check_access(char *command, char **env)
{
	char	*full_command;
	int		i;
	int		res;

	if (access(command, X_OK) == 0)
		return (0);
	i = 0;
	res = -1;
	while (env[i] && res == -1)
	{
		full_command = px_strjoin(env[i], command);
		if (!full_command)
			return (-1);
		ft_printf("Lets try with %s...\n", full_command);
		if (access(full_command, X_OK) == 0)
			res = 0;
		free(full_command);
		i++;
	}
	return (res);
}
