/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:51:36 by jveirman          #+#    #+#             */
/*   Updated: 2024/04/09 16:51:36 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <sys/wait.h>

enum e_ARGV_DATA
{
	INFILE = 1,
	CMD1,
	CMD2,
	OUTFILE
};

enum e_PIPE_DATA
{
	READ = 0,
	WRITE
};

// ------------ UTILS
int		open_check(char *file_path, int option);
void	ft_free_array(char **array);
char	*find_valid_path(char *cmd, char **envp, int i);

#endif
