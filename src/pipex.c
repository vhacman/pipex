/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:57:54 by vhacman           #+#    #+#             */
/*   Updated: 2025/03/23 18:35:54 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_first_command(char **av, char **envp, int *fd)
{
	int	infile;

	infile = open(av[1], O_RDONLY, 0777);
	if (infile == -1)
		error();
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error();
	if (dup2(infile, STDIN_FILENO) == -1)
		error();
	close(fd[0]);
	close(fd[1]);
	close(infile);
	execute(av[2], envp);
}

void	run_second_command(char **av, char **envp, int *fd)
{
	int	outfile;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
	{
		perror(av[4]);
		exit(1);
	}
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error();
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		perror(av[4]);
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	close(outfile);
	execute(av[3], envp);
}

void	pipex(char **av, char **envp)
{
	int		fd[2];
	int		status;
	int		exit_code;

	exit_code = 0;
	if (pipe(fd) == -1)
		error();
	if (fork() == 0)
		run_first_command(av, envp, fd);
	if (fork() == 0)
		run_second_command(av, envp, fd);
	close(fd[0]);
	close(fd[1]);
	while (wait(&status) > 0)
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
	exit(exit_code);
}
