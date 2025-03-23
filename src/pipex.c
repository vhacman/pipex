#include "pipex.h"

/*
** Executes the first command:
** - Opens the input file for reading.
** - Redirects STDIN to the input file.
** - Redirects STDOUT to the write end of the pipe.
** - Closes unused file descriptors and executes the first command.
*/
void	run_first_command(char **av, char **envp, int *fd)
{
	int	infile;

	infile = open(av[1], O_RDONLY, 0777);
	if (infile == -1)
		error("Failed to open input file");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error("dup2 failed on STDOUT");
	if (dup2(infile, STDIN_FILENO) == -1)
		error("dup2 failed on STDIN");
	close(fd[0]);
	close(infile);
	execute(av[2], envp);
}

/*
** Executes the second command:
** - Opens the output file for writing (creates/truncates).
** - Redirects STDIN to the read end of the pipe.
** - Redirects STDOUT to the output file.
** - Closes unused file descriptors and executes the second command.
*/
void	run_second_command(char **av, char **envp, int *fd)
{
	int	outfile;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		error("Failed to open output file");
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error("dup2 failed on STDIN");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		error("dup2 failed on STDOUT");
	close(fd[1]);
	close(outfile);
	execute(av[3], envp);
}

/*
** Core pipex function:
** - Creates a pipe.
** - Forks the first child to execute the first command.
** - Waits for it, then forks a second time for the second command.
** - Waits again and closes the pipe.
**
** This replicates shell behavior: `< infile cmd1 | cmd2 > outfile`
*/
void	pipex(char **av, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error("pipe failed");
	pid = fork();
	if (pid < 0)
		error("fork failed (first)");
	if (pid == 0)
		run_first_command(av, envp, fd);
	waitpid(pid, NULL, 0);
	pid = fork();
	if (pid < 0)
		error("fork failed (second)");
	if (pid == 0)
		run_second_command(av, envp, fd);
	waitpid(pid, NULL, 0);
	close(fd[0]);
	close(fd[1]);
}
