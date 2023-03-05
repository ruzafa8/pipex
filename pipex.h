/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:30:41 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/03/05 17:32:28 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "libft/ft.h"


char	**px_get_path(char **env);
void	px_free_path(char **path);

char	*px_check_access(char *command, char **path);

int		px_exec(char **command, char **path, char **env);

#endif
