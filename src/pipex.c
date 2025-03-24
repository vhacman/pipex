/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 08:00:23 by vhacman           #+#    #+#             */
/*   Updated: 2025/03/24 10:23:18 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** run_first_command:
** Executes the first command of the pipeline.
** Opens the input file (av[1]) in read-only mode.
** Redirects STDIN to the input file and STDOUT to the write end of the pipe.
** Closes unused file descriptors and launches the command via execve.
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
** run_second_command:
** Executes the second command of the pipeline.
** Opens the output file (av[4]) in write mode (truncated or created).
** Redirects STDIN to the read end of the pipe and STDOUT to the output file.
** Closes unused file descriptors and launches the command via execve.
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
** pipex:
** Core function of the program.
** Creates a pipe and forks two child processes:
** - The first reads from the input file and writes to the pipe.
** - The second reads from the pipe and writes to the output file.
** The parent closes both ends of the pipe and waits for both children.
** The program exits with the exit code of the last executed command.
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
