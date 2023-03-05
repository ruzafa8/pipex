/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:25:57 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/03/05 17:33:31 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	px_exec(char **command, char **path, char **env)
{
	char	*full_command;
	
	full_command = px_check_access(command[0], path);
	if (full_command != 0)
	{
		execve(full_command, command, env);
		return (errno);
	}
	else
		return (127); // Command not found exit
}
