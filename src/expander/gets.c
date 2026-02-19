/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:34:32 by sade-ara          #+#    #+#             */
/*   Updated: 2026/01/27 17:37:31 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*get_env_value(char *name, char **envp)
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

char	*get_var_value(char *str, t_shell *shell, int *var_len)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	if (str[i] == '$' && str[i + 1] == '?')
	{
		*var_len = 2;
		return (ft_itoa(shell->exit_status));
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
	value = get_env_value(name, shell->envp_cpy);
	free(name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
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
