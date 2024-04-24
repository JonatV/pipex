/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:23:39 by jveirman          #+#    #+#             */
/*   Updated: 2024/04/24 13:23:39 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <sys/wait.h>

enum e_PIPE_DATA
{
	READ = 0,
	WRITE
};

// ------------ BONUS
char	*to_the_delimiter(char *to_find);

// ------------ UTILS
int		open_check(char *file_path, int option);
void	ft_free_array(char **array);
char	*find_valid_path(char *cmd, char **envp, int i);

#endif
