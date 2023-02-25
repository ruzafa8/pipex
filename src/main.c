/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:01:53 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/02/25 16:59:43 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		px_exec(command, path, env);
		exit(0);
	}
	else
	{
		waitpid(pid, 0, 0);
		int fd2 = open(argv[4], O_WRONLY | O_CREAT);
		dup2(fds[0], 0);
		dup2(fd2, 1);
		close(fds[1]);
		command = ft_split(argv[3], ' ');
		px_exec(command, path, env);
	}
	px_free_path(path);
	return (0);
}
