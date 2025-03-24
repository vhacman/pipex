/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:55:54 by vhacman           #+#    #+#             */
/*   Updated: 2025/03/24 16:20:43 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * handle_exec_error - Handles errors that occur during execve.
 * @path: The resolved path to the command.
 * @command: The command split into arguments.
 *
 * Based on the errno value, prints an appropriate error message
 * (e.g. permission denied, file not found) and exits with the
 * corresponding exit code (127 for general errors, 126 for permission denied).
 ENOENT = macro in errno.h --> file or directory doesn't exist
 */
void	handle_exec_error(char *path, char **command)
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

/**
 * error - Prints an error message in red and exits the program.
 * @msg: The custom message to be passed to perror.
 *
 * This function prints "Error: " followed by the system-generated
 * error message and then terminates the program with EXIT_FAILURE.
 */
void	error(const char *msg)
{
	ft_putstr_fd("\033[31mError: \033[0m", 2);
	perror(msg);
	exit(EXIT_FAILURE);
}

/**
 * print_permission_denied - Prints a permission denied message.
 * @path: The file or command that caused the permission error.
 *
 * This simulates the Bash-style "Permission denied" error for
 * the given path.
 */
void	print_permission_denied(char *path)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": Permission denied\n", 2);
}

/**
 * print_no_such_file - Prints a "no such file or directory" message.
 * @path: The file or command that could not be found.
 *
 * This mimics the typical Bash error when trying to access
 * a file or command that does not exist.
 */
void	print_no_such_file(char *path)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}
