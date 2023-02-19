/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:01:53 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/02/19 21:09:36 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*concat_slash(char *c)
{
	char	*res;
	size_t	len;

	len = ft_strlen(c);
	res = (char *) ft_calloc(len + 2, sizeof(char));
	ft_memcpy(res, c, len);
	res[len + 1] = '/';
	return (res);
}

char	**get_path(char **env)
{
	char	**arg;
	char	**res;
	char	*true_res;

	while (env)
	{
		arg = ft_split(*env, '=');
		if (ft_strncmp(arg[0], "PATH", 4) == 0)
		{
			free(arg[0]);
			res = ft_split(arg[1], ':');
			int i = 0;
			while (res[i])
			{
				true_res = concat_slash(res[i]);
				free(res[i]);
				res[i] = true_res;
				i++;
			}
			free(arg[1]);
			free(arg);
			return (res);
		}
		else
		{
			free(arg[0]);
			free(arg[1]);
			free(arg);
		}
		env++;
	}
	return (0);
}

void	exec(char **command, char **env)
{
	int	res;
	res = access(command[0], F_OK | X_OK);
	ft_printf("%d", res);
	if (res)
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
	path = get_path(env);
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
	return (0);
}
