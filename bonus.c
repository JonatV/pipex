/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:51:32 by jveirman          #+#    #+#             */
/*   Updated: 2024/04/09 16:51:32 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute(char *full_cmd, char **envp)
{
	char	*valid_path;
	char	**cmd_splitted;

	cmd_splitted = ft_split(full_cmd, ' ');
	valid_path = find_valid_path(cmd_splitted[0], envp, 0);
	if (0 == valid_path)
	{
		ft_putstr_fd("Error : No such command exists in the system.\n", \
		STDERR_FILENO);
		ft_free_array(cmd_splitted);
		exit(EXIT_FAILURE);
	}
	execve(valid_path, cmd_splitted, envp);
	ft_putstr_fd("Error : Couldn't execute the command.\n", STDERR_FILENO);
	ft_free_array(cmd_splitted);
	if (valid_path)
		free(valid_path);
	exit(EXIT_FAILURE);
}

static void	pipe_n_fork(char *cmd, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (0 > pipe(pipe_fd))
		exit(EXIT_FAILURE);
	pid = fork();
	if (-1 == pid)
		exit(EXIT_FAILURE);
	if (pid)
	{
		close(pipe_fd[WRITE]);
		dup2(pipe_fd[READ], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
	if (0 == pid) // info - child process
	{
		close(pipe_fd[READ]);
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
		execute(cmd, envp);
	}
}

static void	read_user_input(char *delimiter)
{
	int		pipe_fd[2];
	pid_t	pid;
	char	*text_input;

	if (0 > pipe(pipe_fd))
		exit(EXIT_FAILURE);
	pid = fork();
	if (-1 == pid)
		exit(EXIT_FAILURE);
	if (pid)
	{
		close(pipe_fd[WRITE]);
		dup2(pipe_fd[READ], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
	if (0 == pid)
	{
		close(pipe_fd[READ]);
		text_input = to_the_delimiter(delimiter);
		ft_putstr_fd(text_input, pipe_fd[WRITE]);
		if (text_input != NULL)
			free(text_input);
		close(pipe_fd[WRITE]);
		exit(EXIT_SUCCESS); // info - Exit the child process
	}
}

static void	here_doc_management(int *i, char **argv, int argc, int *outfile)
{
	if (6 > argc)
	{
		ft_putstr_fd("Error : Bonus pipex's call must looks like \
		:./pipex here_doc LIMITER <cmd1> <cmd2> <more> <outfile>\n", \
		STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	i = 3;
	outfile = open_check(argv[argc - 1], 2);
	read_user_input(argv[2]);
}

int	main(int argc, char *argv[], char **envp)
{
	int	infile;
	int	outfile;
	int	i;

	if (argc < 5)
	{
		ft_putstr_fd("Error : Pipex's call must looks like :./pipex \
		<infile> <cmd1> <cmd2> <more> <outfile>\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (0 == ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc"))) // info - it means we're using here_doc then << and >>
		here_doc_management(&i, argv, argc, &outfile);
	else
	{
		i = 2;
		infile = open_check(argv[1], 0);
		outfile = open_check(argv[argc - 1], 1);
		dup2(infile, STDIN_FILENO);
	}
	dup2(outfile, STDOUT_FILENO);
	while (i < argc - 2)
		pipe_n_fork(argv[i++], envp);
	execute(argv[i], envp);
	return (EXIT_FAILURE);
}
