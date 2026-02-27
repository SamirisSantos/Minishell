/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:25:22 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/19 17:38:24 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	exec_cd(t_shell *shell, t_tree *tree)
{
	if (tree->cmd_args && tree->cmd_args[1] && tree->cmd_args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		shell->exit_status = 1;
	}
	else if (tree->cmd_args && tree->cmd_args[1])
		ft_cd(shell, tree->cmd_args[1]);
	else
		ft_cd(shell, NULL);
}

void	update_pwd(t_shell *shell, char *newpath)
{
	char	*tmp;
	int		i;

	i = 0;
	while (shell && shell->envp_cpy && shell->envp_cpy[i])
	{
		if (ft_strncmp(shell->envp_cpy[i], "PWD=", 4) == 0)
		{
			tmp = ft_strjoin("PWD=", newpath);
			if (!tmp)
			{
				shell->exit_status = 12;
				ft_printf(STDERR_FILENO, "malloc: %s", strerror(errno));
				return ;
			}
			free(shell->envp_cpy[i]);
			shell->envp_cpy[i] = tmp;
		}
		i++;
	}
}

static void	cd_error(t_shell *shell, char *data)
{
	ft_putstr_fd("minishell$ cd: ", STDERR_FILENO);
	ft_putstr_fd(data, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	shell->exit_status = 1;
}

void	ft_cd(t_shell *shell, char *data)
{
	char	newpath[PATH_MAX];

	if (!data || *data == '\0')
		data = get_env_value("HOME", shell->envp_cpy);
	if (!data)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		shell->exit_status = 1;
		return ;
	}
	if (chdir(data) != 0)
		return (cd_error(shell, data));
	getcwd(newpath, sizeof(newpath));
	if (shell->cwd)
		free(shell->cwd);
	shell->cwd = ft_strdup(newpath);
	update_pwd(shell, newpath);
	shell->exit_status = 0;
}
