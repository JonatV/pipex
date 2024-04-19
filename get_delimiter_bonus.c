/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_delimiter_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:28:55 by jveirman          #+#    #+#             */
/*   Updated: 2024/04/19 17:04:14 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_delimiter_hunter(int fd, char *text_stored, char *to_find)
{
	char		*buf;
	ssize_t		nbr_bytes;

	buf = malloc((1 + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	nbr_bytes = 1;
	while (!ft_strnstr(text_stored, to_find, ft_strlen(to_find)) && nbr_bytes != 0)
	{
		nbr_bytes = read(fd, buf, 1);
		if (nbr_bytes == -1)
		{
			free(text_stored);
			free(buf);
			return (NULL);
		}
		buf[nbr_bytes] = '\0';
		text_stored = ft_strjoin(text_stored, buf);
	}
	free(buf);
	return (text_stored);
}

char	*to_the_delimiter(char *to_find)
{
	int			fd;
	char		*text_stored;
	char		*text_trimmed;

	fd = STDIN_FILENO;
	text_stored = NULL;
	text_trimmed = NULL;
	if (!to_find || !to_find[0])
		return (NULL);
	text_stored = ft_delimiter_hunter(fd, text_stored, to_find);
	if (!text_stored)
		return (NULL);
	text_trimmed = ft_substr(text_stored, 0, ft_strlen(text_stored) - ft_strlen(to_find));
	free(text_stored);
	if (text_trimmed[0])
		return (text_trimmed);
	else
		free(text_trimmed);
	return (NULL);
}
