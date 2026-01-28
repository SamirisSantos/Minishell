/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:48:47 by sade-ara          #+#    #+#             */
/*   Updated: 2026/01/27 17:39:44 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	process_var_len(char *str, t_shell *shell, int *len, int *i)
{
	int		var_name_len;
	char	*val;

	val = get_var_value(&str[*i], shell, &var_name_len);
	if (val)
	{
		*len += ft_strlen(val);
		free(val);
	}
	*i += var_name_len;
}

static void	process_var_fill(char *new_str, char *old_str, int *i, int *j, t_shell *shell)
{
	int		var_len;
	char	*val;
	int		k;

	val = get_var_value(&old_str[*i], shell, &var_len);
	if (val)
	{
		k = 0;
		while (val[k])
			new_str[(*j)++] = val[k++];
		free(val);
	}
	*i += var_len;
}

void	fill_expanded_str(char *new_str, char *old_str, t_shell *shell)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (old_str[i])
	{
		if ((old_str[i] == '\'' || old_str[i] == '"')
			&& (quote == 0 || old_str[i] == quote))
			quote_flag(old_str[i++], &quote);
		else if (old_str[i] == '$' && quote != '\'')
		{
			process_var_fill(new_str, old_str, &i, &j, shell);
		}
		else
			new_str[j++] = old_str[i++];
	}
	new_str[j] = '\0';
}
