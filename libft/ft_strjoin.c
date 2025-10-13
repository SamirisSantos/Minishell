/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-31 17:59:48 by cpinho-c          #+#    #+#             */
/*   Updated: 2024-10-31 17:59:48 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	f_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	f_len = s1_len + s2_len;
	str = (char *)malloc(s1_len + s2_len + 1);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s1, s1_len);
	ft_memcpy(&str[s1_len], s2, s2_len);
	str[f_len] = '\0';
	return (str);
}
