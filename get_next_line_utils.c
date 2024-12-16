/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:47:42 by ishaaq            #+#    #+#             */
/*   Updated: 2024/12/15 08:08:13 by ishaaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i ++;
	return (i);
}
char	*ft_truncate(char *s, unsigned int start)
{
	unsigned int	i;
	unsigned int	len;
	char			*new_str;

	i = 0;
	len = ft_strlen(s);
	if (start >= len) // If start is beyond the string, return an empty string
	{
		free(s);
		new_str = malloc(sizeof(char));
		if (!new_str)
			return (NULL);
		new_str[0] = '\0';
		return (new_str);
	}
	new_str = malloc(sizeof(char) * (len - start + 1));
	if (!new_str)
		return (NULL);
	while (s[start + i] != 0)
	{
		new_str[i] = s[start + i];
		i ++;
	}
	new_str[i] = '\0';
	free(s);
	return (new_str);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	if (ft_strlen(s) <= start)
		len = 0;
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	i = 0;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (i < len && s[start + i] != '\0')
	{
		ptr[i] = s[start + i];
		i ++;
	}
	ptr[i] = '\0';
	return (ptr);
}