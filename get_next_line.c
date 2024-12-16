/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:43:18 by ishaaq            #+#    #+#             */
/*   Updated: 2024/12/16 12:15:34 by ishaaq           ###   ########.fr       */
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
char	*cleanup(char *text, char *line)
{
	if (text[0] != '\0')
	{
		line = ft_substr(text, 0, countsubstr(text, 0, '\0'));
		free(text);
		text = NULL;
		return line;
	}
	free(text);
	text = NULL;
	return NULL;  
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
	newline_pos = ft_strchri(text, '\n', 0);
	while (newline_pos == -1)
	{
		num_read = read(fd, buffer, BUFFER_SIZE);
		if (num_read <= 0)
			break;
		buffer[num_read] = '\0';
		text = extend(text, buffer, num_read);
		newline_pos = ft_strchri(text, '\n', 0);
	}
	if (newline_pos  >= 0)
	{
		line = ft_substr(text, 0, countsubstr(text, 0, '\n') + 1);
		text = ft_truncate(text, newline_pos + 1);
		return (line);
	}
	// line = NULL;
	// return (cleanup(text, line));
	if (text[0] != '\0')
	{
		line = ft_substr(text, 0, countsubstr(text, 0, '\0'));
		free(text);
		text = NULL;
		return line;
	}
	free(text);
	text = NULL;
	return NULL; 
}

// int main(int ac, char *av[])
// {
// 	if (ac < 2)
// 	{
// 		printf("Usage: %s <filename>\n", av[0]);
// 		return (1);
// 	}

// 	int fd = open(av[1], O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}

// 	char *line;
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line); // Print the line (newlines are preserved)
// 		free(line);         // Free each line after use
// 	}
// 	// printf("%s", get_next_line(fd));
	
// 	// line = malloc(sizeof(char)* 12);
// 	// line = "hello world";
// 	// line[11] = '\0';
// 	// printf("%s\n", ft_truncate(line, 1));
	
// 	close(fd);
// 	return (0);
// }