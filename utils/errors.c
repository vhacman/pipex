/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:55:54 by vhacman           #+#    #+#             */
/*   Updated: 2025/03/24 10:58:38 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(const char *msg)
{
	ft_putstr_fd("\033[31mError: \033[0m", 2);
	perror(msg);
	exit(EXIT_FAILURE);
}

void	print_permission_denied(char *path)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": Permission denied\n", 2);
}

void	print_no_such_file(char *path)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}
