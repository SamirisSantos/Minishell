/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< Updated upstream
/*   By: cpinho-c <cpinho-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-05 14:35:10 by cpinho-c          #+#    #+#             */
/*   Updated: 2025-10-05 14:35:10 by cpinho-c         ###   ########.fr       */
=======
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:35:10 by cpinho-c          #+#    #+#             */
/*   Updated: 2025/10/28 17:25:32 by cpinho-c         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERROR_ARG "Error: too many arguments.\n"

# define ERROR_CDNODIR "cd: no_such_dir: No such file or directory\n"
# define ERROR_FILE_PERMISSION "zsh: permission denied:"
# define ERROR_FILE_ACCESS "zsh: no such file or directory:"

//ctrl + c & ctrl + d exit status
# define EXIT_SIGINT 130
# define EXIT_SIGQUIT 131

#endif
