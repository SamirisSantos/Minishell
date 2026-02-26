/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:53:39 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/21 22:21:37 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_update_envp(t_shell *shell, int i, char *arg)
{
	free(shell->envp_cpy[i]);
	shell->envp_cpy[i] = ft_strdup(arg);
	shell->exit_status = 0;
}

void	ft_add_var(t_shell *shell, char *arg)
{
	char	**new_envp;
	size_t	size;

	size = 0;
	while (shell->envp_cpy[size])
		size++;
	new_envp = ft_realloc_envp(shell, shell->envp_cpy, size);
	if (!new_envp)
	{
		shell->exit_status = 12;
		ft_printf(STDERR_FILENO, "malloc: %s", strerror(errno));
		return ;
	}
	new_envp[size] = ft_strdup(arg);
	new_envp[size + 1] = NULL;
	shell->envp_cpy = new_envp;
	shell->exit_status = 0;
}

bool	check_var_exists(t_shell *shell, char *cmd_arg, size_t size, int j)
{
	if (ft_strncmp(shell->envp_cpy[j], cmd_arg, size) == 0
		&& shell->envp_cpy[j][size] == '=')
		return (true);
	return (false);
}

static void	export_var(t_shell *shell, char **cmd_args, int i)
{
	int		j;
	size_t	size;
	bool	var_found;

	j = 0;
	var_found = false;
	size = ft_find_var_name(cmd_args[i]);
	while (shell->envp_cpy[j])
	{
		var_found = check_var_exists(shell, cmd_args[i], size, j);
		if (var_found)
		{
			ft_update_envp(shell, j, cmd_args[i]);
			break ;
		}
		j++;
	}
	if (!var_found)
		ft_add_var(shell, cmd_args[i]);
}

void	ft_export(t_shell *shell, char **cmd_args)
{
	int	i;

	if (!cmd_args || !cmd_args[1])
	{
		i = 0;
		ft_print_export(shell);
		shell->exit_status = 0;
		return ;
	}
	i = 1;
	while (cmd_args[i])
	{
		if (ft_strchr(cmd_args[i], '='))
			export_var(shell, cmd_args, i);
		i++;
	}
}
