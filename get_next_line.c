/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:43:18 by ishaaq            #+#    #+#             */
/*   Updated: 2024/12/16 11:13:30 by ishaaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchri(const char *s, int c, int start)
{
	int		i;

	i = start;
	while (s[i] != 0)
	{
		if (s[i] == c)
			return (i);
		i ++;
	}
	if (c == 0)
		return (-1);
	return (-1);
}
int	countsubstr(char *str, int start, int c)
{
	int	i;

	i = 0;
	while (str[start + i] != c && str[start + i] != '\0')
		i ++;
	return (i);
}
char	*extend(char *str, char *buffer, ssize_t num_read)
{
	char	*new_str;
	int		i;
	int		j;
	
	new_str = malloc(sizeof(char) * (ft_strlen(str) + num_read + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		new_str[i] = str[i];
		i ++;
	}
	j = 0;
	while (j < num_read)
	{
		new_str[i + j] = buffer[j];
		j ++;
	}
	new_str[i + j] = '\0';
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	ssize_t		num_read;
	static char	*text = NULL;
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	int			newline_pos;

	if (!text)
	{
		text = malloc(sizeof(char));
		if (!text)
			return (NULL);
		text[0] = '\0';
	}
	while ((newline_pos = ft_strchri(text, '\n', 0)) == -1)
	{
		num_read = read(fd, buffer, BUFFER_SIZE);
		if (num_read <= 0)
			break;
		buffer[num_read] = '\0';
		text = extend(text, buffer, num_read);
	}
	if ((newline_pos = ft_strchri(text, '\n', 0)) >= 0)
	{
		line = ft_substr(text, 0, countsubstr(text, 0, '\n') + 1);
		text = ft_truncate(text, newline_pos + 1);
		return (line);
	}
	if (text[0] != '\0')
	{
		line = ft_substr(text, 0, countsubstr(text, 0, '\0'));
		free(text);
		text = NULL;
		return line;
	}
	free(text);
	text = NULL;
	return NULL; // No more content to read
	// while ((num_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	// {
	// 	buffer[num_read] = '\0';
	// 	text = extend(text, buffer, num_read);
	// 	if (!text)
	// 	{
	// 		free(text);
	// 		return (NULL);
	// 	}
	// 	if ((newline_pos = ft_strchri(text, '\n', 0)) >= 0)
	// 	{
	// 		line = ft_substr(text, 0, countsubstr(text, 0, '\n') + 1);
	// 		text = ft_truncate(text, newline_pos + 1);
	// 		return (line);
	// 	}
	// }
	// if (text[0] != '\0') // Remaining content after EOF
	// {
	// 	line = ft_substr(text, 0, countsubstr(text, 0, '\0'));
	// 	free(text);
	// 	text = NULL;
	// 	retur