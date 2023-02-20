/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:01:53 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/02/20 20:11:52 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char **command, char **env)
{
	int	res;
	res = access(command[0], X_OK);
	ft_printf("access: %d", res);
	if (res == 0)
	{
		// Verified that exists and can be executed
		execve(command[0], command, env);
	}
	else
	{
		ft_printf("Command %s does not exists or has not got permission.\n", command[0]);
	}
}

int	main(int argc, char **argv, char **env)
{
	int		pid;
	char	**command;
	int		fds[2];
	char	**path;

	if (argc < 5)
		return (0);
	pipe(fds);
	path = px_get_path(env);
	pid = fork();
	if (pid == 0) // fillo
	{
		int fd = open(argv[1], O_RDONLY);
		dup2(fd, 0);
		dup2(fds[1], 1);
		command = ft_split(argv[2], ' ');
		exec(command, path);
		exit(0);
	}
	else
	{
		waitpid(pid, 0, 0);
		int fd2 = open(argv[4], O_WRONLY);
		dup2(fds[0], 0);
		dup2(fd2, 1);
		close(fd2);
		close(fds[1]);
		command = ft_split(argv[3], ' ');
		exec(command, path);
		ft_printf("\nfinished waiting for command.\n");
	}
	px_free_path(path);
	return (0);
}
