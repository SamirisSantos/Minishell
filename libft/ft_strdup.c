/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:50:45 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/25 11:44:45 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(s);
	dest = (char *)ft_calloc(s_len + 1, sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
