/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-09 14:12:35 by user              #+#    #+#             */
/*   Updated: 2024-11-09 14:12:35 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	check_all_words(char const *s, char c);
static char		*create_words(const char *s, char c, size_t *i);
static void		free_all(char **split_array, size_t total_words);

char	**ft_split(char const *s, char c)
{
	char	**split_array;
	size_t	total_words;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	total_words = check_all_words(s, c);
	split_array = (char **) malloc ((total_words + 1) * sizeof(char *));
	if (split_array == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (j < total_words)
	{
		split_array[j] = create_words(s, c, &i);
		if (split_array[j] == NULL)
		{
			free_all(split_array, j);
			return (NULL);
		}
		j++;
	}
	split_array[j] = NULL;
	return (split_array);
}

static size_t	check_all_words(char const *s, char c)
{
	size_t	i;
	size_t	total_words;

	i = 0;
	total_words = 0;
	if (s[0] != c && (s[0] >= 32 && s[0] <= 126))
	{
		total_words++;
		i++;
	}
	while (s[i])
	{
		if (s[i - 1] == c && s[i] != c && (s[i] >= 32 && s[i] <= 126))
			total_words++;
		i++;
	}
	return (total_words);
}

static char	*create_words(const char *s, char c, size_t *i)
{
	size_t	start;
	size_t	w_len;
	char	*word;

	w_len = 0;
	while (s[*i] && s[*i] == c)
		(*i)++;
	if (s[*i] >= 32 && s[*i] <= 126)
		start = *i;
	while (s[*i] && s[*i] != c)
	{
		if (s[*i] >= 32 && s[*i] <= 126)
			w_len++;
		(*i)++;
	}
	word = ft_substr(s, start, w_len);
	return (word);
}

static void	free_all(char	**split_array, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		free(split_array[i]);
		i++;
	}
	free(split_array);
}

// int	main(int ac, char **av)
// {
// 	char	**splited;
// 	int		i;

// 	i = 0;
// 	if (ac < 2 || ac > 2)
// 		return(0);
// 	splited = ft_split(av[1], ' ');
// 	while (splited[i])
// 	{
// 		ft_printf("%s\n", splited[i]);
// 		i++;
// 	}
// }