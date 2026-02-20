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
	int	i;

	i = 0;
	while (shell && shell->envp_cpy && shell->envp_cpy[i])
	{
		if (ft_strncmp(shell->envp_cpy[i], "PWD=", 4) == 0)
		{
			shell->envp_cpy[i] = ft_strdup("PWD=");
			shell->envp_cpy[i] = ft_strjoin(shell->envp_cpy[i], newpath);
			if (shell->envp_cpy[i] == NULL)
			{
				shell->exit_status = 12;
				ft_printf(STDERR_FILENO, "malloc: %s", strerror(errno));
			}
		}
		i++;
	}
}

void	ft_cd(t_shell *shell, char *data)
{
	char	newpath[PATH_MAX];

	if (chdir(data) == 0)
	{
		setenv("PWD", data, 1);
		getcwd(newpath, sizeof(newpath));
		shell->cwd = newpath;
		update_pwd(shell, newpath);
		shell->exit_status = 0;
	}
	else
	{
		ft_printf(STDERR_FILENO, "%s", strerror(errno));
		shell->exit_status = 1;
	}
}
