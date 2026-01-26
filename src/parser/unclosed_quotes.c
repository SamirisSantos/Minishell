/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:09:59 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/19 14:38:59 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	quote_flag(char c, char *quote_char)
{
	if (*quote_char == 0 && (c == '\'' || c == '"'))
		*quote_char = c;
	else if (*quote_char != 0 && c == *quote_char)
			*quote_char = 0;
}

int	unclosed_quotes(char *input)
{
	char	quote_char;
	t_shell	*shell;

	quote_char = 0;
	while(*input)
	{
		quote_flag(*input, &quote_char);
		input++;
	}
	if (quote_char != 0)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
		ft_putchar_fd(quote_char, 2);
		ft_putstr_fd("'\n", 2);
		ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
		return (1); // ERRO
	}
	return (0)
}
