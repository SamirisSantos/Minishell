/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:15:13 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/19 14:11:25 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	count_args(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == CMD || token->type == CMD_ARG)
			count++;
		token = token->next;
	}
	return (count);
}

static void	fill_cmd(t_cmd *new, t_token **tk)
{
	int	i;

	i = 0;
	new->args = malloc(sizeof(char *) * (count_args(*tk) + 1));
	if (!new->args)
		return ;
	while (*tk && (*tk)->type != PIPE)
	{
		if ((*tk)->type == CMD || (*tk)->type == CMD_ARG)
		{
			new->args[i++] = ft_strdup((*tk)->data);
			*tk = (*tk)->next;
		}
		else if ((*tk)->type >= REDIR_IN && (*tk)->type <= HEREDOC)
		{
			*tk = handle_redirects(*tk, new);
		}
	}
	new->args[i] = NULL;
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current;
	t_cmd	*new;
	int		i;

	head = NULL;
	current = NULL;

	while (tokens)
	{
		new = init_cmd();
		if (!new)
		{
			free_cmd(new);
			return (NULL);
		}
		new->args = malloc(sizeof(char *) * (count_args(tokens) + 1));
		i = 0;
		while (tokens && tokens->type == PIPE)
		{
			while (tokens && tokens->type != PIPE)
			{
				if (tokens->type == CMD || tokens->type == CMD_ARG)
					new->args[i++] = ft_strdup(tokens->data);
				else if (tokens->type >= REDIR_IN && tokens->type <= HEREDOC)
					tokens = handle_redirects(tokens, new);
				tokens = tokens->next;
			}
		}
		new->args[i] = NULL;
		if (!head)
			head = new;
		else
			current->next = new;
		current = new;
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return (head);
}
