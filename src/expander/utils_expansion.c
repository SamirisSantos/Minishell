/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:48:47 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/20 17:09:43 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*get_env_value(char *name, char **envp)
{
	int	len;
	int	i;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 
				&& envp[i][len] == '=')
				return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

static char	*get_var_value(char *str, t_shell *shell, int *var_len)
{
	char	*name;
	char	*value;

	if (str[i] == '?')
	{
		*var_len = 2;
		return(ft_itoa(shell->exit_status));
	}
	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i == 1)
	{
		*var_len = 1;
		return (ft_strdup("$"));
	}
	*var_len = i;
	name = ft_substr(str, 1, i - 1);
	value = get_env_value(name, shell->envp);
	free(name);

	if (!var_value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static void	process_var_len(char *str, t_shell *shell, int *len, int *i)
{
	int		var_name_len;
	char	*val;

	val = get_var_value(&str[*i], shell, var_name_len);
	if (val)
	{
		*total_len += ft_strlen(val);
		free(val);
	}
	*i += var_name_len;
}

int	get_expanded_len(char *str, t_shell *shell)
{
	int		i;
	int		len;
	char	quote;

	i = 0;
	len = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"')
			&& (quote == 0 || str[i] == quote))
			quote_flag(str[i++], &quote);
		else if (str[i] == '$' && quote != '\'')
			process_var_len(str, shell, &len, &i);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
static void	process_var_fill(char *new_str, char *old_str, int *i, int *j,t_shell *shell)
{
	int		var_len;
	char	*val;

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
