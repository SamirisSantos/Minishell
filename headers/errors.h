/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:06:25 by cpinho-c          #+#    #+#             */
/*   Updated: 2025/10/29 16:45:28 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERROR_ARG "Error: too many arguments.\n"

# define ERROR_CDNODIR "cd: no_such_dir: No such file or directory\n"

# define ERROR_MALLOC "minishell: error: cannot allocate memory\n"

# define ERROR_FILE_PERMISSION "zsh: permission denied:"
# define ERROR_FILE_ACCESS "zsh: no such file or directory:"

//ctrl + c & ctrl + d exit status
# define EXIT_SIGINT 130
# define EXIT_SIGQUIT 131

#endif
