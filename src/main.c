/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:01:53 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/02/19 18:30:37 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	int		pid;
	char	**command;
	
	pid = fork();
	(void) argc;
	if (pid == 0) // fillo
	{
		command = ft_split(argv[2], ' ');
		if (!access(command[0], F_OK | X_OK))
		{
			// Verified that exists and can be executed
			execve(command[0], command, 0);
		}
		else
		{
			ft_printf("Command does not exists or has not got permission.\n");
		}
		exit(0);
	}
	else
	{
		waitpid(pid, 0, 0);
		ft_printf("finished waiting for command.\n");
	}
	return (0);
}
