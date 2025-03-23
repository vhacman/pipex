/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:26:01 by gcollet           #+#    #+#             */
/*   Updated: 2025/03/23 13:24:54 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Extracts the list of directories from the PATH variable in envp.
** Returns an array of directory strings (split by ':') or NULL if not found.
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

/*
** Searches for the given command (cmd) inside the array of directories.
** Constructs full paths and returns the first one that is executable.
** Returns NULL if not found.
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
		{
			return (full);
		}
		free(full);
		i++;
	}
	return (NULL);
}

/*
** Resolves the full executable path of a command.
** - If cmd contains '/', it is checked directly.
** - Otherwise, it is searched for inside the PATH directories.
** Returns a malloc'd string or NULL if not found.
*/
char	*get_cmd_path(char *cmd, char **envp)
{
	char	**dirs;
	char	*result;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
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

/*
** Splits the input string into a command and its arguments.
** Then resolves the full path of the command and assigns it to *cmd_path.
** Exits with status 127 if the command is invalid or not found.
*/
char	**split_cmd_and_find(char *input, char **envp, char **cmd_path)
{
	char	**parts;
	int		i;

	i = 0;
	parts = ft_split(input, ' ');
	if (!parts || !parts[0] || parts[0][0] == '\0')
	{
		ft_putstr_fd("Pipex: command not found: ", 2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	*cmd_path = get_cmd_path(parts[0], envp);
	if (!*cmd_path)
	{
		ft_putstr_fd("Pipex: command not found: ", 2);
		ft_putstr_fd(parts[0], 2);
		ft_putstr_fd("\n", 2);
		while (parts[i])
			free(parts[i++]);
		free(parts);
		exit(127);
	}
	return (parts);
}

/*
** Frees a NULL-terminated array of strings.
*/
void	free_words(char **words)
{
	int	i;

	i = 0;
	while (words && words[i])
		free(words[i++]);
	free(words);
}
