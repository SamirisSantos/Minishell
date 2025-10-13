/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-13 14:29:07 by cpinho-c          #+#    #+#             */
/*   Updated: 2024-12-13 14:29:07 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	size_t	f_len;
	size_t	i;
	size_t	j;

	f_len = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	str = (char *)malloc(f_len + 1);
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[f_len] = '\0';
	free(s1);
	return (str);
}
