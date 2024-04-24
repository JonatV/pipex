/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_delimiter_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:28:55 by jveirman          #+#    #+#             */
/*   Updated: 2024/04/24 13:26:00 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*ft_delimiter_hunter(int fd, char *ret, char *to_find)
{
	char	*buf;
	ssize_t	n_byt;
	char	*temp_text;

	buf = malloc(2 * sizeof(char));
	if (!buf)
		return (NULL);
	n_byt = 1;
	while (!ft_strnstr(ret, to_find, ft_strlen(to_find)) && (n_byt != 0))
	{
		n_byt = read(fd, buf, 1);
		if (n_byt == -1)
		{
			if (ret)
				free(ret);
			free(buf);
			return (NULL);
		}
		buf[n_byt] = '\0';
		temp_text = ret;
		ret = ft_strjoin(ret, buf);
		free(temp_text);
	}
	free(buf);
	return (ret);
}

char	*to_the_delimiter(char *to_find)
{
	int		fd;
	char	*text_stored;
	char	*text_trimmed;

	fd = STDIN_FILENO;
	text_stored = NULL;
	text_trimmed = NULL;
	if (!to_find || !to_find[0])
		return (NULL);
	text_stored = ft_delimiter_hunter(fd, text_stored, to_find);
	if (!text_stored)
		return (NULL);
	text_trimmed = ft_substr(text_stored, 0, \
	ft_strlen(text_stored) - ft_strlen(to_find));
	free(text_stored);
	if (text_trimmed[0])
		return (text_trimmed);
	else
		free(text_trimmed);
	return (NULL);
}
