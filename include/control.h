/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:00:24 by crepou            #+#    #+#             */
/*   Updated: 2023/06/17 20:47:14 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROL_H
# define CONTROL_H

# include <signal.h>
# include <termios.h>
#include <errno.h>

//possible struct 
//the first arg should be the command name
// envp[0]: path, envp[1]: NULL
typedef struct s_redirection
{
	char const	**args;
	char const	**envp;
	const char	*filename;
}			t_redirection;

void		cntr_handler(int signum);
void		clear_line(void);
char		*get_env_path(char **envp, char *command);
t_redirection	fill_redirection_struct(char *command, char *filename, char **args, char **envp);
void	block_signals(void);
void	slash_handler(int signum);
#endif