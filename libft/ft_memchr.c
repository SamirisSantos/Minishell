/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-23 14:04:44 by cpinho-c          #+#    #+#             */
/*   Updated: 2024-10-23 14:04:44 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	cc;
	char	*str;

	i = 0;
	cc = (char) c;
	str = (char *) s;
	while (i < n)
	{
		if (str[i] == cc)
			return ((char *) str + i);
		i++;
	}
	return (NULL);
}
