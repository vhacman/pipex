/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:46:21 by vhacman           #+#    #+#             */
/*   Updated: 2025/03/24 16:42:00 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * execute - Resolves and executes a command using execve.
 * @av: The command string (e.g. "ls -l").
 * @envp: The environment variables.
 *
 * This function splits the command, resolves its full path,
 * and attempts to execute it. If execve fails, it delegates
 * error handling to handle_exec_error.
 */
void	execute(char *av, char **envp)
{
	char	**command;
	char	*path;

	command = split_command(av);
	resolve_cmd_path_or_exit(command, envp, &path);
	if (!command || !path)
		exit(127);
	if (execve(path, command, envp) == -1)
		handle_exec_error(path, command);
}

/**
 * free_split - Frees a null-terminated array of strings.
 * @array: The array to free.
 *
 * Frees each string in the array and then the array itself.
 * Safe to call with a NULL pointer.
 */
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
