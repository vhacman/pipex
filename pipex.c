#include "../includes/pipex.h"

/* Child process that run inside a fork, take the filein, put the output inside
 a pipe and then close with the exec function */
void	child_process(char **argv, char **envp, int *fd)
{
	int		filein;

	filein = open(argv[1], O_RDONLY, 0777);
	if (filein == -1)
		error();
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	execute(argv[2], envp);
}

/* Parent process that take the data from the pipe, change the output for the
 fileout and also close with the exec function */
void	parent_process(char **argv, char **envp, int *fd)
{
	int		fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		error();
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	execute(argv[3], envp);
}

/* Main function that run the child and parent process or display an error
 message if arguments are wrong */
int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error();
		pid1 = fork();
		if (pid1 == -1)
			error();
		if (pid1 == 0)
			child_process(argv, envp, fd);
		waitpid(pid1, NULL, 0);
		parent_process(argv, envp, fd);
	}
	else
	{
		ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
	return (0);
}


#include "../includes/pipex.h"

/* Function that will look for the path line inside the environment, will
 split and test each command path and then return the right one. */
char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

/* A simple error displaying function. */
void	error(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

/* Function that take the command and send it to find_path
 before executing it. */
void	execute(char *argv, char **envp)
{
	char	**cmd;
	int 	i;
	char	*path;
	
	i = -1;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], envp);
	if (!path)	
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
		error();
}

/* Function that will read input from the terminal and return line. */
int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}
