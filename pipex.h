/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:30:41 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/02/20 19:58:52 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "unistd.h"
# include "fcntl.h"
# include "libft/ft.h"

char	**px_get_path(char **env);
void	px_free_path(char **path);

#endif
