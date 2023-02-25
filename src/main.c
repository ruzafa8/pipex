/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:01:53 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/02/25 18:32:28 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int		pid1;
	int		pid2;
	char	**command;
	int		fds[2];
	char	**path;

	if (argc < 5)
		return (0);
	pipe(fds);
	path = px_get_path(env);
	pid1 = fork();
	if (pid1 == 0) // fillo
	{
		int fd = open(argv[1], O_RDONLY);
		dup2(fd, 0);
		dup2(fds[1], 1);
		close(fds[0]);
		close(fds[1]);
		command = ft_split(argv[2], ' ');
		px_exec(command, path, env);
		exit(0);
	}
	else
	{
		pid2 = fork();
		if (pid2 == 0)
		{
			int fd2 = open(argv[4], O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
			dup2(fd2, 1);
			dup2(fds[0], 0);
			command = ft_split(argv[3], ' ');
			px_exec(command, path, env);
		}
		else
		{
			close(fds[0]);
			close(fds[1]);
			waitpid(pid1, 0, 0);
			waitpid(pid2, 0, 0);
		}
	}
	px_free_path(path);
	return (0);
}
