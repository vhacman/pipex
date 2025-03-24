/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:26:01 by gcollet           #+#    #+#             */
/*   Updated: 2025/03/24 11:21:05 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * get_path_dirs - Retrieves directories listed in the PATH variable.
 * @envp: The environment variables.
 *
 * Iterates through envp to find the PATH variable, then splits its value
 * using ':' as the delimiter. Returns a NULL-terminated array of directory
 * strings or NULL if PATH is not found.
 *
 * Return: An array of path strings or NULL on failure.
 */
char	**get_path_dirs(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

/**
 * find_cmd_in_dirs - Searches for a command in an array of directories.
 * @cmd: The command name (e.g., "ls").
 * @dirs: An array of directories from the PATH variable.
 *
 * Constructs a potential full path for each directory using the command name
 * and checks if it is accessible and executable.
 *
 * Return: A malloc'd string with the valid path or NULL if not found.
 */
char	*find_cmd_in_dirs(char *cmd, char **dirs)
{
	int		i;
	char	*tmp;
	char	*full;

	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}

/**
 * get_cmd_path - Resolves the full executable path of a command.
 * @cmd: The command to resolve.
 * @envp: The environment variables.
 *
 * If the command includes '/', it's assumed to be a path and checked directly.
 * Otherwise, it is searched for in the PATH directories.
 *
 * Return: A malloc'd string containing the full path or NULL if not found.
 */
char	*get_cmd_path(char *cmd, char **envp)
{
	char	**dirs;
	char	*result;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) != 0)
			return (NULL);
		return (ft_strdup(cmd));
	}
	dirs = get_path_dirs(envp);
	if (!dirs)
		return (NULL);
	result = find_cmd_in_dirs(cmd, dirs);
	while (dirs[i])
		free(dirs[i++]);
	free(dirs);
	return (result);
}

/**
 * split_command - Splits a command string into arguments and validates it.
 * @input: The full command string (e.g. "ls -l").
 *
 * If the input is empty or invalid, prints an error and exits with status 127.
 *
 * Return: A NULL-terminated array of strings (command + args).
 */
char	**split_command(char *input)
{
	char	**parts;

	parts = ft_split(input, ' ');
	if (!parts || !parts[0] || parts[0][0] == '\0')
	{
		ft_putstr_fd("Pipex: command not found: ", 2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd("\n", 2);
		free(parts);
		exit(127);
	}
	return (parts);
}

/**
 * resolve_cmd_path_or_exit - Resolves command path and exits on failure.
 * @parts: The split command array.
 * @envp: The environment variables.
 * @cmd_path: Pointer to store the resolved command path.
 *
 * If the command is not found, prints an error and exits with status 127.
 */
void	resolve_cmd_path_or_exit(char **parts, char **envp, char **cmd_path)
{
	int	i;

	i = 0;
	*cmd_path = get_cmd_path(parts[0], envp);
	if (!*cmd_path)
	{
		ft_putstr_fd("Bash: ", 2);
		ft_putstr_fd(parts[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		while (parts[i])
			free(parts[i++]);
		free(parts);
		exit(127);
	}
}
