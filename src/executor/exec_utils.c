/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:21:20 by cpinho-c          #+#    #+#             */
/*   Updated: 2025/11/19 15:32:05 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	count_cmds(t_tree *temp, int *cmd_count)
{
	if (!temp)
		return ;
	if (temp->type == CMD)
		(*cmd_count)++;
	count_cmds(temp->left, cmd_count);
	count_cmds(temp->right, cmd_count);
}

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_truepath(t_shell *shell, char *cmd, char *fullpath)
{
	char	**splitpath;
	char	*truepath;
	char	*temp;
	int		i;

	splitpath = ft_split(fullpath, ':');
	i = 0;
	while (splitpath[i] && (cmd && cmd[0] != '\0'))
	{
		truepath = ft_strjoin(splitpath[i], "/");
		temp = truepath;
		truepath = ft_strjoin(temp, cmd);
		free(temp);
		if (access(truepath, X_OK) == 0)
		{
			free_array(splitpath);
			return (truepath);
		}
		free(truepath);
		i++;
	}
	free_array(splitpath);
	return (NULL);
}

bool	is_builtin(t_tree *tree)
{
	if ((strncmp(tree->data, "cd", 2) && ft_strlen(tree->data) == 2) ||
		(strncmp(tree->data, "echo", 4) && ft_strlen(tree->data) == 4) ||
		(strncmp(tree->data, "env", 3) && ft_strlen(tree->data) == 3) ||
		(strncmp(tree->data, "exit", 4) && ft_strlen(tree->data) == 4) ||
		(strncmp(tree->data, "export", 6) && ft_strlen(tree->data) == 6) ||
		(strncmp(tree->data, "pwd", 3) && ft_strlen(tree->data) == 3) ||
		(strncmp(tree->data, "unset", 5) && ft_strlen(tree->data) == 5))
		return (true);
	else
		return (false);
}

char	*find_cmd_path(t_shell *shell, t_tree *tree)
{
	char	*cmd_path;

	if(is_builtin(tree))
		return (NULL);
	else
	{
		cmd_path = get_path(shell->envp_cpy);
		cmd_path = find_truepath(shell, tree->data, cmd_path);
		return (cmd_path);
	}
	return (NULL);
}
