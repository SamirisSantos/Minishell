/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-23 10:05:29 by cpinho-c          #+#    #+#             */
/*   Updated: 2024-10-23 10:05:29 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	cvtd_c;

	cvtd_c = (char) c;
	i = 0;
	if (!s && cvtd_c != '\0')
		return (NULL);
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == cvtd_c)
			return ((char *) s + i);
		i--;
	}
	return (NULL);
}
