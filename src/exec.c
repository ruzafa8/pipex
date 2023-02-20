/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:25:57 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/02/20 21:43:12 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	px_exec(char **command, char **env)
{
	int	res;

	res = px_check_access(command[0], env);
	ft_printf("res::: %d\n", res); 
	// Verified that exists and can be executed
	if (res == 0)
	{
		if (execve(command[0], command, env) == -1)
		{
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
