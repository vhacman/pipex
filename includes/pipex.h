/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:50:39 by vhacman           #+#    #+#             */
/*   Updated: 2025/03/23 16:50:39 by vhacman          ###   ########.fr       */
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
void	error(const char *msg);
void	execute(char *cmd_input, char **envp);

// path_utils.c
char	**get_path_dirs(char **envp);
char	*find_cmd_in_dirs(char *cmd, char **dirs);
char	*get_cmd_path(char *cmd, char **envp);
char	**split_cmd_and_find(char *input, char **envp, char **cmd_path);

// pipex.c
void	run_first_command(char **av, char **envp, int *fd);
void	run_second_command(char **av, char **envp, int *fd);
void	pipex(char **av, char **envp);
int		main(int ac, char **av, char **envp);

#endif
