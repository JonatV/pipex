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
	char	 *valid_path;
	char	**cmd_splitted;

	cmd_splitted = ft_split(full_cmd, ' ');
	valid_path = find_valid_path(cmd_splitted[0], envp, 0);
	if (0 == valid_path)
	{
		ft_putstr_fd("Error : No such command exists in the system.\n", STDERR_FILENO);
		ft_free_array(cmd_splitted);
		exit(EXIT_FAILURE);
	}
	execve(valid_path, cmd_splitted, envp);
	ft_putstr_fd("Error : Couldn't execute the command.\n", STDERR_FILENO);	// From here if the code is taken in consideration
	ft_free_array(cmd_splitted);						// it means that the execve has failed, don't need to check for -1 return
	exit(EXIT_FAILURE);
}

static void	pipe_n_fork(char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if(0 > pipe(pipe_fd))
		exit(EXIT_FAILURE); // wip - send an error message if triggered
	pid = fork();
	if (-1 == pid)
		exit(EXIT_FAILURE); // wip - send an error message if triggered
	if (pid)
	{
		close(pipe_fd[WRITE]);
		dup2(pipe_fd[READ], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
	if (0 == pid) //child process
	{
		close(pipe_fd[READ]);
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
		execute(argv[CMD1], envp);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	int	infile;
	int	outfile;

	if(5 != argc)
	{
		ft_putstr_fd("Error : Pipex's call must looks like :./pipex <file1> <cmd1> <cmd2> <file2>\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	infile = open_check(argv[1], 0);
	outfile = open_check(argv[4], 1);
	dup2(infile, STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	pipe_n_fork(argv, envp); // this will create child and parent process will wait for child to finish execution
	execute(argv[CMD2], envp); // parent process execution (last)
	return (EXIT_FAILURE);
}
