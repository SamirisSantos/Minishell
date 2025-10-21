/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-22 13:59:32 by cpinho-c          #+#    #+#             */
/*   Updated: 2024-10-22 13:59:32 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	cc;

	cc = (char) c;
	i = 0;
	if (!s && cc != '\0')
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == cc)
			return ((char *) s + i);
		i++;
	}
	if (cc == '\0')
		return ((char *) s + i);
	return (NULL);
}
