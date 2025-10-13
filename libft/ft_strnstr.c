/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 10:51:47 by cpinho-c          #+#    #+#             */
/*   Updated: 2024-10-29 10:51:47 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	l_len;

	i = 0;
	if (*little == '\0')
		return ((char *) big);
	l_len = ft_strlen(little);
	while (i < len && big[i] != '\0')
	{
		if (l_len > len - i)
			return (NULL);
		if (ft_strncmp((char *)&big[i], little, l_len) == 0)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
