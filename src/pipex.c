/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:23:18 by vhacman           #+#    #+#             */
/*   Updated: 2025/03/24 10:23:18 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** First child process setup:
** - Opens infile (av[1]) in read-only mode.
** - Redirects STDOUT to the pipe's write end.
** - Redirects STDIN to the opened infile.
** - Closes unused file descriptors.
** - Executes av[2] using execve.
*/
void	run_first_command(char **av, char **envp, int *fd)
{
	int	infile;

	infile = open(av[1], O_RDONLY);
	if (infile == -1)
		error(av[1]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error("dup2 (stdout)");
	if (dup2(infile, STDIN_FILENO) == -1)
		error("dup2 (infile)");
	close(fd[0]);
	close(fd[1]);
	close(infile);
	execute(av[2], envp);
}

/*
** Second child process setup:
** - Opens/creates outfile (av[4]) in write mode (truncating if exists).
** - Redirects STDIN to the pipe's read end.
** - Redirects STDOUT to the outfile.
** - Closes unused file descriptors.
** - Executes av[3] using execve.
*/
void	run_second_command(char **av, char **envp, int *fd)
{
	int	outfile;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		if (errno == EACCES)
		{
			ft_putstr_fd("Permission denied: ", 2);
			ft_putstr_fd(av[4], 2);
			ft_putstr_fd("\n", 2);
			exit(126);
		}
		error(av[4]);
	}
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error("dup2 (stdin)");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		error("dup2 (outfile)");
	close(fd[0]);
	close(fd[1]);
	close(outfile);
	execute(av[3], envp);
}

/*
** Main process:
** - Creates a pipe.
** - Forks two child processes:
**   • first runs the first command with infile and writes to pipe
**   • second reads from pipe and writes to outfile
** - Closes pipe file descriptors in the parent.
** - Waits for children and exits with last command's exit status.
*/
void	pipex(char **av, char **envp)
{
	int		fd[2];
	int		status;
	int		exit_code;
	pid_t	pid1;
	pid_t	pid2;

	exit_code = 0;
	if (pipe(fd) == -1)
		error("error in pipe");
	pid1 = fork();
	if (pid1 == -1)
		error("fork error");
	if (pid1 == 0)
		run_first_command(av, envp, fd);
	pid2 = fork();
	if (pid2 == -1)
		error("fork error");
	if (pid2 == 0)
		run_second_command(av, envp, fd);
	close(fd[0]);
	close(fd[1]);
	while (wait(&status) > 0)
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
	exit(exit_code);
}
