/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:48:47 by sade-ara          #+#    #+#             */
/*   Updated: 2026/03/02 12:25:29 by sade-ara         ###   ########.fr       */
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

static void	append_value(char *new_str, char *val, int *j)
{
	int	k;

	if (!val)
		return ;
	k = 0;
	while (val[k])
	{
		new_str[*j] = val[k];
		(*j)++;
		k++;
	}
}

void	fill_expanded_str(char *new_str, char *old_str, t_shell *shell)
{
	int		i;
	int		j;
	int		var_len;
	char	*val;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (old_str[i])
	{
		if ((old_str[i] == '\'' || old_str[i] == '\"')
			&& (quote == 0 || old_str[i] == quote))
			quote_flag(old_str[i++], &quote);
		else if (old_str[i] == '$' && quote != '\'')
		{
			val = get_var_value(&old_str[i], shell, &var_len);
			append_value(new_str, val, &j);
			free(val);
			i += var_len;
		}
		else
			new_str[j++] = old_str[i++];
	}
	new_str[j] = '\0';
}

char	*expand_string(char *str, t_shell *shell)
{
	char	*new_str;
	int		final_len;

	if (!str)
		return (NULL);
	final_len = get_expanded_len(str, shell);
	new_str = (char *)ft_calloc((final_len + 1), sizeof(char));
	if (!new_str)
	{
		shell->exit_status = 12;
		ft_printf(STDERR_FILENO, "minishell: malloc: %s", strerror(errno));
		return (NULL);
	}
	fill_expanded_str(new_str, str, shell);
	return (new_str);
}
