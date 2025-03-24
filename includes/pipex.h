/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 08:00:23 by vhacman           #+#    #+#             */
/*   Updated: 2025/03/24 10:23:18 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "../libft/includes/libft.h"

// exec_utils.c
void	execute(char *cmd_input, char **envp);
void	free_split(char **array);

// path_utils.c
char	**get_path_dirs(char **envp);
char	*find_cmd_in_dirs(char *cmd, char **dirs);
char	*get_cmd_path(char *cmd, char **envp);
char	**split_command(char *input);
void	resolve_cmd_path_or_exit(char **parts, char **envp, char **cmd_path);

//errors
void	print_no_such_file(char *path);
void	print_permission_denied(char *path);
void	error(const char *msg);
void	handle_exec_error(char *path, char **command);

// pipex.c
void	run_first_command(char **av, char **envp, int *fd);
void	run_second_command(char **av, char **envp, int *fd);
void	pipex(char **av, char **envp);
int		main(int ac, char **av, char **envp);

#endif
