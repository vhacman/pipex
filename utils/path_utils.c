/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:26:01 by gcollet           #+#    #+#             */
/*   Updated: 2025/03/24 09:21:43 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
** Retrieves the list of directory paths defined in the PATH variable from envp.
** Returns a NULL-terminated array of strings, each representing a directory,
** or NULL if the PATH variable is not found.
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
** Searches for an executable version of the command 'cmd' in the array 'dirs'.
** For each directory, constructs a potential full path and checks if it is
** accessible and executable using access().
** Returns a newly allocated string with the valid path, or NULL if not found.
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
** Resolves the full executable path of a given command.
** If the command contains '/', it is treated as an absolute or relative path.
** Otherwise, it is searched in the directories from the PATH environment 
	variable.
** Returns a newly allocated string with the full path, or NULL if not found.
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

/*
** Splits the input string (e.g. "ls -l") into an array of strings,
** where the first element is the command and the rest are arguments.
** It then resolves the full path of the command and assigns it to *cmd_path.
** If the command is invalid or not found, prints an error and exits 
	with status 127.
** Returns the split command array.
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
		free(parts);
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

