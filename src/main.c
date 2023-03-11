/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:01:53 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/03/11 20:07:11 by aruzafa-         ###   ########.fr       */
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

void	pipex(int fd_in, char *command1, char *command2, int fd_out, char **path, char **env)
{
	int	pid1;
	int	pid2;
	int	fds[2];
	int	result_code;

	pipe(fds);
	pid1 = fork();
	if (pid1 < 0)
		exit(pid1);
	if (pid1 == 0)
		first_command(fds, fd_in, fds[1], command1, path, env);
	else
	{
		pid2 = fork();
		if (pid2 < 0)
			exit(pid2);
		if (pid2 == 0)
			second_command(fds, fds[0], fd_out, command2, path, env);
		else
		{
			close(fds[0]);
			close(fds[1]);
			waitpid(pid1, 0, 0);
			waitpid(pid2, &result_code, 0);
			if (WIFEXITED(result_code))
				exit(WEXITSTATUS(result_code));
		}
	}

}

int	main(int argc, char **argv, char **env)
{
	char	**path;
	int		fd;
	int		fd2;

	if (argc < 5)
		return (103);
	path = px_get_path(env);
	fd = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd2 < 0)
		return (errno);
	pipex(fd, argv[2], argv[3], fd2, path, env);
	px_free_path(path);
	return (errno);
}
