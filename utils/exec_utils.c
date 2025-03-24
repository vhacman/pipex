/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:46:21 by vhacman           #+#    #+#             */
/*   Updated: 2025/03/24 16:42:00 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_exec_error(char *path, char **command)
{
	int	code;

	code = 127;
	if (errno == EACCES)
	{
		print_permission_denied(path);
		code = 126;
	}
	else if (errno == ENOENT)
		print_no_such_file(path);
	else
		perror("bash");
	free(path);
	free_split(command);
	exit(code);
}

void	execute(char *av, char **envp)
{
	char	**command;
	char	*path;

	command = split_cmd_and_find(av, envp, &path);
	if (!command || !path)
		exit(127);
	if (execve(path, command, envp) == -1)
		handle_exec_error(path, command);
}

void	free_split(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}
