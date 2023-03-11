/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:01:53 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/03/11 20:52:37 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_std(int fd_in, int fd_out)
{
	dup2(fd_in, 0);
	dup2(fd_out, 1);
}

void	first_command(int fd_in, int fd_out, char *command, t_data *data)
{
	int	res;

	set_std(fd_in, fd_out);
	close(data->pipe[0]);
	close(data->pipe[1]);
	res = px_exec(ft_split(command, ' '), data->path, data->env);
	perror(strerror(res));
	close(fd_in);
}

void	second_command(int fd_in, int fd_out, char *command, t_data *data)
{
	int	res;

	set_std(fd_in, fd_out);
	close(data->pipe[1]);
	res = px_exec(ft_split(command, ' '), data->path, data->env);
	perror(strerror(res));
}

void	pipex(char *command1, char *command2, t_data *data)
{
	int		pid1;
	int		pid2;
	int		result_code;

	pipe(data->pipe);
	pid1 = fork();
	if (pid1 < 0)
		exit(pid1);
	if (pid1 == 0)
		first_command(data->in, data->pipe[1], command1, data);
	else
	{
		pid2 = fork();
		if (pid2 < 0)
			exit(pid2);
		if (pid2 == 0)
			second_command(data->pipe[0], data->out, command2, data);
		else
		{
			close(data->pipe[0]);
			close(data->pipe[1]);
			waitpid(pid1, 0, 0);
			waitpid(pid2, &result_code, 0);
			if (WIFEXITED(result_code))
				exit(WEXITSTATUS(result_code));
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	int		permission;
	t_data	data;

	if (argc != 5)
		return (103);
	data.env = env;
	data.path = px_get_path(env);
	data.in = open(argv[1], O_RDONLY);
	if (data.in < 0)
		return (errno);
	permission = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	data.out = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, permission);
	if (data.out < 0)
		return (errno);
	pipex(argv[2], argv[3], &data);
	px_free_path(data.path);
	return (errno);
}
