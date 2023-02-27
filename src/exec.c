/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:25:57 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/02/27 18:07:13 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	px_exec(char **command, char **path, char **env)
{
	char	*full_command;
	
	full_command = px_check_access(command[0], path);
	if (full_command != 0)
	{
		if (execve(full_command, command, env) == -1)
		{
			ft_printf("command: %s. Error:%d\n", command[0], errno);
			perror(strerror(errno));
			exit(errno);
		}
	}
	else
	{
		ft_printf("Command %s does not exists or has not got permission.\n", command[0]);
		exit(127); // Command not found exit
	}
}
