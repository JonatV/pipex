/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:51:39 by jveirman          #+#    #+#             */
/*   Updated: 2024/04/09 16:51:39 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_check(char *file_path, int option)
{
	int	fd;

	if (0 == option)
		fd = open(file_path, O_RDONLY, 0777);
	else if (1 == option)
		fd = open(file_path, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	else
		fd = open(file_path, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (-1 == fd)
	{
		ft_putstr_fd("Error : Open outfile/infile failed.\n", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	ft_free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i][0] != '\0')
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*find_valid_path(char *cmd, char **envp, int i)
{
	char	**all_paths;
	char	*temp_path;
	char	*full_path;

	while (ft_strnstr(envp[i], "PATH", 4) == 0) // find PATH:
		i++;
	all_paths = ft_split(envp[i] + 5, ':'); // go to PATH:here by skipping "PATH:"
	i = -1;
	while (all_paths[++i])
	{
		temp_path = ft_strjoin(all_paths[i], "/"); // path + '/'
		full_path = ft_strjoin(temp_path, cmd); // path/ + 'ls'
		temp_path = NULL;
		if (0 == access(full_path, F_OK | X_OK))
		{
			ft_free_array(all_paths);
			return (full_path);
		}
		free(full_path);
	}
	ft_free_array(all_paths);
	return (0);
}
