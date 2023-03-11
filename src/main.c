/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:01:53 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/03/11 19:41:35 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_std(int fd_in, int fd_out)
{
	dup2(fd_in, 0);
	dup2(fd_out, 1);
}

void	first_command(int *fd_pipe,int fd_in, int fd_out, char *command, char **path, char **env)
{
	int	res;

	set_std(fd_in, fd_out);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	res = px_exec(ft_split(command, ' '), path, env);
	perror(strerror(res));
	close(fd_in);
}

void	second_command(int *fd_pipe, int fd_in, int fd_out, char *command, char **path, char **env)
{
	int	res;

	set_std(fd_in, fd_out);
	close(fd_pipe[1]);
	res = px_exec(ft_split(command, ' '), path, env);
	perror(strerror(res));
}

int	main(int argc, char **argv, char **env)
{
	int		pid1;
	int		pid2;
	int		fds[2];
	char	**path;
	int		result_code;
	int		fd;
	int		fd2;

	if (argc < 5)
		return (103);
	pipe(fds);
	path = px_get_path(env);
	pid1 = fork();
	if (pid1 < 0)
		return (0);
	if (pid1 == 0) // fillo
	{
		fd = open(argv[1], O_RDONLY);
		first_command(fds, fd, fds[1], argv[2], path, env);
	}
	else
	{
		pid2 = fork();
		if (pid2 < 0)
			return (0);
		if (pid2 == 0)
		{
			fd2 = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if (fd2 < 0)
				return (errno);
			second_command(fds, fds[0], fd2, argv[3], path, env);
		}
		else
		{
			close(fds[0]);
			close(fds[1]);
			waitpid(pid1, 0, 0);
			waitpid(pid2, &result_code, 0);
			if (WIFEXITED(result_code))
			{
				return (WEXITSTATUS(result_code));
			}
		}
	}
	px_free_path(path);
	return (errno);
}
