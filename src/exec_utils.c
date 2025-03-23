/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:46:21 by vhacman           #+#    #+#             */
/*   Updated: 2025/03/23 11:46:21 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Displays a formatted error message using perror() and exits the program.
** The error message is prefixed with "Error: " in red.
** Used throughout the project to handle critical failures (open, fork, pipe...).
*/
void	error(const char *msg)
{
	ft_putstr_fd("\033[31mError: ", 2);
	perror(msg);
	ft_putstr_fd("\033[0m", 2);
	exit(EXIT_FAILURE);
}

/*
** Executes a command by:
** 1. Splitting the command string into arguments.
** 2. Resolving the full path using the environment.
** 3. Replacing the current process with the command using execve().
**
** If execve fails, frees resources and exits with the appropriate error code:
** - 126: Permission denied
** - 127: Command not found or other execution error
*/
void	execute(char *av, char **envp)
{
	char	**command;
	char	*path;

	command = split_cmd_and_find(av, envp, &path);
	if (execve(path, command, envp) == -1)
	{
		free(path);
		free_words(command);
		if (errno == EACCES)
			exit (126);
		else
			exit (127);
	}
}
