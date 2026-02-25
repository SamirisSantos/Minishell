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

void	update_pwd(t_shell *shell, char *newpath)
{
	char	*tmp;
	int		i;
	char	*tmp;
	int		i;

	i = 0;
	while (shell && shell->envp_cpy && shell->envp_cpy[i])
	{
		if (ft_strncmp(shell->envp_cpy[i], "PWD=", 4) == 0)
		{
			tmp = ft_strjoin("PWD=", newpath);
			if (!tmp)
			tmp = ft_strjoin("PWD=", newpath);
			if (!tmp)
			{
				shell->exit_status = 12;
				ft_printf(STDERR_FILENO, "minishell: malloc: %s", strerror(errno));
				return ;
			}
			free(shell->envp_cpy[i]);
			shell->envp_cpy[i] = tmp;
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
	if (!data || *data == '\0')
		data = get_env_value("HOME", shell->envp_cpy);
	if (!data)
	{
		ft_printf(STDERR_FILENO, "minishell: cd: HOME not set\n");
		shell->exit_status = 1;
		return ;
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
	if (chdir(data) != 0)
		return (cd_error(shell, data));
	getcwd(newpath, sizeof(newpath));
	if (shell->cwd)
		free(shell->cwd);
	shell->cwd = ft_strdup(newpath);
	update_pwd(shell, newpath);
	shell->exit_status = 0;
}
