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
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <sys/wait.h>


typedef enum {
	INFILE = 1,
	CMD1,
	CMD2,
	OUTFILE
}	ARGV_DATA;

typedef enum {
	READ = 0,
	WRITE
}	PIPE_DATA;

// ------------ UTILS
void	ft_free_array(char **array);

#endif

