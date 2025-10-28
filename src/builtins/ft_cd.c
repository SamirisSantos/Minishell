/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:25:22 by cpinho-c          #+#    #+#             */
/*   Updated: 2025/10/28 16:23:08 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_cd(t_shell *shell)
{
	char	newpath[PATH_MAX];

	newpath = NULL;
	if (chdir(path) == 0)
	{
		getcwd(newpath,sizeof(newpath));
		//update pwd Function
		shell->exit_status = 0;
	}
	else
	{
		ft_printf(STDERR_FILENO,"%s", ERROR_CDNODIR);
		shell->exit_status = 1;
	}
}