/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:48:25 by vhacman           #+#    #+#             */
/*   Updated: 2025/03/23 18:48:25 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Sets up the first child process:
** - Opens the input file av[1] in read-only mode.
** - Redirects STDOUT to the pipe's write-end.
** - Redirects STDIN to the opened infile.
** - Closes unused file descriptors.
** - Executes the command in av[2].
*/
void	run_first_command(char **av, char **envp, int *fd)
{
	int	infile;

	infile = open(av[1], O_RDONLY); //apre file in modalità sola lettura. input del comando1
	if (infile == -1) //apertura fallisce: chiama error con il file per stampare errormsg
		error(av[1]);
	if (dup2(fd[1], STDOUT_FILENO) == -1) //duplica il lato scrittura della pipe sull STDOUT del processo.
		error("dup2 (stdout)");				//tutto quello che cmd1 stampa va sulla pipe
	if (dup2(infile, STDIN_FILENO) == -1) //redireziona lo standardInput del processo sul INFILE. ora 
		error("dup2 (infile)");				//cmd1 riceve input da INFILE
	close(fd[0]);
	close(fd[1]);
	close(infile);
	execute(av[2], envp); //esegue il comando, passando le variabili d'ambiente.
}

/*
** Sets up the second child process:
** - Opens or creates the output file av[4] with proper permissions.
** - Redirects STDIN to the pipe's read-end.
** - Redirects STDOUT to the opened outfile.
** - Closes unused file descriptors.
** - Executes the command in av[3].
*/
void	run_second_command(char **av, char **envp, int *fd)
{
	int	outfile;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644); //apre o crea il OUTFILE in modalità scrittura, e lo tronca se già esiste
	if (outfile == -1)
		error(av[4]);
	if (dup2(fd[0], STDIN_FILENO) == -1) //collega la lettura della pipe allo standard INPUT. ora cmd2 riceve come input l'output di cmd1
		error("dup2 (stdin)");
	if (dup2(outfile, STDOUT_FILENO) == -1)//l'output del comando cmd2 ridiretto su OUTFILE
		error("dup2 (outfile)");
	close(fd[0]);
	close(fd[1]);
	close(outfile);
	execute(av[3], envp);
}

/*
** Main pipex routine:
** - Creates a pipe for inter-process communication.
** - Forks the first and second children for cmd1 and cmd2.
** - Closes pipe in parent.
** - Waits for both children and returns the exit status of the last one.
*/
void	pipex(char **av, char **envp)
{
	int		fd[2]; //variabile dei file descriptor.
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
